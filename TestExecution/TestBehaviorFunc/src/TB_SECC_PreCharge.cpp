#include "TB_SECC_PreCharge.h"
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
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;
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

TestBehavior_SECC_PreCharge::TestBehavior_SECC_PreCharge(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_PreCharge::~TestBehavior_SECC_PreCharge()
{
}

void md_CMN_DC_PreChargeRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode);
void md_CMN_DC_PreChargeReq_001(std::shared_ptr<V2gTpMessage> &msg, DC_EVStatusType &p_dC_EVStatus, PhysicalValueType &p_eVTargetVoltage, PhysicalValueType &p_eVTargetCurrent);

verdict_val TestBehavior_SECC_PreCharge::f_SECC_DC_TB_VTB_PreCharge_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PreChargeReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PreChargeRes>();
  std::static_pointer_cast<PreChargeReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PreChargeRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  this->mtc->vc_EVSEPresentVoltage = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::v, .Value = 0};
  // current ev batteryVoltage level
  memcpy(&this->mtc->vc_EVTargetVoltage, &par_EVBatteryVoltage, sizeof(PhysicalValueType));
  Logging::info(LogTbFnc_ENABLE, fmt::format("this->mtc->vc_EVTargetVoltage: {}", f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVTargetVoltage)));
  // deviation level
  float v_deviation = (f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVTargetVoltage) / 100.0) * par_ValidDeviationPerCent;
  float v_EVTargetVoltageValidMaxDeviation = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVTargetVoltage) + v_deviation;
  float v_EVTargetVoltageValidMinDeviation = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVTargetVoltage) - v_deviation;

  md_CMN_DC_PreChargeReq_001(sendMsg, this->mtc->vc_DC_EVStatus, this->mtc->vc_EVTargetVoltage, this->mtc->vc_EVPreChargeTargetCurrent);
  md_CMN_DC_PreChargeRes_001(expectedMsg, iso1Part4_ResponseCodeType::oK);

  auto receive_handler = [this, &v_vct](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PreChargeRes> cast_expected = std::dynamic_pointer_cast<PreChargeRes>(expected);
    std::shared_ptr<PreChargeRes> cast_received = std::make_shared<PreChargeRes>();
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
          memcpy(&this->mtc->vc_EVSEPresentVoltage, cast_received->getEVSEPresentVoltage(), sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPresentVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEPresentVoltage");
          Logging::info(LogTbFnc_ENABLE, fmt::format("this->mtc->vc_EVSEPresentVoltage: {}", f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEPresentVoltage)));
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
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "PreChargeRes message was correct.");
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
  this->mtc->tc_V2G_EVCC_PreCharge_Timer->start(par_V2G_EVCC_PreCharge_Timeout);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PreChargeReq);
  do
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
      {
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_PreCharge_Timer->stop();
        v_EVTargetVoltageValidMinDeviation = 0.0;
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_PreCharge_Timer->stop();
        v_EVTargetVoltageValidMinDeviation = 0.0;
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_PreCharge_Timer->stop();
          v_EVTargetVoltageValidMinDeviation = 0.0;
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received PreChargeRes message, but with invalid data content."))
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        this->mtc->tc_V2G_EVCC_PreCharge_Timer->stop();
        v_EVTargetVoltageValidMinDeviation = 0.0;
        break;
      }
      if (this->cmn->a_SECC_Timeout(v_vct))
      {
        this->mtc->tc_V2G_EVCC_PreCharge_Timer->stop();
        v_EVTargetVoltageValidMinDeviation = 0.0;
        break;
      }
      if (this->mtc->tc_V2G_EVCC_PreCharge_Timer->timeout())
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        v_EVTargetVoltageValidMinDeviation = 0.0;
        this->mtc->setverdict(v_vct, "PreChargeTimer was triggered. PreCharge wasn't successful.");
        break;
      }
    }
    if (f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEPresentVoltage) < v_EVTargetVoltageValidMinDeviation)
    {
      Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing EVSE PreCharge Voltage check"));
      PAsleep(1);
    }
  } while (f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEPresentVoltage) < v_EVTargetVoltageValidMinDeviation);
  memcpy(&this->mtc->vc_EVTargetVoltage, &par_EVMaximumVoltageLimit, sizeof(PhysicalValueType));
  Logging::info(LogTbFnc_ENABLE, fmt::format("AFTER this->mtc->vc_EVTargetVoltage: {}", f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVTargetVoltage)));
  if (f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEPresentVoltage) > v_EVTargetVoltageValidMaxDeviation)
  {
    this->mtc->setverdict(inconc, "The present voltage is greater than the valid maximal deviation of the target voltage.");
  }
  return this->mtc->getverdict();
}
verdict_val TestBehavior_SECC_PreCharge::f_SECC_DC_TB_VTB_PreCharge_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
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

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);

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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PreChargeReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PreChargeRes message, but with invalid data content."))
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
verdict_val TestBehavior_SECC_PreCharge::f_SECC_DC_TB_VTB_PreCharge_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PreChargeReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PreChargeRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<PreChargeReq>(sendMsg)->setSessionId(randomSessionID);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);

  md_CMN_DC_PreChargeReq_001(sendMsg, this->mtc->vc_DC_EVStatus, this->mtc->vc_EVTargetVoltage, this->mtc->vc_EVPreChargeTargetCurrent);
  md_CMN_DC_PreChargeRes_001(expectedMsg, iso1Part4_ResponseCodeType::fAILED_UnknownSession);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PreChargeRes> cast_expected = std::dynamic_pointer_cast<PreChargeRes>(expected);
    std::shared_ptr<PreChargeRes> cast_received = std::make_shared<PreChargeRes>();
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
          this->mtc->setverdict(pass, "PreChargeRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PreChargeReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PreChargeRes message, but with invalid data content."))
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
verdict_val TestBehavior_SECC_PreCharge::f_SECC_DC_TB_VTB_PreCharge_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
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
  // deactivate(this->mtc->vc_Default_IEC_61851_ListenerBehavior);
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

void md_CMN_DC_PreChargeReq_001(std::shared_ptr<V2gTpMessage> &msg,
                                DC_EVStatusType &p_dC_EVStatus, PhysicalValueType &p_eVTargetVoltage, PhysicalValueType &p_eVTargetCurrent)
{
  std::static_pointer_cast<PreChargeReq>(msg)->setDCEVStatus(&p_dC_EVStatus);
  std::static_pointer_cast<PreChargeReq>(msg)->setEVTargetVoltage(&p_eVTargetVoltage);
  std::static_pointer_cast<PreChargeReq>(msg)->setEVTargetCurrent(&p_eVTargetCurrent);
}
void md_CMN_DC_PreChargeRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode)
{
  std::static_pointer_cast<PreChargeRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<PreChargeRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<PreChargeRes>(msg)->pDC_EVSEStatus_flag = has_value;
  std::static_pointer_cast<PreChargeRes>(msg)->pEVSEPresentVoltage_flag = has_value;
}