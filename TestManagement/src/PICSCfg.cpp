#include "PICSCfg.h"

/* Protocol Implementation Conformance Statement (PICS) */
namespace Pics_15118
{
  using namespace DataStructure_PICS_15118;
  namespace PICS_CMN
  {
    uint32_t par_CMN_MaxEntriesSAScheduleTuple = 12;
    /* Indication for enabling combined testing including SLAC association & V2G messaging - PLC_SLAC test operation ISO15118-5*/
    bool PICS_CMN_CMN_CombinedTesting = false;
    /* Indication for testing either AC or DC charging mode */
    iso1Part4_ChargingMode PICS_CMN_CMN_ChargingMode = iso1Part4_ChargingMode::dC;
    /* Indication for testing either EIM or PnC identification mode  */
    iso1Part4_IdentificationMode PICS_CMN_CMN_IdentificationMode = iso1Part4_IdentificationMode::eIM;
    /* ndication for testing either type1 or type2 plug type  */
    iso1Part4_PlugType PICS_CMN_CMN_PlugType = iso1Part4_PlugType::type2;
    /* Indication for used AC cable type Choice: i) capability13A, ii) capability20A, iii) capability32A, iv) capability63A, v) capability70A  */
    iso1Part4_CableCapabilityACType PICS_CMN_AC_CableCapability = iso1Part4_CableCapabilityACType::capability32A;
    /* Indication for the sleep time within a paused session  */
    float PICS_CMN_CMN_WakeUp = 300.0;
  } // namespace PICS_CMN
  namespace PICS_SECC_Tester
  {
    /* Indication for enabling a charging pause  */
    bool PICS_SECC_CMN_Pause = false;
    /* Indication for initiating EIM Authorization process Choice: i) beforePlugin, ii) afterPlugin, iii) duringSlac, iv) v2gAuthorization  */
    iso1Part4_EIMDone PICS_SECC_CMN_EIMDone = iso1Part4_EIMDone::v2gAuthorization;
  } // namespace PICS_SECC_Tester
  namespace PICS_EVCC_Tester
  {
    /* Indication for enabling a PmaxScheduleList with a list element pMax = 0W (triggering pause) 
      Choice: i) sleepWithoutCharge, ii) sleepAfterCharge, iii) none_ */
    iso1Part4_ZeroPow PICS_EVCC_CMN_PmaxSchedulewithZeroPow = iso1Part4_ZeroPow::none_;
  } // namespace PICS_EVCC_Tester
} // namespace Pics_15118

namespace Pics_15118_2
{
  using namespace DataStructure_HAL_61851;
  using namespace DataStructure_PICS_15118;
  using namespace DataStructure_PIXIT_15118_2;
  namespace PICS_15118_2 {
    namespace PICS_CMN {
      /* Indication for explicit testing V2GTP by using SDP payload  */
      bool PICS_CMN_CMN_V2gtpSdp = true;
      /* Indication for explicit testing V2GTP by using V2G payload */
      bool PICS_CMN_CMN_V2gtpV2g = true;
      /* Indication for explicit testing of Renegotiation  */
      bool PICS_CMN_CMN_Renegotiation = false;
      /* Indicates the iteration of the ChargingStatus (AC) or 
        CurrentDemand (DC) loop, when ReNegotiation shall be triggered 
        (shall be smaller or equal to PICS_CMN_CMN_LoopCounter).  */
      uint32_t PICS_CMN_CMN_RenegotiationLoopIndication = 1200;
      /* Indicates the number of iterations of the ChargingStatus (AC) or CurrentDemand (DC) loop  */
      uint32_t PICS_CMN_CMN_LoopCounter = 2400;
      /* Indication for enabling Test Group: Invalid V2GTP data fields  */
      bool PICS_CMN_CMN_InvalidV2gtpDataFields = true;
      /* Indication for enabling Test Group: SDP Timeouts and invalid SDP data fields  */
      bool PICS_CMN_CMN_SDPTimeoutsAndInvalidData = true;
      /* Indication for enabling Test Group: V2G fAILED response codes  */
      bool PICS_CMN_CMN_FailedResponseCodes = true;
      /* Indication for enabling Test Group: V2G timeouts  */
      bool PICS_CMN_CMN_V2gTimeouts = true;
      /* Indication for selected PKI Choice: i) PKI_1, ii) PKI_2, iii) PKI_3, iv) PKI_4, v) PKI_5, vi) PKI_6, vii) PKI_7  */
      iso1Part4_PkiType PICS_CMN_CMN_PkiName = iso1Part4_PkiType::PKI_1;
    }
    namespace PICS_SECC_Tester {
      int8_t par_EVRESSSOC = 0;
      /* Indication for explicit testing of State C/D of IEC 61851‐1:2017, Annex A during charging  */
      IEC_61851_States PICS_SECC_CMN_EvStateInChargeProgress = C;
      /* Indication for explicit testing of WeldingDetection  */
      bool PICS_SECC_DC_WeldingDetection = true;
      /* Indication for using a departure time  */
      bool PICS_SECC_CMN_DepartureTime = true;
      /* Indication for enabling a maximal number of entries in the SAScheduleTuple */
      bool PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true;
    }
    namespace PICS_EVCC_Tester {
      /* Indication for explicit testing of MeteringReceipt message  */
      bool PICS_EVCC_CMN_ReceiptRequired = true;
      /* Indication for enabling Test Group: Invalid states and duty cycles */
      bool PICS_EVCC_CMN_InvalidStatesAndDutyCycles = true;
      /* Indication for enabling Test Group: Invalid V2G messages  */
      bool PICS_EVCC_CMN_InvalidV2GMessages = true;
      /* Indication for using a SalesTariff  */
      bool PICS_CMN_EVCC_SalesTariff = true;
    }
  }
} // namespace Pics_15118_2