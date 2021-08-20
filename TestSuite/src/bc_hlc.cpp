#include "runTC.h"
#include <time.h>
#include <regex>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <algorithm>
#include <SeccBasicSignaling.h>

using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118::PICS_EVCC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_EVCC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_EVCC_Tester;
using namespace DataStructure_PICS_15118;
using namespace DataStructure_PIXIT_15118_2;
using namespace DataStructure_PIXIT_15118;

using namespace rapidjson;

#define IPV6_ADDR "ff02::01"
#define IPV6_PORT 15118
// global data
std::shared_ptr<IfRuntime> runenv;
std::shared_ptr<SECC_Tester> mtc;
std::shared_ptr<System_SECC> stc;
std::shared_ptr<Configuration_15118_2> cfg;
std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
std::shared_ptr<PreConditions_SECC_15118_2> pre;
std::shared_ptr<PostConditions_SECC_15118_2> post;
LogLevelType log_level_cfg = LOG_INFO;
LogOutputType log_output_cfg = LOG_OUT_FILE;
std::map<std::string, float *> SLAC_TIMER_MAP = {
    {"TP_EV_vald_state_duration", &Plc::TP_EV_vald_state_duration},
    {"TP_EV_vald_toggle", &Plc::TP_EV_vald_toggle},
    {"TP_EV_SLAC_init", &Plc::TP_EV_SLAC_init}};
std::map<std::string, uint8_t *> SLAC_THRESHOLD_MAP = {
    {"C_EV_vald_nb_toggles", &Plc::C_EV_vald_nb_toggles},
    {"C_EV_match_signalattn_direct", &Plc::C_EV_match_signalattn_direct},
    {"C_EV_match_signalattn_indirect", &Plc::C_EV_match_signalattn_indirect}};
std::map<std::string, float *> TIMER_MAP =
    {
        {"par_TP_EV_vald_state_duration", &par_TP_EV_vald_state_duration},
        {"par_T_conn_max_comm", &par_T_conn_max_comm},
        {"par_CMN_Transmission_Delay", &par_CMN_Transmission_Delay},
        {"par_CMN_HAL_Timeout", &par_CMN_HAL_Timeout},
        {"par_CMN_waitForNextHAL", &par_CMN_waitForNextHAL},
        {"par_CMN_Intern_PTC_Timeout", &par_CMN_Intern_PTC_Timeout},
        {"par_CMN_setKey", &par_CMN_setKey},
        {"par_EVCC_waitForNextTC", &par_EVCC_waitForNextTC},
        {"par_SECC_waitForNextTC", &par_SECC_waitForNextTC},
        {"par_SECC_T_step_X1", &par_SECC_T_step_X1},
        {"par_SECC_Pmax0W", &par_SECC_Pmax0W},
        {"par_V2G_SECC_Sequence_Timeout", &par_V2G_SECC_Sequence_Timeout},
        {"par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq", &par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq},
        {"par_V2G_EVCC_Msg_Timeout_SessionSetupReq", &par_V2G_EVCC_Msg_Timeout_SessionSetupReq},
        {"par_V2G_EVCC_Msg_Timeout_ServiceDiscoveryReq", &par_V2G_EVCC_Msg_Timeout_ServiceDiscoveryReq},
        {"par_V2G_EVCC_Msg_Timeout_ServiceDetailReq", &par_V2G_EVCC_Msg_Timeout_ServiceDetailReq},
        {"par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq", &par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq},
        {"par_V2G_EVCC_Msg_Timeout_CertificateInstallationReq", &par_V2G_EVCC_Msg_Timeout_CertificateInstallationReq},
        {"par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq", &par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq},
        {"par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq", &par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq},
        {"par_V2G_EVCC_Msg_Timeout_AuthorizationReq", &par_V2G_EVCC_Msg_Timeout_AuthorizationReq},
        {"par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq", &par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq},
        {"par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq", &par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq},
        {"par_V2G_EVCC_Msg_Timeout_ChargingStatusReq", &par_V2G_EVCC_Msg_Timeout_ChargingStatusReq},
        {"par_V2G_EVCC_Msg_Timeout_MeteringReceiptReq", &par_V2G_EVCC_Msg_Timeout_MeteringReceiptReq},
        {"par_V2G_EVCC_Msg_Timeout_SessionStopReq", &par_V2G_EVCC_Msg_Timeout_SessionStopReq},
        {"par_V2G_EVCC_Msg_Timeout_CableCheckReq", &par_V2G_EVCC_Msg_Timeout_CableCheckReq},
        {"par_V2G_EVCC_Msg_Timeout_PreChargeReq", &par_V2G_EVCC_Msg_Timeout_PreChargeReq},
        {"par_V2G_EVCC_Msg_Timeout_CurrentDemandReq", &par_V2G_EVCC_Msg_Timeout_CurrentDemandReq},
        {"par_V2G_EVCC_Msg_Timeout_WeldingDetectionReq", &par_V2G_EVCC_Msg_Timeout_WeldingDetectionReq},
        {"par_V2G_EVCC_Ongoing_Timeout", &par_V2G_EVCC_Ongoing_Timeout},
        {"par_V2G_EVCC_Ongoing_Performance_Timeout", &par_V2G_EVCC_Ongoing_Performance_Timeout},
        {"par_V2G_EVCC_CommunicationSetup_Timeout", &par_V2G_EVCC_CommunicationSetup_Timeout},
        {"par_V2G_SECC_CommunicationSetup_Performance_Time", &par_V2G_SECC_CommunicationSetup_Performance_Time},
        {"par_V2G_EVCC_CableCheck_Timeout", &par_V2G_EVCC_CableCheck_Timeout},
        {"par_V2G_EVCC_PreCharge_Timeout", &par_V2G_EVCC_PreCharge_Timeout},
        {"par_EVCC_SDP_Timeout", &par_EVCC_SDP_Timeout},
        {"par_SECC_B1_B2_Timeout", &par_SECC_B1_B2_Timeout},
        {"par_SECC_chargingLoop_pause", &par_SECC_chargingLoop_pause},
        {"par_V2G_SECC_CPState_Error_Detection_Timeout", &par_V2G_SECC_CPState_Error_Detection_Timeout},
        {"par_V2G_SECC_CPState_Detection_Timeout", &par_V2G_SECC_CPState_Detection_Timeout},
        {"par_CMN_TCP_Connection_Termination_Timeout", &par_CMN_TCP_Connection_Termination_Timeout}};
