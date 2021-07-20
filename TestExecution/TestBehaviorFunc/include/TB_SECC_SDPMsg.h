#ifndef __TB_SECC_SDPMSG_H__
#define __TB_SECC_SDPMSG_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_SDP
{
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
public:
  TestBehavior_SECC_SDP(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC>& _systemSECC)
    : mtc(_mtc), systemSECC(_systemSECC){
    this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
  }
  ~TestBehavior_SECC_SDP() {}
  verdict_val f_SECC_CMN_TB_VTB_SDP_001(iso1Part4_Security_TYPE v_security, verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_SDP_002(iso1Part4_Security_TYPE v_security);
  verdict_val f_SECC_CMN_TB_VTB_SDP_003();
};

#endif // __TB_SECC_SDPMSG_H__