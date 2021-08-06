#include "TimerCfg.h"

namespace Timer_15118 {
  namespace Timer_par_15118 {
    float par_TP_EV_vald_state_duration = 0.25;
    float par_T_conn_max_comm = 10;
    // ------------------ Non-standardised CMN Processing timeouts -------
    float par_CMN_Transmission_Delay = 0.25;
    float par_CMN_HAL_Timeout = 2.0;
    float par_CMN_waitForNextHAL = 0.5;
    float par_CMN_Intern_PTC_Timeout = 0.4;
    float par_CMN_setKey = 3.0;
    // ------------------ Non-standardised EVCC Processing timeouts -------
    float par_EVCC_waitForNextTC = 2.0;
    // ------------------ Non-standardised SECC Processing timeouts -------
    float par_SECC_waitForNextTC = 5.0; // 20.0
    float par_SECC_T_step_X1 = 3.0;
    float par_SECC_Pmax0W = 200.0;
  }
}

namespace Timer_15118_2
{
  namespace Timer_par_15118_2
  {
    //------------------ SECC message performance timeouts ---------------
    float par_V2G_SECC_Sequence_Timeout = 60.0;
    //------------------ EVCC message timeouts ---------------------------
    float par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_SessionSetupReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_ServiceDiscoveryReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_ServiceDetailReq = 5.0;
    float par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_CertificateInstallationReq = 5.0;
    float par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq = 5.0;
    float par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_AuthorizationReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq = 5.0;
    float par_V2G_EVCC_Msg_Timeout_ChargingStatusReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_MeteringReceiptReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_SessionStopReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_CableCheckReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_PreChargeReq = 2.0;
    float par_V2G_EVCC_Msg_Timeout_CurrentDemandReq = 0.25;
    float par_V2G_EVCC_Msg_Timeout_WeldingDetectionReq = 2.0;
    //------------------ EVCC Processing timeouts ------------------------
    float par_V2G_EVCC_Ongoing_Timeout = 60.0;
    float par_V2G_EVCC_Ongoing_Performance_Timeout = 55.0;
    //------------------ Sequence CommunicationSetup timeouts ------------
    float par_V2G_EVCC_CommunicationSetup_Timeout = 20.0;
    float par_V2G_SECC_CommunicationSetup_Performance_Time = 18.0;
    // ------------------ Sequence CableCheck timeouts -------------------
    float par_V2G_EVCC_CableCheck_Timeout = 40.0;
    // ------------------ Sequence PreCharge timeouts --------------------
    float par_V2G_EVCC_PreCharge_Timeout = 17.0;
    // ------------------ SDP timeout ------------------------------------
    float par_EVCC_SDP_Timeout = 1.25;  // 0.25
    // ------------------ Non-standardised SECC Processing timeouts ------
    float par_SECC_B1_B2_Timeout = 8.0;
    float par_SECC_chargingLoop_pause = 0.25;  // 0.1
    // ------------------ Non-standardised EVCC Processing timeouts ------
    float par_V2G_SECC_CPState_Error_Detection_Timeout = 1.5;
    float par_V2G_SECC_CPState_Detection_Timeout = 0.25;
    // ------------------ Non-standardised CMN Processing timeouts -------
    float par_CMN_TCP_Connection_Termination_Timeout = 5.0;
  } // namespace Timer_par_15118_2
} // namespace Timer_15118_2
