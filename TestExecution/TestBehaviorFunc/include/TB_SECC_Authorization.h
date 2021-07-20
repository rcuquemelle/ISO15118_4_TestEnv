#ifndef __TB_SECC_AUTHORIZATION_H__
#define __TB_SECC_AUTHORIZATION_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"


class TestBehavior_SECC_Authorization {
public:
  TestBehavior_SECC_Authorization(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_Authorization();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_Authorization_002(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_Authorization_003();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_004();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_005();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_006();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_007();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_008();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_009();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_010();
  verdict_val f_SECC_CMN_TB_VTB_Authorization_011();
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_AUTHORIZATION_H__