std::map<std::string, void *> PICS_MAP =
    {
        {"par_CMN_MaxEntriesSAScheduleTuple", (void *)&par_CMN_MaxEntriesSAScheduleTuple},
        {"PICS_CMN_CMN_CombinedTesting", (void *)&PICS_CMN_CMN_CombinedTesting},
        {"PICS_CMN_CMN_ChargingMode", (void *)&PICS_CMN_CMN_ChargingMode},
        {"PICS_CMN_CMN_IdentificationMode", (void *)&PICS_CMN_CMN_IdentificationMode},
        {"PICS_CMN_CMN_PlugType", (void *)&PICS_CMN_CMN_PlugType},
        {"PICS_CMN_AC_CableCapability", (void *)&PICS_CMN_AC_CableCapability},
        {"PICS_CMN_CMN_WakeUp", (void *)&PICS_CMN_CMN_WakeUp},
        {"PICS_SECC_CMN_Pause", (void *)&PICS_SECC_CMN_Pause},
        {"PICS_SECC_CMN_EIMDone", (void *)&PICS_SECC_CMN_EIMDone},
        {"PICS_EVCC_CMN_PmaxSchedulewithZeroPow", (void *)&PICS_EVCC_CMN_PmaxSchedulewithZeroPow},
        {"PICS_CMN_CMN_V2gtpSdp", (void *)&PICS_CMN_CMN_V2gtpSdp},
        {"PICS_CMN_CMN_V2gtpV2g", (void *)&PICS_CMN_CMN_V2gtpV2g},
        {"PICS_CMN_CMN_Renegotiation", (void *)&PICS_CMN_CMN_Renegotiation},
        {"PICS_CMN_CMN_RenegotiationLoopIndication", (void *)&PICS_CMN_CMN_RenegotiationLoopIndication},
        {"PICS_CMN_CMN_LoopCounter", (void *)&PICS_CMN_CMN_LoopCounter},
        {"PICS_CMN_CMN_InvalidV2gtpDataFields", (void *)&PICS_CMN_CMN_InvalidV2gtpDataFields},
        {"PICS_CMN_CMN_SDPTimeoutsAndInvalidData", (void *)&PICS_CMN_CMN_SDPTimeoutsAndInvalidData},
        {"PICS_CMN_CMN_FailedResponseCodes", (void *)&PICS_CMN_CMN_FailedResponseCodes},
        {"PICS_CMN_CMN_V2gTimeouts", (void *)&PICS_CMN_CMN_V2gTimeouts},
        {"PICS_CMN_CMN_PkiName", (void *)&PICS_CMN_CMN_PkiName},
        {"par_EVRESSSOC", (void *)&par_EVRESSSOC},
        {"PICS_SECC_CMN_EvStateInChargeProgress", (void *)&PICS_SECC_CMN_EvStateInChargeProgress},
        {"PICS_SECC_DC_WeldingDetection", (void *)&PICS_SECC_DC_WeldingDetection},
        {"PICS_SECC_CMN_DepartureTime", (void *)&PICS_SECC_CMN_DepartureTime},
        {"PICS_SECC_CMN_MaxEntriesSAScheduleTuple", (void *)&PICS_SECC_CMN_MaxEntriesSAScheduleTuple},
        {"PICS_EVCC_CMN_ReceiptRequired", (void *)&PICS_EVCC_CMN_ReceiptRequired},
        {"PICS_EVCC_CMN_InvalidStatesAndDutyCycles", (void *)&PICS_EVCC_CMN_InvalidStatesAndDutyCycles},
        {"PICS_EVCC_CMN_InvalidV2GMessages", (void *)&PICS_EVCC_CMN_InvalidV2GMessages},
        {"PICS_CMN_EVCC_SalesTariff", (void *)&PICS_CMN_EVCC_SalesTariff}};
