#ifndef __TB_SECC_SESSIONSTOP_H__
#define __TB_SECC_SESSIONSTOP_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_SessionStop {
public:
  TestBehavior_SECC_SessionStop(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_SessionStop();
  verdict_val f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType chargingSession, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct);
  verdict_val f_SECC_CMN_TB_VTB_SessionStop_002(void);
  verdict_val f_SECC_CMN_TB_VTB_SessionStop_003(iso1Part4_ChargingSessionType chargingSession);
  verdict_val f_SECC_CMN_TB_VTB_SessionStop_004(void);
  verdict_val f_SECC_CMN_TB_VTB_SessionStop_005(iso1Part4_ChargingSessionType chargingSession);
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_SESSIONSTOP_H__
