#ifndef __TB_SECC_CERTIFICATEUPDATE_H__
#define __TB_SECC_CERTIFICATEUPDATE_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_CertificateUpdate {
public:
  TestBehavior_SECC_CertificateUpdate(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_CertificateUpdate();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_002();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_003();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_004();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_005();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_006();
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_007(const std::string &v_config);
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_008(const std::string &v_EMAID_Unknown);
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_009(const std::string &v_certName);
  verdict_val f_SECC_CMN_TB_VTB_CertificateUpdate_010(const std::string &v_certName, const std::vector<responseCodeType> &v_responseCodeList);

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_CERTIFICATEUPDATE_H__