std::map<std::string, void *> PIXIT_MAP =
    {
        {"PIXIT_CMN_CMN_WakeUp", (void *)&PIXIT_CMN_CMN_WakeUp},
        {"PIXIT_EVCC_CMN_Pause", (void *)&PIXIT_EVCC_CMN_Pause},
        {"PIXIT_CMN_CMN_PkiName", (void *)&PIXIT_CMN_CMN_PkiName},
        {"PIXIT_CMN_CMN_Renegotiation", (void *)&PIXIT_CMN_CMN_Renegotiation},
        {"PIXIT_CMN_CMN_MeterReading", (void *)&PIXIT_CMN_CMN_MeterReading},
        {"par_EVBatteryVoltage", (void *)&par_EVBatteryVoltage},
        {"par_EVMaximumVoltageLimit", (void *)&par_EVMaximumVoltageLimit},
        {"par_EVMaximumCurrentLimit", (void *)&par_EVMaximumCurrentLimit},
        {"par_ValidDeviationPerCent", (void *)&par_ValidDeviationPerCent},
        {"par_LoadStartValCurrent", (void *)&par_LoadStartValCurrent},
        {"par_EVBatteryStepSize", (void *)&par_EVBatteryStepSize},
        {"PIXIT_SECC_CMN_VAS", (void *)&PIXIT_SECC_CMN_VAS},
        {"PIXIT_SECC_CMN_ReceiptRequired", (void *)&PIXIT_SECC_CMN_ReceiptRequired},
        {"PIXIT_SECC_CMN_CertificateHandling", (void *)&PIXIT_SECC_CMN_CertificateHandling},
        {"PIXIT_SECC_CMN_SalesTariff", (void *)&PIXIT_SECC_CMN_SalesTariff},
        {"PIXIT_SECC_CMN_TLS", (void *)&PIXIT_SECC_CMN_TLS},
        {"PIXIT_SECC_CMN_VersionNumberMinor", (void *)&PIXIT_SECC_CMN_VersionNumberMinor},
        {"PIXIT_SECC_CMN_InternetAccess", (void *)&PIXIT_SECC_CMN_InternetAccess},
        {"PIXIT_SECC_DC_CableCheckOngoing", (void *)&PIXIT_SECC_DC_CableCheckOngoing},
        {"PIXIT_SECC_CMN_AuthorizationOngoing", (void *)&PIXIT_SECC_CMN_AuthorizationOngoing},
        {"PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing", (void *)&PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing},
        {"PIXIT_SECC_CMN_MeterInfo", (void *)&PIXIT_SECC_CMN_MeterInfo},
        {"PIXIT_SECC_CMN_PaymentOption", (void *)&PIXIT_SECC_CMN_PaymentOption},
        {"PIXIT_EVCC_CMN_VAS", (void *)&PIXIT_EVCC_CMN_VAS},
        {"PIXIT_EVCC_DC_WeldingDetection", (void *)&PIXIT_EVCC_DC_WeldingDetection},
        {"PIXIT_EVCC_CMN_TLS", (void *)&PIXIT_EVCC_CMN_TLS},
        {"PIXIT_EVCC_CMN_CertificateHandling", (void *)&PIXIT_EVCC_CMN_CertificateHandling},
        {"PIXIT_EVCC_CMN_DepartureTime", (void *)&PIXIT_EVCC_CMN_DepartureTime},
        {"PIXIT_EVCC_AC_MaxNumberOfPhasesInUse", (void *)&PIXIT_EVCC_AC_MaxNumberOfPhasesInUse},
        {"PIXIT_EVCC_CMN_ChargingProfileOptimization", (void *)&PIXIT_EVCC_CMN_ChargingProfileOptimization},
        {"PIXIT_EVCC_CMN_NewSAScheduleTupleID", (void *)&PIXIT_EVCC_CMN_NewSAScheduleTupleID},
        {"PIXIT_EVCC_CMN_SAScheduleTupleIDMR", (void *)&PIXIT_EVCC_CMN_SAScheduleTupleIDMR}};

