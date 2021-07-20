#ifndef __V2GTPSECCV2GTPSDP_H__
#define __V2GTPSECCV2GTPSDP_H__

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

class TestCases_SECC_V2GTPSessionSetup: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_V2GTPSessionSetup::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_V2GTPSessionSetup> tb;
public:
  TestCases_SECC_V2GTPSessionSetup(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_V2GTPSessionSetup();
  verdict_val TC_SECC_CMN_VTB_V2GTPSessionSetup_001();
  verdict_val TC_SECC_CMN_VTB_V2GTPSessionSetup_002();
  verdict_val TC_SECC_CMN_VTB_V2GTPSessionSetup_003();
  verdict_val TC_SECC_CMN_VTB_V2GTPSessionSetup_004();
  verdict_val TC_SECC_CMN_VTB_V2GTPSessionSetup_005();
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

class TestCases_SECC_V2GTPSDP: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_V2GTPSDP::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_V2GTPSDP> tb;
public:
  TestCases_SECC_V2GTPSDP(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_V2GTPSDP();
  verdict_val TC_SECC_CMN_VTB_V2GTPSDP_001();
  verdict_val TC_SECC_CMN_VTB_V2GTPSDP_002();
  verdict_val TC_SECC_CMN_VTB_V2GTPSDP_003();
  verdict_val TC_SECC_CMN_VTB_V2GTPSDP_004();
  verdict_val TC_SECC_CMN_VTB_V2GTPSDP_005();
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


#endif // __V2GTPSECCV2GTPSDP_H__