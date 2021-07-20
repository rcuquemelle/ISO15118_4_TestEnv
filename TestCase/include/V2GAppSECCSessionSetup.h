#ifndef __V2GAPPSECCSESSIONSETUP_H__
#define __V2GAPPSECCSESSIONSETUP_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TB_SECC_Msg.h"
#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"
#include "V2GTestcase.h"

class TestCases_SECC_SessionSetup: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_SessionSetup::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_SessionSetup> tb;
public:
  TestCases_SECC_SessionSetup(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_SessionSetup();

  verdict_val TC_SECC_CMN_VTB_SessionSetup_001(void);
  verdict_val TC_SECC_CMN_VTB_SessionSetup_002(void);
  verdict_val TC_SECC_CMN_VTB_SessionSetup_003(void);
  verdict_val TC_SECC_CMN_VTB_SessionSetup_004(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_001(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_002(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_003(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_004(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_005(void);
  verdict_val TC_SECC_AC_VTB_SessionSetup_006(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_001(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_002(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_003(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_004(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_005(void);
  verdict_val TC_SECC_DC_VTB_SessionSetup_006(void);
  verdict_val call(const std::string &testcase_name) override {
    if (this->testcase_map.end() != this->testcase_map.find(testcase_name)){
      return (this->*testcase_map[testcase_name])();
    }
    else {
      Logging::error(LogTc_ENABLE, fmt::format("Testcase {0} is not existed. Please check {1}",testcase_name, __FILE__));
      return none;
    }
  }
};

#endif // __V2GAPPSECCSESSIONSETUP_H__