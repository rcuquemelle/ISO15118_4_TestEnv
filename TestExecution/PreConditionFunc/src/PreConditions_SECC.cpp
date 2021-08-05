#include "PreConditions_SECC.h"
#include "Common_Cfg.h"
#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"
#include "PAInterface.h"
#include "TestSystemLogging.h"
#include "TB_SECC_Msg.h"
#include "CommonLib.h"

using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_CMN;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_2::Timer_par_15118_2;
using namespace DataStructure_PICS_15118;
using namespace urn_iso_15118_2_2013_MsgDataTypes;
using namespace DataStructure_PIXIT_15118_2;

// check power flow ??
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SetPowerFlowConfiguration_001()
{
  // connect CP, PE
  f_SECC_changeValidStateCondition(A);
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return pass;
}
// check plc data link status (polling to external program)
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_PLCLinkStatusCombinedTesting_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict = f_SECC_CMN_PR_SetPowerFlowConfiguration_001();
  // if CombineTesting enable -> f_SECC_CMN_PR_PLCLinkStatus_001 -> call to API 15118-5 -> establish Datalink
  if (PICS_CMN_CMN_CombinedTesting)
  {
    // TODO: polling external program - PreConditions_SECC_15118_3, plc link status (not implement yet)
    verdict = f_SECC_CMN_PR_PLCLinkStatus_002(systemSECC, mtc, v_HAL_61851_Listener);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
// set state A and check status
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_StateA_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // plc link check
  verdict_val verdict = f_SECC_CMN_PR_PLCLinkStatusCombinedTesting_001(v_HAL_61851_Listener);
  // if combinedTesting enable -> above PLC function already establish DataLink and in state B
  // -> below step of transition from A to B is unnecessary
  if (!PICS_CMN_CMN_CombinedTesting)
  {
    // change to State A
    f_SECC_changeValidStateCondition(A);
    verdict = f_SECC_setState(this->systemSECC, A, v_HAL_61851_Listener);
    PAsleep(par_CMN_waitForNextHAL);
    if (this->mtc != nullptr) {
      if (this->mtc->pt_HAL_61851_Port != nullptr) {
        this->mtc->pt_HAL_61851_Port->clear();
      }
      else{
        Logging::error(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]: MTC HAL61851 port is not mapped before use",__FUNCTION__));
      }
    }
    else{
      Logging::error(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]: MTC reference is null",__FUNCTION__));
    }
    verdict = f_SECC_setProximity(0);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
// config proximity value
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SetProximityPilot_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // set state A
  verdict_val verdict = f_SECC_CMN_PR_StateA_001(v_HAL_61851_Listener);
  // if combinedTesting enable -> above PLC function already establish DataLink and in state B
  // -> below step of transition from A to B is unnecessary
  if (!PICS_CMN_CMN_CombinedTesting)
  {
    // start HAL 61851
    v_HAL_61851_Listener->stop();
    v_HAL_61851_Listener->start();
    if (PICS_CMN_CMN_ChargingMode == DataStructure_PICS_15118::iso1Part4_ChargingMode::aC)
    {
      // check frequency
      f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
      f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
      this->mtc->vc_validDutyCycleLowerBound2 = 100;
      this->mtc->vc_validDutyCycleUpperBound2 = 100;
    }
    // set proximity line
    if (verdict == pass)
    {
      /* TODO: Check proximity condition in system (different between AC(current level), DC) */
      if (PICS_CMN_CMN_PlugType == DataStructure_PICS_15118::iso1Part4_PlugType::type1)
      {
        // cc_proximity_type1: constant value -> change value of proximity detect circuit?
        verdict = f_SECC_setProximity(cc_proximity_type1);
      }
      else
      {
        if (PICS_CMN_CMN_ChargingMode == iso1Part4_ChargingMode::aC)
        {
          int v_proximity_type2_AC;
          if (PICS_CMN_AC_CableCapability == iso1Part4_CableCapabilityACType::capability13A)
          {
            v_proximity_type2_AC = cc_proximity_type2_AC_13A;
          }
          else if (PICS_CMN_AC_CableCapability == iso1Part4_CableCapabilityACType::capability20A)
          {
            v_proximity_type2_AC = cc_proximity_type2_AC_20A;
          }
          else if (PICS_CMN_AC_CableCapability == iso1Part4_CableCapabilityACType::capability32A)
          {
            v_proximity_type2_AC = cc_proximity_type2_AC_32A;
          }
          else
          {
            v_proximity_type2_AC = cc_proximity_type2_AC_63A;
          }
          // set proximity base on AC type
          verdict = f_SECC_setProximity(v_proximity_type2_AC);
        }
        else
        {
          verdict = f_SECC_setProximity(cc_proximity_type2_DC);
        }
      }
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
// set state B and SLAC connection
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_StateB_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  // control/check proximity is connect (state A)
  verdict_val verdict = f_SECC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
  if (!PICS_CMN_CMN_CombinedTesting)
  {
    if (verdict == pass)
    {
      // check state
      f_SECC_changeValidStateCondition(B);
      // change to state B
      verdict = f_SECC_setState(this->systemSECC, B, v_HAL_61851_Listener);
      // wait 0.5s (plug in)
      PAsleep(par_CMN_waitForNextHAL);
      // if combinedTesting enable -> this PLC function already establish DataLink and in state B
      verdict = f_SECC_CMN_PR_PLCLinkStatus_001(systemSECC, mtc);
    }
  }
  // start CommunicationSetup_Timer
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->start();
  this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->start();
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
// to state B and get port/ip of server by SDP
// UDP enabled in f_SECC_CMN_PR_InitConfiguration_001
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_Binding_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_SDP> tb = std::make_shared<TestBehavior_SECC_SDP>(this->mtc, this->systemSECC);
  // call state B and SLAC check for datalink before binding operation
  verdict_val verdict = f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  if (PICS_CMN_CMN_CombinedTesting)
  {
    // unmap slac after connection datalink is done for combine testing
    // this->cfg->f_SECC_PO_ShutdownConfiguration_002(this->systemSECC);
  }
  // SECC_Binding Behavior
  if (verdict == pass)
  {
    iso1Part4_Security_TYPE v_security = cc_hexTls;
    // external identification mean (rfid) and no TLS
    if ((PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM) && (PIXIT_SECC_CMN_TLS == false))
    {
      v_security = cc_hexTcp;
    }
    // send SDP to get SUT TCP IPV6 address and port, if incorrect security return then result in inconclusion result
    verdict = tb->f_SECC_CMN_TB_VTB_SDP_001(v_security, inconc);
    // vc_Security of receive SDP == TCP without TLS
    // this->systemSECC->_pUDPIf->stop();
    if (this->mtc->vc_Security == cc_hexTcp)
    {
      // store result to vc_v2g_tcp_tls_parameter for later use/ get data from UDP var to TCP struct
      this->mtc->vc_v2g_tcp_tls_parameter->seccIpaddress = this->mtc->vc_V2G_Port_IpAddress;
      this->mtc->vc_v2g_tcp_tls_parameter->seccPort = this->mtc->vc_V2G_Port_PortNumber;
      this->mtc->vc_v2g_tcp_tls_parameter->security = cc_hexTcp;
    }
    else if (this->mtc->vc_Security == cc_hexTls)
    {
      // NO TLS CERT
      this->mtc->vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
      if (this->mtc->getverdict() == pass)
      {
        this->mtc->vc_v2g_tcp_tls_parameter->seccIpaddress = this->mtc->vc_V2G_Port_IpAddress;
        this->mtc->vc_v2g_tcp_tls_parameter->seccPort = this->mtc->vc_V2G_Port_PortNumber;
        this->mtc->vc_v2g_tcp_tls_parameter->security = cc_hexTls;
        // TODO: TLS, current implementation does not has TLS (plug and charge)
        // tlsParameter := {
        //   cipherSuite := p_cipherSuite,
        //   enabledProtocol := p_enabledProtocol,
        //   result := {
        //   certificate := p_certificate
        //   }
        // }
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.cipherSuite = this->mtc->vc_cipherSuite;
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.enabledProtocol = "";
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.result.certificate = *(this->mtc->vc_v2gRootCert);
      }
    }
    else
    {
      Logging::error(LogPreFnc_ENABLE, "Invalid security type was chosen.");
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SupportedAppProtocol_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_SupportedAppProtocol> tb = std::make_shared<TestBehavior_SECC_SupportedAppProtocol>(this->mtc, this->systemSECC);
  std::shared_ptr<Configuration_15118_2> cfg = std::make_shared<Configuration_15118_2>(this->mtc);
  // binding operation
  verdict_val verdict = f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  // SECC_SupportedAppProtocol Behavior
  if (verdict == pass)
  {
    // connect TCP port
    cfg->f_SECC_CMN_PR_InitConfiguration_002(this->systemSECC, pass, inconc);
    // send supportedAppProtocolRequest message
    verdict = this->mtc->getverdict();
    if (pass == verdict)
    {
      verdict = tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_001(inconc);
      //clear SDP Port
      this->mtc->pt_V2G_UDP_SDP_Port->clear();
    }
    // this->mtc->vc_Default_SDP_Message = activate(a_SDP_Message());
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SessionSetup_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict = f_SECC_CMN_PR_SupportedAppProtocol_001(v_HAL_61851_Listener);
  std::shared_ptr<TestBehavior_SECC_SessionSetup> tb = std::make_shared<TestBehavior_SECC_SessionSetup>(this->mtc, this->systemSECC);
  // SECC_SessionSetup Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_CMN_TB_VTB_SessionSetup_001(inconc);
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
    this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->stop();
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_ServiceDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict = f_SECC_CMN_PR_SessionSetup_001(v_HAL_61851_Listener);
  std::shared_ptr<TestBehavior_SECC_ServiceDiscovery> tb = std::make_shared<TestBehavior_SECC_ServiceDiscovery>(this->mtc, this->systemSECC);
  // SECC_ServiceDiscovery Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_CMN_TB_VTB_ServiceDiscovery_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_ServiceDetail_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict = f_SECC_CMN_PR_ServiceDiscovery_001(v_HAL_61851_Listener);
  std::shared_ptr<TestBehavior_SECC_ServiceDetail> tb = std::make_shared<TestBehavior_SECC_ServiceDetail>(this->mtc, this->systemSECC);
  // SECC_ServiceDetail Behavior
  if ((verdict == pass) && (ispresent(this->mtc->vc_serviceList) && (PIXIT_SECC_CMN_VAS == DataStructure_PIXIT_15118_2::iso1Part4_VASSECC::serviceDetail)))
  {
    // if CS return service list and configuration check service details enable
    if (!((PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM) && (PIXIT_SECC_CMN_TLS == false)))
    {  // if identification mode = P&C or TLS enable
      verdict = tb->f_SECC_CMN_TB_VTB_ServiceDetail_001(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_PaymentServiceSelection_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict = f_SECC_CMN_PR_ServiceDetail_001(v_HAL_61851_Listener);
  std::shared_ptr<TestBehavior_SECC_PaymentServiceSelection> tb = std::make_shared<TestBehavior_SECC_PaymentServiceSelection>(this->mtc, this->systemSECC);
  // SECC_PaymentServiceSelection Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_CMN_TB_VTB_PaymentServiceSelection_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_CertificateInstallation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_CertificateInstallation> tb_certIns = std::make_shared<TestBehavior_SECC_CertificateInstallation>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  /* SECC_CertificateInstallation Behavior Implement when Plug and Charge function is available */
  if (verdict == pass)
  {
    verdict = tb_certIns->f_SECC_CMN_TB_VTB_CertificateInstallation_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_CertificateUpdate_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_CertificateUpdate> tb_certUp = std::make_shared<TestBehavior_SECC_CertificateUpdate>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  /* SECC_CertificateUpdate Behavior Implement when Plug and Charge function is available */
  if (verdict == pass)
  {
    verdict = tb_certUp->f_SECC_CMN_TB_VTB_CertificateUpdate_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_PaymentDetails_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  /* Implement when Plug and Charge function is available */
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_PaymentDetails> tb_pmentDetail = std::make_shared<TestBehavior_SECC_PaymentDetails>(this->mtc, this->systemSECC);
  if ((PIXIT_SECC_CMN_CertificateHandling == DataStructure_PIXIT_15118_2::iso1Part4_CertificateHandlingSECC::certUpdate) &&
    (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
  {
    verdict = f_SECC_CMN_PR_CertificateUpdate_001(v_HAL_61851_Listener);
  }
  if ((PIXIT_SECC_CMN_CertificateHandling == DataStructure_PIXIT_15118_2::iso1Part4_CertificateHandlingSECC::certInstall) &&
      (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
  {
    verdict = f_SECC_CMN_PR_CertificateInstallation_001(v_HAL_61851_Listener);
  }
  if ((PIXIT_SECC_CMN_CertificateHandling == DataStructure_PIXIT_15118_2::iso1Part4_CertificateHandlingSECC::none_) &&
      (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
  {
    verdict = f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  }
  // SECC_PaymentDetails Behavior
  if (verdict == pass)
  {
    verdict = tb_pmentDetail->f_SECC_CMN_TB_VTB_PaymentDetails_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_Authorization_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_Authorization> tb = std::make_shared<TestBehavior_SECC_Authorization>(this->mtc, this->systemSECC);

  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
  {
    verdict = f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  }
  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM)
  {
    verdict = f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  }
  // SECC_Authorization Behavior
  if (verdict == pass)
  {
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM)
    {
      verdict = tb->f_SECC_CMN_TB_VTB_Authorization_001(inconc);
    }
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
    {
      verdict = tb->f_SECC_CMN_TB_VTB_Authorization_002(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

/* PreConditions for AC-TestCases */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_ChargeParameterDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);

  /* SECC_ChargeParameterDiscovery Behavior */
  if (verdict == pass)
  {
    if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
    {
      // normal PMax Schedule
      verdict = tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(inconc);
    }
    else
    {
      // Plug and Charge
      verdict = tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_PowerDeliveryStart_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  // SECC_PowerDeliveryStart Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_ChargingStatus_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargingStatus> tb = std::make_shared<TestBehavior_SECC_ChargingStatus>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_AC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  // SECC_ChargingStatus Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_AC_TB_VTB_ChargingStatus_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* AC Precondition for charging loop - stop */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_ChargingStatus> tb_chargeSts = std::make_shared<TestBehavior_SECC_ChargingStatus>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb_meterRe = std::make_shared<TestBehavior_SECC_MeteringReceipt>(this->mtc, this->systemSECC);
  // authorization precondition
  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    uint32_t loopCounter = 0;
    uint32_t renegotiationLoopInd = PICS_CMN_CMN_RenegotiationLoopIndication;
    if (!PICS_CMN_CMN_Renegotiation)
    {
      /* if renegotiation is no enable */
      renegotiationLoopInd = -1;
    };
    /* Loop until charging progress end - default MTC vc_ChargeProgress = iso1Part4_ChargeProgressType::start_ */
    while (this->mtc->vc_ChargeProgress != iso1Part4_ChargeProgressType::stop_)
    {
      // ChargeParameterDiscovery
      if (verdict == pass)
      {
        if ((this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_) && (loopCounter == 0))
        {
          if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
          {
            verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(inconc);
          }
          else
          {
            verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(inconc);
          }
        }
      }
      else
      {
        return verdict;
      }
      // PowerDelivery
      if (verdict == pass)
      {
        if (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_)
        {
          verdict = tb_powerDeli->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, inconc);
        }
      }
      else
      {
        return verdict;
      }
      /* EVSE Notification not stop or renegotiation and loop counter < max value and loop counter != renegotiation loop counter */
      while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter) && (loopCounter != renegotiationLoopInd))
      {
        // ChargingStatus
        if (verdict == pass)
        {
          verdict = tb_chargeSts->f_SECC_AC_TB_VTB_ChargingStatus_001(inconc);
        }
        else
        {
          return verdict;
        }
        // MeteringReceipt
        if (verdict == pass)
        {
          /* if vc_receiptRequired status = true and P&C mode*/
          if (this->mtc->vc_receiptRequired && (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
          {
            verdict = tb_meterRe->f_SECC_AC_TB_VTB_MeteringReceipt_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        loopCounter = loopCounter + 1;
        if (verdict == pass)
        {
          Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> ChargingStatus: {}", loopCounter));
          PAsleep(par_SECC_chargingLoop_pause);
        }
      }
      /* if evse status return = renegotiation or reached negotiation loop */
      if ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::reNegotiation) || ((loopCounter == renegotiationLoopInd) && PICS_CMN_CMN_Renegotiation))
      {
        if (verdict == pass)
        {
          /* change mtc charge progress */
          this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::renegotiate;
        }
        else
        {
          return verdict;
        }
        if (verdict == pass)
        {
          /* request renegotiation from ev */
          verdict = tb_powerDeli->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, inconc);
        }
        else
        {
          return verdict;
        }
        if (verdict == pass)
        {
          /* change max request current to 10A */
          this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 10};
          if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
          {
            verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(inconc);
          }
          else
          {
            verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(inconc);
          }
          if (verdict == pass)
          {
            /* after renegotiation > change chargeProgress back to start_ */
            this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::start_;
            renegotiationLoopInd = 0;
            this->mtc->vc_EVSENotification = iso1Part4_EVSENotificationType::none_;
          }
        }
        else
        {
          return verdict;
        }
      }
      if ((loopCounter == PICS_CMN_CMN_LoopCounter) || (this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::stopCharging))
      {
        /* if loopcounter = end, or evse notification = stop > change chargeProgress to stop_ and break while loop */
        this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::stop_;
      }
    }
    Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  }
  return verdict;
}
/* AC create renegotiation precondition */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_ChargingStatusOrMeteringReceiptRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_ChargingStatus> tb_chargeSts = std::make_shared<TestBehavior_SECC_ChargingStatus>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb_meterRe = std::make_shared<TestBehavior_SECC_MeteringReceipt>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    while (this->mtc->vc_ChargeProgress != iso1Part4_ChargeProgressType::renegotiate)
    {
      // ChargeParameterDiscovery
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
        {
          verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(inconc);
        }
        else
        {
          verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(inconc);
        }
      }
      else
      {
        return verdict;
      }
      // PowerDelivery
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_powerDeli->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, inconc);
      }
      else
      {
        return verdict;
      }
      uint32_t loopCounter = 0;
      while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) &&
        (loopCounter < PICS_CMN_CMN_LoopCounter) &&
          (loopCounter != PICS_CMN_CMN_RenegotiationLoopIndication))
      {
        // ChargingStatus
        if (verdict == pass)
        {
          verdict = tb_chargeSts->f_SECC_AC_TB_VTB_ChargingStatus_001(inconc);
        }
        else
        {
          return verdict;
        }
        // MeteringReceipt
        if (verdict == pass)
        {
          if (this->mtc->vc_receiptRequired && (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
          {
            verdict = tb_meterRe->f_SECC_AC_TB_VTB_MeteringReceipt_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        loopCounter = loopCounter + 1;
        if (verdict == pass)
        {
          Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> ChargingStatus: {}", loopCounter));
          PAsleep(par_SECC_chargingLoop_pause);
        }
      }
      if ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::reNegotiation) ||
        ((loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication) && PICS_CMN_CMN_Renegotiation))
      {
        if (verdict == pass)
        {
          this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::renegotiate;
        }
        else
        {
          return verdict;
        }
      }
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* AC send precondition powerdelivery renegotiation */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_PowerDeliveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict = f_SECC_AC_PR_ChargingStatusOrMeteringReceiptRenegotiation_001(v_HAL_61851_Listener);
  // f_SECC_PowerDeliveryStopAC Behavior
  if (verdict == pass)
  {
    verdict = tb_powerDeli->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* AC renegotiation precondition for powerdelivery start */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_ChargeParameterDiscoveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  verdict = f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  // f_SECC_ChargeParameterDiscovery Behavior
  if (verdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 10};
    if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
    {
      verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(inconc);
    }
    else
    {
      verdict = tb_chargParam->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_PowerDeliveryStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict = f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  // SECC_f_SECC_PowerDeliveryStopAC Behavior
  if (verdict == pass)
  {
    verdict = tb_powerDeli->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* run a full sequence charging then pause */
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_SessionStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_SessionStop> tb_sessionStop = std::make_shared<TestBehavior_SECC_SessionStop>(this->mtc, this->systemSECC);
  verdict = f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  // SECC_WeldingDetection Behavior
  if (verdict == pass)
  {
    verdict = tb_sessionStop->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::pause, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* run a full charging sequence then terminate*/
verdict_val PreConditions_SECC_15118_2::f_SECC_AC_PR_SessionStop_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_SessionStop> tb_sessionStop = std::make_shared<TestBehavior_SECC_SessionStop>(this->mtc, this->systemSECC);
  verdict = f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  // SECC_WeldingDetection Behavior
  if (verdict == pass)
  {
    verdict = tb_sessionStop->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

/*********************************************************************************/
/* PreConditions for DC-TestCases */
verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_ChargeParameterDiscovery_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  // SECC_ChargeParameterDiscovery Behavior
  if (verdict == pass)
  {
    if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
    {
      verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
    }
    else
    {
      verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_CableCheck_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_CableCheck> tb_cableCheck = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  // SECC_CableCheck Behavior
  if (verdict == pass)
  {
    verdict = tb_cableCheck->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, inconc);
  }
  /* function to control external power load?? */
  // if (PIXIT_CMN_DC_PowerFlow && (verdict == pass))
  // {
  //   // external hw function
  //   if (PICS_CMN_DC_TwoQuadrantOperation)
  //   {
  //     ExternalFunctions_PSI9000.fx_setDCPowerSwitchStatus(true);
  //   }
  //   fx_setDCPowerSwitchStatus(true);
  // }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_PreCharge_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_PreCharge> tb_preCharge = std::make_shared<TestBehavior_SECC_PreCharge>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_DC_PR_CableCheck_001(v_HAL_61851_Listener);
  // SECC_PreCharge Behavior
  if (verdict == pass)
  {
    verdict = tb_preCharge->f_SECC_DC_TB_VTB_PreCharge_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_PowerDeliveryStart_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  // SECC_PowerDeliveryStart Behavior
  if (verdict == pass)
  {
    verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, false, true, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_CurrentDemand_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->systemSECC);
  verdict_val verdict = f_SECC_DC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    // SECC_PowerDeliveryStart Behavior
    verdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}
/* DC charging loop until stop */
verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CableCheck> tb_cableCheck = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PreCharge> tb_preCharge = std::make_shared<TestBehavior_SECC_PreCharge>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb_meterRe = std::make_shared<TestBehavior_SECC_MeteringReceipt>(this->mtc, this->systemSECC);

  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    uint32_t loopCounter = 0;
    uint32_t renegotiationLoopInd = PICS_CMN_CMN_RenegotiationLoopIndication;
    if (!PICS_CMN_CMN_Renegotiation)
    {
      renegotiationLoopInd = -1;
    };
    while (this->mtc->vc_ChargeProgress != iso1Part4_ChargeProgressType::stop_)
    {
      // ChargeParameterDiscovery for 1st start, skip with renegotiation phase
      if (verdict == pass)
      {
        if ((this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_) && (loopCounter == 0))
        {
          if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
          {
            verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
          }
          else
          {
            verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
          }
        }
      }
      else
      {
        return verdict;
      }
      // CableCheck
      if (verdict == pass)
      {
        if (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_)
        {
          verdict = tb_cableCheck->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, inconc);
        }
      }
      else
      {
        return verdict;
      }
      // PreCharge
      if (verdict == pass)
      {
        if (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_)
        {
          verdict = tb_preCharge->f_SECC_DC_TB_VTB_PreCharge_001(inconc);
        }
      }
      else
      {
        return verdict;
      }
      // PowerDelivery
      if (verdict == pass)
      {
        if (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_)
        {
          verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, false, true, inconc);
        }
      }
      else
      {
        return verdict;
      }
      /* run charging loop until renegotion loop or endloop or request from evse */
      while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter) && (loopCounter != renegotiationLoopInd))
      {
        // CurrentDemand
        if (verdict == pass)
        {
          // increase SOC
          if ((this->mtc->vc_DC_EVStatus.EVRESSSOC+100/PICS_CMN_CMN_LoopCounter)  <= 100)
          {
            this->mtc->vc_DC_EVStatus.EVRESSSOC += 100/PICS_CMN_CMN_LoopCounter;
            Logging::info(LogPreFnc_ENABLE, fmt::format("this->mtc->vc_DC_EVStatus.EVRESSSOC = {0}%", this->mtc->vc_DC_EVStatus.EVRESSSOC));
          }
          verdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
        }
        else
        {
          return verdict;
        }
        // MeteringReceipt
        if (verdict == pass)
        {
          if ((this->mtc->vc_receiptRequired) && (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
          {
            verdict = tb_meterRe->f_SECC_DC_TB_VTB_MeteringReceipt_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        loopCounter = loopCounter + 1;
        if (verdict == pass)
        {
          Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> CurrentDemand: {}", loopCounter));
          PAsleep(par_SECC_chargingLoop_pause);
        }
      }
      /* RENEGOTIATION */
      if ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::reNegotiation) ||
          ((loopCounter == renegotiationLoopInd) && PICS_CMN_CMN_Renegotiation))
      {
        if (verdict == pass)
        {
          this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::renegotiate;
        }
        else
        {
          return verdict;
        }
        if (verdict == pass)
        {
          verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, false, true, inconc);
        }
        else
        {
          return verdict;
        }
        if (verdict == pass)
        {
          this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 50};
          if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
          {
            verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
          }
          else
          {
            verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
          }
          if (verdict == pass)
          {
            this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::start_;
            renegotiationLoopInd = 0;
            this->mtc->vc_EVSENotification = iso1Part4_EVSENotificationType::none_;
          }
        }
        else
        {
          return verdict;
        }
      }
      if ((loopCounter == PICS_CMN_CMN_LoopCounter) ||
        (this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::stopCharging))
      {
        this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::stop_;
      }
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CableCheck> tb_cableCheck = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PreCharge> tb_preCharge = std::make_shared<TestBehavior_SECC_PreCharge>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb_meterRe = std::make_shared<TestBehavior_SECC_MeteringReceipt>(this->mtc, this->systemSECC);

  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    while (this->mtc->vc_ChargeProgress != iso1Part4_ChargeProgressType::renegotiate)
    {
      // ChargeParameterDiscovery
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
        {
          verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
        }
        else
        {
          verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
        }
      }
      else
      {
        return verdict;
      }
      // CableCheck
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_cableCheck->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, inconc);
      }
      else
      {
        return verdict;
      }
      // PreCharge
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_preCharge->f_SECC_DC_TB_VTB_PreCharge_001(inconc);
      }
      else
      {
        return verdict;
      }
      // PowerDelivery
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, false, true, inconc);
      }
      else
      {
        return verdict;
      }
      uint32_t loopCounter = 0;
      while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) &&
        (loopCounter < PICS_CMN_CMN_LoopCounter) &&
          (loopCounter != PICS_CMN_CMN_RenegotiationLoopIndication))
      {
        // CurrentDemand
        if (verdict == pass)
        {
          if ((this->mtc->vc_DC_EVStatus.EVRESSSOC+100/PICS_CMN_CMN_LoopCounter)  <= 100)
          {
            this->mtc->vc_DC_EVStatus.EVRESSSOC += 100/PICS_CMN_CMN_LoopCounter;
            Logging::info(LogPreFnc_ENABLE, fmt::format("this->mtc->vc_DC_EVStatus.EVRESSSOC = {0}%", this->mtc->vc_DC_EVStatus.EVRESSSOC));
          }
          verdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
        }
        else
        {
          return verdict;
        }
        // MeteringReceipt
        if (verdict == pass)
        {
          if (this->mtc->vc_receiptRequired && (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
          {
            verdict = tb_meterRe->f_SECC_DC_TB_VTB_MeteringReceipt_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        loopCounter = loopCounter + 1;
        if (verdict == pass)
        {
          Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> CurrentDemand: {}", loopCounter));
          PAsleep(par_SECC_chargingLoop_pause);
        }
      }
      if ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::reNegotiation) ||
          ((loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication) && PICS_CMN_CMN_Renegotiation))
      {
        if (verdict == pass)
        {
          this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::renegotiate;
        }
        else
        {
          return verdict;
        }
      }
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_002(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CableCheck> tb_cableCheck = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PreCharge> tb_preCharge = std::make_shared<TestBehavior_SECC_PreCharge>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_MeteringReceipt> tb_meterRe = std::make_shared<TestBehavior_SECC_MeteringReceipt>(this->mtc, this->systemSECC);

  verdict_val verdict = f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  if (verdict == pass)
  {
    int moduloValueSOC;
    if (PICS_CMN_CMN_LoopCounter >= 100)
    {
      //soc init values
      int socDifference = 100 - par_EVRESSSOC;
      float socValue = (int2float(socDifference) / int2float(PICS_CMN_CMN_LoopCounter));
      moduloValueSOC = float2int(1.0 / socValue);
    }
    while (this->mtc->vc_ChargeProgress != iso1Part4_ChargeProgressType::renegotiate)
    {
      // ChargeParameterDiscovery
      if (verdict == pass && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
        {
          verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
        }
        else
        {
          verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
        }
      }
      else
      {
        return verdict;
      }
      // CableCheck
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_cableCheck->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, inconc);
      }
      else
      {
        return verdict;
      }
      // PreCharge
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_preCharge->f_SECC_DC_TB_VTB_PreCharge_001(inconc);
      }
      else
      {
        return verdict;
      }
      // PowerDelivery
      if ((verdict == pass) && (this->mtc->vc_ChargeProgress == iso1Part4_ChargeProgressType::start_))
      {
        verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, false, true, inconc);
      }
      else
      {
        return verdict;
      }
      uint32_t loopCounter = 0;
      while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) &&
        (loopCounter < PICS_CMN_CMN_LoopCounter) &&
          (loopCounter != PICS_CMN_CMN_RenegotiationLoopIndication))
      {
        if (PICS_CMN_CMN_LoopCounter >= 100)
        {
          /* Call external function to control load?? */
          float measVoltage = 300;
          // float measVoltage = fx_getMeasuredVoltage();
          // Logging::info(LogPreFnc_ENABLE, fmt::format("ELR9000 measured voltage ", measVoltage));
          // float measCurrent = fx_getMeasuredCurrent();
          // Logging::info(LogPreFnc_ENABLE, fmt::format("ELR9000 measured current ", measCurrent));
          if (loopCounter == 0)
          {
            /* Set current for external load */
            // fx_setCurrent(par_LoadStartValCurrent);
            // float getCurrent = fx_getCurrent();
            this->mtc->vc_EVTargetCurrent.Value = this->mtc->vc_EVTargetCurrent.Value + 1;
            Logging::info(LogPreFnc_ENABLE, fmt::format("INITIAL Set current: {}", this->mtc->vc_EVTargetCurrent.Value));
          }
          int loopDifference = PICS_CMN_CMN_LoopCounter - loopCounter;
          // increase voltage loop, increase voltage by step until reaching vc_EVTargetVoltage value
          if ((loopCounter > 10) && (measVoltage >= f_CMN_PhysicalValue_GetValue(par_EVBatteryVoltage)))
          {
            float voltageDifference = int2float(this->mtc->vc_EVTargetVoltage.Value) - measVoltage;
            float voltageStep = voltageDifference / int2float(loopDifference);
            float voltageIncrease = measVoltage + voltageStep;
            if (voltageIncrease <= int2float(this->mtc->vc_EVTargetVoltage.Value))
            {
              /* Set voltage for external load */
              // fx_setVoltage(voltageIncrease);
            }
          }
          //soc loop
          if ((loopCounter % moduloValueSOC) == 0)
          {
            // increase SOC
            if ((this->mtc->vc_DC_EVStatus.EVRESSSOC + 1) <= par_EVBatteryStepSize)
            {
              this->mtc->vc_DC_EVStatus.EVRESSSOC = this->mtc->vc_DC_EVStatus.EVRESSSOC + 1;
              Logging::info(LogPreFnc_ENABLE, fmt::format("vc_DC_EVStatus.EVRESSSOC: {0}%, vc_DC_EVStatus.EVErrorCode: {1}, vc_DC_EVStatus.EVErrorCode: {2}"\
                ,this->mtc->vc_DC_EVStatus.EVRESSSOC, this->mtc->vc_DC_EVStatus.EVErrorCode, this->mtc->vc_DC_EVStatus.EVReady));
            }
          }
          // increase current loop
          if ((loopCounter > 1) && ((loopCounter % 100) == 0))
          {
            // float currentValue = fx_getCurrent();
            float currentValue = 0;
            if (currentValue < f_CMN_PhysicalValue_GetValue(par_EVMaximumCurrentLimit))
            {
              // fx_setCurrent(currentValue + 1.0);
              this->mtc->vc_EVTargetCurrent.Value = this->mtc->vc_EVTargetCurrent.Value + 1;
            }
          }
        }
        else
        {
          // fx_setCurrent(par_LoadStartValCurrent);
          // float getCurrent = fx_getCurrent();
          float getCurrent = 1;
          Logging::info(LogPreFnc_ENABLE, fmt::format("INITIAL Set current: {}", getCurrent));
          // keep start current for first 100 loop
          this->mtc->vc_EVTargetCurrent.Value = float2int(par_LoadStartValCurrent);
        }
        // CurrentDemand
        if (verdict == pass)
        {
          if (true)
          {
            verdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        // MeteringReceipt
        if (verdict == pass)
        {
          if ((this->mtc->vc_receiptRequired) && (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
          {
            verdict = tb_meterRe->f_SECC_DC_TB_VTB_MeteringReceipt_001(inconc);
          }
        }
        else
        {
          return verdict;
        }
        loopCounter = loopCounter + 1;
        if (verdict == pass)
        {
          Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> CurrentDemand: {}", loopCounter));
          PAsleep(par_SECC_chargingLoop_pause);
        }
      }
      if ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::reNegotiation) ||
          ((loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication) && PICS_CMN_CMN_Renegotiation))
      {
        if (verdict == pass)
        {
          this->mtc->vc_ChargeProgress = iso1Part4_ChargeProgressType::renegotiate;
        }
        else
        {
          return verdict;
        }
      }
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_PowerDeliveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict = f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_001(v_HAL_61851_Listener);
  // f_SECC_PowerDeliveryStopDC Behavior
  if (verdict == pass)
  {
    verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, false, true, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_ChargeParameterDiscoveryRenegotiation_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_ChargeParameterDiscovery> tb_chargParam = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CableCheck> tb_cableCheck = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PreCharge> tb_preCharge = std::make_shared<TestBehavior_SECC_PreCharge>(this->mtc, this->systemSECC);
  verdict = f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  // f_SECC_ChargeParameterDiscovery Behavior
  if (verdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 50};
    if (PIXIT_SECC_CMN_SalesTariff == iso1Part4_SalesTariff::unknown)
    {
      verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(inconc);
    }
    else
    {
      verdict = tb_chargParam->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(inconc);
    }
  }
  // CableCheck
  if (verdict == pass)
  {
    verdict = tb_cableCheck->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, inconc);
  }
  else
  {
    return verdict;
  }
  // PreCharge
  if (verdict == pass)
  {
    verdict = tb_preCharge->f_SECC_DC_TB_VTB_PreCharge_001(inconc);
  }
  else
  {
    return verdict;
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_PowerDeliveryStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, bool v_setState)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_PowerDelivery> tb_powerDeli = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->systemSECC);
  verdict = f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  // SECC_PowerDeliveryStopDC Behavior
  if (verdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    verdict = tb_powerDeli->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, v_setState, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_WeldingDetection_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_WeldingDetection> tb_weldDetect = std::make_shared<TestBehavior_SECC_WeldingDetection>(this->mtc, this->systemSECC);
  verdict = f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  // SECC_WeldingDetection Behavior
  if (verdict == pass)
  {
    verdict = tb_weldDetect->f_SECC_DC_TB_VTB_WeldingDetection_001(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_SessionStop_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_SessionStop> tb_sessionStop = std::make_shared<TestBehavior_SECC_SessionStop>(this->mtc, this->systemSECC);
  if (PICS_SECC_DC_WeldingDetection)
  {
    verdict = f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  }
  else
  {
    verdict = f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  }
  // SECC_WeldingDetection Behavior
  if (verdict == pass)
  {
    // pause session
    verdict = tb_sessionStop->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::pause, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_DC_PR_SessionStop_002(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_SessionStop> tb_sessionStop = std::make_shared<TestBehavior_SECC_SessionStop>(this->mtc, this->systemSECC);
  if (PICS_SECC_DC_WeldingDetection)
  {
    verdict = f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  }
  else
  {
    verdict = f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  }
  // SECC_WeldingDetection Behavior
  if (verdict == pass)
  {
    // terminate session
    verdict = tb_sessionStop->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

/* Paused Session */
verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  verdict_val verdict = pass;
  std::shared_ptr<TestBehavior_SECC_SupportedAppProtocol> tb_spAppPro = std::make_shared<TestBehavior_SECC_SupportedAppProtocol>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_SDP> tb_sdp = std::make_shared<TestBehavior_SECC_SDP>(this->mtc, this->systemSECC);

  v_HAL_61851_Listener->stop();
  // v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(true));
  if (PICS_CMN_CMN_ChargingMode == DataStructure_PICS_15118::iso1Part4_ChargingMode::aC)
  {
    f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
    f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
    this->mtc->vc_validDutyCycleLowerBound2 = 100;
    this->mtc->vc_validDutyCycleUpperBound2 = 100;
  }
  /* TODO: check the wakeup condition config */
  if (PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp)
  {
    // B toggle
    this->mtc->tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_setState(this->systemSECC, B, v_HAL_61851_Listener);
    this->mtc->tc_TP_EV_vald_state_duration->wait_timeout();
    // C toggle
    this->mtc->tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_changeValidStateCondition(C);
    f_SECC_setState(this->systemSECC, C, v_HAL_61851_Listener);
    this->mtc->tc_TP_EV_vald_state_duration->wait_timeout();
    // B toggle
    this->mtc->tc_TP_EV_vald_state_duration->start(par_TP_EV_vald_state_duration);
    f_SECC_changeValidStateCondition(B);
    f_SECC_setState(this->systemSECC, B, v_HAL_61851_Listener);
    this->mtc->tc_TP_EV_vald_state_duration->wait_timeout();
  }
  else
  {
    // f_SECC_confirmDutyCycle(v_HAL_61851_Listener, (PICS_CMN_CMN_WakeUp - PIXIT_CMN_CMN_WakeUp + 5.0), inconc);
    if (this->mtc->getverdict() != pass)
    {
      Logging::info(LogPreFnc_ENABLE, "The SUT did not initiate a wake-up within 'PICS_CMN_CMN_WakeUp'.");
    }
  }

  this->mtc->tc_T_conn_max_comm->start(par_T_conn_max_comm);
  /* TODO: ON PLC after pause */
  // f_SECC_getPLCLinkEstablishmentAfterSleepMode(pass, inconc, inconc);
  // unmap(this->mtc->pt_SLAC_Port);
  if (this->mtc->getverdict() == pass)
  {
    f_SECC_setIsConfirmationFlagDC();
    // verdict = f_SECC_confirmDutyCycle(v_HAL_61851_Listener, (par_T_conn_max_comm - this->mtc->tc_T_conn_max_comm->read()), inconc);
  }
  if (this->mtc->getverdict() == pass)
  {
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->start();
    /* SECC_Binding Behavior */
    iso1Part4_Security_TYPE v_security = cc_hexTls;
    if ((PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM) && (PIXIT_SECC_CMN_TLS == false))
    {
      v_security = cc_hexTcp;
    }
    verdict = tb_sdp->f_SECC_CMN_TB_VTB_SDP_001(v_security, inconc);
    if (this->mtc->vc_Security == cc_hexTcp)
    {
      this->mtc->vc_v2g_tcp_tls_parameter->seccIpaddress = this->mtc->vc_V2G_Port_IpAddress;
      this->mtc->vc_v2g_tcp_tls_parameter->seccPort = this->mtc->vc_V2G_Port_PortNumber;
      this->mtc->vc_v2g_tcp_tls_parameter->security = cc_hexTcp;
    }
    else if (this->mtc->vc_Security == cc_hexTls)
    {
      this->mtc->vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
      if (this->mtc->getverdict() == pass)
      {
        this->mtc->vc_v2g_tcp_tls_parameter->seccIpaddress = this->mtc->vc_V2G_Port_IpAddress;
        this->mtc->vc_v2g_tcp_tls_parameter->seccPort = this->mtc->vc_V2G_Port_PortNumber;
        this->mtc->vc_v2g_tcp_tls_parameter->security = cc_hexTls;
        // TODO: TLS, current implementation does not has TLS (plug and charge)
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.cipherSuite = this->mtc->vc_cipherSuite;
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.enabledProtocol = "";
        // this->mtc->vc_v2g_tcp_tls_parameter->tlsParameter.result.certificate = *(this->mtc->vc_v2gRootCert);
      }
    }
    else
    {
      Logging::info(LogPreFnc_ENABLE, "Invalid security type was chosen.");
    }
    /* SECC_SupportedAppProtocol Behavior */
    if (verdict == pass)
    {
      cfg->f_SECC_CMN_PR_InitConfiguration_002(this->systemSECC, pass, inconc);
      verdict = tb_spAppPro->f_SECC_CMN_TB_VTB_SupportedAppProtocol_001(inconc);
      /* clear SDP Port */
      this->mtc->pt_V2G_UDP_SDP_Port->clear();
      // this->mtc->vc_Default_SDP_Message = activate(a_SDP_Message());
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return this->mtc->getverdict();
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_SessionSetupPausedSession_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_SessionSetup> tb = std::make_shared<TestBehavior_SECC_SessionSetup>(this->mtc, this->systemSECC);
  verdict = f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  // SECC_SessionSetup Behavior
  if (verdict == pass)
  {
    verdict = tb->f_SECC_CMN_TB_VTB_SessionSetup_005(inconc);
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}

verdict_val PreConditions_SECC_15118_2::f_SECC_CMN_PR_AuthorizationPausedSession_001(std::shared_ptr<HAL_61851_Listener> & v_HAL_61851_Listener)
{
  verdict_val verdict;
  std::shared_ptr<TestBehavior_SECC_ServiceDiscovery> tb_servDiscovery = std::make_shared<TestBehavior_SECC_ServiceDiscovery>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_ServiceDetail> tb_servDetail = std::make_shared<TestBehavior_SECC_ServiceDetail>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PaymentServiceSelection> tb_pmentSelect = std::make_shared<TestBehavior_SECC_PaymentServiceSelection>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CertificateInstallation> tb_certIns = std::make_shared<TestBehavior_SECC_CertificateInstallation>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_CertificateUpdate> tb_certUp = std::make_shared<TestBehavior_SECC_CertificateUpdate>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_PaymentDetails> tb_pmentDetail = std::make_shared<TestBehavior_SECC_PaymentDetails>(this->mtc, this->systemSECC);
  std::shared_ptr<TestBehavior_SECC_Authorization> tb_auth = std::make_shared<TestBehavior_SECC_Authorization>(this->mtc, this->systemSECC);

  verdict = f_SECC_CMN_PR_SessionSetupPausedSession_001(v_HAL_61851_Listener);
  /* SECC_ServiceDiscovery Behavior */
  if (verdict == pass)
  {
    verdict = tb_servDiscovery->f_SECC_CMN_TB_VTB_ServiceDiscovery_005(inconc);
  }
  /* SECC_ServiceDetail Behavior */
  if ((verdict == pass) && (ispresent(this->mtc->vc_serviceList)))
  {
    verdict = tb_servDetail->f_SECC_CMN_TB_VTB_ServiceDetail_001(inconc);
  }
  /* SECC_PaymentServiceSelection Behavior */
  if (verdict == pass)
  {
    verdict = tb_pmentSelect->f_SECC_CMN_TB_VTB_PaymentServiceSelection_001(inconc);
  }
  if (verdict == pass)
  {
    if ((PIXIT_SECC_CMN_CertificateHandling == DataStructure_PIXIT_15118_2::iso1Part4_CertificateHandlingSECC::certInstall) &&
        (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
    {
      verdict = tb_certIns->f_SECC_CMN_TB_VTB_CertificateInstallation_001(inconc);
    }
  }
  if (verdict == pass)
  {
    if ((PIXIT_SECC_CMN_CertificateHandling == DataStructure_PIXIT_15118_2::iso1Part4_CertificateHandlingSECC::certUpdate) &&
        (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC))
    {
      verdict = tb_certUp->f_SECC_CMN_TB_VTB_CertificateUpdate_001(inconc);
    }
  }
  /* SECC_PaymentDetails Behavior */
  if (verdict == pass)
  {
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
    {
      verdict = tb_pmentDetail->f_SECC_CMN_TB_VTB_PaymentDetails_001(inconc);
    }
  }
  /* SECC_Authorization Behavior */
  if (verdict == pass)
  {
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::eIM)
    {
      verdict = tb_auth->f_SECC_CMN_TB_VTB_Authorization_001(inconc);
    }
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
    {
      verdict = tb_auth->f_SECC_CMN_TB_VTB_Authorization_002(inconc);
    }
  }
  Logging::debug(LogPreFnc_ENABLE, fmt::format("[PRE_CND][{}]",__FUNCTION__));
  return verdict;
}