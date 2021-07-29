#include "TB_SECC_PowerDelivery.h"
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

#define HAS_VAL ((int)0xFFFFF)
#define OMIT ((int)0xFFFFE)

TestBehavior_SECC_PowerDelivery::TestBehavior_SECC_PowerDelivery(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_PowerDelivery::~TestBehavior_SECC_PowerDelivery()
{
}

static void md_CMN_AC_PowerDeliveryReq_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ChargeProgressType p_chargeProgress, int p_sAScheduleTupleID);
static void md_CMN_DC_PowerDeliveryReq_002(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ChargeProgressType p_chargeProgress,
                                           uint8_t p_sAScheduleTupleID, ChargingProfileType *p_chargingProfile, DC_EVPowerDeliveryParameterType *p_dcEVPowerDeliveryParameter);
static void md_CMN_AC_PowerDeliveryReq_003(std::shared_ptr<V2gTpMessage> &msg,
                                           iso1Part4_ChargeProgressType p_enablePower, uint8_t p_sAScheduleTupleID, ChargingProfileType *p_CProfile);
/* static void md_CMN_CMN_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, EVSEStatusType *p_evsestatus); */
static void md_CMN_AC_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, AC_EVSEStatusType *p_evsestatus);
/* static void md_CMN_DC_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, DC_EVSEStatusType *p_evsestatus); */
static bool checkInvalidTupleID(std::shared_ptr<SECC_Tester> &_mtc, uint8_t v_id, SAScheduleListType &SAScheduleTuple_List);
static void md_CMN_CMN_ProfileEntry_001(ProfileEntryType *profile_entry, uint32_t entryStart, PhysicalValueType *maxPower, int maxNumPhases);
static DC_EVPowerDeliveryParameterType *md_CMN_DC_EVPowerDeliveryParameter(DC_EVStatusType &dC_EVStatus, int bulkChargingComplete, bool chargingComplete);
static ChargingProfileType *md_CMN_CMN_ChargingProfile_001(ProfileEntryType *entry_list, uint8_t size);

void TestBehavior_SECC_PowerDelivery::f_SECC_61851_State_CorDorB(iso1Part4_ChargeProgressType cpt, std::shared_ptr<HAL_61851_Listener> &listener)
{
  IEC_61851_States v_state;
  // set 61851 state C or B depending on charge progress type
  if (cpt == iso1Part4_ChargeProgressType::start_)
  {
    v_state = PICS_SECC_CMN_EvStateInChargeProgress;
  }
  else if (cpt == iso1Part4_ChargeProgressType::stop_)
  {
    v_state = B;
  }
  if (cpt != iso1Part4_ChargeProgressType::renegotiate)
  {
    f_SECC_changeValidStateCondition(v_state);
    f_SECC_setState(this->systemSECC, v_state, listener);
    PAsleep(par_CMN_waitForNextHAL);
  }
}

bool TestBehavior_SECC_PowerDelivery::a_AC_PowerDeliveryRes_Message(iso1Part4_ChargeProgressType c, iso1Part4_ResponseCodeType rc)
{
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)rc);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pAC_EVSEStatus_flag = has_value;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pDC_EVSEStatus_flag = omit;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pEVSEStatus_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          // get EVSEStatus.Notification
          AC_EVSEStatusType* ACEVSEStatus = cast_received->getACEVSEStatus();
          if (nullptr != ACEVSEStatus)
          {
            if (ACEVSEStatus->EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
            }
            this->mtc->setverdict(pass, "PowerDeliveryRes message was correct.");
          }
          else
          {
            this->mtc->setverdict(fail, "PowerDeliveryRes message does not return ACEVSEStatus or ACEVSEStatus_isUsed = false");
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

  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
  {
    return true;
  }
  return false;
}

