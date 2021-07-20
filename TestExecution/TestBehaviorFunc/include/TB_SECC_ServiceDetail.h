#ifndef __TB_SECC_SERVICEDETAIL_H__
#define __TB_SECC_SERVICEDETAIL_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_ServiceDetail {
public:
  TestBehavior_SECC_ServiceDetail(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_ServiceDetail();
  verdict_val f_SECC_CMN_TB_VTB_ServiceDetail_001(verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_ServiceDetail_002(void);
  verdict_val f_SECC_CMN_TB_VTB_ServiceDetail_003(void);
  verdict_val f_SECC_CMN_TB_VTB_ServiceDetail_004(void);
  verdict_val f_SECC_CMN_TB_VTB_ServiceDetail_005(void);

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_SERVICEDETAIL_H__