static void init_tc(const std::string &testcase_name)
{
  std::time_t curr_time = std::time(nullptr);
  std::string logfile = fmt::format("{0}_{1:%Y_%m_%d-%H_%M_%S}.log", testcase_name, fmt::localtime(curr_time));
  CppCommon::Path path = CppCommon::Path("/home/pi/v2glog");
  if (!path.IsExists())
    CppCommon::Directory::Create(path);

  Logging::setLogFile(fmt::format("/home/pi/v2glog/{}", logfile));
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(log_level_cfg);
  Logging::setLogOutput(log_output_cfg);
  runenv = std::make_shared<IfRuntime>();
  stc = std::make_shared<System_SECC>(runenv, IPV6_ADDR, IPV6_PORT, "eth1", "/home/pi/pev.ini");
  stc->start();
  mtc = std::make_shared<SECC_Tester>(runenv);
  mtc->start();
  cfg = std::make_shared<Configuration_15118_2>(mtc);
  cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(mtc);
  pre = std::make_shared<PreConditions_SECC_15118_2>(mtc, stc, cfg);
  post = std::make_shared<PostConditions_SECC_15118_2>(mtc, stc);

}
static void deinit_tc()
{
  post.reset();
  pre.reset();
  cmn.reset();
  cfg.reset();
  mtc.reset();
  stc.reset();
  runenv.reset();
  Logging::closeLogFile();
}

std::set<std::string> MODE_CMD = {"A", "B", "C", "D", "START", "STOP", "BC", "HLC", "DI", "SH", "PE"};
std::map<std::string, DataStructure_HAL_61851::IEC_61851_States> CP_STATE_MAP = {
  {"A", A},
  {"B", B},
  {"C", C},
  {"D", D}
};
std::map<std::string, std::pair<SeccBasicSignaling::relay_pin_t, SeccBasicSignaling::relay_val_t>> CP_ERROR_MAP = {
  {"SH", {SeccBasicSignaling::relay_pin_t::RELAY_SHORT_CIRCUIT, SeccBasicSignaling::relay_val_t::RELAY_VAL_ON}},
  {"DI", {SeccBasicSignaling::relay_pin_t::RELAY_DIODE, SeccBasicSignaling::relay_val_t::RELAY_VAL_ON}},
  {"PE", {SeccBasicSignaling::relay_pin_t::RELAY_PE_LINE, SeccBasicSignaling::relay_val_t::RELAY_VAL_OFF}}
};
std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;

void bc_start(void);
void bc_stop(void);
void hlc_start(void);
void hlc_stop(void);

