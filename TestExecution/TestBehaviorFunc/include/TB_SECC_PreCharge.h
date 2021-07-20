#ifndef __TB_SECC_PRECHARGE_H__
#define __TB_SECC_PRECHARGE_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_PreCharge {
public:
  TestBehavior_SECC_PreCharge(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_PreCharge();
  verdict_val f_SECC_DC_TB_VTB_PreCharge_001(verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_PreCharge_002();
  verdict_val f_SECC_DC_TB_VTB_PreCharge_003();
  verdict_val f_SECC_DC_TB_VTB_PreCharge_004();
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_PRECHARGE_H__
