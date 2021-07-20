#include "TB_SECC_SessionStop.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TimerCfg.h"
#include "PIXITCfg.h"
#include "PICSCfg.h"
#include "V2gALMsg.h"
#include "TB_SECC_Msg.h"
#include "TestSystemLogging.h"

using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Timer_15118::Timer_par_15118;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace DataStructure_PIXIT_15118_2;
using namespace urn_iso_15118_2_2013_MsgDataTypes;
using namespace DataStructure_PICS_15118;

TestBehavior_SECC_SessionStop::TestBehavior_SECC_SessionStop(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_SessionStop::~TestBehavior_SECC_SessionStop()
{
}

verdict_val TestBehavior_SECC_SessionStop::f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType chargingSession,
                                                                             std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isClosed = false;
  bool vc_isShutdownOSC;
  iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE ackType = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_unkownCommand;
  iso1Part4_ChargingSessionType chargingSessionTerminate = iso1Part4_ChargingSessionType::terminate;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  sendCmd->TcpControlReq = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq>();
  sendCmd->TcpControlReq->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
  sendCmd->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
  sendCmd->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionStopReq>();
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setChargingSession((chargingSessionType)chargingSession);
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionStopRes>();
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->mResponseCode_flag = specific;

  // V2G_TCP_TLS_Port_Control_Internal_MessageRes v_internalResponseMessage;
  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionStopRes> cast_expected = std::dynamic_pointer_cast<SessionStopRes>(expected);
    std::shared_ptr<SessionStopRes> cast_received = std::make_shared<SessionStopRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  auto event_handler = [this, &isClosed, &ackType](std::shared_ptr<BaseOperation> &expect, std::shared_ptr<BaseOperation> &event) -> bool
  {
    bool result = false;
    if ((expect->TcpControlRes != nullptr) && (event->TcpControlRes != nullptr))
    {
      if ((expect->TcpControlRes->command == event->TcpControlRes->command))
      {
        isClosed = event->TcpControlRes->result.portStatus.closed;
        ackType = event->TcpControlRes->ack;
        result = true;
      }
      else
      {
        result = false;
      }
    }
    else
    {
      result = false;
    }
    return result;
  };

  if (chargingSession == chargingSessionTerminate)
  {
    v_HAL_61851_Listener->stop();
    // v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false));
    f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
    f_SECC_changeValidDutyCycleRange(this->systemSECC, 0, 0);
    f_SECC_changeValidStateCondition(E);
    // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  }
  else
  {
    f_SECC_setIsConfirmationFlagDC();
    f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
    f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
    // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  }
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionStopReq);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      while (true)
      {
        if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
        {
          vc_isShutdownOSC = true;
        }
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(sendCmd, event_handler))
        {
          break;
        }
      }
      if (isClosed && (ackType == iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success))
      {
        this->mtc->vc_isTcpPortClosed = isClosed;
        this->mtc->setverdict(pass, "SessionStopRes message was correct.");
      }
      else
      {
        this->mtc->setverdict(v_vct, "TCP socket could not be closed.");
      }
      if (PICS_CMN_CMN_CombinedTesting)
      {
        map(this->mtc->pt_SLAC_Port, this->systemSECC->pt_SLAC_Port);
        // f_SECC_getPLCLinkTermination(par_TP_match_leave + par_CMN_Transmission_Delay, v_vct);
        unmap(this->mtc->pt_SLAC_Port, this->systemSECC->pt_SLAC_Port);
      }
      if ((!vc_isShutdownOSC) && (!(chargingSession == chargingSessionTerminate)))
      {
        if (this->mtc->getverdict() == pass)
        {
          this->mtc->setverdict(v_vct, "The SUT did asleep its low-layer communication module, but the control pilot oscillator was still on.");
          v_HAL_61851_Listener->stop();
          // v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false));
        }
        if (PICS_CMN_CMN_WakeUp < par_SECC_T_step_X1)
        {
          // tc_T_step_X1.start(par_SECC_T_step_X1);
        }
      }
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received SessionStopRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionStop::f_SECC_CMN_TB_VTB_SessionStop_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();

  std::static_pointer_cast<ServiceDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SequenceError);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pChargeService_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pServiceList_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pPaymentOptionList_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServiceDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ServiceDiscoveryRes>(expected);
    std::shared_ptr<ServiceDiscoveryRes> cast_received = std::make_shared<ServiceDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "ServiceDiscoveryRes with responseCode 'fAILED_SequenceError' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionStopReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
        {
          if (isShutdownOSC == false)
          {
            Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
          }
          this->mtc->pt_HAL_61851_Internal_Port->clear();
          break;
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
        {
          break;
        }
        if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
        {
          break;
        }
      }
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SessionStopRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionStop::f_SECC_CMN_TB_VTB_SessionStop_003(iso1Part4_ChargingSessionType chargingSession)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionStopReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionStopRes>();
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setChargingSession((chargingSessionType)chargingSession);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->mResponseCode_flag = specific;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionStopRes> cast_expected = std::dynamic_pointer_cast<SessionStopRes>(expected);
    std::shared_ptr<SessionStopRes> cast_received = std::make_shared<SessionStopRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "SessionStopRes with responseCode 'fAILED_UnknownSession' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionStopReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
        {
          if (isShutdownOSC == false)
          {
            Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
          }
          this->mtc->pt_HAL_61851_Internal_Port->clear();
          break;
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
        {
          break;
        }
        if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
        {
          break;
        }
      }
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SessionStopRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionStop::f_SECC_CMN_TB_VTB_SessionStop_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  // Wait until sequence timeout in SUT should expire
  t_wait->start(par_V2G_SECC_Sequence_Timeout - par_CMN_Transmission_Delay);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
  while (true)
  {
    if (t_wait->timeout())
    {
      break;
    }
  }
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
    {
      if (isShutdownOSC == false)
      {
        Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
      }
      this->mtc->pt_HAL_61851_Internal_Port->clear();
      break;
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
    {
      break;
    }
    if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionStop::f_SECC_CMN_TB_VTB_SessionStop_005(iso1Part4_ChargingSessionType chargingSession)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionStopReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionStopRes>();
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionStopReq>(sendMsg)->setChargingSession((chargingSessionType)chargingSession);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED);
  std::static_pointer_cast<SessionStopRes>(expectedMsg)->mResponseCode_flag = specific;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionStopRes> cast_expected = std::dynamic_pointer_cast<SessionStopRes>(expected);
    std::shared_ptr<SessionStopRes> cast_received = std::make_shared<SessionStopRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "SessionStopRes with responseCode 'fAILED' is successful. SUT could not measuring state B before.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionStopReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
        {
          if (isShutdownOSC == false)
          {
            Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
          }
          this->mtc->pt_HAL_61851_Internal_Port->clear();
          break;
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
        {
          break;
        }
        if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
        {
          break;
        }
      }
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SessionStopRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}