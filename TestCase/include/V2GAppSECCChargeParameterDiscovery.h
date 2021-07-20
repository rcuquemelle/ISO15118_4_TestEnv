#ifndef __V2GAPPSECCCHARGEPARAMETERDISCOVERY_H__
#define __V2GAPPSECCCHARGEPARAMETERDISCOVERY_H__

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

class TestCases_SECC_ChargeParameterDiscovery: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_ChargeParameterDiscovery::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb;
public:
  TestCases_SECC_ChargeParameterDiscovery(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_ChargeParameterDiscovery();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_001();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_002();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_003();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_004();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_005();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_006();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_007();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_008();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_009();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_010();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_011();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_012();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_013();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_014();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_015();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_016();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_017();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_018();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_019();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_020();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_021();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_022();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_023();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_024();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_025();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_026();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_027();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_028();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_029();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_030();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_031();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_032();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_033();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_034();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_035();
  verdict_val TC_SECC_AC_VTB_ChargeParameterDiscovery_036();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_001();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_002();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_003();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_004();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_005();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_006();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_007();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_008();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_009();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_010();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_011();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_012();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_013();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_014();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_015();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_016();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_017();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_018();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_019();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_020();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_021();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_022();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_023();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_024();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_025();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_026();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_027();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_028();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_029();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_030();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_031();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_032();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_033();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_034();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_035();
  verdict_val TC_SECC_DC_VTB_ChargeParameterDiscovery_036();
  verdict_val TC_SECC_CMN_VTB_ChargeParameterDiscovery_001();
  verdict_val TC_SECC_CMN_VTB_ChargeParameterDiscovery_002();
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
#endif // __V2GAPPSECCCHARGEPARAMETERDISCOVERY_H__