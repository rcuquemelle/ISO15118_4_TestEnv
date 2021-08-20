#ifndef _PIXITCFG_H_
#define _PIXITCFG_H_
#include "TsDataType.h"

/* Protocol Implementation extra Information for Testing */
namespace Pixit_15118 {
  using namespace DataStructure_PIXIT_15118;
  namespace PIXIT_15118 {
    namespace PIXIT_CMN {
      extern float PIXIT_CMN_CMN_WakeUp;
    }
    namespace PIXIT_EVCC_Tester {
      extern iso1Part4_Pause PIXIT_EVCC_CMN_Pause;
    }
  }
}
namespace Pixit_15118_2 {
  using namespace DataStructure_PIXIT_15118_2;
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  namespace PIXIT_15118_2 {
    namespace PIXIT_CMN {
      extern iso1Part4_PkiType PIXIT_CMN_CMN_PkiName;
      extern iso1Part4_Renegotiation PIXIT_CMN_CMN_Renegotiation;
      extern iso1Part4_MeterReading PIXIT_CMN_CMN_MeterReading;
      extern iso1Part4_PhysicalValueType par_EVTargetVoltage;
      extern iso1Part4_PhysicalValueType par_EVTargetCurrent;
      extern iso1Part4_PhysicalValueType par_EVBatteryVoltage;
      extern iso1Part4_PhysicalValueType par_EVMaximumVoltageLimit;
      extern iso1Part4_PhysicalValueType par_EVMaximumCurrentLimit;
      extern float par_ValidDeviationPerCent;
      extern float par_LoadStartValCurrent;
      extern int8_t par_EVBatteryStepSize;
    }
    namespace PIXIT_SECC_Tester {
      extern iso1Part4_VASSECC PIXIT_SECC_CMN_VAS;
      extern bool PIXIT_SECC_CMN_ReceiptRequired;
      extern iso1Part4_CertificateHandlingSECC PIXIT_SECC_CMN_CertificateHandling;
      extern iso1Part4_SalesTariff PIXIT_SECC_CMN_SalesTariff;
      extern bool PIXIT_SECC_CMN_TLS;
      extern int PIXIT_SECC_CMN_VersionNumberMinor;
      extern iso1Part4_InternetAccess PIXIT_SECC_CMN_InternetAccess;
      extern iso1Part4_Ongoing PIXIT_SECC_DC_CableCheckOngoing;
      extern iso1Part4_Ongoing PIXIT_SECC_CMN_AuthorizationOngoing;
      extern iso1Part4_Ongoing PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing;
      extern iso1Part4_MeterInfo PIXIT_SECC_CMN_MeterInfo;
      extern iso1Part4_PaymentOption PIXIT_SECC_CMN_PaymentOption;
    }
    namespace PIXIT_EVCC_Tester {
      extern iso1Part4_VASEVCC PIXIT_EVCC_CMN_VAS;
      extern iso1Part4_WeldingDetection PIXIT_EVCC_DC_WeldingDetection;
      extern iso1Part4_TLS PIXIT_EVCC_CMN_TLS;
      extern iso1Part4_CertificateHandlingEVCC PIXIT_EVCC_CMN_CertificateHandling;
      extern iso1Part4_DepartureTime PIXIT_EVCC_CMN_DepartureTime;
      extern iso1Part4_MaxNumberOfPhasesInUse PIXIT_EVCC_AC_MaxNumberOfPhasesInUse;
      extern iso1Part4_ChargingProfileOpt PIXIT_EVCC_CMN_ChargingProfileOptimization;
      extern iso1Part4_NewSAScheduleTupleID PIXIT_EVCC_CMN_NewSAScheduleTupleID;
      extern iso1Part4_SAScheduleTupleIDMR PIXIT_EVCC_CMN_SAScheduleTupleIDMR;
    }
  }
}

#endif