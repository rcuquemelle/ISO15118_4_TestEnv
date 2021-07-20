#ifndef __TB_SECC_POWERDELIVERY_H__
#define __TB_SECC_POWERDELIVERY_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_PowerDelivery {
public:
  TestBehavior_SECC_PowerDelivery(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_PowerDelivery();

  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, verdict_val v_vct);
  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_002(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_004(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_005(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_TB_VTB_PowerDelivery_006(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType chargeProgress, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, bool v_chargingComplete, bool v_setState, verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_002();
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType chargeProgress);
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_004(iso1Part4_ChargeProgressType chargeProgress);
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_005(iso1Part4_ChargeProgressType chargeProgress);
  verdict_val f_SECC_DC_TB_VTB_PowerDelivery_006();
  verdict_val f_SECC_CMN_TB_VTB_PowerDelivery_001();

private:
  bool a_DC_PowerDeliveryRes_Message(iso1Part4_ChargeProgressType c, iso1Part4_ResponseCodeType rc);
  bool a_AC_PowerDeliveryRes_Message(iso1Part4_ChargeProgressType c, iso1Part4_ResponseCodeType rc);
  void f_SECC_61851_State_CorDorB(iso1Part4_ChargeProgressType cpt, std::shared_ptr<HAL_61851_Listener> &listener);

private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_POWERDELIVERY_H__