bool TestBehavior_SECC_PowerDelivery::a_DC_PowerDeliveryRes_Message(iso1Part4_ChargeProgressType c, iso1Part4_ResponseCodeType rc)
{
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)rc);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pDC_EVSEStatus_flag = has_value;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pAC_EVSEStatus_flag = omit;
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pEVSEStatus_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          // get EVSEStatus.Notification
          DC_EVSEStatusType* DCEVSEStatus = cast_received->getDCEVSEStatus();
          if (nullptr != DCEVSEStatus)
          {
            if (DCEVSEStatus->EVSEIsolationStatus_isUsed == 1)
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
            this->mtc->setverdict(pass, "PowerDeliveryRes message was correct.");
          }
          else
          {
            this->mtc->setverdict(fail, "PowerDeliveryRes message does not return DCEVSEStatus or DCEVSEStatus_isUsed = false");
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
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
  {
    return true;
  }
  return false;
}

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_001(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  const int c_maxProfileEntries = 24;
  const int c_numberProfilEntries = this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.arrayLen;
  int v_numberProfilEntries;
  if (c_numberProfilEntries > c_maxProfileEntries)
  {
    v_numberProfilEntries = c_maxProfileEntries;
  }
  else
  {
    v_numberProfilEntries = c_numberProfilEntries;
  }
  ProfileEntryType *v_profileList = new ProfileEntryType[v_numberProfilEntries];
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  if (chargeProgress == iso1Part4_ChargeProgressType::start_)
  {
    for (int i = 0; i < v_numberProfilEntries; i = i + 1)
    {
      md_CMN_CMN_ProfileEntry_001(&v_profileList[i],
        this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.array[i].RelativeTimeInterval.start,
          &this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.array[i].PMax, OMIT);
    }
    md_CMN_AC_PowerDeliveryReq_003(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId, md_CMN_CMN_ChargingProfile_001(v_profileList, v_numberProfilEntries));
  }
  else
  {
    md_CMN_AC_PowerDeliveryReq_001(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId);
  }
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  f_SECC_61851_State_CorDorB(chargeProgress, v_HAL_61851_Listener);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
  while (true)
  {
    if (a_AC_PowerDeliveryRes_Message(chargeProgress, iso1Part4_ResponseCodeType::oK))
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received PowerDeliveryRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
  }
  delete[] v_profileList;
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_002(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
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
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

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
  f_SECC_61851_State_CorDorB(chargeProgress, v_HAL_61851_Listener);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_003(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(randomSessionID);
  md_CMN_AC_PowerDeliveryReq_001(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->mResponseCode_flag = specific;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  f_SECC_61851_State_CorDorB(chargeProgress, v_HAL_61851_Listener);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_004(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  bool isShutdownOSC = false;
  ProfileEntryType v_profileList[7];
  ;
  PhysicalValueType mpower;
  memcpy(&mpower, &this->mtc->vc_EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
  mpower.Value = 2 * mpower.Value;
  md_CMN_CMN_ProfileEntry_001(&v_profileList[0], 1400, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[1], 1410, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[2], 1420, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[3], 1430, &mpower, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[4], 1440, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[5], 1450, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[6], 1500, &this->mtc->vc_EVSEMaximumPowerLimit, 3);

  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_PowerDeliveryReq_003(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId, md_CMN_CMN_ChargingProfile_001(v_profileList, 7));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_ChargingProfileInvalid);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->mResponseCode_flag = specific;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_ChargingProfileInvalid' is successful.");
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
  f_SECC_61851_State_CorDorB(chargeProgress, v_HAL_61851_Listener);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_005(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  bool isValid;
  bool isShutdownOSC = false;
  ProfileEntryType v_profileList[7];
  ;
  md_CMN_CMN_ProfileEntry_001(&v_profileList[0], 1400, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[1], 1410, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[2], 1420, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[3], 1430, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[4], 1440, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[5], 1450, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[6], 1500, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  this->mtc->vc_SAScheduleTupleId = 255;
  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_PowerDeliveryReq_003(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId, md_CMN_CMN_ChargingProfile_001(v_profileList, 7));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_PowerDeliveryRes_001(expectedMsg, iso1Part4_ResponseCodeType::fAILED_TariffSelectionInvalid, nullptr);
  isValid = checkInvalidTupleID(this->mtc, this->mtc->vc_SAScheduleTupleId, this->mtc->vc_SASchedule_List);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_TariffSelectionInvalid' is successful.");
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

  if (isValid)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
    f_SECC_61851_State_CorDorB(chargeProgress, v_HAL_61851_Listener);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_AC_TB_VTB_PowerDelivery_006(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  bool isShutdownOSC = false;
  IEC_61851_States v_state;

  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_PowerDeliveryReq_003(sendMsg, iso1Part4_ChargeProgressType::renegotiate, this->mtc->vc_SAScheduleTupleId, nullptr);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_AC_PowerDeliveryRes_001(expectedMsg, iso1Part4_ResponseCodeType::fAILED, nullptr);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED' is successful. No PowerDeliveryReq with ChargeProgress set to 'Start' has been received before. ");
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
  v_state = PICS_SECC_CMN_EvStateInChargeProgress;
  f_SECC_changeValidStateCondition(v_state);
  f_SECC_setState(this->systemSECC, v_state, v_HAL_61851_Listener);
  PAsleep(par_CMN_waitForNextHAL);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_001(
    iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, bool v_chargingComplete, bool v_setState, verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  const int c_maxProfileEntries = 24;
  const int c_numberProfilEntries = this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.arrayLen;
  int v_numberProfilEntries;
  if (c_numberProfilEntries > c_maxProfileEntries)
  {
    v_numberProfilEntries = c_maxProfileEntries;
  }
  else
  {
    v_numberProfilEntries = c_numberProfilEntries;
  }
  ProfileEntryType *v_profileList = new ProfileEntryType[v_numberProfilEntries];
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  if (chargeProgress == iso1Part4_ChargeProgressType::start_)
  {
    for (int i = 0; i < v_numberProfilEntries; i = i + 1)
    {
      md_CMN_CMN_ProfileEntry_001(&v_profileList[i], this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.array[i].RelativeTimeInterval.start,
                                  &this->mtc->vc_PMaxSchedule.PMaxScheduleEntry.array[i].PMax, OMIT);
    }
    md_CMN_DC_PowerDeliveryReq_002(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId,
                                   md_CMN_CMN_ChargingProfile_001(v_profileList, v_numberProfilEntries),
                                   md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, v_chargingComplete));
  }
  else
  {
    if ((chargeProgress == iso1Part4_ChargeProgressType::stop_) && (!PICS_SECC_DC_WeldingDetection))
    {
      this->mtc->vc_DC_EVStatus.EVReady = false;
    }
    md_CMN_DC_PowerDeliveryReq_002(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId, nullptr,
                                   md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, v_chargingComplete));
  }
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
  while (true)
  {
    if (a_DC_PowerDeliveryRes_Message(chargeProgress, iso1Part4_ResponseCodeType::oK))
    {
      if ((chargeProgress == iso1Part4_ChargeProgressType::stop_) && v_setState)
      {
        f_SECC_changeValidStateCondition(B);
        f_SECC_setState(this->systemSECC, B, v_HAL_61851_Listener);
        PAsleep(par_CMN_waitForNextHAL);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received PowerDeliveryRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
  }
  delete[] v_profileList;
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_002()
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
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType chargeProgress)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(randomSessionID);
  md_CMN_DC_PowerDeliveryReq_002(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId, nullptr, md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, false));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->mResponseCode_flag = specific;
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_UnknownSession' is successful.");
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

  if ((chargeProgress == iso1Part4_ChargeProgressType::stop_) && !(PICS_SECC_DC_WeldingDetection))
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
  }
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_004(iso1Part4_ChargeProgressType chargeProgress)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  bool isShutdownOSC = false;
  ProfileEntryType v_profileList[7];
  PhysicalValueType mpower;
  memcpy(&mpower, &this->mtc->vc_EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
  mpower.Value = 1 + mpower.Value;
  md_CMN_CMN_ProfileEntry_001(&v_profileList[0], 1400, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[1], 1410, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[2], 1420, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[3], 1430, &mpower, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[4], 1440, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[5], 1450, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[6], 1500, &this->mtc->vc_EVSEMaximumPowerLimit, 3);

  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_PowerDeliveryReq_002(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId,
                                 md_CMN_CMN_ChargingProfile_001(v_profileList, 7),
                                 md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, false));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_ChargingProfileInvalid);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pDC_EVSEStatus_flag = has_value;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_ChargingProfileInvalid' is successful.");
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

  if ((chargeProgress == iso1Part4_ChargeProgressType::stop_) && !(PICS_SECC_DC_WeldingDetection))
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
  }
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_005(iso1Part4_ChargeProgressType chargeProgress)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();
  bool isValid;
  bool isShutdownOSC = false;
  ProfileEntryType v_profileList[7];
  ;
  md_CMN_CMN_ProfileEntry_001(&v_profileList[0], 1400, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[1], 1410, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[2], 1420, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[3], 1430, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[4], 1440, &this->mtc->vc_EVSEMaximumPowerLimit, 1);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[5], 1450, &this->mtc->vc_EVSEMaximumPowerLimit, 2);
  md_CMN_CMN_ProfileEntry_001(&v_profileList[6], 1500, &this->mtc->vc_EVSEMaximumPowerLimit, 3);
  this->mtc->vc_SAScheduleTupleId = 255;
  isValid = checkInvalidTupleID(this->mtc, this->mtc->vc_SAScheduleTupleId, this->mtc->vc_SASchedule_List);

  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_PowerDeliveryReq_002(sendMsg, chargeProgress, this->mtc->vc_SAScheduleTupleId,
                                 md_CMN_CMN_ChargingProfile_001(v_profileList, 7),
                                 md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, false));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_TariffSelectionInvalid);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pDC_EVSEStatus_flag = has_value;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED_TariffSelectionInvalid' is successful.");
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

  if ((chargeProgress == iso1Part4_ChargeProgressType::stop_) && !(PICS_SECC_DC_WeldingDetection))
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
  }
  if (isValid)
  {
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_DC_TB_VTB_PowerDelivery_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<PowerDeliveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<PowerDeliveryRes>();

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);

  std::static_pointer_cast<PowerDeliveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_CMN_DC_PowerDeliveryReq_002(sendMsg, iso1Part4_ChargeProgressType::renegotiate, this->mtc->vc_SAScheduleTupleId, nullptr,
                                 md_CMN_DC_EVPowerDeliveryParameter(this->mtc->vc_DC_EVStatus, OMIT, false));
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED);
  std::static_pointer_cast<PowerDeliveryRes>(expectedMsg)->pDC_EVSEStatus_flag = has_value;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<PowerDeliveryRes> cast_expected = std::dynamic_pointer_cast<PowerDeliveryRes>(expected);
    std::shared_ptr<PowerDeliveryRes> cast_received = std::make_shared<PowerDeliveryRes>();
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
          this->mtc->setverdict(pass, "PowerDeliveryRes with responseCode 'fAILED' is successful. No PowerDeliveryReq with ChargeProgress set to 'Start' has been received before. ");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PowerDeliveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PowerDelivery::f_SECC_CMN_TB_VTB_PowerDelivery_001()
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
  //deactivate(vc_Default_IEC_61851_ListenerBehavior);
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

