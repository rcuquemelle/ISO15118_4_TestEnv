#ifndef _V2GAPPSECCSERVICEDETAIL_H_
#define _V2GAPPSECCSERVICEDETAIL_H_

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

class TestCases_SECC_ServiceDetail: public V2GTestcaseBase
{
private:
  std::map<std::string, verdict_val(TestCases_SECC_ServiceDetail::*)(void)> testcase_map;
  std::shared_ptr<TestBehavior_SECC_ServiceDetail> tb;
public:
  TestCases_SECC_ServiceDetail(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post);
  ~TestCases_SECC_ServiceDetail();

  verdict_val TC_SECC_CMN_VTB_ServiceDetail_001(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_002(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_003(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_004(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_005(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_006(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_007(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_008(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_009(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_010(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_011(void);
  verdict_val TC_SECC_CMN_VTB_ServiceDetail_012(void);
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