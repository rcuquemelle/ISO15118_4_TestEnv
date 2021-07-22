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
std::map<std::string, float *>   TIMER_MAP = {
    {"TP_EV_vald_state_duration", &Plc::TP_EV_vald_state_duration},
    {"TP_EV_vald_toggle", &Plc::TP_EV_vald_toggle},
    {"TP_EV_SLAC_init", &Plc::TP_EV_SLAC_init}};
std::map<std::string, uint8_t *>   THRESHOLD_MAP = {
    {"C_EV_vald_nb_toggles", &Plc::C_EV_vald_nb_toggles},
    {"C_EV_match_signalattn_direct", &Plc::C_EV_match_signalattn_direct},
    {"C_EV_match_signalattn_indirect", &Plc::C_EV_match_signalattn_indirect}};

static void init_tc(const std::string &testcase_name, const std::string &tc_type)
{
  std::time_t curr_time = std::time(nullptr);
  std::string logfile = fmt::format("{0}_{1:%Y-%m-%d-%H-%M-%S}.log", testcase_name, fmt::localtime(curr_time));
  CppCommon::Path path = CppCommon::Path("/home/pi/v2glog");
  if (!path.IsExists())
    CppCommon::Directory::Create(path);

  Logging::setLogFile(fmt::format("/home/pi/v2glog/{}", logfile));
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(LOG_INFO);
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

static void deinit_tc(const std::string &tc_type)
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

int main(int argc, const char *argv[])
{
  // load json configuration data
  std::ifstream ifs;
  if (argc > 1)
  {
    ifs.open(argv[1], std::ios_base::in);
  }
  else
  {
    ifs.open("/home/pi/slac_config.json", std::ios_base::in);
  }
  if (!ifs.good())
  {
    Logging::error(0, "configuration file is not exist");
    printf("error %d : %s\n", errno, strerror(errno));
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
    printf("TIMER %s : %f\n", val_name.c_str(), *(TIMER_MAP[val_name]));
  }
  for (auto it = document["threshold"].MemberBegin(); it < document["threshold"].MemberEnd(); ++it)
  {
    std::string val_name = (*it).name.GetString();
    *(THRESHOLD_MAP[val_name]) = (*it).value.GetUint();
    printf("THRESHOLD %s : %d\n", val_name.c_str(), *(THRESHOLD_MAP[val_name]));
  }

  init_tc("slac_check", "slac");
  std::shared_ptr<TestCases_SECC_SessionStop> tc16;
  tc16 = std::make_shared<TestCases_SECC_SessionStop>(mtc, stc, cfg, cmn, pre, post);
  tc16->TC_SECC_DC_VTB_SessionStop_002();
  tc16.reset();
  deinit_tc("slac");
  return 0;
}