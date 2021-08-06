#include "MainTestComponent.h"
#include "TimerCfg.h"
#include "PIXITCfg.h"
// call to system component
using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_2::Timer_par_15118_2;
using namespace urn_iso_15118_2_2013_MsgDataTypes;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;

const char* VERDICT_RESULT[] = {
  [none] = "NONE",
  [pass] = "PASS",
  [inconc] = "INCONCLUDE",
  [fail] = "FAIL",
  [error] = "ERROR"
};

SECC_Tester::SECC_Tester(const std::shared_ptr<IfRuntime>& runtime) {
  this->_pRuntime = runtime;
  this->_ptrService = this->_pRuntime->getService();
  this->pt_TimerManager = std::make_shared<PATimerManager>(this->_ptrService);
  this->tc_V2G_EVCC_Msg_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_Msg_Timer", 0);
  this->tc_EVCC_SDP_Timer = this->pt_TimerManager->createTimer("tc_EVCC_SDP_Timer", par_EVCC_SDP_Timeout);
  this->tc_V2G_EVCC_CommunicationSetup_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_CommunicationSetup_Timer", par_V2G_EVCC_CommunicationSetup_Timeout);
  this->tc_V2G_SECC_CommunicationSetup_Timer = this->pt_TimerManager->createTimer("tc_V2G_SECC_CommunicationSetup_Timer", par_V2G_SECC_CommunicationSetup_Performance_Time);
  this->tc_CMN_TCP_Connection_Termination_Timer = this->pt_TimerManager->createTimer("tc_CMN_TCP_Connection_Termination_Timer", par_CMN_TCP_Connection_Termination_Timeout);
  this->tc_V2G_SECC_Sequence_Timer = this->pt_TimerManager->createTimer("tc_V2G_SECC_Sequence_Timer", 0);
  this->tc_V2G_EVCC_Sequence_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_Sequence_Timer", 0);
  this->tc_V2G_EVCC_Ongoing_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_Ongoing_Timer", par_V2G_EVCC_Ongoing_Timeout);
  this->tc_V2G_SECC_Ongoing_Timer = this->pt_TimerManager->createTimer("tc_V2G_SECC_Ongoing_Timer", par_V2G_EVCC_Ongoing_Performance_Timeout - par_CMN_Transmission_Delay);
  this->tc_V2G_EVCC_CableCheck_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_CableCheck_Timer", par_V2G_EVCC_CableCheck_Timeout);
  this->tc_V2G_EVCC_PreCharge_Timer = this->pt_TimerManager->createTimer("tc_V2G_EVCC_PreCharge_Timer", par_V2G_EVCC_PreCharge_Timeout);
  this->tc_TP_EV_vald_state_duration = this->pt_TimerManager->createTimer("tc_TP_EV_vald_state_duration", par_CMN_waitForNextHAL);
  this->tc_T_conn_max_comm = this->pt_TimerManager->createTimer("tc_T_conn_max_comm", 0);

  //sessionID
  this->vc_eVCCID.reserve(6); // mac address of evcc
  this->vc_eVCCID.assign({0x00, 0x01, 0x87, 0x00, 0x00, 0x1A});
  this->vc_SessionID.reserve(8); // session ID
  this->vc_SessionID.assign(8, 0);
  this->vc_EvseId = ""; // mac address of evse
  this->vc_ServiceId = 0; // selected service id (1 = charging service)
  this->vc_testCaseSpecific = true;
  this->vc_receiptRequired = false;

  // 61851
  this->vc_validDutyCycleUpperBound2 = 0;
  this->vc_validDutyCycleLowerBound2 = 0;

  // tcp
  this->vc_isTcpPortClosed = true;
  this->vc_v2g_tcp_tls_parameter = std::make_shared<iso1Part4_V2G_TCP_TLS_Parameter>();

  // udp
  this->vc_V2G_Port_IpAddress = "";
  this->vc_V2G_Port_PortNumber = 15118;
  this->vc_Security = 0;
  this->vc_maxRepetitionSDP = 5;

  // support app protocol
  this->vc_Supported_ISO_Namespace = "urn:iso:15118:2:2013:MsgDef";
  this->vc_Supported_DIN_Namespace = "urn:din:70121:2012:MsgDef";
  this->vc_Supported_ISO2_Namespace = "urn:iso:15118:2:2016:MsgDef";
  this->vc_versionNumberMajor = 2;
  this->vc_versionNumberMinor = 0;

  // service discovery
  init_iso1ServiceListType(&this->vc_serviceList);
  init_iso1ChargeServiceType(&this->vc_chargeService);
  init_iso1PaymentOptionListType(&this->vc_paymentOptionList);
  init_iso1SupportedEnergyTransferModeType(&this->vc_supportedEnergyTransferMode);
  this->vc_SelectedPaymentOption = (paymentOptionType)iso1Part4_PaymentOptionType::contract;

  // authorization
  this->vc_contractPrivateKey = "";
  this->vc_GenChallenge = {0};

  // charging params discovery
  this->vc_ChargeProgress = iso1Part4_ChargeProgressType::start_;
  this->vc_EVSENotification = iso1Part4_EVSENotificationType::none_;
  this->vc_requestedEnergyTransferModeAC = (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::aC_three_phase_core;
  this->vc_requestedEnergyTransferModeDC = (EnergyTransferModeType)iso1Part4_EnergyTransferModeType::dC_extended;
  this->vc_DepartureTime = 50;//86400;
  this->vc_EAmount = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::w, .Value=30000};
  this->vc_SAScheduleTupleId = 0;
  init_iso1SAScheduleListType(&this->vc_SASchedule_List);
  init_iso1SAScheduleListType(&this->vc_SASchedules);
  init_iso1PMaxScheduleType(&this->vc_PMaxSchedule);
  this->vc_EVMaxVoltage = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=500}; // AC?
  this->vc_EVMaxCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=32}; // AC?
  this->vc_EVMinCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=1};
  this->vc_EVSEMaxCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=0};
  this->vc_EVSENominalVoltage= {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=0};

  /* receive value from evse ChargeParameterDiscoveryRes */
  this->vc_EVSEMaximumCurrentLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=0};
  this->vc_EVSEMinimumCurrentLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=0};
  this->vc_EVSEMaximumVoltageLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=0};
  this->vc_EVSEMinimumVoltageLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=0};
  this->vc_EVSEMaximumPowerLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::w, .Value=0};
  this->vc_EVSEPeakCurrentRipple = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=0};

  this->vc_EVTargetVoltage = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=500};
  this->vc_EVTargetCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=2};
  this->vc_EVPreChargeTargetCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=2};
  this->vc_EVSEPresentVoltage = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=0};
  this->vc_EVSEPresentCurrent = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=0};

  memcpy(&this->vc_EVMaximumVoltageLimit, &par_EVMaximumVoltageLimit, sizeof(PhysicalValueType));
  // this->vc_EVMaximumVoltageLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::v, .Value=550};
  memcpy(&this->vc_EVMaximumCurrentLimit, &par_EVMaximumCurrentLimit, sizeof(PhysicalValueType));
  // this->vc_EVMaximumCurrentLimit = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::a, .Value=110};
  this->vc_EVMaximumPowerLimit = {.Multiplier=2, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::wh, .Value=605};
  init_iso1MeterInfoType(&this->vc_MeterInfo);
  init_iso1DC_EVStatusType(&this->vc_DC_EVStatus);
  /* State of charge of the EV’s battery */
  this->vc_DC_EVStatus.EVReady = true;
  this->vc_DC_EVStatus.EVRESSSOC = 0;
  this->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)(iso1Part4_DC_EVErrorCodeType::nO_ERROR);

  this->vc_DC_remainingTimeToBulkSoC = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::h, .Value=1};
  this->vc_DC_remainingTimeToFullSoC = {.Multiplier=0, .Unit=(unitSymbolType)iso1Part4_UnitSymbolType::h, .Value=1};
  Logging::debug(LogComponent_ENABLE, "[MTC]: SECC Tester component created");
}


