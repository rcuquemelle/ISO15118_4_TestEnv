#include "runTC.h"
#include <time.h>
#include <regex>
#include "InputConfig.h"

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

typedef std::map<std::string, std::shared_ptr<V2GTestcaseBase>> MapTCType;

MapTCType mapTC;
template <typename T>
std::shared_ptr<V2GTestcaseBase> createT(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> _stc,
                                         std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,
                                         std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
{
  return std::make_shared<T>(_mtc, _stc, _cfg, _cmn, _pre, _post);
}

static void init_tc(const std::string &testcase_name, const std::string &tc_type)
{
  std::time_t curr_time = std::time(nullptr);
  std::string logfile = fmt::format("{0}_{1:%Y_%m_%d-%H_%M_%S}.log", testcase_name, fmt::localtime(curr_time));
  CppCommon::Path path = CppCommon::Path("/home/pi/v2glog");
  if (!path.IsExists())
    CppCommon::Directory::Create(path);

  Logging::setLogFile(fmt::format("/home/pi/v2glog/{}", logfile));
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(log_level_cfg);
  Logging::setLogOutput(LOG_OUT_BOTH);
  runenv = std::make_shared<IfRuntime>();
  stc = std::make_shared<System_SECC>(runenv, IPV6_ADDR, IPV6_PORT, "eth1", "/home/pi/pev.ini");
  stc->start();
  mtc = std::make_shared<SECC_Tester>(runenv);
  mtc->start();
  cfg = std::make_shared<Configuration_15118_2>(mtc);
  cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(mtc);
  pre = std::make_shared<PreConditions_SECC_15118_2>(mtc, stc, cfg);
  post = std::make_shared<PostConditions_SECC_15118_2>(mtc, stc);

  if (tc_type == "TestCases_SECC_SDP")
    mapTC["TestCases_SECC_SDP"] = createT<TestCases_SECC_SDP>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_V2GTPSDP")
    mapTC["TestCases_SECC_V2GTPSDP"] = createT<TestCases_SECC_V2GTPSDP>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_V2GTPSessionSetup")
    mapTC["TestCases_SECC_V2GTPSessionSetup"] = createT<TestCases_SECC_V2GTPSessionSetup>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_SupportedAppProtocol")
    mapTC["TestCases_SECC_SupportedAppProtocol"] = createT<TestCases_SECC_SupportedAppProtocol>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_SessionSetup")
    mapTC["TestCases_SECC_SessionSetup"] = createT<TestCases_SECC_SessionSetup>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_ServiceDiscovery")
    mapTC["TestCases_SECC_ServiceDiscovery"] = createT<TestCases_SECC_ServiceDiscovery>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_ServiceDetail")
    mapTC["TestCases_SECC_ServiceDetail"] = createT<TestCases_SECC_ServiceDetail>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_PaymentServiceSelection")
    mapTC["TestCases_SECC_PaymentServiceSelection"] = createT<TestCases_SECC_PaymentServiceSelection>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_Authorization")
    mapTC["TestCases_SECC_Authorization"] = createT<TestCases_SECC_Authorization>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_ChargeParameterDiscovery")
    mapTC["TestCases_SECC_ChargeParameterDiscovery"] = createT<TestCases_SECC_ChargeParameterDiscovery>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_CableCheck")
    mapTC["TestCases_SECC_CableCheck"] = createT<TestCases_SECC_CableCheck>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_PreCharge")
    mapTC["TestCases_SECC_PreCharge"] = createT<TestCases_SECC_PreCharge>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_PowerDelivery")
    mapTC["TestCases_SECC_PowerDelivery"] = createT<TestCases_SECC_PowerDelivery>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_CurrentDemand")
    mapTC["TestCases_SECC_CurrentDemand"] = createT<TestCases_SECC_CurrentDemand>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_WeldingDetection")
    mapTC["TestCases_SECC_WeldingDetection"] = createT<TestCases_SECC_WeldingDetection>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_SessionStop")
    mapTC["TestCases_SECC_SessionStop"] = createT<TestCases_SECC_SessionStop>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_CertificateUpdate")
    mapTC["TestCases_SECC_CertificateUpdate"] = createT<TestCases_SECC_CertificateUpdate>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_CertificateInstallation")
    mapTC["TestCases_SECC_CertificateInstallation"] = createT<TestCases_SECC_CertificateInstallation>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_ChargingStatus")
    mapTC["TestCases_SECC_ChargingStatus"] = createT<TestCases_SECC_ChargingStatus>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_MeteringReceipt")
    mapTC["TestCases_SECC_MeteringReceipt"] = createT<TestCases_SECC_MeteringReceipt>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_PaymentDetails")
    mapTC["TestCases_SECC_PaymentDetails"] = createT<TestCases_SECC_PaymentDetails>(mtc, stc, cfg, cmn, pre, post);
  if (tc_type == "TestCases_SECC_Abnormal")
    mapTC["TestCases_SECC_Abnormal"] = createT<TestCases_SECC_Abnormal>(mtc, stc, cfg, cmn, pre, post);
}
static void deinit_tc(const std::string &tc_type)
{
  if (tc_type == "TestCases_SECC_SDP")
    mapTC["TestCases_SECC_SDP"].reset();
  if (tc_type == "TestCases_SECC_V2GTPSDP")
    mapTC["TestCases_SECC_V2GTPSDP"].reset();
  if (tc_type == "TestCases_SECC_V2GTPSessionSetup")
    mapTC["TestCases_SECC_V2GTPSessionSetup"].reset();
  if (tc_type == "TestCases_SECC_SupportedAppProtocol")
    mapTC["TestCases_SECC_SupportedAppProtocol"].reset();
  if (tc_type == "TestCases_SECC_SessionSetup")
    mapTC["TestCases_SECC_SessionSetup"].reset();
  if (tc_type == "TestCases_SECC_ServiceDiscovery")
    mapTC["TestCases_SECC_ServiceDiscovery"].reset();
  if (tc_type == "TestCases_SECC_ServiceDetail")
    mapTC["TestCases_SECC_ServiceDetail"].reset();
  if (tc_type == "TestCases_SECC_PaymentServiceSelection")
    mapTC["TestCases_SECC_PaymentServiceSelection"].reset();
  if (tc_type == "TestCases_SECC_Authorization")
    mapTC["TestCases_SECC_Authorization"].reset();
  if (tc_type == "TestCases_SECC_ChargeParameterDiscovery")
    mapTC["TestCases_SECC_ChargeParameterDiscovery"].reset();
  if (tc_type == "TestCases_SECC_CableCheck")
    mapTC["TestCases_SECC_CableCheck"].reset();
  if (tc_type == "TestCases_SECC_PreCharge")
    mapTC["TestCases_SECC_PreCharge"].reset();
  if (tc_type == "TestCases_SECC_PowerDelivery")
    mapTC["TestCases_SECC_PowerDelivery"].reset();
  if (tc_type == "TestCases_SECC_CurrentDemand")
    mapTC["TestCases_SECC_CurrentDemand"].reset();
  if (tc_type == "TestCases_SECC_WeldingDetection")
    mapTC["TestCases_SECC_WeldingDetection"].reset();
  if (tc_type == "TestCases_SECC_SessionStop")
    mapTC["TestCases_SECC_SessionStop"].reset();
  if (tc_type == "TestCases_SECC_CertificateUpdate")
    mapTC["TestCases_SECC_CertificateUpdate"].reset();
  if (tc_type == "TestCases_SECC_CertificateInstallation")
    mapTC["TestCases_SECC_CertificateInstallation"].reset();
  if (tc_type == "TestCases_SECC_ChargingStatus")
    mapTC["TestCases_SECC_ChargingStatus"].reset();
  if (tc_type == "TestCases_SECC_MeteringReceipt")
    mapTC["TestCases_SECC_MeteringReceipt"].reset();
  if (tc_type == "TestCases_SECC_PaymentDetails")
    mapTC["TestCases_SECC_PaymentDetails"].reset();
  if (tc_type == "TestCases_SECC_Abnormal")
    mapTC["TestCases_SECC_Abnormal"].reset();
  post.reset();
  pre.reset();
  cmn.reset();
  cfg.reset();
  mtc.reset();
  stc.reset();
  runenv.reset();
  Logging::closeLogFile();
}

int main(int argc, const char *argv[])
{
  if (argc == 1)
  {
    Logging::error(0, "Please input testcase name ");
    return -1;
  }
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogOutput(LOG_OUT_CONSOLE);
  if (argc > 2) {
    if (strcmp(argv[2],"D") == 0) {
      log_level_cfg = LOG_DEBUG;
      Logging::setLogLevel(log_level_cfg);
      Logging::info(0, "DEBUG");
    }
    else if (strcmp(argv[2],"I") == 0) {
      log_level_cfg = LOG_INFO;
      Logging::setLogLevel(log_level_cfg);
      Logging::info(0, "INFO");
    }
    else {
      log_level_cfg = LOG_INFO;
      Logging::setLogLevel(log_level_cfg);
      Logging::info(0, "INFO");
    }
  }
  std::string testconfig;
  std::string slac_config;
  if (argc > 3)
  {
    testconfig.assign(argv[3]);
    Logging::info(0, fmt::format("V2G config file {}", argv[3]));
  }
  else
  {
    testconfig.assign("/home/pi/testconfig.json");
    Logging::info(0, "V2G config file /home/pi/testconfig.json");
  }
  if (argc > 4)
  {
    slac_config.assign(argv[4]);
    Logging::info(0, fmt::format("SLAC config file {}", argv[4]));
  }
  else
  {
    slac_config.assign("/home/pi/slac_config.json");
    Logging::info(0, "SLAC config file /home/pi/slac_config.json");
  }
  if (-1 == load_config(testconfig, slac_config))
    return -1;

  std::regex regex_msg("TC_SECC_(AC|DC|CMN)_VTB_(\\w+)_\\d{3}", std::regex_constants::ECMAScript);
  std::smatch matches;
  std::string testcase_type = "TestCases_SECC_";
  std::string testcase_name(argv[1]);
  if (std::regex_search(testcase_name, matches, regex_msg))
  {
    testcase_type += matches.str(2);
    Logging::info(0, fmt::format("Execute testcase {0}::{1}", testcase_type, testcase_name));
  }
  else
  {
    Logging::error(0, fmt::format("Incorrect message name of input testcase - {}", argv[1]));
    return -1;
  }
  init_tc(testcase_name, testcase_type);

  verdict_val execute_result = mapTC[testcase_type]->call(testcase_name);

  deinit_tc(testcase_type);

  return execute_result;
}
