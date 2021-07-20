#ifndef __TB_SECC_CHARGEPARAMETERDISCOVERY_H__
#define __TB_SECC_CHARGEPARAMETERDISCOVERY_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_ChargeParameterDiscovery {
public:
  TestBehavior_SECC_ChargeParameterDiscovery(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_ChargeParameterDiscovery();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(verdict_val v_vct);
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_002();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_003();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_004();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(verdict_val v_vct);
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
  verdict_val f_SECC_AC_TB_VTB_ChargeParameterDiscovery_008();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_002();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_003();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_004();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
  verdict_val f_SECC_DC_TB_VTB_ChargeParameterDiscovery_008();
  verdict_val f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_001();
  verdict_val f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_002();
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_CHARGEPARAMETERDISCOVERY_H__
