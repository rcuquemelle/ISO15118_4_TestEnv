#include "TB_SECC_ChargingStatus.h"
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
using namespace DataStructure_Security;

TestBehavior_SECC_ChargingStatus::TestBehavior_SECC_ChargingStatus(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_ChargingStatus::~TestBehavior_SECC_ChargingStatus()
{
}

#define OMIT ((int)0xFFFFE)
#define HAS_VAL ((int)0xFFFFF)

static void md_CMN_AC_ChargingStatusRes_001(std::shared_ptr<V2gTpMessage> &msg,
                                            iso1Part4_ResponseCodeType p_responseCode, std::string *p_evseID, int p_sAScheduleTuple,
                                            PhysicalValueType *p_eVSEMaxCurrent, MeterInfoType *p_meterInfo, int p_receiptRequired, AC_EVSEStatusType *p_aCeVSEStatus);
// MeterInfoType md_CMN_AC_meterInfoType(MeterIDType p_meterID, XSDAUX.unsignedLong p_meterReading, SigMeterReadingType p_sigMeterReading, MeterStatusType p_meterStatus, XSDAUX.long p_tMeter);

verdict_val TestBehavior_SECC_ChargingStatus::f_SECC_AC_TB_VTB_ChargingStatus_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargingStatusReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargingStatusRes>();

  std::static_pointer_cast<ChargingStatusReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_ChargingStatusRes_001(expectedMsg, iso1Part4_ResponseCodeType::oK, &this->mtc->vc_EvseId, this->mtc->vc_SAScheduleTupleId, nullptr, nullptr, OMIT, nullptr);

  auto receive_handler = [this, &v_vct](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargingStatusRes> cast_expected = std::dynamic_pointer_cast<ChargingStatusRes>(expected);
    std::shared_ptr<ChargingStatusRes> cast_received = std::make_shared<ChargingStatusRes>();
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
              if (this->mtc->vc_receiptRequired == true)
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
            this->mtc->setverdict(pass, "ChargingStatusRes message was correct.");
            if (nullptr != cast_received->getACEVSEStatus())
            {
              auto ACEVSEStatus = cast_received->getACEVSEStatus();
              this->mtc->vc_EVSENotification = (urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSENotificationType)ACEVSEStatus->EVSENotification;
            }
            if (nullptr != cast_received->getMeterInfo())
            {
              memcpy(&this->mtc->vc_MeterInfo, cast_received->getMeterInfo(), sizeof(MeterInfoType));
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargingStatusReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ChargingStatusRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargingStatus::f_SECC_AC_TB_VTB_ChargingStatus_002()
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargingStatusReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargingStatusRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargingStatus::f_SECC_AC_TB_VTB_ChargingStatus_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargingStatusReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargingStatusRes>();

  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<ChargingStatusReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->mEVSEID_flag = omit;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->mSAScheduleTupleID_flag = omit;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->pEVSEMaxCurrent_flag = omit;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->pMeterInfo_flag = omit;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->mReceiptRequired_flag = omit;
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->pAC_EVSEStatus_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargingStatusRes> cast_expected = std::dynamic_pointer_cast<ChargingStatusRes>(expected);
    std::shared_ptr<ChargingStatusRes> cast_received = std::make_shared<ChargingStatusRes>();
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
          this->mtc->setverdict(pass, "ChargingStatusRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargingStatusReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargingStatusRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargingStatus::f_SECC_AC_TB_VTB_ChargingStatus_004()
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

verdict_val TestBehavior_SECC_ChargingStatus::f_SECC_AC_TB_VTB_ChargingStatus_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargingStatusReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargingStatusRes>();

  std::static_pointer_cast<ChargingStatusReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargingStatusRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_ChargingStatusRes_001(expectedMsg, iso1Part4_ResponseCodeType::oK, &this->mtc->vc_EvseId, this->mtc->vc_SAScheduleTupleId, nullptr, nullptr, OMIT, nullptr);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargingStatusRes> cast_expected = std::dynamic_pointer_cast<ChargingStatusRes>(expected);
    std::shared_ptr<ChargingStatusRes> cast_received = std::make_shared<ChargingStatusRes>();
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
          if (nullptr != cast_received->getMeterInfo())
          {
            memcpy(&this->mtc->vc_MeterInfo, cast_received->getMeterInfo(), sizeof(MeterInfoType));
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
              if (this->mtc->vc_receiptRequired == true)
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
            this->mtc->setverdict(pass, "ChargingStatusRes message was correct.");
            if (nullptr != cast_received->getACEVSEStatus())
            {
              auto ACEVSEStatus = cast_received->getACEVSEStatus();
              this->mtc->vc_EVSENotification = (urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSENotificationType)ACEVSEStatus->EVSENotification;
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargingStatusReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargingStatusRes message, but with invalid data content."))
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

static void md_CMN_AC_ChargingStatusRes_001(std::shared_ptr<V2gTpMessage> &msg,
                                            iso1Part4_ResponseCodeType p_responseCode, std::string *p_evseID, int p_sAScheduleTuple,
                                            PhysicalValueType *p_eVSEMaxCurrent, MeterInfoType *p_meterInfo, int p_receiptRequired, AC_EVSEStatusType *p_aCeVSEStatus)
{
  std::static_pointer_cast<ChargingStatusRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<ChargingStatusRes>(msg)->mResponseCode_flag = specific;
  if (nullptr != p_evseID)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setEVSEID(*p_evseID);
    std::static_pointer_cast<ChargingStatusRes>(msg)->mEVSEID_flag = specific;
  }
  if (OMIT != p_sAScheduleTuple)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setSAScheduleTupleID(p_sAScheduleTuple);
    std::static_pointer_cast<ChargingStatusRes>(msg)->mSAScheduleTupleID_flag = specific;
  }
  if (nullptr != p_eVSEMaxCurrent)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setEVSEMaxCurrent(p_eVSEMaxCurrent);
    std::static_pointer_cast<ChargingStatusRes>(msg)->pEVSEMaxCurrent_flag = specific;
  }
  if (nullptr != p_meterInfo)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setMeterInfo(p_meterInfo);
    std::static_pointer_cast<ChargingStatusRes>(msg)->pMeterInfo_flag = specific;
  }
  if (OMIT != p_receiptRequired)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setReceiptRequired(p_receiptRequired);
    std::static_pointer_cast<ChargingStatusRes>(msg)->mReceiptRequired_flag = specific;
  }
  if (nullptr != p_aCeVSEStatus)
  {
    std::static_pointer_cast<ChargingStatusRes>(msg)->setACEVSEStatus(p_aCeVSEStatus);
    std::static_pointer_cast<ChargingStatusRes>(msg)->pAC_EVSEStatus_flag = specific;
  }
}