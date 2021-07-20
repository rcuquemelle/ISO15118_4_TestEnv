#ifndef __TB_SECC_PAYMENTSERVICESELECTION_H__
#define __TB_SECC_PAYMENTSERVICESELECTION_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_PaymentServiceSelection {
public:
  TestBehavior_SECC_PaymentServiceSelection(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_PaymentServiceSelection();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_002();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_003();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_004();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_005();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_006();
  verdict_val f_SECC_CMN_TB_VTB_PaymentServiceSelection_007();

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_PAYMENTSERVICESELECTION_H__
