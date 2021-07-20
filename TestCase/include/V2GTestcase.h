#ifndef __V2GTESTCASE_H__
#define __V2GTESTCASE_H__
#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TB_SECC_Msg.h"
#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"
#include <map>


class V2GTestcaseBase
{
public:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> stc;
  std::shared_ptr<Configuration_15118_2> cfg;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
  std::shared_ptr<PreConditions_SECC_15118_2> pre;
  std::shared_ptr<PostConditions_SECC_15118_2> post;

  V2GTestcaseBase(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post) {
      this->mtc = _mtc;
      this->stc = _stc;
      this->cfg = _cfg;
      this->cmn = _cmn;
      this->pre = _pre;
      this->post = _post;
    }
  ~V2GTestcaseBase() {}
  virtual verdict_val call(const std::string &testcase_name) = 0;
};


#endif // __V2GTESTCASE_H__