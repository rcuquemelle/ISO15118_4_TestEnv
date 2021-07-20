#ifndef __TB_SECC_PAYMENTDETAILS_H__
#define __TB_SECC_PAYMENTDETAILS_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_PaymentDetails {
public:
  TestBehavior_SECC_PaymentDetails(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_PaymentDetails();
  verdict_val f_SECC_CMN_TB_VTB_PaymentDetails_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_PaymentDetails_002(void);
  verdict_val f_SECC_CMN_TB_VTB_PaymentDetails_003(void);
  verdict_val f_SECC_CMN_TB_VTB_PaymentDetails_004(void);
  verdict_val f_SECC_CMN_TB_VTB_PaymentDetails_005(const std::string &v_certName, const std::string &v_sub2CertName, const std::string &v_sub1CertName, responseCodeType v_responseCode);
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_PAYMENTDETAILS_H__
