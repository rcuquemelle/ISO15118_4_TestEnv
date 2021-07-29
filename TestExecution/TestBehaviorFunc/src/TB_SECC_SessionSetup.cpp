#include "TB_SECC_SessionSetup.h"
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

TestBehavior_SECC_SessionSetup::TestBehavior_SECC_SessionSetup(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_SessionSetup::~TestBehavior_SECC_SessionSetup()
{
}

static uint64_t oct2int(std::vector<uint8_t> sessionID)
{
  uint64_t result = 0;
  for (size_t i = 0; i < sessionID.size(); i++)
  {
    result |= (uint64_t)sessionID[i] << (8 * i);
  }
  return result;
}
static bool f_is_SessionID_not_zero(iso1Part4_SessionIDType &sessionID)
{
  if (oct2int(sessionID) == 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionSetupReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionSetupRes>();
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setEVCCID(this->mtc->vc_eVCCID);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK_NewSessionEstablished);
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mEVSEID_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mTimeStamp_flag = omit;

  auto receive_handler = [this, &v_vct](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionSetupRes> cast_expected = std::dynamic_pointer_cast<SessionSetupRes>(expected);
    std::shared_ptr<SessionSetupRes> cast_received = std::make_shared<SessionSetupRes>();
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
          this->mtc->vc_SessionID = cast_received->getSessionId();
          this->mtc->vc_EvseId = cast_received->getEVSEID();
          auto sessionid = f_outHexString(this->mtc->vc_SessionID);
          Logging::info(LogTbFnc_ENABLE, fmt::format("Session ID: {0}", sessionid));
          Logging::info(LogTbFnc_ENABLE, fmt::format("EVSE ID: {0}", this->mtc->vc_EvseId));
          // EVSETimeStamp: 1608971686
          // iso1responseCodeType_OK
          // iso1faultCodeType_ParsingError(default notification status of header)
          if (this->mtc->vc_EvseId != cc_EvseId_NotSup)
          {
            bool result = fx_validateEVSEID(this->mtc->vc_EvseId, "ISO");
            if (!result)
            {
              this->mtc->setverdict(v_vct, "Invalid EVSEID syntax was detected.");
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            if (!f_is_SessionID_not_zero(this->mtc->vc_SessionID))
            {
              this->mtc->setverdict(v_vct, "Invalid SessionID was detected.");
            }
            else
            {
              this->mtc->setverdict(pass, "SessionSetup message was correct.");
            }
          }
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received SessionSetupRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();
  // not provide EVCCID value
  std::static_pointer_cast<ServiceDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SequenceError);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pChargeService_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pServiceList_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pPaymentOptionList_flag = omit;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);

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

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
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
        // dequeue event queue and check tcp port status
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
        {
          if (isShutdownOSC == false)
          {
            Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the "
                                            "TCP connection was terminated.");
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SessionSetupRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);
  // Wait until sequence timeout in SUT should expire
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
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
        Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the "
                                        "TCP connection was terminated.");
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

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // Wait until V2G_SECC_CommunicationSetup timeout in SUT should expire
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
  while (true)
  {
    if (this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->timeout())
    {
      break;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive())
    {
      this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->stop();
      this->mtc->setverdict(fail, "No V2G message was expected.");
      break;
    }
  }
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
        Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the "
                                        "TCP connection was terminated.");
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

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_005(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionSetupReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionSetupRes>();
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setEVCCID(this->mtc->vc_eVCCID);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK_OldSessionJoined);
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mEVSEID_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mTimeStamp_flag = omit;

  auto receive_handler = [this, &v_vct](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionSetupRes> cast_expected = std::dynamic_pointer_cast<SessionSetupRes>(expected);
    std::shared_ptr<SessionSetupRes> cast_received = std::make_shared<SessionSetupRes>();
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
          this->mtc->vc_EvseId = cast_received->getEVSEID();
          Logging::info(LogTbFnc_ENABLE, fmt::format("EVSE ID: {0}", this->mtc->vc_EvseId);
          if (this->mtc->vc_EvseId != cc_EvseId_NotSup)
          {
            bool result = fx_validateEVSEID(this->mtc->vc_EvseId, "ISO");
            if (!result)
            {
              this->mtc->setverdict(v_vct, "Invalid EVSEID syntax was detected.");
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "SessionSetupRes message with responseCode 'oK_OldSessionJoined' was correct after paused session.");
          }
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received SessionSetupRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SessionSetup::f_SECC_CMN_TB_VTB_SessionSetup_006(bool v_isZero)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  iso1Part4_SessionIDType v_SessionID_old;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionSetupReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionSetupRes>();
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setEVCCID(this->mtc->vc_eVCCID);

  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK_NewSessionEstablished);
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mResponseCode_flag = specific;

  v_SessionID_old = this->mtc->vc_SessionID;
  if (v_isZero)
  {
    this->mtc->vc_SessionID = {0, 0, 0, 0, 0, 0, 0, 0};
  }
  else
  {
    this->mtc->vc_SessionID = f_rnd_SessionID(1, 429496);
  }
  auto receive_handler = [this, &v_SessionID_old](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionSetupRes> cast_expected = std::dynamic_pointer_cast<SessionSetupRes>(expected);
    std::shared_ptr<SessionSetupRes> cast_received = std::make_shared<SessionSetupRes>();
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
          this->mtc->vc_EvseId = cast_received->getEVSEID();
          this->mtc->vc_SessionID = cast_received->getSessionId();
          Logging::info(LogTbFnc_ENABLE, fmt::format("Session ID: {0}", f_outHexString(this->mtc->vc_SessionID)));
          Logging::info(LogTbFnc_ENABLE, fmt::format("EVSE ID: {0}", f_outHexString(this->mtc->vc_EvseId)));
          if (this->mtc->vc_EvseId != cc_EvseId_NotSup)
          {
            bool result = fx_validateEVSEID(this->mtc->vc_EvseId, "ISO");
            if (!result)
            {
              this->mtc->setverdict(fail, "Invalid EVSEID syntax was detected.");
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            if (f_is_SessionID_not_zero(this->mtc->vc_SessionID) && (this->mtc->vc_SessionID != v_SessionID_old))
            {
              this->mtc->setverdict(pass, "SessionSetupRes message with responseCode "
                                          "'oK_NewSessionEstablished' was correct "
                                          "after paused session.");
            }
            else
            {
              this->mtc->setverdict(fail, "The received SessionID is not unequal "
                                          "to '0' and not unequal to the SessionID value "
                                          "stored from the preceding V2G Communication "
                                          "Session.");
            }
          }
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SessionSetupRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}