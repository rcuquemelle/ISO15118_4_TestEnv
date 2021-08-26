#include "TB_SECC_ChargeParameterDiscovery.h"
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
TestBehavior_SECC_ChargeParameterDiscovery::TestBehavior_SECC_ChargeParameterDiscovery(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_ChargeParameterDiscovery::~TestBehavior_SECC_ChargeParameterDiscovery()
{
}

static bool f_checkRequestedEnergyTransfermode(EnergyTransferModeType &v_requestedEnergyTransferMode, SupportedEnergyTransferModeType &v_supportedEnergyTransferMode);
static void f_checkSalesTariffTimeIntervals(std::shared_ptr<SECC_Tester> &_mtc, uint32_t DepartureTime, SAScheduleListType &SASchedules, verdict_val v_vct);
static void f_checkEVSEChargeParameter(std::shared_ptr<SECC_Tester> &_mtc, verdict_val v_vct);
static void f_checkSalesTariffStructure(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List, bool v_isMaxEntriesLimit, verdict_val v_vct);
static bool f_compareToPreviousSAScheduleTuple(SAScheduleListType &SASchedule_List, uint8_t SAScheduleTupleId);
static void f_checkPMaxSchedulesTimeIntervals(std::shared_ptr<SECC_Tester> &_mtc, uint32_t DepartureTime, SAScheduleListType &SASchedules, verdict_val v_vct);
static void f_checkACPMaxScheduleEntries(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List, float v_pMax, verdict_val v_vct);
static void f_checkPMaxSchedulesStructure(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List, float maximum_value_physicalValue, bool isMaxEntriesLimit, verdict_val v_vct);

/* static void mdw_SECC_CMN_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode); */

static void md_SECC_AC_ChargeParameterDiscoveryReq_001(std::shared_ptr<V2gTpMessage> &msg,
                                                       uint16_t p_maxEntriesSAScheduleTuple, EnergyTransferModeType p_requestedEnergyTransferMode, uint16_t p_departureTime,
                                                       PhysicalValueType *p_eAmount, PhysicalValueType *p_eVMaxVoltage, PhysicalValueType *p_eVMaxCurrent, PhysicalValueType *p_eVMinCurrent);
static void md_SECC_AC_ChargeParameterDiscoveryReq_002(std::shared_ptr<V2gTpMessage> &msg, EnergyTransferModeType p_requestedEnergyTransferMode);
static void mdw_SECC_AC_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg,
                                                        iso1Part4_EVSEProcessingType p_evseproc, AC_EVSEStatusType *p_aCeVSEStatus, SalesTariffType *p_salesTariff);
static void mdw_SECC_AC_ChargeParameterDiscoveryRes_002(std::shared_ptr<V2gTpMessage> &msg, AC_EVSEStatusType *p_aCeVSEStatus);
/* static void mw_SECC_AC_ChargeParameterDiscoveryRes_003(std::shared_ptr<V2gTpMessage> &msg); */

#define HAS_VAL ((int)0xFFFF)
#define OMIT ((int)0xFFFE)
#define OMIT0 ((uint16_t)0x0)

static void md_SECC_DC_ChargeParameterDiscoveryReq_001(std::shared_ptr<V2gTpMessage> &msg,
                                                       uint16_t p_maxEntriesSAScheduleTuple, EnergyTransferModeType p_requestedEnergyTransferMode, uint16_t p_departureTime,
                                                       DC_EVStatusType *p_dC_EVStatus, PhysicalValueType *p_eVMaximumCurrentLimit, PhysicalValueType *p_eVMaximumPowerLimit, PhysicalValueType *p_eVMaximumVoltageLimit);
static void md_SECC_DC_ChargeParameterDiscoveryReq_002(std::shared_ptr<V2gTpMessage> &msg, EnergyTransferModeType p_requestedEnergyTransferMode);
static void mdw_SECC_DC_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_EVSEProcessingType p_evseproc, iso1Part4_EVSENotificationType p_eVSENotification,
                                                        int p_eVSEStatusCode, SalesTariffType *p_salesTariff);
