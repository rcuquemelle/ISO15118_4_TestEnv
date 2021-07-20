#ifndef __TB_SECC_CERTIFICATEINSTALLATION_H__
#define __TB_SECC_CERTIFICATEINSTALLATION_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_CertificateInstallation {
public:
  TestBehavior_SECC_CertificateInstallation(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_CertificateInstallation();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_002();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_003();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_004();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_005();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_006();
  verdict_val f_SECC_CMN_TB_VTB_CertificateInstallation_007(const std::string &v_certName, const std::vector<responseCodeType> &v_responseCodeList);
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_CERTIFICATEINSTALLATION_H__
