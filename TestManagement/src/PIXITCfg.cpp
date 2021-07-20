#include "PIXITCfg.h"

/*  Protocol Implementation extra Information for Testing (PIXIT) */
namespace Pixit_15118 {
  namespace PIXIT_15118 {
    namespace PIXIT_CMN {
      /* Indication for the wake‐up time (SUT) within a paused session  */
      float PIXIT_CMN_CMN_WakeUp = 200.0;
    }
    namespace PIXIT_EVCC_Tester {
      /* Indication for enabling a charging pause 
        Choice: i) pause, ii) unknown, iii) none_  */
      iso1Part4_Pause PIXIT_EVCC_CMN_Pause = iso1Part4_Pause::unknown;
    }
  }
}
namespace Pixit_15118_2 {
  namespace PIXIT_15118_2 {
    namespace PIXIT_CMN {
      /* Indication for selected PKI 
          Choice: i) PKI_1, ii) PKI_2, iii) PKI_3, iv) PKI_4, v) PKI_5, vi) PKI_6, vii) PKI_7  */
      iso1Part4_PkiType PIXIT_CMN_CMN_PkiName = iso1Part4_PkiType::PKI_1;
      /* Indication for explicit testing of Renegotiation initiated by the SUT Choice: i) renegotiation, ii) unknown  */
      iso1Part4_Renegotiation PIXIT_CMN_CMN_Renegotiation = iso1Part4_Renegotiation::unknown;
      /* Indication for explicit testing of MeterReading element Choice: i) meterReading, ii) unknown  */
      iso1Part4_MeterReading PIXIT_CMN_CMN_MeterReading = iso1Part4_MeterReading::unknown;
      iso1Part4_PhysicalValueType par_EVBatteryVoltage = {.multiplier=0, .unit=iso1Part4_UnitSymbolType::v,.value_=300};
      iso1Part4_PhysicalValueType par_EVMaximumVoltageLimit = {.multiplier=0, .unit=iso1Part4_UnitSymbolType::v,.value_=500};
      iso1Part4_PhysicalValueType par_EVMaximumCurrentLimit = {.multiplier=0, .unit=iso1Part4_UnitSymbolType::a,.value_=110};
      float par_ValidDeviationPerCent = 5.0;
      float par_LoadStartValCurrent = 10.0;
      int8_t par_EVBatteryStepSize = 99;
    }
    namespace PIXIT_SECC_Tester {
      /* Indication for explicit testing of ServiceDetail message (SUT shall send a serviceList within ServiceDiscoveryRes message) 
          Choice: i) serviceDetail, ii) none_, iii) unknown  */
      iso1Part4_VASSECC PIXIT_SECC_CMN_VAS = iso1Part4_VASSECC::serviceDetail;
      /* Indication for explicit testing of MeteringReceipt message */
      bool PIXIT_SECC_CMN_ReceiptRequired = true;
      /* Indication for explicit testing of CertificateInstallation or CertificateUpdate message  
          Choice: i) certInstall, ii) certUpdate, iii) none_ */
      iso1Part4_CertificateHandlingSECC PIXIT_SECC_CMN_CertificateHandling = iso1Part4_CertificateHandlingSECC::none_;
      /* Indication for explicit testing of Sales Tariff elements 
          Choice: i) salesTariff, ii) unknown  */
      iso1Part4_SalesTariff PIXIT_SECC_CMN_SalesTariff = iso1Part4_SalesTariff::unknown;
      /* Indication for explicit testing of TLS in EIM mode  */
      bool PIXIT_SECC_CMN_TLS = false;
      /* Indication for the supported VersionNumberMinor of the SUT  */
      int PIXIT_SECC_CMN_VersionNumberMinor = 0;
      /* Indication for support of InternetAccess service Choice: i) internetAccess, ii) unknown  */
      iso1Part4_InternetAccess PIXIT_SECC_CMN_InternetAccess = iso1Part4_InternetAccess::unknown;
      /* Indication for explicit testing of the repetition of the CableCheck message sequence Choice: i) ongoing, ii) unknown  */
      iso1Part4_Ongoing PIXIT_SECC_DC_CableCheckOngoing = iso1Part4_Ongoing::unknown;
      /* Indication for explicit testing of the repetition of the Authorization 
          message sequence until V2G_SECC_Ongoing_Timer expires on SUT side Choice: i) ongoing, ii) unknown */
      iso1Part4_Ongoing PIXIT_SECC_CMN_AuthorizationOngoing = iso1Part4_Ongoing::unknown;
      /* Indication for explicit testing of the repetition of the 
          ChargeParameterDiscovery message sequence until 
          V2G_SECC_Ongoing_Timer expires on SUT side 
          Choice: i) ongoing, ii) unknown  */
      iso1Part4_Ongoing PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing = iso1Part4_Ongoing::unknown;
      /* Indication for explicit testing of MeterInfo element Choice: i) meterInfo, ii) unknown  */
      iso1Part4_MeterInfo PIXIT_SECC_CMN_MeterInfo = iso1Part4_MeterInfo::unknown;
      /* Indication for supported payment option within ServiceDiscoveryRes 
          message (Only one payment option possible) 
          Choice: i) externalPayment, ii) contract  */
      iso1Part4_PaymentOption PIXIT_SECC_CMN_PaymentOption = iso1Part4_PaymentOption::externalPayment;
    }
    namespace PIXIT_EVCC_Tester {
      /* Indication for explicit testing of ServiceDetail message (SUT shall send a 
        ServiceDetailReq message for each service of the received serviceList) 
        Choice: i) serviceDetail, ii) none_, iii) unknown  */
      iso1Part4_VASEVCC PIXIT_EVCC_CMN_VAS = iso1Part4_VASEVCC::unknown;
      /* Indication for explicit testing of WeldingDetection message 
        Choice: i) weldingDetection, ii) none_, iii) unknown  */
      iso1Part4_WeldingDetection PIXIT_EVCC_DC_WeldingDetection = iso1Part4_WeldingDetection::unknown;
      /* Indication for explicit testing of TLS in EIM mode 
          Choice: i) tls, ii) none_, iii) unknown  */
      iso1Part4_TLS PIXIT_EVCC_CMN_TLS = iso1Part4_TLS::unknown;
      /* Indication for explicit testing of CertificateInstallation or CertificateUpdate message 
        Choice: i) certInstall, ii) certUpdate, iii) none_, iv) unknown */
      iso1Part4_CertificateHandlingEVCC PIXIT_EVCC_CMN_CertificateHandling = iso1Part4_CertificateHandlingEVCC::unknown;
      /* Indication for explicit testing of DepartureTime element 
          Choice: i) departureTime, ii) none_, iii) unknown  */
      iso1Part4_DepartureTime PIXIT_EVCC_CMN_DepartureTime = iso1Part4_DepartureTime::unknown;
      /* Indication for explicit testing of MaxNumberOfPhasesInUse element 
          Choice: i) maxNumberOfPhasesInUse, ii) unknown  */
      iso1Part4_MaxNumberOfPhasesInUse PIXIT_EVCC_AC_MaxNumberOfPhasesInUse = iso1Part4_MaxNumberOfPhasesInUse::unknown;
      /* Indication for the SUTs capability to optimize charging profiles based on the charge schedule 
          Choice: i) optimization, ii) none_, iii) unknown  */
      iso1Part4_ChargingProfileOpt PIXIT_EVCC_CMN_ChargingProfileOptimization = iso1Part4_ChargingProfileOpt::unknown;
      /* Indication for explicit testing of using a new SAScheduleTupleID after renegotiation by the SUT 
          Choice: i) newSAScheduleTupleID, ii) unknown  */
      iso1Part4_NewSAScheduleTupleID PIXIT_EVCC_CMN_NewSAScheduleTupleID = iso1Part4_NewSAScheduleTupleID::unknown;
      /* Indication for explicit testing SAScheduleTupleID within MeteringReceiptReq message 
          Choice: i) sAScheduleTupleID, ii) unknown  */
      iso1Part4_SAScheduleTupleIDMR PIXIT_EVCC_CMN_SAScheduleTupleIDMR = iso1Part4_SAScheduleTupleIDMR::unknown;
    }
  }
}