static void md_CMN_AC_PowerDeliveryReq_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ChargeProgressType p_chargeProgress, int p_sAScheduleTupleID)
{
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setChargeProgress((chargeProgressType)p_chargeProgress);
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setSAScheduleTupleID((uint8_t)p_sAScheduleTupleID);
}

static void md_CMN_DC_PowerDeliveryReq_002(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ChargeProgressType p_chargeProgress,
                                           uint8_t p_sAScheduleTupleID, ChargingProfileType *p_chargingProfile, DC_EVPowerDeliveryParameterType *p_dcEVPowerDeliveryParameter)
{
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setChargeProgress((chargeProgressType)p_chargeProgress);
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setSAScheduleTupleID(p_sAScheduleTupleID);
  if (p_chargingProfile != nullptr)
  {
    std::static_pointer_cast<PowerDeliveryReq>(msg)->setChargingProfile(p_chargingProfile);
  }
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setDCEVPowerDeliveryParameter(p_dcEVPowerDeliveryParameter);
}

static void md_CMN_AC_PowerDeliveryReq_003(std::shared_ptr<V2gTpMessage> &msg,
                                           iso1Part4_ChargeProgressType p_enablePower, uint8_t p_sAScheduleTupleID, ChargingProfileType *p_CProfile)
{
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setChargeProgress((chargeProgressType)p_enablePower);
  std::static_pointer_cast<PowerDeliveryReq>(msg)->setSAScheduleTupleID(p_sAScheduleTupleID);
  if (nullptr != p_CProfile)
  {
    std::static_pointer_cast<PowerDeliveryReq>(msg)->setChargingProfile(p_CProfile);
  }
}

