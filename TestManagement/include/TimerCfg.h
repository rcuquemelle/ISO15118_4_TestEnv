#ifndef _TIMERCFG_H_
#define _TIMERCFG_H_

namespace Timer_15118
{
  namespace Timer_par_15118 {
    extern float par_TP_EV_vald_state_duration;
    extern float par_T_conn_max_comm;
    // ------------------ Non-standardised CMN Processing timeouts -------
    extern float par_CMN_Transmission_Delay;
    extern float par_CMN_HAL_Timeout;
    extern float par_CMN_waitForNextHAL;
    extern float par_CMN_Intern_PTC_Timeout;
    extern float par_CMN_setKey;
    // ------------------ Non-standardised EVCC Processing timeouts -------
    extern float par_EVCC_waitForNextTC;
    // ------------------ Non-standardised SECC Processing timeouts -------
    extern float par_SECC_waitForNextTC;
    extern float par_SECC_T_step_X1;
    extern float par_SECC_Pmax0W;
  }
} // namespace Timer_15118

namespace Timer_15118_2
{
  namespace Timer_par_15118_2
  {
    //------------------ SECC message performance timeouts ---------------
    extern float par_V2G_SECC_Sequence_Timeout;
    //------------------ EVCC message timeouts ---------------------------
    extern float par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq;
    extern float par_V2G_EVCC_Msg_Timeout_SessionSetupReq;
    extern float par_V2G_EVCC_Msg_Timeout_ServiceDiscoveryReq;
    extern float par_V2G_EVCC_Msg_Timeout_ServiceDetailReq;
    extern float par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq;
    extern float par_V2G_EVCC_Msg_Timeout_CertificateInstallationReq;
    extern float par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq;
    extern float par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq;
    extern float par_V2G_EVCC_Msg_Timeout_AuthorizationReq;
    extern float par_V2G_EVCC_Msg_Timeout_ChargeParameterDiscoveryReq;
    extern float par_V2G_EVCC_Msg_Timeout_PowerDeliveryReq;
    extern float par_V2G_EVCC_Msg_Timeout_ChargingStatusReq;
    extern float par_V2G_EVCC_Msg_Timeout_MeteringReceiptReq;
    extern float par_V2G_EVCC_Msg_Timeout_SessionStopReq;
    extern float par_V2G_EVCC_Msg_Timeout_CableCheckReq;
    extern float par_V2G_EVCC_Msg_Timeout_PreChargeReq;
    extern float par_V2G_EVCC_Msg_Timeout_CurrentDemandReq;
    extern float par_V2G_EVCC_Msg_Timeout_WeldingDetectionReq;
    //------------------ EVCC Processing timeouts ------------------------
    extern float par_V2G_EVCC_Ongoing_Timeout;
    extern float par_V2G_EVCC_Ongoing_Performance_Timeout;
    //------------------ Sequence CommunicationSetup timeouts ------------
    extern float par_V2G_EVCC_CommunicationSetup_Timeout;
    extern float par_V2G_SECC_CommunicationSetup_Performance_Time;
    // ------------------ Sequence CableCheck timeouts -------------------
    extern float par_V2G_EVCC_CableCheck_Timeout;
    // ------------------ Sequence PreCharge timeouts --------------------
    extern float par_V2G_EVCC_PreCharge_Timeout;
    // ------------------ SDP timeout ------------------------------------
    extern float par_EVCC_SDP_Timeout;
    // ------------------ Non-standardised SECC Processing timeouts ------
    extern float par_SECC_B1_B2_Timeout;
    extern float par_SECC_chargingLoop_pause;
    // ------------------ Non-standardised EVCC Processing timeouts ------
    extern float par_V2G_SECC_CPState_Error_Detection_Timeout;
    extern float par_V2G_SECC_CPState_Detection_Timeout;
    // ------------------ Non-standardised CMN Processing timeouts -------
    extern float par_CMN_TCP_Connection_Termination_Timeout;
  } // namespace Timer_par_15118_2
} // namespace Timer_15118_2

#endif