SECC_Tester::~SECC_Tester() {
  this->tc_V2G_EVCC_Msg_Timer.reset();
  this->tc_EVCC_SDP_Timer.reset();
  this->tc_V2G_EVCC_CommunicationSetup_Timer.reset();
  this->tc_V2G_SECC_CommunicationSetup_Timer.reset();
  this->tc_CMN_TCP_Connection_Termination_Timer.reset();
  this->tc_V2G_SECC_Sequence_Timer.reset();
  this->tc_V2G_EVCC_Sequence_Timer.reset();
  this->tc_V2G_EVCC_Ongoing_Timer.reset();
  this->tc_V2G_SECC_Ongoing_Timer.reset();
  this->tc_V2G_EVCC_CableCheck_Timer.reset();
  this->tc_V2G_EVCC_PreCharge_Timer.reset();
  this->tc_TP_EV_vald_state_duration .reset();
  this->tc_T_conn_max_comm.reset();
  this->pt_TimerManager.reset();
  this->pt_V2G_TCP_TLS_ALM_SECC_Port = nullptr;
  this->pt_V2G_UDP_SDP_Port = nullptr;
  this->pt_HAL_61851_Port = nullptr;
  this->pt_HAL_61851_Internal_Port = nullptr;
  this->pt_SLAC_Port = nullptr;
  Logging::debug(LogComponent_ENABLE, "[MTC]: SECC Tester disposed");
}