/* static void md_CMN_CMN_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, EVSEStatusType *p_evsestatus)
{
  std::static_pointer_cast<PowerDeliveryRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<PowerDeliveryRes>(msg)->mResponseCode_flag = specific;
  if (nullptr != p_evsestatus)
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->setEVSEStatus(p_evsestatus);
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pEVSEStatus_flag = specific;
  }
  else
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pEVSEStatus_flag = has_value;
  }
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pAC_EVSEStatus_flag = omit;
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pDC_EVSEStatus_flag = omit;
} */

static void md_CMN_AC_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, AC_EVSEStatusType *p_evsestatus)
{
  std::static_pointer_cast<PowerDeliveryRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<PowerDeliveryRes>(msg)->mResponseCode_flag = specific;
  if (nullptr != p_evsestatus)
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->setACEVSEStatus(p_evsestatus);
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pAC_EVSEStatus_flag = specific;
  }
  else
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pAC_EVSEStatus_flag = has_value;
  }
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pDC_EVSEStatus_flag = omit;
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pEVSEStatus_flag = omit;
}

/* static void md_CMN_DC_PowerDeliveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode, DC_EVSEStatusType *p_evsestatus)
{
  std::static_pointer_cast<PowerDeliveryRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<PowerDeliveryRes>(msg)->mResponseCode_flag = specific;
  if (nullptr != p_evsestatus)
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->setDCEVSEStatus(p_evsestatus);
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pDC_EVSEStatus_flag = specific;
  }
  else
  {
    std::static_pointer_cast<PowerDeliveryRes>(msg)->pDC_EVSEStatus_flag = has_value;
  }
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pAC_EVSEStatus_flag = omit;
  std::static_pointer_cast<PowerDeliveryRes>(msg)->pEVSEStatus_flag = omit;
} */