int main(int argc, const char *argv[])
{
  log_level_cfg = LOG_INFO;
  if (argc > 1) {
    if (strcmp(argv[1],"D") == 0) {
      log_level_cfg = LOG_DEBUG;
      log_output_cfg = LOG_OUT_BOTH;
    }
  }
  // load json configuration data
  std::ifstream ifs;
  if (argc > 2)
  {
    ifs.open(argv[2], std::ios_base::in);
  }
  else
  {
    ifs.open("/home/pi/testconfig.json", std::ios_base::in);
  }
  if (!ifs.good())
  {
    return -1;
  }
  IStreamWrapper isw(ifs);
  Document document;
  // dom tree
  document.ParseStream(isw);
  for (auto it = document["timer"].MemberBegin(); it < document["timer"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    *(TIMER_MAP[val_name]) = (*it).value.GetFloat();
  }

  for (auto it = document["pics"].MemberBegin(); it < document["pics"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    if ((*it).value.IsBool())
    {
      *(static_cast<bool *>(PICS_MAP[val_name])) = (*it).value.GetBool();
    }
    else if ((*it).value.IsNumber())
    {
      if (!val_name.compare("PICS_CMN_CMN_ChargingMode"))
      {
        *(static_cast<iso1Part4_ChargingMode *>(PICS_MAP[val_name])) = static_cast<iso1Part4_ChargingMode>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_CMN_CMN_IdentificationMode"))
      {
        *(static_cast<iso1Part4_IdentificationMode *>(PICS_MAP[val_name])) = static_cast<iso1Part4_IdentificationMode>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_CMN_CMN_PlugType"))
      {
        *(static_cast<iso1Part4_PlugType *>(PICS_MAP[val_name])) = static_cast<iso1Part4_PlugType>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_CMN_AC_CableCapability"))
      {
        *(static_cast<iso1Part4_CableCapabilityACType *>(PICS_MAP[val_name])) = static_cast<iso1Part4_CableCapabilityACType>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_SECC_CMN_EIMDone"))
      {
        *(static_cast<iso1Part4_EIMDone *>(PICS_MAP[val_name])) = static_cast<iso1Part4_EIMDone>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_EVCC_CMN_PmaxSchedulewithZeroPow"))
      {
        *(static_cast<iso1Part4_ZeroPow *>(PICS_MAP[val_name])) = static_cast<iso1Part4_ZeroPow>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_CMN_CMN_PkiName"))
      {
        *(static_cast<iso1Part4_PkiType *>(PICS_MAP[val_name])) = static_cast<iso1Part4_PkiType>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_SECC_CMN_EvStateInChargeProgress"))
      {
        *(static_cast<IEC_61851_States *>(PICS_MAP[val_name])) = static_cast<IEC_61851_States>((*it).value.GetInt());
      }
      else if (!val_name.compare("par_EVRESSSOC"))
      {
        *(static_cast<int8_t *>(PICS_MAP[val_name])) = static_cast<int8_t>((*it).value.GetInt());
      }
      else if (!val_name.compare("PICS_CMN_CMN_WakeUp"))
      {
        *(static_cast<float *>(PICS_MAP[val_name])) = static_cast<float>((*it).value.GetFloat());
      }
      else
      {
        *(static_cast<uint32_t *>(PICS_MAP[val_name])) = static_cast<uint32_t>((*it).value.GetInt());
      }
    }
  }
  for (auto it = document["pixit"].MemberBegin(); it < document["pixit"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    if ((*it).value.IsBool())
    {
      *(static_cast<bool *>(PIXIT_MAP[val_name])) = (*it).value.GetBool();
    }
    else if ((*it).value.IsNumber())
    {
      if (!val_name.compare("PIXIT_EVCC_CMN_Pause"))
      {
        *(static_cast<iso1Part4_Pause *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_Pause>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_CMN_CMN_PkiName"))
      {
        *(static_cast<iso1Part4_PkiType *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_PkiType>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_CMN_CMN_Renegotiation"))
      {
        *(static_cast<iso1Part4_Renegotiation *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_Renegotiation>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_CMN_CMN_MeterReading"))
      {
        *(static_cast<iso1Part4_MeterReading *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_MeterReading>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_VAS"))
      {
        *(static_cast<iso1Part4_VASSECC *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_VASSECC>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_CertificateHandling"))
      {
        *(static_cast<iso1Part4_CertificateHandlingSECC *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_CertificateHandlingSECC>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_SalesTariff"))
      {
        *(static_cast<iso1Part4_SalesTariff *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_SalesTariff>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_InternetAccess"))
      {
        *(static_cast<iso1Part4_InternetAccess *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_InternetAccess>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_DC_CableCheckOngoing"))
      {
        *(static_cast<iso1Part4_Ongoing *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_Ongoing>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_AuthorizationOngoing"))
      {
        *(static_cast<iso1Part4_Ongoing *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_Ongoing>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing"))
      {
        *(static_cast<iso1Part4_Ongoing *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_Ongoing>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_MeterInfo"))
      {
        *(static_cast<iso1Part4_MeterInfo *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_MeterInfo>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_SECC_CMN_PaymentOption"))
      {
        *(static_cast<iso1Part4_PaymentOption *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_PaymentOption>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_VAS"))
      {
        *(static_cast<iso1Part4_VASEVCC *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_VASEVCC>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_DC_WeldingDetection"))
      {
        *(static_cast<iso1Part4_WeldingDetection *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_WeldingDetection>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_TLS"))
      {
        *(static_cast<iso1Part4_TLS *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_TLS>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_CertificateHandling"))
      {
        *(static_cast<iso1Part4_CertificateHandlingEVCC *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_CertificateHandlingEVCC>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_DepartureTime"))
      {
        *(static_cast<iso1Part4_DepartureTime *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_DepartureTime>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_AC_MaxNumberOfPhasesInUse"))
      {
        *(static_cast<iso1Part4_MaxNumberOfPhasesInUse *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_MaxNumberOfPhasesInUse>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_ChargingProfileOptimization"))
      {
        *(static_cast<iso1Part4_ChargingProfileOpt *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_ChargingProfileOpt>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_NewSAScheduleTupleID"))
      {
        *(static_cast<iso1Part4_NewSAScheduleTupleID *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_NewSAScheduleTupleID>((*it).value.GetInt());
      }
      else if (!val_name.compare("PIXIT_EVCC_CMN_SAScheduleTupleIDMR"))
      {
        *(static_cast<iso1Part4_SAScheduleTupleIDMR *>(PIXIT_MAP[val_name])) = static_cast<iso1Part4_SAScheduleTupleIDMR>((*it).value.GetInt());
      }
      else if (!val_name.compare("par_ValidDeviationPerCent"))
      {
        *(static_cast<float *>(PIXIT_MAP[val_name])) = static_cast<float>((*it).value.GetFloat());
      }
      else if (!val_name.compare("par_LoadStartValCurrent"))
      {
        *(static_cast<float *>(PIXIT_MAP[val_name])) = static_cast<float>((*it).value.GetFloat());
      }
      else if (!val_name.compare("PIXIT_CMN_CMN_WakeUp"))
      {
        *(static_cast<float *>(PIXIT_MAP[val_name])) = static_cast<float>((*it).value.GetFloat());
      }
      else
      {
        *(static_cast<int *>(PIXIT_MAP[val_name])) = static_cast<int>((*it).value.GetInt());
      }
    }
    else if ((*it).value.IsObject())
    {
      auto object = (*it).value.GetObject();
      (static_cast<iso1Part4_PhysicalValueType *>(PIXIT_MAP[val_name]))->multiplier = (iso1Part4_UnitMultiplierType)(object["multiplier"].GetInt());
      (static_cast<iso1Part4_PhysicalValueType *>(PIXIT_MAP[val_name]))->unit = (iso1Part4_UnitSymbolType)(object["unit"].GetInt());
      (static_cast<iso1Part4_PhysicalValueType *>(PIXIT_MAP[val_name]))->value_ = (short)(object["value_"].GetInt());
    }
  }
  ifs.close();

  if (argc > 3)
  {
    ifs.open(argv[3], std::ios_base::in);
  }
  else
  {
    ifs.open("/home/pi/slac_config.json", std::ios_base::in);
  }
  if (!ifs.good())
  {
    return -1;
  }
  IStreamWrapper isw2(ifs);
  Document document2;
  // dom tree
  document2.ParseStream(isw2);
  for (auto it = document2["timer"].MemberBegin(); it < document2["timer"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    *(SLAC_TIMER_MAP[val_name]) = (*it).value.GetFloat();
  }
  for (auto it = document2["threshold"].MemberBegin(); it < document2["threshold"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    *(SLAC_THRESHOLD_MAP[val_name]) = (*it).value.GetUint();
  }
  ifs.close();

  init_tc("bc_hlc");

  stc->_pPLC->stop();

  std::string cmd_input;
  std::string mode = "";
  std::cout << "Select charging mode: BC or HLC" << std::endl;
  while (true)
  {
    std::cout << fmt::format("{}> ", mode) << std::ends;
    std::getline(std::cin, cmd_input);
    if (cmd_input == "") continue;
    if (cmd_input == "!") break;
    std::transform(cmd_input.begin(), cmd_input.end(), cmd_input.begin(), ::toupper);
    if (0 == MODE_CMD.count(cmd_input))
    {
      std::cout << fmt::format("{}> ", mode) << "Invalid input" << std::endl;
      continue;
    }
  // charge mode: operation
  // BC: A unplug
  // BC: B plug
  // BC: C/D charge
  // BC: HLC >> stop BC change to HLC
    if (mode == "BC")
    {
      if (CP_STATE_MAP.count(cmd_input))
      {
        std::cout << fmt::format("{}> ", mode) << "set state " << cmd_input << std::endl;
        stc->_pBCIf->setState(CP_STATE_MAP[cmd_input]);
      }
      else if (CP_ERROR_MAP.count(cmd_input))
      {
        std::cout << fmt::format("{}> ", mode) << "set error state " << cmd_input << std::endl;
        stc->_pBCIf->setRelay(CP_ERROR_MAP[cmd_input].first, CP_ERROR_MAP[cmd_input].second);
      }
      else if (cmd_input == "START")
      {
        std::cout << fmt::format("{}> ", mode) << "start Basic Charging" << std::endl;
        bc_start();
      }
      else if (cmd_input == "STOP")
      {
        std::cout << fmt::format("{}> ", mode) << "stop Basic Charging" << std::endl;
        bc_stop();
      }
      else if (cmd_input == "HLC")
      {
        mode = cmd_input;
        std::cout << fmt::format("{}> ", mode) << "change to charge mode " << mode << std::endl;
      }
    }
  // HLC: START
  // HLC: STOP
  // HLC: BC >> stop HLC change to BC
    else if (mode == "HLC")
    {
      if (CP_STATE_MAP.count(cmd_input))
      {
        std::cout << fmt::format("{}> ", mode) << "set state " << cmd_input << std::endl;
        stc->_pBCIf->setState(CP_STATE_MAP[cmd_input]);
      }
      else if (CP_ERROR_MAP.count(cmd_input))
      {
        std::cout << fmt::format("{}> ", mode) << "set error state " << cmd_input << std::endl;
        stc->_pBCIf->setRelay(CP_ERROR_MAP[cmd_input].first, CP_ERROR_MAP[cmd_input].second);
      }
      else if (cmd_input == "START")
      {
        std::cout << fmt::format("{}> ", mode) << "start HLC" << std::endl;
        hlc_start();
      }
      else if (cmd_input == "STOP")
      {
        std::cout << fmt::format("{}> ", mode) << "stop HLC" << std::endl;
        hlc_stop();
      }
      else if (cmd_input == "BC")
      {
        mode = cmd_input;
        std::cout << fmt::format("{}> ", mode) << "change to charge mode " << mode << std::endl;
      }
    }
    else
    {
      if (cmd_input == "HLC") mode = "HLC";
      else if (cmd_input == "BC") mode = "BC";
      else std::cout << fmt::format("{}> ", mode) << "Invalid input" << std::endl;
    }
  }
  deinit_tc();
  return 0;
}

void bc_start(void)
{
  std::cout << "SET State B" << std::endl;
  stc->_pBCIf->setState(B);
  PAsleep(5);
  std::cout << "SET State C - Charging..." << std::endl;
  stc->_pBCIf->setState(C);
}

void bc_stop(void)
{
  std::cout << "SET State B" << std::endl;
  stc->_pBCIf->setState(B);
  PAsleep(2);
  std::cout << "SET State A - Unplug" << std::endl;
  stc->_pBCIf->setState(A);
}

void hlc_start(void)
{
  std::cout << "Start HLC - logicalink setup - v2g" << std::endl;
  stc->_pPLC->init(true);
  std::shared_ptr<TestBehavior_SECC_SessionStop> tb = std::make_shared<TestBehavior_SECC_SessionStop>(mtc, stc);
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, stc);
  preConVerdict = pre->f_SECC_AC_PR_PowerDeliveryStop_002(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    tb->f_SECC_CMN_TB_VTB_SessionStop_002();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
}

void hlc_stop(void)
{
  //------------- Post Conditions--------------------------------------------------------
  std::cout << "Stop HLC" << std::endl;
  post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, stc);
  mtc->dumpverdict();
  stc->_pPLC->stop();
}