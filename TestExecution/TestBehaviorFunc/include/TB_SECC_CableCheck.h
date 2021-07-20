#ifndef __TB_SECC_CABLECHECK_H__
#define __TB_SECC_CABLECHECK_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_CableCheck {
public:
  TestBehavior_SECC_CableCheck(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_CableCheck();
  verdict_val f_SECC_DC_TB_VTB_CableCheck_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_CableCheck_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_TB_VTB_CableCheck_003(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_TB_VTB_CableCheck_004();
  verdict_val f_SECC_DC_TB_VTB_CableCheck_005();
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_CABLECHECK_H__
