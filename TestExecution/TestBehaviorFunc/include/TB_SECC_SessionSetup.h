#ifndef __TB_SECC_SESSIONSETUP_H__
#define __TB_SECC_SESSIONSETUP_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_SessionSetup {
public:
  TestBehavior_SECC_SessionSetup(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_SessionSetup();
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_002();
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_003();
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_004();
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_005(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_SessionSetup_006(bool v_isZero);

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_SESSIONSETUP_H__
