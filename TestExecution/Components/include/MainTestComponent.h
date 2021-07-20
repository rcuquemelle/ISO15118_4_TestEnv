#ifndef _MAINTESTCOMPONENT_H_
#define _MAINTESTCOMPONENT_H_
#include "PortType.h"
#include "IfRuntime.h"
#include "TCPAdapter.h"
#include "EVCCUdpClient.h"
#include "TsDataType.h"
#include "SeccBasicSignaling.h"
#include "PAInterface.h"
#include "TestSystemLogging.h"
#include "V2gCodecs.h"

// main test component for SECC SUT
// contains test configuration and delimits the lifeline during test execution
// using port for communication, local timers, variables or contants may be assigned to  components
// to store dynamic information during test case execution.
class SECC_Tester : public std::enable_shared_from_this<SECC_Tester>
{
public:
  // runtime
  std::shared_ptr<IfRuntime> _pRuntime;
  /* Runtime var for MTC*/
  std::shared_ptr<CppCommon::Asio::Service> _ptrService;

  /* PORT variable for MTC*/
  // V2G_TCP_TLS_ALM_SECC_Port port
  std::shared_ptr<V2G_TCP_TLS_ALM_SECC_Port> pt_V2G_TCP_TLS_ALM_SECC_Port;
  // V2G_UDP_SDP_Port port
  std::shared_ptr<V2G_UDP_SDP_Port> pt_V2G_UDP_SDP_Port;
  // HAL_61851_Port
  std::shared_ptr<HAL_61851_Port> pt_HAL_61851_Port;
  // HAL_61851_Internal_Port
  std::shared_ptr<HAL_61851_Internal_Port> pt_HAL_61851_Internal_Port;
  // slac port for checking data link layer
  std::shared_ptr<SLAC_Port> pt_SLAC_Port;

  // verdict result
  verdicttype tc_verdict;

  /* Timer variable for MTC*/
  // local timers manager
  std::shared_ptr<PATimerManager> pt_TimerManager;
  // Message Timer in the EVCC | EVCC message timeouts
  std::shared_ptr<PATimer> tc_V2G_EVCC_Msg_Timer;
  // SDP timeout
  std::shared_ptr<PATimer> tc_EVCC_SDP_Timer;
  // Sequence CommunicationSetup timeouts (fixed value)
  std::shared_ptr<PATimer> tc_V2G_EVCC_CommunicationSetup_Timer;
  std::shared_ptr<PATimer> tc_V2G_SECC_CommunicationSetup_Timer;

  // Non-standardized CMN Processing timeouts
  std::shared_ptr<PATimer> tc_CMN_TCP_Connection_Termination_Timer;

  std::shared_ptr<PATimer> tc_V2G_SECC_Sequence_Timer;
  // Sequence Timer in the EVCC
  std::shared_ptr<PATimer> tc_V2G_EVCC_Sequence_Timer;

  // Ongoing Timer in the EVCC
  std::shared_ptr<PATimer> tc_V2G_EVCC_Ongoing_Timer;
  std::shared_ptr<PATimer> tc_V2G_SECC_Ongoing_Timer;

  std::shared_ptr<PATimer> tc_V2G_EVCC_CableCheck_Timer;
  std::shared_ptr<PATimer> tc_V2G_EVCC_PreCharge_Timer;

  // 61851 state transition delay
  std::shared_ptr<PATimer> tc_TP_EV_vald_state_duration;
  std::shared_ptr<PATimer> tc_T_conn_max_comm;

public:
  /* TEST variable for MTC*/
  // MAC address of evcc 6byte
  std::vector<uint8_t> vc_eVCCID;
  // session id 8byte
  std::vector<uint8_t> vc_SessionID;
  // MAC address of secc 6byte
  std::string vc_EvseId;
  uint16_t vc_ServiceId;
  bool vc_testCaseSpecific;
  bool vc_receiptRequired;

