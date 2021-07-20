#ifndef __PRECONDITIONS_SECC_H__
#define __PRECONDITIONS_SECC_H__

#include "Components.h"
#include "Common_Cfg.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "TestSystemLogging.h"

class PreConditions_SECC_15118_2: public std::enable_shared_from_this<PreConditions_SECC_15118_2> {
public:
  PreConditions_SECC_15118_2(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_systemSECC, std::shared_ptr<Configuration_15118_2>& _cfg)
    : mtc(_mtc), cfg(_cfg), systemSECC(_systemSECC) {
    }
  ~PreConditions_SECC_15118_2(){}
  verdict_val f_SECC_CMN_PR_SetPowerFlowConfiguration_001();
  verdict_val f_SECC_CMN_PR_PLCLinkStatusCombinedTesting_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_StateA_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_Binding_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_SupportedAppProtocol_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_SessionSetup_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_ServiceDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_ServiceDetail_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_PaymentServiceSelection_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_CertificateInstallation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_CertificateUpdate_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_PaymentDetails_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_Authorization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_ChargeParameterDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_PowerDeliveryStart_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_ChargingStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_ChargingStatusOrMeteringReceiptRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_PowerDeliveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_ChargeParameterDiscoveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_PowerDeliveryStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_SessionStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_AC_PR_SessionStop_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_ChargeParameterDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_CableCheck_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_PreCharge_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_PowerDeliveryStart_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_CurrentDemand_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_002(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_PowerDeliveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_ChargeParameterDiscoveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_PowerDeliveryStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, bool v_setState);
  verdict_val f_SECC_DC_PR_WeldingDetection_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_SessionStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_DC_PR_SessionStop_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_SessionSetupPausedSession_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);
  verdict_val f_SECC_CMN_PR_AuthorizationPausedSession_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener);

public:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<Configuration_15118_2> cfg;
  std::shared_ptr<System_SECC> systemSECC;
};

#endif // __PRECONDITIONS_SECC_H__