static void mdw_SECC_DC_ChargeParameterDiscoveryRes_002(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_EVSENotificationType p_eVSENotification, int p_eVSEStatusCode);
/* static void mdw_SECC_DC_ChargeParameterDiscoveryRes_003(std::shared_ptr<V2gTpMessage> &msg); */

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  float v_pMax;

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  // expected respone processin status is finished
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, (AC_EVSEStatusType *)HAS_VAL, (SalesTariffType *)OMIT);
  // expected respone processin status is ongoing
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_002(expectedMsg2, (AC_EVSEStatusType *)HAS_VAL);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_pMax, &v_vct](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto ACChargeParam = cast_received->getACEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          // EVSEProcessing = finished
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // get SAScheduleList
          memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          // get 1st PMaxSchedule val
          memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
          // get 1st SAScheduleID
          memcpy(&this->mtc->vc_SAScheduleTupleId, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID, sizeof(uint8_t));

          // get nominal voltage
          memcpy(&this->mtc->vc_EVSENominalVoltage, &ACChargeParam->EVSENominalVoltage, sizeof(PhysicalValueType));
          // check max nominal voltage
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSENominalVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSENominalVoltage");

          memcpy(&this->mtc->vc_EVSEMaxCurrent, &ACChargeParam->EVSEMaxCurrent, sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaxCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMaxCurrent");

          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          if (this->mtc->vc_requestedEnergyTransferModeAC == (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core)
          {
            // max power value for 3 phase
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent) * 3.0;
          }
          else
          {
            // max power value for 1 phase
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent);
          }
          // check max power schedule provide
          f_checkACPMaxScheduleEntries(this->mtc, this->mtc->vc_SASchedule_List, v_pMax, v_vct);
          // check max power schedule structure
          f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
          if (this->mtc->getverdict() == pass)
          {
            // check time interval of timeschedule
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct.");
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          // response message is EVSEProcessing is ongoing
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
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

  // check requestedEnergyTransferModeAC is supported by supportedTransferMode (from service discovery)
  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      // sending departure time value
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          // not send max entry SA Schedule tuple
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          // send max number of entry SA SChedule
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(v_vct))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(v_vct, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(randomSessionID);
  md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_UnknownSession' is successful.");
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  this->mtc->vc_requestedEnergyTransferModeAC = (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::dC_extended;
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_WrongEnergyTransferMode);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_WrongEnergyTransferMode' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  this->mtc->vc_requestedEnergyTransferModeAC = (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core;
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_SECC_AC_ChargeParameterDiscoveryReq_002(sendMsg, this->mtc->vc_requestedEnergyTransferModeAC);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_WrongChargeParameter);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_WrongChargeParameter' is successful.");
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

  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  float v_pMax;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  // expected respone processin status is finished
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, (AC_EVSEStatusType *)HAS_VAL, (SalesTariffType *)OMIT);
  // expected respone processin status is ongoing
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_002(expectedMsg2, (AC_EVSEStatusType *)HAS_VAL);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_pMax](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto ACChargeParam = cast_received->getACEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // get SAScheduleList
          memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          // get 1st PMaxSchedule val
          memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
          // get 1st SAScheduleID
          memcpy(&this->mtc->vc_SAScheduleTupleId, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID, sizeof(uint8_t));

          // get nominal voltage
          memcpy(&this->mtc->vc_EVSENominalVoltage, &ACChargeParam->EVSENominalVoltage, sizeof(PhysicalValueType));
          // check max nominal voltage
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSENominalVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSENominalVoltage");

          memcpy(&this->mtc->vc_EVSEMaxCurrent, &ACChargeParam->EVSEMaxCurrent, sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaxCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMaxCurrent");

          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          if (this->mtc->vc_requestedEnergyTransferModeAC == (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core)
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent) * 3.0;
          }
          else
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent);
          }

          // check max power schedule provide
          f_checkACPMaxScheduleEntries(this->mtc, this->mtc->vc_SASchedule_List, v_pMax, fail);
          // check max power schedule structure
          f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
          if (this->mtc->getverdict() == pass)
          {
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
          }
          if (this->mtc->getverdict() == pass)
          {
            if (f_compareToPreviousSAScheduleTuple(this->mtc->vc_SASchedule_List, this->mtc->vc_SAScheduleTupleId))
            {
              this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct. A valid SAScheduleTuple was received after paused session.");
            }
            else
            {
              this->mtc->setverdict(fail, "Invalid SAScheduleTuple was received after paused session.");
            }
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }

      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(fail, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  float v_pMax;
  bool isSignatureOk = true;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  // expected respone processin status is finished
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, (AC_EVSEStatusType *)HAS_VAL, (SalesTariffType *)HAS_VAL);
  // expected respone processin status is ongoing
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_002(expectedMsg2, (AC_EVSEStatusType *)HAS_VAL);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_pMax, &v_vct, &isSignatureOk](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto ACChargeParam = cast_received->getACEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // get SAScheduleList
          memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          // get 1st PMaxSchedule val
          memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
          // get 1st SAScheduleID
          memcpy(&this->mtc->vc_SAScheduleTupleId, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID, sizeof(uint8_t));

          // get nominal voltage
          memcpy(&this->mtc->vc_EVSENominalVoltage, &ACChargeParam->EVSENominalVoltage, sizeof(PhysicalValueType));
          // check max nominal voltage
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSENominalVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSENominalVoltage");

          memcpy(&this->mtc->vc_EVSEMaxCurrent, &ACChargeParam->EVSEMaxCurrent, sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaxCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMaxCurrent");

          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          if (this->mtc->vc_requestedEnergyTransferModeAC == (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core)
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent) * 3.0;
          }
          else
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent);
          }
          f_checkACPMaxScheduleEntries(this->mtc, this->mtc->vc_SASchedule_List, v_pMax, v_vct);
          if (this->mtc->getverdict() == pass)
          {
            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkSalesTariffStructure(this->mtc, this->mtc->vc_SASchedule_List, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkSalesTariffTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
          }
          if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::pnC)
          {
            // get digest value from msg body
            std::shared_ptr<iso1Part4_idDigestValueMap> resultIdDigestValueMap = f_calculateIdDigestMapFromBodyType((cast_received->getExiData())->V2G_Message.Body);
            if (resultIdDigestValueMap->digestValue.length() > 0)
            {
              // get signed signature of header
              SignatureType *authSignature = cast_received->getSignature();
              BodyType *chargeParameterResBodyType = &(cast_received->getExiData())->V2G_Message.Body;
              // verify signature
              isSignatureOk = f_verifySignature(chargeParameterResBodyType, authSignature, &this->mtc->vc_contractSignatureCertChain.subCertificates.x509Certificate_list[0], v_vct);
              if (isSignatureOk)
              {
                this->mtc->setverdict(pass, "Valid signature of the sales tariff was received.");
              }
              else
              {
                this->mtc->setverdict(v_vct, "Invalid signature of the sales tariff was received.");
              }
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct.");
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(v_vct))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(v_vct, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  float v_pMax;
  bool isSignatureOk = true;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  // expected respone processin status is finished
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, (AC_EVSEStatusType *)HAS_VAL, (SalesTariffType *)HAS_VAL);
  // expected respone processin status is ongoing
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_002(expectedMsg2, (AC_EVSEStatusType *)HAS_VAL);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_pMax, &isSignatureOk](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto ACChargeParam = cast_received->getACEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // get SAScheduleList
          memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
          // get 1st PMaxSchedule val
          memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
          // get 1st SAScheduleID
          memcpy(&this->mtc->vc_SAScheduleTupleId, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID, sizeof(uint8_t));

          // get nominal voltage
          memcpy(&this->mtc->vc_EVSENominalVoltage, &ACChargeParam->EVSENominalVoltage, sizeof(PhysicalValueType));
          // check max nominal voltage
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSENominalVoltage, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSENominalVoltage");

          memcpy(&this->mtc->vc_EVSEMaxCurrent, &ACChargeParam->EVSEMaxCurrent, sizeof(PhysicalValueType));
          f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaxCurrent, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMaxCurrent");

          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
          }
          if (this->mtc->vc_requestedEnergyTransferModeAC == (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core)
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent) * 3.0;
          }
          else
          {
            v_pMax = f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSENominalVoltage) * f_CMN_PhysicalValue_GetValue(this->mtc->vc_EVSEMaxCurrent);
          }

          f_checkACPMaxScheduleEntries(this->mtc, this->mtc->vc_SASchedule_List, v_pMax, fail);
          if (this->mtc->getverdict() == pass)
          {
            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkSalesTariffStructure(this->mtc, this->mtc->vc_SASchedule_List, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
          }
          if (this->mtc->getverdict() == pass)
          {
            f_checkSalesTariffTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
          }

          if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::pnC)
          {
            std::shared_ptr<iso1Part4_idDigestValueMap> resultIdDigestValueMap = f_calculateIdDigestMapFromBodyType((cast_received->getExiData())->V2G_Message.Body);
            if (resultIdDigestValueMap->digestValue.length() > 0)
            {
              SignatureType *authSignature = cast_received->getSignature();
              BodyType *chargeParameterResBodyType = &(cast_received->getExiData())->V2G_Message.Body;
              isSignatureOk = f_verifySignature(chargeParameterResBodyType, authSignature, &this->mtc->vc_contractSignatureCertChain.subCertificates.x509Certificate_list[0], fail);
              if (isSignatureOk)
              {
                this->mtc->setverdict(pass, "Valid signature of the sales tariff was received.");
              }
              else
              {
                this->mtc->setverdict(fail, "Invalid signature of the sales tariff was received.");
              }
            }
          }
          if (this->mtc->getverdict() == pass)
          {
            if (f_compareToPreviousSAScheduleTuple(this->mtc->vc_SASchedule_List, this->mtc->vc_SAScheduleTupleId))
            {
              this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct. A valid SAScheduleTuple was received after paused session.");
            }
            else
            {
              this->mtc->setverdict(fail, "Invalid SAScheduleTuple was received after paused session.");
            }
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          if (ACChargeParam->AC_EVSEStatus.EVSENotification != (EVSENotificationType)iso1Part4_EVSENotificationType::none_)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSENotification' should be set to 'none_'.");
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(fail, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_AC_TB_VTB_ChargeParameterDiscovery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  // expected respone processin status is finished
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, (AC_EVSEStatusType *)HAS_VAL, (SalesTariffType *)OMIT);
  // expected respone processin status is ongoing
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_AC_ChargeParameterDiscoveryRes_002(expectedMsg2, (AC_EVSEStatusType *)HAS_VAL);
  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(inconc, "Charge parameter information should not be available.");
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_SECC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_SECC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Performance_Timeout - par_CMN_Transmission_Delay);
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, this->mtc->vc_DepartureTime, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
        else
        {
          md_SECC_AC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeAC, OMIT0, &this->mtc->vc_EAmount, &this->mtc->vc_EVMaxVoltage, &this->mtc->vc_EVMaxCurrent, &this->mtc->vc_EVMinCurrent);
        }
      }
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_SECC_Ongoing_Timer->timeout())
        {
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
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool v_receivedOngoing = true;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, iso1Part4_EVSENotificationType::none_, HAS_VAL, (SalesTariffType *)OMIT);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_002(expectedMsg2, iso1Part4_EVSENotificationType::none_, HAS_VAL);

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_receivedOngoing, &v_vct](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto DCChargeParam = cast_received->getDCEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          if (nullptr != cast_received->getSAScheduleList())
          {
            memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            this->mtc->vc_SAScheduleTupleId = this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID;
            memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));

            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (nullptr != DCChargeParam)
          {
            // get/verify max current
            memcpy(&this->mtc->vc_EVSEMaximumCurrentLimit, &DCChargeParam->EVSEMaximumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMaximumCurrentLimit");
            // get/verify max voltage
            memcpy(&this->mtc->vc_EVSEMaximumVoltageLimit, &DCChargeParam->EVSEMaximumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEMaximumVoltageLimit");
            // get/verify max power
            memcpy(&this->mtc->vc_EVSEMaximumPowerLimit, &DCChargeParam->EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumPowerLimit, iso1Part4_UnitSymbolType::w, cc_maximum_value_physicalValue_case4, v_vct, "vc_EVSEMaximumPowerLimit");
            // get/verify min voltage
            memcpy(&this->mtc->vc_EVSEMinimumVoltageLimit, &DCChargeParam->EVSEMinimumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEMinimumVoltageLimit");
            // get/verify min current
            memcpy(&this->mtc->vc_EVSEMinimumCurrentLimit, &DCChargeParam->EVSEMinimumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMinimumCurrentLimit");
            // get/verify peak current ripple
            memcpy(&this->mtc->vc_EVSEPeakCurrentRipple, &DCChargeParam->EVSEPeakCurrentRipple, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPeakCurrentRipple, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEPeakCurrentRipple");

            f_checkEVSEChargeParameter(this->mtc, v_vct);
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct.");
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          v_receivedOngoing = true;
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (1 == DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus_isUsed)
          {
            if (DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::invalid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'invalid'.");
            }
          }
          if (DCChargeParam->DC_EVSEStatus.EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_Ready)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_Ready'.");
          }
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
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

  if (PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing)
  {
    v_receivedOngoing = false;
  }
  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime,
                                                     &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime,
                                                     &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus,
                                                     &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0,
                                                     &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(v_vct))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(v_vct, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (iso1Part4_EVSEProcessingType::ongoing == v_EVSEprocessing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
    if ((PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing) && !(v_receivedOngoing))
    {
      this->mtc->setverdict(inconc, "The SUT did not repeat the ChargeParameter  message sequence.");
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  // load random ID to create session error
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(randomSessionID);
  md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, nullptr, &this->mtc->vc_EVMaximumVoltageLimit);

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_UnknownSession' is successful.");
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  // push incorrect requested energy transfer mode to create error
  md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, OMIT0, &this->mtc->vc_EVMaximumVoltageLimit);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_WrongEnergyTransferMode);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_WrongEnergyTransferMode' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  md_SECC_DC_ChargeParameterDiscoveryReq_002(sendMsg, this->mtc->vc_requestedEnergyTransferModeDC);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_WrongChargeParameter);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->pEVSEChargeParameter_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes with responseCode 'fAILED_WrongChargeParameter' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  bool v_receivedOngoing = true;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, iso1Part4_EVSENotificationType::none_, HAS_VAL, (SalesTariffType *)OMIT);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_002(expectedMsg2, iso1Part4_EVSENotificationType::none_, HAS_VAL);

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_receivedOngoing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto DCChargeParam = cast_received->getDCEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          if (nullptr != cast_received->getSAScheduleList())
          {
            memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));

            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
            f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
            if (this->mtc->getverdict() == pass)
            {
              if (f_compareToPreviousSAScheduleTuple(this->mtc->vc_SASchedule_List, this->mtc->vc_SAScheduleTupleId))
              {
                this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct. A valid SAScheduleTuple was received after paused session.");
              }
              else
              {
                this->mtc->setverdict(fail, "Invalid SAScheduleTuple was received after paused session.");
              }
            }
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (nullptr != DCChargeParam)
          {
            // get/verify max current
            memcpy(&this->mtc->vc_EVSEMaximumCurrentLimit, &DCChargeParam->EVSEMaximumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMaximumCurrentLimit");
            // get/verify max voltage
            memcpy(&this->mtc->vc_EVSEMaximumVoltageLimit, &DCChargeParam->EVSEMaximumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSEMaximumVoltageLimit");
            // get/verify max power
            memcpy(&this->mtc->vc_EVSEMaximumPowerLimit, &DCChargeParam->EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumPowerLimit, iso1Part4_UnitSymbolType::w, cc_maximum_value_physicalValue_case4, fail, "vc_EVSEMaximumPowerLimit");
            // get/verify min voltage
            memcpy(&this->mtc->vc_EVSEMinimumVoltageLimit, &DCChargeParam->EVSEMinimumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSEMinimumVoltageLimit");
            // get/verify min current
            memcpy(&this->mtc->vc_EVSEMinimumCurrentLimit, &DCChargeParam->EVSEMinimumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMinimumCurrentLimit");
            // get/verify peak current ripple
            memcpy(&this->mtc->vc_EVSEPeakCurrentRipple, &DCChargeParam->EVSEPeakCurrentRipple, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPeakCurrentRipple, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEPeakCurrentRipple");

            f_checkEVSEChargeParameter(this->mtc, fail);
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          v_receivedOngoing = true;
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (1 == DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus_isUsed)
          {
            if (DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::invalid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'invalid'.");
            }
          }
          if (DCChargeParam->DC_EVSEStatus.EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_Ready)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_Ready'.");
          }
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
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

  if (PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing)
  {
    v_receivedOngoing = false;
  }
  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(fail, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (iso1Part4_EVSEProcessingType::ongoing == v_EVSEprocessing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
    if ((PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing) && !(v_receivedOngoing))
    {
      this->mtc->setverdict(inconc, "The SUT did not repeat the ChargeParameter  message sequence.");
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isSignatureOk = true;
  bool v_receivedOngoing = true;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, iso1Part4_EVSENotificationType::none_, HAS_VAL, (SalesTariffType *)HAS_VAL);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_002(expectedMsg2, iso1Part4_EVSENotificationType::none_, HAS_VAL);

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_receivedOngoing, &isSignatureOk, &v_vct](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto DCChargeParam = cast_received->getDCEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // check nullptr since Charging Station not response schedule list yet
          if (nullptr != cast_received->getSAScheduleList())
          {
            memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            this->mtc->vc_SAScheduleTupleId = this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID;
            memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
            if (this->mtc->getverdict() == pass)
            {
              f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
            }
            if (this->mtc->getverdict() == pass)
            {
              f_checkSalesTariffStructure(this->mtc, this->mtc->vc_SASchedule_List, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, v_vct);
            }
            if (this->mtc->getverdict() == pass)
            {
              f_checkSalesTariffTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, v_vct);
            }
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::pnC)
          {
            std::shared_ptr<iso1Part4_idDigestValueMap> resultIdDigestValueMap = f_calculateIdDigestMapFromBodyType((cast_received->getExiData())->V2G_Message.Body);
            if (resultIdDigestValueMap->digestValue.length() > 0)
            {
              SignatureType *authSignature = cast_received->getSignature();
              BodyType *chargeParameterResBodyType = &(cast_received->getExiData())->V2G_Message.Body;
              isSignatureOk = f_verifySignature(chargeParameterResBodyType, authSignature, &this->mtc->vc_contractSignatureCertChain.subCertificates.x509Certificate_list[0], v_vct);
              if (isSignatureOk)
              {
                this->mtc->setverdict(pass, "Valid signature of the sales tariff was received.");
              }
              else
              {
                this->mtc->setverdict(v_vct, "Invalid signature of the sales tariff was received.");
              }
            }
          }
          // check nullptr since Charging Station not response charge param
          if (nullptr != DCChargeParam)
          {
            // get/verify max current
            memcpy(&this->mtc->vc_EVSEMaximumCurrentLimit, &DCChargeParam->EVSEMaximumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMaximumCurrentLimit");
            // get/verify max voltage
            memcpy(&this->mtc->vc_EVSEMaximumVoltageLimit, &DCChargeParam->EVSEMaximumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEMaximumVoltageLimit");
            // get/verify max power
            memcpy(&this->mtc->vc_EVSEMaximumPowerLimit, &DCChargeParam->EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumPowerLimit, iso1Part4_UnitSymbolType::w, cc_maximum_value_physicalValue_case4, v_vct, "vc_EVSEMaximumPowerLimit");
            // get/verify min voltage
            memcpy(&this->mtc->vc_EVSEMinimumVoltageLimit, &DCChargeParam->EVSEMinimumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, v_vct, "vc_EVSEMinimumVoltageLimit");
            // get/verify min current
            memcpy(&this->mtc->vc_EVSEMinimumCurrentLimit, &DCChargeParam->EVSEMinimumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEMinimumCurrentLimit");
            // get/verify peak current ripple
            memcpy(&this->mtc->vc_EVSEPeakCurrentRipple, &DCChargeParam->EVSEPeakCurrentRipple, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPeakCurrentRipple, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, v_vct, "vc_EVSEPeakCurrentRipple");

            f_checkEVSEChargeParameter(this->mtc, v_vct);
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct.");
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          v_receivedOngoing = true;
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (1 == DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus_isUsed)
          {
            if (DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::invalid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'invalid'.");
            }
          }
          if (DCChargeParam->DC_EVSEStatus.EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_Ready)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_Ready'.");
          }
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
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

  if (PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing)
  {
    v_receivedOngoing = false;
  }
  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(v_vct))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(v_vct, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (iso1Part4_EVSEProcessingType::ongoing == v_EVSEprocessing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
    if ((PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing) && !(v_receivedOngoing))
    {
      this->mtc->setverdict(inconc, "The SUT did not repeat the ChargeParameter  message sequence.");
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isSignatureOk = true;
  bool v_receivedOngoing = true;
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, iso1Part4_EVSENotificationType::none_, HAS_VAL, (SalesTariffType *)HAS_VAL);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_002(expectedMsg2, iso1Part4_EVSENotificationType::none_, HAS_VAL);

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing, &v_receivedOngoing, &isSignatureOk](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        auto DCChargeParam = cast_received->getDCEVSEChargeParamter();
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          // check nullptr since Charging Station not response schedule list yet
          if (nullptr != cast_received->getSAScheduleList())
          {
            memcpy(&this->mtc->vc_SASchedule_List, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_SASchedules, cast_received->getSAScheduleList(), sizeof(SAScheduleListType));
            memcpy(&this->mtc->vc_PMaxSchedule, &this->mtc->vc_SASchedule_List.SAScheduleTuple.array[0].PMaxSchedule, sizeof(PMaxScheduleType));
            f_checkPMaxSchedulesStructure(this->mtc, this->mtc->vc_SASchedule_List, cc_maximum_value_physicalValue_case4, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
            if (this->mtc->getverdict() == pass)
            {
              f_checkPMaxSchedulesTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
            }
            if (this->mtc->getverdict() == pass)
            {
              f_checkSalesTariffStructure(this->mtc, this->mtc->vc_SASchedule_List, PICS_SECC_CMN_MaxEntriesSAScheduleTuple, fail);
            }
            if (this->mtc->getverdict() == pass)
            {
              f_checkSalesTariffTimeIntervals(this->mtc, this->mtc->vc_DepartureTime, this->mtc->vc_SASchedules, fail);
            }
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (PICS_CMN_CMN_IdentificationMode == iso1Part4_IdentificationMode::pnC)
          {
            std::shared_ptr<iso1Part4_idDigestValueMap> resultIdDigestValueMap = f_calculateIdDigestMapFromBodyType((cast_received->getExiData())->V2G_Message.Body);
            if (resultIdDigestValueMap->digestValue.length() > 0)
            {
              SignatureType *authSignature = cast_received->getSignature();
              BodyType *chargeParameterResBodyType = &(cast_received->getExiData())->V2G_Message.Body;
              isSignatureOk = f_verifySignature(chargeParameterResBodyType, authSignature, &this->mtc->vc_contractSignatureCertChain.subCertificates.x509Certificate_list[0], fail);
              if (isSignatureOk)
              {
                this->mtc->setverdict(pass, "Valid signature of the sales tariff was received.");
              }
              else
              {
                this->mtc->setverdict(fail, "Invalid signature of the sales tariff was received.");
              }
            }
          }
          // check nullptr since Charging Station not response charge param
          if (nullptr != DCChargeParam)
          {
            // get/verify max current
            memcpy(&this->mtc->vc_EVSEMaximumCurrentLimit, &DCChargeParam->EVSEMaximumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMaximumCurrentLimit");
            // get/verify max voltage
            memcpy(&this->mtc->vc_EVSEMaximumVoltageLimit, &DCChargeParam->EVSEMaximumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSEMaximumVoltageLimit");
            // get/verify max power
            memcpy(&this->mtc->vc_EVSEMaximumPowerLimit, &DCChargeParam->EVSEMaximumPowerLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMaximumPowerLimit, iso1Part4_UnitSymbolType::w, cc_maximum_value_physicalValue_case4, fail, "vc_EVSEMaximumPowerLimit");
            // get/verify min voltage
            memcpy(&this->mtc->vc_EVSEMinimumVoltageLimit, &DCChargeParam->EVSEMinimumVoltageLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumVoltageLimit, iso1Part4_UnitSymbolType::v, cc_maximum_value_physicalValue_case2, fail, "vc_EVSEMinimumVoltageLimit");
            // get/verify min current
            memcpy(&this->mtc->vc_EVSEMinimumCurrentLimit, &DCChargeParam->EVSEMinimumCurrentLimit, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEMinimumCurrentLimit, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEMinimumCurrentLimit");
            // get/verify peak current ripple
            memcpy(&this->mtc->vc_EVSEPeakCurrentRipple, &DCChargeParam->EVSEPeakCurrentRipple, sizeof(PhysicalValueType));
            f_check_PhysicalValue_valueRange(this->mtc, this->mtc->vc_EVSEPeakCurrentRipple, iso1Part4_UnitSymbolType::a, cc_maximum_value_physicalValue_case1, fail, "vc_EVSEPeakCurrentRipple");

            f_checkEVSEChargeParameter(this->mtc, fail);
          }
          else
          {
            this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
            return false;
          }
          if (this->mtc->getverdict() == pass)
          {
            if (f_compareToPreviousSAScheduleTuple(this->mtc->vc_SASchedule_List, this->mtc->vc_SAScheduleTupleId))
            {
              this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct. A valid SAScheduleTuple was received after paused session.");
            }
            else
            {
              this->mtc->setverdict(fail, "Invalid SAScheduleTuple was received after paused session.");
            }
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          v_receivedOngoing = true;
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (1 == DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus_isUsed)
          {
            if (DCChargeParam->DC_EVSEStatus.EVSEIsolationStatus != (isolationLevelType)iso1Part4_IsolationLevelType::invalid)
            {
              Logging::error(LogTbFnc_ENABLE, "The field 'eVSEIsolationStatus' should be set to 'invalid'.");
            }
          }
          if (DCChargeParam->DC_EVSEStatus.EVSEStatusCode != (DC_EVSEStatusCodeType)iso1Part4_DC_EVSEStatusCodeType::eVSE_Ready)
          {
            Logging::error(LogTbFnc_ENABLE, "The field 'eVSEStatusCode' should be set to 'eVSE_Ready'.");
          }
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
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

  if (PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing)
  {
    v_receivedOngoing = false;
  }
  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->setverdict(fail, "EVSEProcessing = Finished was not sent in time.");
          break;
        }
      }
      if (iso1Part4_EVSEProcessingType::ongoing == v_EVSEprocessing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
    if ((PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing == iso1Part4_Ongoing::ongoing) && !(v_receivedOngoing))
    {
      this->mtc->setverdict(inconc, "The SUT did not repeat the ChargeParameter  message sequence.");
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_DC_TB_VTB_ChargeParameterDiscovery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  iso1Part4_EVSEProcessingType v_EVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  bool isShutdownOSC = false;

  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ChargeParameterDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ChargeParameterDiscoveryRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<ChargeParameterDiscoveryRes>();

  std::static_pointer_cast<ChargeParameterDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_001(expectedMsg, iso1Part4_EVSEProcessingType::finished, iso1Part4_EVSENotificationType::none_, HAS_VAL, (SalesTariffType *)OMIT);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  mdw_SECC_DC_ChargeParameterDiscoveryRes_002(expectedMsg2, iso1Part4_EVSENotificationType::none_, HAS_VAL);

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_EVSEprocessing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // expected 1: EVSEProcessing = finished
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[0]);
    // expected 2: EVSEProcessing = ongoing
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_expected2 = std::dynamic_pointer_cast<ChargeParameterDiscoveryRes>(expected[1]);
    std::shared_ptr<ChargeParameterDiscoveryRes> cast_received = std::make_shared<ChargeParameterDiscoveryRes>();
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
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(pass, "ChargeParameterDiscoveryRes message was correct.");
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
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

  if (f_checkRequestedEnergyTransfermode(this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_supportedEnergyTransferMode))
  {
    while (v_EVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, this->mtc->vc_DepartureTime, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      else
      {
        if (!PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, OMIT0, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
        else
        {
          md_SECC_DC_ChargeParameterDiscoveryReq_001(sendMsg, par_CMN_MaxEntriesSAScheduleTuple, this->mtc->vc_requestedEnergyTransferModeDC, OMIT0, &this->mtc->vc_DC_EVStatus, &this->mtc->vc_EVMaximumCurrentLimit, &this->mtc->vc_EVMaximumPowerLimit, &this->mtc->vc_EVMaximumVoltageLimit);
        }
      }
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
      while (true)
      {
        if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
        {
          break;
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->isError())
        {
          if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
          {
            v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
            break;
          }
        }
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
        if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
        {
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
          v_EVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (iso1Part4_EVSEProcessingType::ongoing == v_EVSEprocessing)
      {
        Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 1s wait ongoing charge parameter processing"));
        PAsleep(1);
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "Requested energy transfer mode is not supported by the SECC.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ChargeParameterDiscoveryRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_ChargeParameterDiscovery::f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_002()
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

static bool f_checkRequestedEnergyTransfermode(EnergyTransferModeType &v_requestedEnergyTransferMode, SupportedEnergyTransferModeType &v_supportedEnergyTransferMode)
{
  // loop through all supported energy transfer mode
  for (int i = 0; i < v_supportedEnergyTransferMode.EnergyTransferMode.arrayLen; i = i + 1)
  {
    // check if requestedMode is supported
    if (v_supportedEnergyTransferMode.EnergyTransferMode.array[i] == v_requestedEnergyTransferMode)
    {
      return true;
    }
  }
  return false;
}
static void f_checkPMaxSchedulesStructure(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List,
                                          float maximum_value_physicalValue, bool isMaxEntriesLimit, verdict_val v_vct)
{
  for (uint32_t i = 0; i < SASchedule_List.SAScheduleTuple.arrayLen; i = i + 1)
  {
    if ((SASchedule_List.SAScheduleTuple.array[i].SAScheduleTupleID < 1) ||
        (SASchedule_List.SAScheduleTuple.array[i].SAScheduleTupleID > 255))
    {
      _mtc->setverdict(v_vct, "The SUT shall use the values 1 to 255 for the parameter SAScheduleTupleID.");
      break;
    }
    for (uint32_t j = i + 1; j < SASchedule_List.SAScheduleTuple.arrayLen; j = j + 1)
    {
      if (SASchedule_List.SAScheduleTuple.array[i].SAScheduleTupleID ==
          SASchedule_List.SAScheduleTuple.array[j].SAScheduleTupleID)
      {
        _mtc->setverdict(v_vct, "The element 'SAScheduleTupleID' is not unique.");
        break;
      }
    }
    uint32_t listLength = SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.arrayLen;
    if ((listLength > par_CMN_MaxEntriesSAScheduleTuple) && PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
    {
      _mtc->setverdict(v_vct, "The SUT did not have considered 'MaxEntriesSAScheduleTuple' within SAScheduleTuple (PMaxScheduleEntryList).");
      break;
    }
    for (uint32_t k = 0; k < listLength; k = k + 1)
    {
      PhysicalValueType &v_pmax = SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.array[k].PMax;
      f_check_PhysicalValue_valueRange(_mtc, v_pmax, iso1Part4_UnitSymbolType::w, maximum_value_physicalValue, v_vct, fmt::format("Schedule_{0}-PMax_{1}", i, k));
    }
    for (uint32_t n = 0; n < listLength - 1; n = n + 1)
    {
      if (1 == SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.array[n].RelativeTimeInterval.duration_isUsed)
      {
        _mtc->setverdict(v_vct, "The element 'duration' shall only be used for the last interval of the PMaxSchedule.");
        break;
      }
    }
    if (0 == SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.array[listLength - 1].RelativeTimeInterval.duration_isUsed)
    {
      _mtc->setverdict(v_vct, "The element 'duration' shall be used for the last interval of the PMaxSchedule.");
    }
  }
}
static void f_checkACPMaxScheduleEntries(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List, float v_pMax, verdict_val v_vct)
{
  for (int i = 0; i < SASchedule_List.SAScheduleTuple.arrayLen; i = i + 1)
  {
    int listLength = SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.arrayLen;
    for (int m = 0; m < listLength; m = m + 1)
    {
      if (v_pMax < f_CMN_PhysicalValue_GetValue(SASchedule_List.SAScheduleTuple.array[i].PMaxSchedule.PMaxScheduleEntry.array[m].PMax))
      {
        _mtc->setverdict(v_vct, "Invalid PMaxSchedule entry. The SUT did not calculated the PMax values based on the parameter EVSENominalVoltage.");
      }
    }
  }
}
static void f_checkPMaxSchedulesTimeIntervals(std::shared_ptr<SECC_Tester> &_mtc, uint32_t DepartureTime, SAScheduleListType &SASchedules, verdict_val v_vct)
{
  uint32_t v_time24h = 86400;
  for (int i = 0; i < SASchedules.SAScheduleTuple.arrayLen; i = i + 1)
  {
    SAScheduleTupleType *v_scheduleTuple = &SASchedules.SAScheduleTuple.array[i];
    uint32_t v_sumPmaxSchedule = 0;
    int v_start = v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.start;
    int v_stop = v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.array[(v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.arrayLen) - 1].RelativeTimeInterval.start;
    if (1 == v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.array[(v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.arrayLen) - 1].RelativeTimeInterval.duration_isUsed)
    {
      uint32_t v_duration = v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.array[(v_scheduleTuple->PMaxSchedule.PMaxScheduleEntry.arrayLen) - 1].RelativeTimeInterval.duration;
      v_sumPmaxSchedule = v_stop - v_start + v_duration;
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (v_sumPmaxSchedule != DepartureTime)
        {
          _mtc->setverdict(v_vct, "The sum of the individual time intervals (PMaxSchedule) did not match the period of time indicated by the EVCC (DepartureTime).");
        }
      }
      else
      {
        if (v_sumPmaxSchedule < v_time24h)
        {
          _mtc->setverdict(v_vct, "The sum of the individual time intervals (PMaxSchedule) was smaller than 24h.");
        }
      }
    }
  }
}
static bool f_compareToPreviousSAScheduleTuple(SAScheduleListType &SASchedule_List, uint8_t SAScheduleTupleId)
{
  for (int i = 0; i < SASchedule_List.SAScheduleTuple.arrayLen; i = i + 1)
  {
    if (SASchedule_List.SAScheduleTuple.array[0].SAScheduleTupleID == SAScheduleTupleId)
    {
      return true;
    }
  }
  return false;
}
void f_checkSalesTariffStructure(std::shared_ptr<SECC_Tester> &_mtc, SAScheduleListType &SASchedule_List, bool v_isMaxEntriesLimit, verdict_val v_vct)
{
  for (int i = 0; i < SASchedule_List.SAScheduleTuple.arrayLen; i = i + 1)
  {
    uint32_t listLength = SASchedule_List.SAScheduleTuple.array[i].SalesTariff.SalesTariffEntry.arrayLen;
    if ((listLength > par_CMN_MaxEntriesSAScheduleTuple) && PICS_SECC_CMN_MaxEntriesSAScheduleTuple)
    {
      _mtc->setverdict(v_vct, "The SUT did not have considered 'MaxEntriesSAScheduleTuple' within SAScheduleTuple (SalesTariffEntryList).");
      break;
    }
  }
}
static void f_checkSalesTariffTimeIntervals(std::shared_ptr<SECC_Tester> &_mtc, uint32_t DepartureTime, SAScheduleListType &SASchedules, verdict_val v_vct)
{
  uint32_t v_time24h = 86400;
  // loop through all schedule
  for (int i = 0; i < SASchedules.SAScheduleTuple.arrayLen; i = i + 1)
  {
    SAScheduleTupleType *v_scheduleTuple = &SASchedules.SAScheduleTuple.array[i];
    uint32_t v_sumSalesTariff = 0;
    // get start time(first tariff entry start)
    int v_start = v_scheduleTuple->SalesTariff.SalesTariffEntry.array[0].RelativeTimeInterval.start;
    // get end time(last tariff entry start)
    int v_stop = v_scheduleTuple->SalesTariff.SalesTariffEntry.array[v_scheduleTuple->SalesTariff.SalesTariffEntry.arrayLen - 1].RelativeTimeInterval.start;
    if (1 == (v_scheduleTuple->SalesTariff.SalesTariffEntry.array[v_scheduleTuple->SalesTariff.SalesTariffEntry.arrayLen - 1].RelativeTimeInterval.duration_isUsed))
    {
      uint32_t v_duration = v_scheduleTuple->SalesTariff.SalesTariffEntry.array[v_scheduleTuple->SalesTariff.SalesTariffEntry.arrayLen - 1].RelativeTimeInterval.duration;
      v_sumSalesTariff = v_stop - v_start + v_duration;
      if (PICS_SECC_CMN_DepartureTime)
      {
        if (v_sumSalesTariff != DepartureTime)
        {
          _mtc->setverdict(v_vct, "The sum of the individual time intervals (SalesTariff) did not match the period of time indicated by the EVCC (DepartureTime).");
        }
      }
      else
      {
        if (v_sumSalesTariff < v_time24h)
        {
          _mtc->setverdict(v_vct, "The sum of the individual time intervals (SalesTariff) was smaller than 24h.");
        }
      }
    }
  }
}
static void f_checkEVSEChargeParameter(std::shared_ptr<SECC_Tester> &_mtc, verdict_val v_vct)
{
  if ((f_CMN_PhysicalValue_GetValue(_mtc->vc_EVMaximumCurrentLimit) >
       f_CMN_PhysicalValue_GetValue(_mtc->vc_EVSEMaximumCurrentLimit)) ||
      (f_CMN_PhysicalValue_GetValue(_mtc->vc_EVMaximumVoltageLimit) >
       f_CMN_PhysicalValue_GetValue(_mtc->vc_EVSEMaximumVoltageLimit)))
  {
    if (f_CMN_PhysicalValue_GetValue(_mtc->vc_EVTargetVoltage) >
        f_CMN_PhysicalValue_GetValue(_mtc->vc_EVSEMaximumVoltageLimit))
    {
      _mtc->setverdict(v_vct, "Invalid EVSE charging limits. Charging is not possible.");
    }
    else
    {
      Logging::error(LogTbFnc_ENABLE, "The EV maximum limits are higher than the EVSE maximum limits. The EV should adapt the corresponding parameter to the EVSE limits.");
      memcpy(&_mtc->vc_EVMaximumCurrentLimit, &_mtc->vc_EVSEMaximumCurrentLimit, sizeof(PhysicalValueType));
      memcpy(&_mtc->vc_EVMaximumVoltageLimit, &_mtc->vc_EVSEMaximumVoltageLimit, sizeof(PhysicalValueType));
    }
  }
}

static void md_SECC_AC_ChargeParameterDiscoveryReq_001(std::shared_ptr<V2gTpMessage> &msg,
                                                       uint16_t p_maxEntriesSAScheduleTuple,
                                                       EnergyTransferModeType p_requestedEnergyTransferMode,
                                                       uint16_t p_departureTime,
                                                       PhysicalValueType *p_eAmount,
                                                       PhysicalValueType *p_eVMaxVoltage,
                                                       PhysicalValueType *p_eVMaxCurrent,
                                                       PhysicalValueType *p_eVMinCurrent)
{

  AC_EVChargeParameterType temp;
  if (p_maxEntriesSAScheduleTuple != 0)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setMaxEntriesSAScheduleTuple(p_maxEntriesSAScheduleTuple);
  }
  if (0xFF != p_requestedEnergyTransferMode)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setEnergyTransferModeReq(p_requestedEnergyTransferMode);
  }
  if (0 != p_departureTime)
  {
    temp.DepartureTime = p_departureTime;
    temp.DepartureTime_isUsed = 1;
  }
  if (nullptr != p_eAmount)
    memcpy(&temp.EAmount, p_eAmount, sizeof(PhysicalValueType));
  if (nullptr != p_eVMaxVoltage)
    memcpy(&temp.EVMaxVoltage, p_eVMaxVoltage, sizeof(PhysicalValueType));
  if (nullptr != p_eVMaxCurrent)
    memcpy(&temp.EVMaxCurrent, p_eVMaxCurrent, sizeof(PhysicalValueType));
  if (nullptr != p_eVMinCurrent)
    memcpy(&temp.EVMinCurrent, p_eVMinCurrent, sizeof(PhysicalValueType));
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setACEVChargeParamter(&temp);
}

static void md_SECC_AC_ChargeParameterDiscoveryReq_002(std::shared_ptr<V2gTpMessage> &msg, EnergyTransferModeType p_requestedEnergyTransferMode)
{
  AC_EVChargeParameterType temp;
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setEnergyTransferModeReq(p_requestedEnergyTransferMode);
  // omit MaxEntriesSAScheduleTuple
  temp.DepartureTime = 0;
  temp.DepartureTime_isUsed = 0;
  temp.EAmount      = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::w, .Value = 100};
  temp.EVMaxVoltage = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::v, .Value = 400};
  temp.EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = -100};
  temp.EVMinCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 500};
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setACEVChargeParamter(&temp);
}

static void mdw_SECC_AC_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg,
                                                        iso1Part4_EVSEProcessingType p_evseproc, AC_EVSEStatusType *p_aCeVSEStatus, SalesTariffType *p_salesTariff)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)p_evseproc);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;
  // SAScheduleListType
  if (HAS_VAL == (uintptr_t)p_salesTariff)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  }
  else if ((OMIT == (uintptr_t)p_salesTariff) || (nullptr == p_salesTariff))
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  }
  else
  {
    SAScheduleListType schedule;
    memcpy(&schedule.SAScheduleTuple.array[0].SalesTariff, p_salesTariff, sizeof(SalesTariffType));
    schedule.SAScheduleTuple.arrayLen = 1;
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setSAScheduleList(&schedule);
  }
  // AC_EVSEChargeParameterType
  if (HAS_VAL == (uintptr_t)p_aCeVSEStatus)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  }
  else if ((OMIT == (uintptr_t)p_aCeVSEStatus) || (nullptr == p_aCeVSEStatus))
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  }
  else
  {
    AC_EVSEChargeParameterType param;
    memcpy(&param.AC_EVSEStatus, p_aCeVSEStatus, sizeof(AC_EVSEStatusType));
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setACEVSEChargeParameter(&param);
  }

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
}

static void mdw_SECC_AC_ChargeParameterDiscoveryRes_002(std::shared_ptr<V2gTpMessage> &msg, AC_EVSEStatusType *p_aCeVSEStatus)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;
  // SAScheduleListType
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  // AC_EVSEChargeParameterType
  if (HAS_VAL == (uintptr_t)p_aCeVSEStatus)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  }
  else if ((OMIT == (uintptr_t)p_aCeVSEStatus) || (nullptr == p_aCeVSEStatus))
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  }
  else
  {
    AC_EVSEChargeParameterType param;
    memcpy(&param.AC_EVSEStatus, p_aCeVSEStatus, sizeof(AC_EVSEStatusType));
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setACEVSEChargeParameter(&param);
  }

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
}
/* static void mw_SECC_AC_ChargeParameterDiscoveryRes_003(std::shared_ptr<V2gTpMessage> &msg)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;
  // SAScheduleListType
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  // AC_EVSEChargeParameterType
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pAC_EVSEChargeParameter_flag = has_value;

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
} */

static void md_SECC_DC_ChargeParameterDiscoveryReq_001(std::shared_ptr<V2gTpMessage> &msg,
                                                       uint16_t p_maxEntriesSAScheduleTuple, EnergyTransferModeType p_requestedEnergyTransferMode, uint16_t p_departureTime,
                                                       DC_EVStatusType *p_dC_EVStatus, PhysicalValueType *p_eVMaximumCurrentLimit, PhysicalValueType *p_eVMaximumPowerLimit, PhysicalValueType *p_eVMaximumVoltageLimit)
{
  DC_EVChargeParameterType temp;
  if (0 != p_maxEntriesSAScheduleTuple)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setMaxEntriesSAScheduleTuple(p_maxEntriesSAScheduleTuple);
  }
  if (0xFF != p_requestedEnergyTransferMode)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setEnergyTransferModeReq(p_requestedEnergyTransferMode);
  }
  if (0 != p_departureTime)
  {
    temp.DepartureTime = p_departureTime;
    temp.DepartureTime_isUsed = 1;
  }
  if (nullptr != p_dC_EVStatus)
  {
    memcpy(&temp.DC_EVStatus, p_dC_EVStatus, sizeof(DC_EVStatusType));
  }
  if (nullptr != p_eVMaximumCurrentLimit)
  {
    memcpy(&temp.EVMaximumCurrentLimit, p_eVMaximumCurrentLimit, sizeof(PhysicalValueType));
  }
  if (nullptr != p_eVMaximumPowerLimit)
  {
    memcpy(&temp.EVMaximumPowerLimit, p_eVMaximumPowerLimit, sizeof(PhysicalValueType));
    temp.EVMaximumPowerLimit_isUsed = 1;
  }
  if (nullptr != p_eVMaximumVoltageLimit)
  {
    memcpy(&temp.EVMaximumVoltageLimit, p_eVMaximumVoltageLimit, sizeof(PhysicalValueType));
  }
  memset(&temp.EVEnergyCapacity, 0, sizeof(PhysicalValueType));
  temp.EVEnergyCapacity_isUsed = 0;
  memset(&temp.EVEnergyRequest, 0, sizeof(PhysicalValueType));
  temp.EVEnergyRequest_isUsed = 0;
  temp.FullSOC_isUsed = 0;
  temp.FullSOC = 0;
  temp.BulkSOC_isUsed = 0;
  temp.BulkSOC = 0;
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setDCEVChargeParamter(&temp);
}
static void md_SECC_DC_ChargeParameterDiscoveryReq_002(std::shared_ptr<V2gTpMessage> &msg, EnergyTransferModeType p_requestedEnergyTransferMode)
{
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setEnergyTransferModeReq(p_requestedEnergyTransferMode);
  DC_EVChargeParameterType temp;
  memset(&temp, 0, sizeof(DC_EVChargeParameterType));
  temp.DC_EVStatus = {.EVReady = 0, .EVErrorCode = (DC_EVErrorCodeType)(iso1Part4_DC_EVErrorCodeType::nO_ERROR), .EVRESSSOC = 50};
  temp.EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)(iso1Part4_UnitSymbolType::a), .Value = -100};
  temp.EVMaximumVoltageLimit = {.Multiplier = 0, .Unit = (unitSymbolType)(iso1Part4_UnitSymbolType::v), .Value = 400};
  std::static_pointer_cast<ChargeParameterDiscoveryReq>(msg)->setDCEVChargeParamter(&temp);
}
static void mdw_SECC_DC_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_EVSEProcessingType p_evseproc, iso1Part4_EVSENotificationType p_eVSENotification,
                                                        int p_eVSEStatusCode, SalesTariffType *p_salesTariff)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)p_evseproc);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;

  if (HAS_VAL == (uintptr_t)p_salesTariff)
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  }
  else if ((OMIT == (uintptr_t)p_salesTariff) || (nullptr == p_salesTariff))
  {
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  }
  else
  {
    SAScheduleListType schedule;
    memcpy(&schedule.SAScheduleTuple.array[0].SalesTariff, p_salesTariff, sizeof(SalesTariffType));
    schedule.SAScheduleTuple.arrayLen = 1;
    std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setSAScheduleList(&schedule);
  }

  DC_EVSEChargeParameterType param;
  param.DC_EVSEStatus.EVSENotification = (EVSENotificationType)p_eVSENotification;
  if ((OMIT != p_eVSEStatusCode) && (HAS_VAL != p_eVSEStatusCode))
  {
    param.DC_EVSEStatus.EVSEStatusCode = (DC_EVSEStatusCodeType)p_eVSEStatusCode;
  }
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setDCEVSEChargeParameter(&param);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = has_value;

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
}
static void mdw_SECC_DC_ChargeParameterDiscoveryRes_002(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_EVSENotificationType p_eVSENotification, int p_eVSEStatusCode)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  DC_EVSEChargeParameterType param;
  param.DC_EVSEStatus.EVSENotification = (EVSENotificationType)p_eVSENotification;
  if ((OMIT != p_eVSEStatusCode) && (HAS_VAL != p_eVSEStatusCode))
  {
    param.DC_EVSEStatus.EVSEStatusCode = (DC_EVSEStatusCodeType)p_eVSEStatusCode;
  }
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setDCEVSEChargeParameter(&param);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = has_value;

  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
}
/* static void mdw_SECC_DC_ChargeParameterDiscoveryRes_003(std::shared_ptr<V2gTpMessage> &msg)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = has_value;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = has_value;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pAC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
} */

/* static void mdw_SECC_CMN_ChargeParameterDiscoveryRes_001(std::shared_ptr<V2gTpMessage> &msg, iso1Part4_ResponseCodeType p_responseCode)
{
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->setResponseCode((responseCodeType)p_responseCode);
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->mEVSEProcessing_flag = has_value;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pSASchedules_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pAC_EVSEChargeParameter_flag = has_value;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pDC_EVSEChargeParameter_flag = omit;
  std::static_pointer_cast<ChargeParameterDiscoveryRes>(msg)->pEVSEChargeParameter_flag = omit;
} */