static bool checkInvalidTupleID(std::shared_ptr<SECC_Tester> &_mtc, uint8_t v_id, SAScheduleListType &SAScheduleTuple_List)
{
  for (int i = 0; i < SAScheduleTuple_List.SAScheduleTuple.arrayLen; i = i + 1)
  {
    if (v_id == SAScheduleTuple_List.SAScheduleTuple.array[i].SAScheduleTupleID)
    {
      _mtc->setverdict(inconc, "Selected tupleID is not invalid.");
      return false;
    }
  }
  return true;
}

static void md_CMN_CMN_ProfileEntry_001(ProfileEntryType *profile_entry, uint32_t entryStart, PhysicalValueType *maxPower, int maxNumPhases)
{
  profile_entry->ChargingProfileEntryStart = entryStart;
  memcpy(&profile_entry->ChargingProfileEntryMaxPower, maxPower, sizeof(PhysicalValueType));
  if ((int)maxNumPhases != OMIT)
  {
    profile_entry->ChargingProfileEntryMaxNumberOfPhasesInUse_isUsed = 1;
    profile_entry->ChargingProfileEntryMaxNumberOfPhasesInUse = (int8_t)maxNumPhases;
  }
}

static DC_EVPowerDeliveryParameterType *md_CMN_DC_EVPowerDeliveryParameter(DC_EVStatusType &dC_EVStatus, int bulkChargingComplete, bool chargingComplete)
{
  static DC_EVPowerDeliveryParameterType powDel;
  init_iso1DC_EVPowerDeliveryParameterType(&powDel);
  if ((int)bulkChargingComplete != OMIT)
  {
    powDel.BulkChargingComplete_isUsed = 1;
  }
  powDel.BulkChargingComplete = 1;
  powDel.ChargingComplete = (uint8_t)chargingComplete;
  memcpy(&powDel.DC_EVStatus, &dC_EVStatus, sizeof(DC_EVStatusType));
  return &powDel;
}

static ChargingProfileType *md_CMN_CMN_ChargingProfile_001(ProfileEntryType *entry_list, uint8_t size)
{
  static ChargingProfileType Profile;
  init_iso1ChargingProfileType(&Profile);
  Profile.ProfileEntry.arrayLen = size;
  for (size_t i = 0; i < size; i++)
  {
    memcpy(&Profile.ProfileEntry.array[i], &entry_list[i], sizeof(ProfileEntryType));
  }
  return &Profile;
}