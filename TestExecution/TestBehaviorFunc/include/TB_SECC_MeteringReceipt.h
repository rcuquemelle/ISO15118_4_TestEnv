#ifndef __TB_SECC_METERINGRECEIPT_H__
#define __TB_SECC_METERINGRECEIPT_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_MeteringReceipt {
public:
  TestBehavior_SECC_MeteringReceipt(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_MeteringReceipt();
  verdict_val f_SECC_AC_TB_VTB_MeteringReceipt_001(verdict_val v_vct);
  verdict_val f_SECC_AC_TB_VTB_MeteringReceipt_002(void);
  verdict_val f_SECC_AC_TB_VTB_MeteringReceipt_003(void);
  verdict_val f_SECC_AC_TB_VTB_MeteringReceipt_004(void);
  verdict_val f_SECC_AC_TB_VTB_MeteringReceipt_005(void);
  verdict_val f_SECC_DC_TB_VTB_MeteringReceipt_001(verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_MeteringReceipt_002(void);
  verdict_val f_SECC_DC_TB_VTB_MeteringReceipt_003(void);
  verdict_val f_SECC_DC_TB_VTB_MeteringReceipt_004(void);
  verdict_val f_SECC_DC_TB_VTB_MeteringReceipt_005(void);
  verdict_val f_SECC_CMN_TB_VTB_MeteringReceipt_001(void);
  verdict_val f_SECC_CMN_TB_VTB_MeteringReceipt_002(void);
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_METERINGRECEIPT_H__
