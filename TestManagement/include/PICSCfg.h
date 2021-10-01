#ifndef _PICSCFG_H_
#define _PICSCFG_H_
#include "TsDataType.h"

/* Protocol Implementation Conformance Statement */
namespace Pics_15118
{
  using namespace DataStructure_PICS_15118;
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  namespace PICS_CMN
  {
    extern uint32_t par_CMN_MaxEntriesSAScheduleTuple;
    extern bool PICS_CMN_CMN_CombinedTesting;
    extern iso1Part4_ChargingMode PICS_CMN_CMN_ChargingMode;
    extern iso1Part4_IdentificationMode PICS_CMN_CMN_IdentificationMode;
    extern iso1Part4_PlugType PICS_CMN_CMN_PlugType;
    extern iso1Part4_CableCapabilityACType PICS_CMN_AC_CableCapability;
    extern float PICS_CMN_CMN_WakeUp;
    extern iso1Part4_EnergyTransferModeType PICS_CMN_CMN_EnergyTransferModeAC;
    extern iso1Part4_EnergyTransferModeType PICS_CMN_CMN_EnergyTransferModeDC;
  } // namespace PICS_CMN
  namespace PICS_SECC_Tester
  {
    extern bool PICS_SECC_CMN_Pause;
    extern iso1Part4_EIMDone PICS_SECC_CMN_EIMDone;
  } // namespace PICS_SECC_Tester
  namespace PICS_EVCC_Tester
  {
    extern iso1Part4_ZeroPow PICS_EVCC_CMN_PmaxSchedulewithZeroPow;
  } // namespace PICS_EVCC_Tester
} // namespace Pics_15118

namespace Pics_15118_2
{
  using namespace DataStructure_HAL_61851;
  using namespace DataStructure_PICS_15118;
  using namespace DataStructure_PIXIT_15118_2;
  // using namespace DataStructure_Security;
  namespace PICS_15118_2 {
    namespace PICS_CMN {
      extern bool PICS_CMN_CMN_V2gtpSdp;
      extern bool PICS_CMN_CMN_V2gtpV2g;
      extern bool PICS_CMN_CMN_Renegotiation;
      extern uint32_t PICS_CMN_CMN_RenegotiationLoopIndication;
      extern uint32_t PICS_CMN_CMN_LoopCounter;
      extern bool PICS_CMN_CMN_InvalidV2gtpDataFields;
      extern bool PICS_CMN_CMN_SDPTimeoutsAndInvalidData;
      extern bool PICS_CMN_CMN_FailedResponseCodes;
      extern bool PICS_CMN_CMN_V2gTimeouts;
      extern iso1Part4_PkiType PICS_CMN_CMN_PkiName;
    }
    namespace PICS_SECC_Tester {
      extern int8_t par_EVRESSSOC;
      extern IEC_61851_States PICS_SECC_CMN_EvStateInChargeProgress;
      extern bool PICS_SECC_DC_WeldingDetection;
      extern bool PICS_SECC_CMN_DepartureTime;
      extern bool PICS_SECC_CMN_MaxEntriesSAScheduleTuple;
    }
    namespace PICS_EVCC_Tester {
      extern bool PICS_EVCC_CMN_ReceiptRequired;
      extern bool PICS_EVCC_CMN_InvalidStatesAndDutyCycles;
      extern bool PICS_EVCC_CMN_InvalidV2GMessages;
      extern bool PICS_CMN_EVCC_SalesTariff;
    }
  }
} // namespace Pics_15118_2

#endif