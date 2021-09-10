#include "runTC.h"
#include <time.h>
#include <regex>
#include <InputConfig.h>

using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;
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

static void init_tc(const std::string &testcase_name)
{
  std::time_t curr_time = std::time(nullptr);
  std::string logfile = fmt::format("{0}_{1:%Y_%m_%d-%H_%M_%S}.log", testcase_name, fmt::localtime(curr_time));
  CppCommon::Path path = CppCommon::Path("/home/pi/v2glog");
  if (!path.IsExists())
    CppCommon::Directory::Create(path);

  Logging::setLogFile(fmt::format("/home/pi/v2glog/{}", logfile));
  Logging::LogCfg.value = LogAll_ENABLE ^ LogPAIf_ENABLE;
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
}
static void deinit_tc(void) {
  post.reset();
  pre.reset();
  cmn.reset();
  cfg.reset();
  mtc.reset();
  stc.reset();
  runenv.reset();
  Logging::closeLogFile();
}

int main(int argc, char *argv[])
{
  // toggle relay B 5 lan
  std::shared_ptr<TestCases_SECC_SessionStop> tc16;

  log_level_cfg = LOG_INFO;
  if (argc > 1) {
    if (strcmp(argv[1],"D") == 0) {
      log_level_cfg = LOG_DEBUG;
    }
  }
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

  init_tc("dc_aging");
  tc16 = std::make_shared<TestCases_SECC_SessionStop>(mtc, stc, cfg, cmn, pre, post);

  for (size_t i = 0; i < 5; i++)
  {
    stc->_pBCIf->setRelay(SeccBasicSignaling::relay_pin_t_En::RELAY_PE_LINE, SeccBasicSignaling::relay_val_En::RELAY_VAL_ON);
    PAsleep(0.2);
    stc->_pBCIf->setRelay(SeccBasicSignaling::relay_pin_t_En::RELAY_PE_LINE, SeccBasicSignaling::relay_val_En::RELAY_VAL_OFF);
    PAsleep(0.2);
  }

  while (0 == stc->_pBCIf->getBtnPressCounter()){
  }
  PAsleep(1.5);
  if (stc->_pBCIf->getBtnPressCounter() == 1){
    // 30kw
    Logging::info(LogTc_ENABLE, "------ DC 30KW AGING TEST ------");
  }
  else {
    // 60kw
    Logging::info(LogTc_ENABLE, "------ DC 60KW AGING TEST ------");
    par_EVTargetCurrent.value_ *= 2;
    mtc->vc_EVMaximumCurrentLimit.Value *= 2;
  }
  Logging::info(LogTc_ENABLE, fmt::format("Target current: {}A", par_EVTargetCurrent.value_));
  Logging::info(LogTc_ENABLE, fmt::format("Target voltage: {}V", par_EVTargetVoltage.value_));
  stc->_pBCIf->resetBtnCounter();
  tc16->TC_SECC_DC_VTB_SessionStop_010();
  stc->_pBCIf->resetBtnCounter();
  tc16.reset();
  deinit_tc();
}