  // charging params discovery
  EnergyTransferModeType vc_requestedEnergyTransferModeAC;
  EnergyTransferModeType vc_requestedEnergyTransferModeDC;
  uint32_t vc_DepartureTime;
  PhysicalValueType vc_EAmount;
  PhysicalValueType vc_EVMaxVoltage;
  PhysicalValueType vc_EVMaxCurrent;
  PhysicalValueType vc_EVMinCurrent;
  urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ChargeProgressType vc_ChargeProgress;
  urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSENotificationType vc_EVSENotification;

  urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType vc_contractSignatureCertChain;

  SAScheduleListType vc_SASchedule_List;
  SAScheduleListType vc_SASchedules;
  PMaxScheduleType vc_PMaxSchedule;
  uint8_t vc_SAScheduleTupleId;
  PhysicalValueType vc_EVSENominalVoltage;
  PhysicalValueType vc_EVSEMaxCurrent;
  PhysicalValueType vc_EVSEMaximumCurrentLimit;
  PhysicalValueType vc_EVSEMinimumCurrentLimit;
  PhysicalValueType vc_EVSEMaximumVoltageLimit;
  PhysicalValueType vc_EVSEMinimumVoltageLimit;
  PhysicalValueType vc_EVSEMaximumPowerLimit;
  PhysicalValueType vc_EVSEPeakCurrentRipple;

  PhysicalValueType vc_EVTargetVoltage;
  PhysicalValueType vc_EVTargetCurrent;
  PhysicalValueType vc_EVPreChargeTargetCurrent;
  PhysicalValueType vc_EVSEPresentVoltage;
  PhysicalValueType vc_EVSEPresentCurrent;

  MeterInfoType vc_MeterInfo;

  // vc_DC_EVStatus
  DC_EVStatusType vc_DC_EVStatus;
  PhysicalValueType vc_EVMaximumVoltageLimit;
  PhysicalValueType vc_EVMaximumCurrentLimit;
  PhysicalValueType vc_EVMaximumPowerLimit;

  PhysicalValueType vc_DC_remainingTimeToBulkSoC;
  PhysicalValueType vc_DC_remainingTimeToFullSoC;

  // authorization
  std::string vc_contractPrivateKey;
  std::vector<uint8_t> vc_GenChallenge;

  // service discovery var
  ServiceListType vc_serviceList;
  ChargeServiceType vc_chargeService;
  PaymentOptionListType vc_paymentOptionList;
  SupportedEnergyTransferModeType vc_supportedEnergyTransferMode;
  paymentOptionType vc_SelectedPaymentOption;

  // support app protocol namespace
  std::string vc_Supported_ISO_Namespace;
  std::string vc_Supported_DIN_Namespace;
  std::string vc_Supported_ISO2_Namespace;
  uint32_t vc_versionNumberMajor;
  uint32_t vc_versionNumberMinor;

  // UDP
  std::string vc_V2G_Port_IpAddress;
  int vc_V2G_Port_PortNumber;
  int vc_Security;
  // numer of SDP request repeat
  int vc_maxRepetitionSDP;

  // TCP
  bool vc_isTcpPortClosed;
  std::shared_ptr<iso1Part4_V2G_TCP_TLS_Parameter> vc_v2g_tcp_tls_parameter;

  // TLS
  std::string vc_cipherSuite;
  std::shared_ptr<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType> vc_v2gRootCert;

  //61851
  float vc_validDutyCycleLowerBound2;
  float vc_validDutyCycleUpperBound2;
public:
  SECC_Tester(const std::shared_ptr<IfRuntime>& runtime);
  ~SECC_Tester();
  bool create(std::string &component_name);
  // start test system  and await for input queue and event for output queue
  bool start();
  bool stop();
  void kill();
  verdict_val dumpverdict();
  verdict_val getverdict();
  void setverdict(const verdicttype &verdict);
  void setverdict(const verdict_val val);
  void setverdict(const verdict_val val, const std::string &message);
  verdict_val clearverdict(void);
  std::shared_ptr<IfRuntime> getRuntime() {
    return this->_pRuntime;
  }
};


#endif