bool SECC_Tester::create(std::string &component_name)
{
  // nothings
  return true;
}

bool SECC_Tester::start()
{
  return true;
}

bool SECC_Tester::stop()
{
  return true;
}

void SECC_Tester::kill()
{

}

verdict_val SECC_Tester::dumpverdict() {
  std::string temp;
  for (auto &&i : this->tc_verdict.msg_list)
  {
    temp.append(fmt::format("{}\n",i));
  }
  Logging::info(0, fmt::format("VERDICT: {0}\n{1}", VERDICT_RESULT[this->tc_verdict.value], temp));
  return this->clearverdict();
}
// Table 29: Overwriting rules for the verdict
// Current value     New verdict assignment value
//  of Verdict
//   ----              pass    inconc  fail  none
//   None              pass    inconc  fail  none
//   Pass              pass    inconc  fail  pass
//   Inconc            inconc  inconc  fail  inconc
//   Fail              fail    fail    fail  fail
void SECC_Tester::setverdict(const verdicttype &verdict) {
  std::string temp;
  for (auto &&i : verdict.msg_list)
  {
    temp.append(fmt::format("{}\n",i));
  }
  this->tc_verdict = verdict;
  Logging::info(0, fmt::format("[MTC]: Verdict: {0}\n{1}", VERDICT_RESULT[this->tc_verdict.value], temp));
}
void SECC_Tester::setverdict(const verdict_val val) {
  this->tc_verdict = val;
  std::string temp;
  for (auto &&i : this->tc_verdict.msg_list)
  {
    temp.append(fmt::format("{}\n",i));
  }
  Logging::info(0, fmt::format("[MTC]: Verdict: {0}\n{1}", VERDICT_RESULT[this->tc_verdict.value], temp));
}
void SECC_Tester::setverdict(const verdict_val val, const std::string &message) {
  this->tc_verdict = val;
  if (!this->tc_verdict.msg_list.empty()) {
    if (this->tc_verdict.msg_list.back().compare(message) != 0) {
      this->tc_verdict.msg_list.emplace_back(message);
    }
  }
  else {
    this->tc_verdict.msg_list.emplace_back(message);
  }
  Logging::info(0, fmt::format("[MTC]: Verdict: {0}\n{1}", VERDICT_RESULT[this->tc_verdict.value], message));
}
verdict_val SECC_Tester::getverdict() {
  return this->tc_verdict.value;
}
verdict_val SECC_Tester::clearverdict(void) {
  verdict_val res = this->tc_verdict.value;
  this->tc_verdict.value = none;
  this->tc_verdict.msg_list.clear();
  return res;
}