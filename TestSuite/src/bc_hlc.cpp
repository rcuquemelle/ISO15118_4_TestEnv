#include "runTC.h"
#include <time.h>
#include <regex>
#include <InputConfig.h>
#include <set>

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
  std::string testconfig;
  std::string slac_config;
  if (argc > 2)
  {
    testconfig.assign(argv[2]);
    Logging::info(0, fmt::format("V2G config file {}", argv[2]));
  }
  else
  {
    testconfig.assign("/home/pi/testconfig.json");
    Logging::info(0, "V2G config file /home/pi/testconfig.json");
  }
  if (argc > 3)
  {
    slac_config.assign(argv[3]);
    Logging::info(0, fmt::format("SLAC config file {}", argv[3]));
  }
  else
  {
    slac_config.assign("/home/pi/slac_config.json");
    Logging::info(0, "SLAC config file /home/pi/slac_config.json");
  }
  if (-1 == load_config(testconfig, slac_config))
    return -1;

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