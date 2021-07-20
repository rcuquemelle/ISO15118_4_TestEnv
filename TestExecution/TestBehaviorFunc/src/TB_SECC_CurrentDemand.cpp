#include "TB_SECC_CurrentDemand.h"
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

// Plug and charge message
#define HAS_VAL ((int)0xFFFF)
#define OMIT ((int)0xFFFE)
TestBehavior_SECC_CurrentDemand::TestBehavior_SECC_CurrentDemand(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_CurrentDemand::~TestBehavior_SECC_CurrentDemand()
{
}

void md_CMN_DC_CurrentDemandReq_001(std::shared_ptr<V2gTpMessage> &msg, DC_EVStatusType &p_dC_EVStatus,
                                    PhysicalValueType &p_eVTargetCurrent, PhysicalValueType &p_eVTargetVoltage,
                                    PhysicalValueType &p_eVMaximumCurrentLimit, PhysicalValueType &p_eVMaximumVoltageLimit,
                                    PhysicalValueType &p_eVMaximumPowerLimit,
                                    bool p_bulkChargingComplete, PhysicalValueType &p_remainingTimeToBulkSoC,
                                    bool p_chargingComplete, PhysicalValueType &p_remainingTimeToFullSoC);

void f_checkPresentChargeParameter(std::shared_ptr<SECC_Tester> &_mtc,
                                   PhysicalValueType &EVSEPresentCurrent, PhysicalValueType &EVSEPresentVoltage,
                                   PhysicalValueType &EVMaximumCurrentLimit, PhysicalValueType &EVMaximumVoltageLimit, verdict_val v_vct);

void md_CMN_DC_CurrentDemandRes_001(std::shared_ptr<V2gTpMessage> &msg, responseCodeType m_responseCode,
                                    DC_EVSEStatusType *p_dC_EVSEStatus, PhysicalValueType *p_eVSEPresentVoltage, PhysicalValueType *p_eVSEPresentCurrent,
                                    int m_eVSECurrentLimitAchieved, int m_eVSEVoltageLimitAchieved, int m_eVSEPowerLimitAchieved,
                                    PhysicalValueType *p_eVSEMaximumVoltageLimit, PhysicalValueType *p_eVSEMaximumCurrentLimit, PhysicalValueType *p_eVSEMaximumPowerLimit,
                                    std::string *p_eVSEID, int m_sAScheduleTupleID, MeterInfoType *p_meterInfo, int m_receiptRequired);

verdict_val TestBehavior_SECC_CurrentDemand::f_SECC_DC_TB_VTB_CurrentDemand_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CurrentDemandReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CurrentDemandRes>();

  std::static_pointer_cast<CurrentDemandReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_CurrentDemandReq_001(sendMsg, this->mtc->vc_DC_EVStatus, this->mtc->vc_EVTargetCurrent, this->mtc->vc_EVTargetVoltage,
                                 this->mtc->vc_EVMaximumCurrentLimit, this->mtc->vc_EVMaximumVoltageLimit, this->mtc->vc_EVMaximumPowerLimit,
                                 false, this->mtc->vc_DC_remainingTimeToBulkSoC,
                                 true, this->mtc->vc_DC_remainingTimeToFullSoC);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_CurrentDemandRes_001(expectedMsg, (responseCodeType)iso1Part4_ResponseCodeType::oK,
                                 (DC_EVSEStatusType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, HAS_VAL, HAS_VAL, HAS_VAL, nullptr, nullptr, nullptr, (std::string *)HAS_VAL, HAS_VAL, nullptr, OMIT);

  auto receive_handler = [this, &v_vct](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<CurrentDemandRes> cast_expected = std::dynamic_pointer_cast<CurrentDemandRes>(expected);
    std::shared_ptr<CurrentDemandRes> cast_received = std::make_shared<CurrentDemandRes>();
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
          auto DCEVSEStatus = cast_received->getDCEVSEStatus();
          memcpy(&this->mtc->vc_EVSEPresentVoltage, cast_received->getEVSEPresentVoltage(), sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPresentVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEPresentVoltage");
          memcpy(&this->mtc->vc_EVSEPresentCurrent, cast_received->getEVSEPresentCurrent(), sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPresentCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEPresentCurrent");
          this->mtc->vc_EVSENotification = (urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSENotificationType)DCEVSEStatus->EVSENotification;
          this->mtc->vc_EvseId = cast_received->getEVSEID();
          if (nullptr != cast_received->getMeterInfo())
          {
            memcpy(&this->mtc->vc_MeterInfo, cast_received->getMeterInfo(), sizeof(MeterInfoType));
          }
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
          if (this->mtc->vc_EvseId.compare(cc_EvseId_NotSup))
          {
            bool result = fx_validateEVSEID(this->mtc->vc_EvseId, "ISO");
            if (!result)
            {
              this->mtc->setverdict(v_vct, "Invalid EVSEID syntax was detected.");
            }
          }
          if (-1 != cast_received->getReceiptRequired())
          {
            this->mtc->vc_receiptRequired = (bool)cast_received->getReceiptRequired();
            if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::eIM)
            {
              if (!(this->mtc->vc_receiptRequired == false))
              {
                this->mtc->setverdict(v_vct, "ReceiptRequired shall always set to false EIM Identification Mode.");
              }
            }
            else
            {
              if (PIXIT_SECC_CMN_ReceiptRequired)
              {
                if (this->mtc->vc_receiptRequired == false)
                {
                  this->mtc->setverdict(v_vct, "ReceiptRequired shall always set to true if the SECC requires a metering receipt from the EVCC");
                }
              }
              else
              {
                if (this->mtc->vc_receiptRequired == true)
                {
                  this->mtc->setverdict(v_vct, "ReceiptRequired shall always set to false if the SECC not requires a metering receipt from the EVCC");
                }
              }
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "CurrentDemandRes message was correct.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CurrentDemandReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received CurrentDemandRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_CurrentDemand::f_SECC_DC_TB_VTB_CurrentDemand_002()
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CurrentDemandReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CurrentDemandRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_CurrentDemand::f_SECC_DC_TB_VTB_CurrentDemand_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CurrentDemandReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CurrentDemandRes>();

  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<CurrentDemandReq>(sendMsg)->setSessionId(randomSessionID);
  md_CMN_DC_CurrentDemandReq_001(sendMsg, this->mtc->vc_DC_EVStatus, this->mtc->vc_EVTargetCurrent, this->mtc->vc_EVTargetVoltage,
                                 this->mtc->vc_EVMaximumCurrentLimit, this->mtc->vc_EVMaximumVoltageLimit, this->mtc->vc_EVMaximumPowerLimit,
                                 false, this->mtc->vc_DC_remainingTimeToBulkSoC,
                                 true, this->mtc->vc_DC_remainingTimeToFullSoC);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->mResponseCode_flag = specific;
  md_CMN_DC_CurrentDemandRes_001(expectedMsg, (responseCodeType)iso1Part4_ResponseCodeType::oK,
                                 (DC_EVSEStatusType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, HAS_VAL, HAS_VAL, HAS_VAL, nullptr, nullptr, nullptr, (std::string *)HAS_VAL, HAS_VAL, nullptr, OMIT);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<CurrentDemandRes> cast_expected = std::dynamic_pointer_cast<CurrentDemandRes>(expected);
    std::shared_ptr<CurrentDemandRes> cast_received = std::make_shared<CurrentDemandRes>();
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
          this->mtc->setverdict(pass, "CurrentDemandRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CurrentDemandReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CurrentDemandRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_CurrentDemand::f_SECC_DC_TB_VTB_CurrentDemand_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
  // Wait until sequence timeout SUT should expire
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

verdict_val TestBehavior_SECC_CurrentDemand::f_SECC_DC_TB_VTB_CurrentDemand_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<CurrentDemandReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<CurrentDemandRes>();
  std::static_pointer_cast<CurrentDemandReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_CurrentDemandReq_001(sendMsg, this->mtc->vc_DC_EVStatus, this->mtc->vc_EVTargetCurrent, this->mtc->vc_EVTargetVoltage,
                                 this->mtc->vc_EVMaximumCurrentLimit, this->mtc->vc_EVMaximumVoltageLimit, this->mtc->vc_EVMaximumPowerLimit,
                                 false, this->mtc->vc_DC_remainingTimeToBulkSoC,
                                 true, this->mtc->vc_DC_remainingTimeToFullSoC);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<CurrentDemandRes>(expectedMsg)->mResponseCode_flag = specific;
  md_CMN_DC_CurrentDemandRes_001(expectedMsg, (responseCodeType)iso1Part4_ResponseCodeType::oK,
                                 (DC_EVSEStatusType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, (PhysicalValueType *)HAS_VAL, HAS_VAL, HAS_VAL, HAS_VAL, nullptr, nullptr, nullptr, (std::string *)HAS_VAL, HAS_VAL, (MeterInfoType *)HAS_VAL, OMIT);
  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<CurrentDemandRes> cast_expected = std::dynamic_pointer_cast<CurrentDemandRes>(expected);
    std::shared_ptr<CurrentDemandRes> cast_received = std::make_shared<CurrentDemandRes>();
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
          auto DCEVSEStatus = cast_received->getDCEVSEStatus();
          memcpy(&this->mtc->vc_EVSEPresentVoltage, cast_received->getEVSEPresentVoltage(), sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPresentVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSEPresentVoltage");
          memcpy(&this->mtc->vc_EVSEPresentCurrent, cast_received->getEVSEPresentCurrent(), sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPresentCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEPresentCurrent");
          this->mtc->vc_EVSENotification = (urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSENotificationType)DCEVSEStatus->EVSENotification;
          this->mtc->vc_EvseId = cast_received->getEVSEID();
          if (nullptr != cast_received->getMeterInfo())
          {
            memcpy(&this->mtc->vc_MeterInfo, cast_received->getMeterInfo(), sizeof(MeterInfoType));
          }
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
          if (this->mtc->vc_EvseId.compare(cc_EvseId_NotSup))
          {
            bool result = fx_validateEVSEID(this->mtc->vc_EvseId, "ISO");
            if (!result)
            {
              this->mtc->setverdict(fail, "Invalid EVSEID syntax was detected.");
            }
          }
          if (-1 != cast_received->getReceiptRequired())
          {
            this->mtc->vc_receiptRequired = (bool)cast_received->getReceiptRequired();
            if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::eIM)
            {
              if (!(this->mtc->vc_receiptRequired == false))
              {
                this->mtc->setverdict(fail, "ReceiptRequired shall always set to false EIM Identification Mode.");
              }
            }
            else
            {
              if (PIXIT_SECC_CMN_ReceiptRequired)
              {
                if (this->mtc->vc_receiptRequired == false)
                {
                  this->mtc->setverdict(fail, "ReceiptRequired shall always set to true if the SECC requires a metering receipt from the EVCC");
                }
              }
              else
              {
                if (this->mtc->vc_receiptRequired == true)
                {
                  this->mtc->setverdict(fail, "ReceiptRequired shall always set to false if the SECC not requires a metering receipt from the EVCC");
                }
              }
            }
          }
          if (this->mtc->vc_MeterInfo.MeterReading_isUsed == 1)
          {
            if ((this->mtc->vc_MeterInfo.MeterReading < 0) ||
                (this->mtc->vc_MeterInfo.MeterReading > cc_maximum_value_meterReading))
            {
              this->mtc->setverdict(fail, "Invalid value range for MeterReading detected.");
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "CurrentDemandRes message was correct.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CurrentDemandReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CurrentDemandRes message, but with invalid data content."))
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

void f_checkPresentChargeParameter(std::shared_ptr<SECC_Tester> &_mtc,
                                   PhysicalValueType &EVSEPresentCurrent, PhysicalValueType &EVSEPresentVoltage,
                                   PhysicalValueType &EVMaximumCurrentLimit, PhysicalValueType &EVMaximumVoltageLimit, verdict_val v_vct)
{
  if (f_CMN_PhysicalValue_GetValue(EVSEPresentCurrent) > f_CMN_PhysicalValue_GetValue(EVMaximumCurrentLimit))
  {
    _mtc->setverdict(v_vct, "The present current is greater than the EV maximum current limit. The charging process will be terminated.");
  }
  if (f_CMN_PhysicalValue_GetValue(EVSEPresentVoltage) > f_CMN_PhysicalValue_GetValue(EVMaximumVoltageLimit))
  {
    _mtc->setverdict(v_vct, "The present voltage is greater than the EV maximum voltage limit. The charging process will be terminated.");
  }
}

void md_CMN_DC_CurrentDemandReq_001(std::shared_ptr<V2gTpMessage> &msg, DC_EVStatusType &p_dC_EVStatus,
                                    PhysicalValueType &p_eVTargetCurrent, PhysicalValueType &p_eVTargetVoltage,
                                    PhysicalValueType &p_eVMaximumCurrentLimit, PhysicalValueType &p_eVMaximumVoltageLimit,
                                    PhysicalValueType &p_eVMaximumPowerLimit,
                                    bool p_bulkChargingComplete, PhysicalValueType &p_remainingTimeToBulkSoC,
                                    bool p_chargingComplete, PhysicalValueType &p_remainingTimeToFullSoC)
{

  std::static_pointer_cast<CurrentDemandReq>(msg)->setDcEvStatus(&p_dC_EVStatus);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setEvTargetCurrent(&p_eVTargetCurrent);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setEvTargetVoltage(&p_eVTargetVoltage);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setEvMaxVoltageLimit(&p_eVMaximumVoltageLimit);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setEvMaxCurrentLimit(&p_eVMaximumCurrentLimit);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setEvMaxPowerLimit(&p_eVMaximumPowerLimit);

  std::static_pointer_cast<CurrentDemandReq>(msg)->setBulkChargeCompleteStatus(p_bulkChargingComplete);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setBulkChargeRemainTime(&p_remainingTimeToBulkSoC);

  std::static_pointer_cast<CurrentDemandReq>(msg)->setChargingCompleteStatus(p_chargingComplete);
  std::static_pointer_cast<CurrentDemandReq>(msg)->setFullChargeRemainTime(&p_remainingTimeToFullSoC);
}

void md_CMN_DC_CurrentDemandRes_001(std::shared_ptr<V2gTpMessage> &msg,
                                    responseCodeType m_responseCode, DC_EVSEStatusType *p_dC_EVSEStatus,
                                    PhysicalValueType *p_eVSEPresentVoltage, PhysicalValueType *p_eVSEPresentCurrent,
                                    int m_eVSECurrentLimitAchieved, int m_eVSEVoltageLimitAchieved, int m_eVSEPowerLimitAchieved,
                                    PhysicalValueType *p_eVSEMaximumVoltageLimit, PhysicalValueType *p_eVSEMaximumCurrentLimit, PhysicalValueType *p_eVSEMaximumPowerLimit,
                                    std::string *p_eVSEID, int m_sAScheduleTupleID, MeterInfoType *p_meterInfo, int m_receiptRequired)
{
  std::static_pointer_cast<CurrentDemandRes>(msg)->setResponseCode(m_responseCode);
  std::static_pointer_cast<CurrentDemandRes>(msg)->mResponseCode_flag = specific;

  if ((int)m_eVSECurrentLimitAchieved == HAS_VAL)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSECurrentLimitArchived_flag = has_value;
  }
  else if ((int)m_eVSECurrentLimitAchieved == OMIT)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSECurrentLimitArchived_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSECurrentLimitArchived((bool)m_eVSECurrentLimitAchieved);
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSECurrentLimitArchived_flag = specific;
  }

  if ((int)m_eVSEVoltageLimitAchieved == HAS_VAL)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEVoltageLimitArchived_flag = has_value;
  }
  else if ((int)m_eVSEVoltageLimitAchieved == OMIT)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEVoltageLimitArchived_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEVoltageLimitArchived((bool)m_eVSEVoltageLimitAchieved);
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEVoltageLimitArchived_flag = specific;
  }

  if ((int)m_eVSEPowerLimitAchieved == HAS_VAL)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEPowerLimitAchieved_flag = has_value;
  }
  else if ((int)m_eVSEPowerLimitAchieved == OMIT)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEPowerLimitAchieved_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSECurrentLimitArchived((bool)m_eVSEPowerLimitAchieved);
    std::static_pointer_cast<CurrentDemandRes>(msg)->mEVSEPowerLimitAchieved_flag = specific;
  }

  if ((int)m_sAScheduleTupleID == HAS_VAL)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mSAScheduleTupleID_flag = has_value;
  }
  else if ((int)m_sAScheduleTupleID == OMIT)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mSAScheduleTupleID_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setSAScheduleTupleID((uint8_t)m_sAScheduleTupleID);
    std::static_pointer_cast<CurrentDemandRes>(msg)->mSAScheduleTupleID_flag = specific;
  }

  if ((int)m_receiptRequired == HAS_VAL)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mReceiptRequired_flag = has_value;
  }
  else if ((int)m_receiptRequired == OMIT)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->mReceiptRequired_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setReceiptRequired((bool)m_receiptRequired);
    std::static_pointer_cast<CurrentDemandRes>(msg)->mReceiptRequired_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_dC_EVSEStatus)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pDCEVSEStatus_flag = has_value;
  }
  else if (nullptr == p_dC_EVSEStatus)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pDCEVSEStatus_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setDCEVSEStatus(p_dC_EVSEStatus);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pDCEVSEStatus_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEPresentVoltage)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentVoltage_flag = has_value;
  }
  else if (nullptr == p_eVSEPresentVoltage)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentVoltage_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEPresentVoltage(p_eVSEPresentVoltage);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentVoltage_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEPresentCurrent)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentCurrent_flag = has_value;
  }
  else if (nullptr == p_eVSEPresentCurrent)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentCurrent_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEPresentCurrent(p_eVSEPresentCurrent);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEPresentCurrent_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEMaximumVoltageLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumVoltageLimit_flag = has_value;
  }
  else if (nullptr == p_eVSEMaximumVoltageLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumVoltageLimit_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEMaximumVoltageLimit(p_eVSEMaximumVoltageLimit);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumVoltageLimit_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEMaximumCurrentLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumCurrentLimit_flag = has_value;
  }
  else if (nullptr == p_eVSEMaximumCurrentLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumCurrentLimit_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEMaximumCurrentLimit(p_eVSEMaximumCurrentLimit);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumCurrentLimit_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEMaximumPowerLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumPowerLimit_flag = has_value;
  }
  else if (nullptr == p_eVSEMaximumPowerLimit)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumPowerLimit_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEMaximumPowerLimit(p_eVSEMaximumPowerLimit);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEMaximumPowerLimit_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_eVSEID)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEID_flag = has_value;
  }
  else if (nullptr == p_eVSEID)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEID_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setEVSEID(*p_eVSEID);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pEVSEID_flag = specific;
  }

  if (HAS_VAL == (uintptr_t)p_meterInfo)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pMeterInfo_flag = has_value;
  }
  else if (nullptr == p_meterInfo)
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->pMeterInfo_flag = omit;
  }
  else
  {
    std::static_pointer_cast<CurrentDemandRes>(msg)->setMeterInfo(p_meterInfo);
    std::static_pointer_cast<CurrentDemandRes>(msg)->pMeterInfo_flag = specific;
  }
}