#ifndef __TB_SECC_V2GTP_H__
#define __TB_SECC_V2GTP_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

using namespace DataStructure_V2GTP;
class TestBehavior_SECC_V2GTPSessionSetup
{
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
public:
  TestBehavior_SECC_V2GTPSessionSetup(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC>& _systemSECC)
  : mtc(_mtc), systemSECC(_systemSECC) {
    this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
  }
  ~TestBehavior_SECC_V2GTPSessionSetup(){}
  verdict_val f_SECC_CMN_TB_VTB_V2GTPSessionSetup_001();
  verdict_val f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(iso1Part4_V2GTP_header_TYPE v_v2gtpHeader);
};

class TestBehavior_SECC_V2GTPSDP
{
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
public:
  TestBehavior_SECC_V2GTPSDP(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> _systemSECC)
    : mtc(_mtc), systemSECC(_systemSECC){
    this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(_mtc);
  }
  ~TestBehavior_SECC_V2GTPSDP() {}

  verdict_val f_SECC_CMN_TB_VTB_V2GTPSDP_001();
  verdict_val f_SECC_CMN_TB_VTB_V2GTPSDP_002(iso1Part4_V2GTP_header_TYPE v_v2gtpHeader);
};

#endif // __TB_SECC_V2GTP_H__