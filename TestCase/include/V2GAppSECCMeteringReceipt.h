#ifndef _V2GAPPSECCMeteringReceipt_H_
#define _V2GAPPSECCMeteringReceipt_H_

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

class TestCases_SECC_MeteringReceipt: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_MeteringReceipt::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb;
public:
  TestCases_SECC_MeteringReceipt(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_MeteringReceipt();

  verdict_val TC_SECC_AC_VTB_MeteringReceipt_001(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_002(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_003(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_004(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_005(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_006(void);
  verdict_val TC_SECC_AC_VTB_MeteringReceipt_007(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_001(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_002(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_003(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_004(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_005(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_006(void);
  verdict_val TC_SECC_DC_VTB_MeteringReceipt_007(void);
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
#endif