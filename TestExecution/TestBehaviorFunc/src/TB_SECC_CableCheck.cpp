#include "TB_SECC_CableCheck.h"
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
using namespace DataStructure_HAL_61851;

TestBehavior_SECC_CableCheck::TestBehavior_SECC_CableCheck(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_CableCheck::~TestBehavior_SECC_CableCheck()
{
}
void md_CMN_DC_EVStatus_001(DC_EVStatusType &eVStatus, bool p_eVReady, DC_EVErrorCodeType p_eVErrorCode, int8_t p_eVRESSSOC);
void md_CMN_DC_CableCheckRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, iso1Part4_EVSEProcessingType p_EVSEProcessing);

verdict_val TestBehavior_SECC_CableCheck::f_SECC_DC_TB_VTB_CableCheck_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  IEC_61851_States v_state;
  bool ongoingProcess = false;
  bool v_receivedOngoing = true;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CableCheckReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CableCheckRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<CableCheckRes>();

  if (PIXIT_SECC_DC_CableCheckOngoing == iso1Part4_Ongoing::ongoing)
  {
    v_receivedOngoing = false;
  }
  // set state C before send cable check message
  v_state = PICS_SECC_CMN_EvStateInChargeProgress;
  f_SECC_changeValidStateCondition(v_state);
  f_SECC_setState(this->systemSECC, v_state, v_HAL_61851_Listener);
  PAsleep(par_CMN_waitForNextHAL);
  md_CMN_DC_EVStatus_001(this->mtc->vc_DC_EVStatus, true, (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::nO_ERROR, par_EVRESSSOC);

  std::static_pointer_cast<CableCheckReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<CableCheckReq>(sendMsg)->setDCEVStatus(&this->mtc->vc_DC_EVStatus);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<CableCheckRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_CableCheckRes_001(expectedMsg, iso1Part4_ResponseCodeType::oK, iso1Part4_EVSEProcessingType::finished);
  md_CMN_DC_CableCheckRes_001(expectedMsg2, iso1Part4_ResponseCodeType::oK, iso1Part4_EVSEProcessingType::ongoing);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &ongoingProcess, &v_receivedOngoing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<CableCheckRes> cast_expected = std::dynamic_pointer_cast<CableCheckRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<CableCheckRes> cast_expected2 = std::dynamic_pointer_cast<CableCheckRes>(expected[1]);
    std::shared_ptr<CableCheckRes> cast_received = std::make_shared<CableCheckRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto DCEVSEStatus = cast_received->getDCEVSEStatus();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          ongoingProcess = false;
          if (1 == DCEVSEStatus->EVSEIsolationStatus_isUsed)
          {
            if (DCEVSEStatus->EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::valid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'valid'.");
            }
          }
          if (DCEVSEStatus->EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_Ready)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_Ready'.");
          }
          if (DCEVSEStatus->EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          this->mtc->setverdict(pass, "CableCheckRes message was correct.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          // response code = ongoing
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          v_receivedOngoing = true;
          if (1 == DCEVSEStatus->EVSEIsolationStatus_isUsed)
          {
            // should be invalid since cable check is not completed yet
            if (DCEVSEStatus->EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::invalid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'invalid'.");
            }
          }
          if (DCEVSEStatus->EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_IsolationMonitoringActive)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_IsolationMonitoringActive'.");
          }
          if (DCEVSEStatus->EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          if (ongoingProcess == false)
          {
            ongoingProcess = true;
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
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

  this->mtc->tc_V2G_EVCC_CableCheck_Timer->start(par_V2G_EVCC_CableCheck_Timeout);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CableCheckReq);
  while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
      {
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
      {
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
      {
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received CableCheckRes message, but with invalid data content."))
      {
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
        break;
      }
      if (this->cmn->a_SECC_Timeout(v_vct))
      {
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
        break;
      }
      if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
      {
        this->mtc->setverdict(v_vct, "Ongoing_Timer was triggered. CableCheckRes wasn't successful.");
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_CableCheck_Timer->stop();
        break;
      }
      if (this->mtc->tc_V2G_EVCC_CableCheck_Timer->timeout())
      {
        this->mtc->setverdict(v_vct, "CableCheck_Timer was triggered. CableCheckRes wasn't successful.");
        v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        break;
      }
    }
    if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 0.1s wait ongoing cable check"));
      PAsleep(0.1);
    }
  }
  if ((PIXIT_SECC_DC_CableCheckOngoing == iso1Part4_Ongoing::ongoing) && (!v_receivedOngoing))
  {
    this->mtc->setverdict(inconc, "The SUT did not repeat the CableCheck message sequence.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CableCheck::f_SECC_DC_TB_VTB_CableCheck_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  IEC_61851_States v_state;
  // set state
  v_state = PICS_SECC_CMN_EvStateInChargeProgress;
  f_SECC_changeValidStateCondition(v_state);
  f_SECC_setState(this->systemSECC, v_state, v_HAL_61851_Listener);
  PAsleep(par_CMN_waitForNextHAL);
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();
  std::static_pointer_cast<ServiceDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SequenceError);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pChargeService_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pServiceList_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pPaymentOptionList_flag = omit;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

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

  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CableCheckReq);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CableCheckRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_CableCheck::f_SECC_DC_TB_VTB_CableCheck_003(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  IEC_61851_States v_state;
  // set state
  v_state = PICS_SECC_CMN_EvStateInChargeProgress;
  f_SECC_changeValidStateCondition(v_state);
  f_SECC_setState(this->systemSECC, v_state, v_HAL_61851_Listener);
  PAsleep(par_CMN_waitForNextHAL);
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);
  md_CMN_DC_EVStatus_001(this->mtc->vc_DC_EVStatus, true, (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::nO_ERROR, par_EVRESSSOC);

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CableCheckReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CableCheckRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<CableCheckReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<CableCheckReq>(sendMsg)->setDCEVStatus(&this->mtc->vc_DC_EVStatus);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->mResponseCode_flag = specific;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<CableCheckRes> cast_expected = std::dynamic_pointer_cast<CableCheckRes>(expected);
    std::shared_ptr<CableCheckRes> cast_received = std::make_shared<CableCheckRes>();
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
          this->mtc->setverdict(pass, "CableCheckRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CableCheckReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CableCheckRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_CableCheck::f_SECC_DC_TB_VTB_CableCheck_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
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
  //deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);
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

verdict_val TestBehavior_SECC_CableCheck::f_SECC_DC_TB_VTB_CableCheck_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CableCheckReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CableCheckRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  // set state
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);
  md_CMN_DC_EVStatus_001(this->mtc->vc_DC_EVStatus, true, (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::nO_ERROR, par_EVRESSSOC);

  std::static_pointer_cast<CableCheckReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<CableCheckReq>(sendMsg)->setDCEVStatus(&this->mtc->vc_DC_EVStatus);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED);
  std::static_pointer_cast<CableCheckRes>(expectedMsg)->mResponseCode_flag = specific;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<CableCheckRes> cast_expected = std::dynamic_pointer_cast<CableCheckRes>(expected);
    std::shared_ptr<CableCheckRes> cast_received = std::make_shared<CableCheckRes>();
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
          this->mtc->setverdict(pass, "CableCheckRes with responseCode 'fAILED' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CableCheckReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CableCheckRes message, but with invalid data content."))
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

void md_CMN_DC_EVStatus_001(DC_EVStatusType &eVStatus, bool p_eVReady, DC_EVErrorCodeType p_eVErrorCode, int8_t p_eVRESSSOC)
{
  eVStatus.EVReady = (int)p_eVReady;
  eVStatus.EVErrorCode = p_eVErrorCode;
  eVStatus.EVRESSSOC = p_eVRESSSOC;
}

void md_CMN_DC_CableCheckRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, iso1Part4_EVSEProcessingType p_EVSEProcessing)
{
  std::static_pointer_cast<CableCheckRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<CableCheckRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<CableCheckRes>(msg)->setEVSEProcessing((EVSEProcessingType)p_EVSEProcessing);
  std::static_pointer_cast<CableCheckRes>(msg)->mEVSEProcessing_flag = specific;
  std::static_pointer_cast<CableCheckRes>(msg)->pDC_EVSEStatus_flag = has_value;
}