#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"
#include "V2GAppSECCSessionStop.h"

using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Timer_15118::Timer_par_15118;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace DataStructure_PICS_15118;
using namespace DataStructure_PIXIT_15118_2;

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
static void init_tc(uint8_t a)
{
  Logging::LogCfg.value = LogAll_ENABLE ^ LogPAIf_ENABLE;//LogSut61851_ENABLE | LogSLAC_ENABLE | LogCmnFnc_ENABLE | LogCfgFnc_ENABLE | LogPreFnc_ENABLE | LogPosFnc_ENABLE | LogTbFnc_ENABLE | LogTc_ENABLE;
  std::time_t curr_time = std::time(nullptr);
  std::string logfile = fmt::format("test_{0:%Y-%m-%d-%H-%M-%S}.log", fmt::localtime(curr_time));
  CppCommon::Path path = CppCommon::Path("/home/pi/v2glog");
  if (!path.IsExists())
    CppCommon::Directory::Create(path);
  Logging::setLogFile(fmt::format("/home/pi/v2glog/{}", logfile));
  Logging::setLogLevel(LOG_DEBUG);
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
  uint8_t count = 0;
  // toggle relay B 5 lan
  std::shared_ptr<TestCases_SECC_SessionStop> tc16;

  init_tc(0);
  tc16 = std::make_shared<TestCases_SECC_SessionStop>(mtc, stc, cfg, cmn, pre, post);
/*   for (size_t i = 0; i < 5; i++)
  {
    stc->_pBCIf->setRelay(SeccBasicSignaling::relay_pin_t_En::RELAY_PE_LINE, SeccBasicSignaling::relay_val_En::RELAY_VAL_ON);
    PAsleep(0.2);
    stc->_pBCIf->setRelay(SeccBasicSignaling::relay_pin_t_En::RELAY_PE_LINE, SeccBasicSignaling::relay_val_En::RELAY_VAL_OFF);
    PAsleep(0.2);
  } */
  /* 30kW th� request d�ng 55A 500V nh�. c�n 60kW th� d�ng 110A 500V */
  while (0 == stc->_pBCIf->getBtnPressCounter()){
  }
  PAsleep(1.5);
  if (stc->_pBCIf->getBtnPressCounter() == 1){
    // 30kw
    Logging::info(LogTc_ENABLE, "------ DC 30KW AGING TEST ------");
    mtc->vc_EVTargetCurrent.Value = 0;
  }
  else {
    // 60kw
    Logging::info(LogTc_ENABLE, "------ DC 60KW AGING TEST ------");
    mtc->vc_EVTargetCurrent.Value = 0;
  }
  stc->_pBCIf->resetBtnCounter();
    tc16->TC_SECC_DC_VTB_SessionStop_002();
  stc->_pBCIf->resetBtnCounter();
  tc16.reset();
  deinit_tc();
  count++;
}
