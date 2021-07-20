#include "Common_Cfg.h"
#include "PICSCfg.h"
#include "PIXITCfg.h"

using namespace DataStructure_V2G_TCP_TLS_Port_Control;
using namespace Pics_15118::PICS_CMN;
// map "(" ComponentRef ":" Port "," ComponentRef ":" Port ")"
// [ param "(" [ { ActualPar [","] }+ ] ")" ]

Configuration_15118_2::Configuration_15118_2(std::shared_ptr<SECC_Tester> &_mtc)
{
  mtc = _mtc;
}

Configuration_15118_2::~Configuration_15118_2()
{
}

// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
/* Precondition for every test case execution */
void Configuration_15118_2::f_SECC_CMN_PR_InitConfiguration_001(
  std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<System_SECC> &systemSECC)
{
  /* Indication for enabling combined testing including SLAC association & V2G messaging */
  if (PICS_CMN_CMN_CombinedTesting)
  {
    // map SLAC port
    map(mtc->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  }
  // map tcp port
  map(mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, systemSECC->pt_V2G_TCP_TLS_ALM_SECC_Port);
  // map sdp port
  map(mtc->pt_V2G_UDP_SDP_Port, systemSECC->pt_V2G_UDP_SDP_Port);
  // map 61851 port
  map(mtc->pt_HAL_61851_Port, systemSECC->pt_HAL_61851_Port);
  // create 61851 listener for current executed test case
  // v_HAL_61851_Listener := HAL_61851_Listener.create("IEC 61851 Listener") alive;
  v_HAL_61851_Listener = std::make_shared<HAL_61851_Listener>(mtc->getRuntime());
  // start listener component
  v_HAL_61851_Listener->start();
  // map listener port with system (data from STC to PTC)
  map(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, systemSECC->pt_HAL_61851_Listener_Port);
  // map listener port with mtc (parallel test component sync with mtc)
  map(mtc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  // enable operation for internal listener port (parallel test component shall monitoring 61851 operation)
  // TODO: current hw does not provide interface to measure/monitoring PWM operation of HAL61851
  // vc_Default_IEC_61851_ListenerBehavior = activate(a_CMN_IEC61851ListenerBehavior(pt_HAL_61851_Internal_Port));

  // map tcp param between mtc and stc, test case receive data from mtc-> sync with stc for config TCP
  systemSECC->pt_TCP_Param = mtc->vc_v2g_tcp_tls_parameter;
  Logging::debug(LogCfgFnc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
}
// ::::::::::::::::::::::: Config Functions :::::::::::::::::::::::::
/* specific InitConfiguration for SupportedAppProtocol msg test case */
void Configuration_15118_2::f_SECC_CMN_PR_InitConfiguration_002(std::shared_ptr<System_SECC> &systemSECC, verdict_val v_verdict1, verdict_val v_verdict2)
{
  map(mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, systemSECC->pt_V2G_TCP_TLS_ALM_SECC_Port);
  std::shared_ptr<BaseOperation> cmd = std::make_shared<BaseOperation>(OpType_TCP);
  cmd->TcpControlReq = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq>();
  cmd->TcpControlReq->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort;
  cmd->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();

  auto handler = [this](std::shared_ptr<BaseOperation>& expected, std::shared_ptr<BaseOperation>& received) -> bool {
    if (received->TcpControlRes->command == iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort){
      Logging::debug(LogCfgFnc_ENABLE, "[CMN_CFG]: TCP connected handler called - CONNECTED");
      expected->TcpControlRes->ack = received->TcpControlRes->ack;
      expected->TcpControlRes->result.portNumber.intValue = received->TcpControlRes->result.portNumber.intValue;
      expected->TcpControlRes->result.portStatus.closed = received->TcpControlRes->result.portStatus.closed;
      this->mtc->vc_isTcpPortClosed = expected->TcpControlRes->result.portStatus.closed;
      return true;
    }
    else {
      Logging::error(LogCfgFnc_ENABLE, "[CMN_CFG]: TCP connected handler called - FAILED");
      return false;
    }
  };

  // request create TCP connection, timeout after 5s
  std::shared_ptr<PATimer> t_sleep = this->mtc->pt_TimerManager->createTimer("local", 5);
  mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(cmd);
  t_sleep->start();
  while(1)
  {
    if (mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(cmd, handler))
    {
      t_sleep->stop();
      this->mtc->pt_TimerManager->popTimer("local");
      break;
    }
    if (t_sleep->timeout()){
      Logging::error(LogCfgFnc_ENABLE, "[CMN_CFG]: TCP connect timeout");
      this->mtc->pt_TimerManager->popTimer("local");
      cmd->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_failed;
      break;
    }
  }
  if (cmd->TcpControlRes->ack == iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success)
  {
    PAsleep(0.1);
    Logging::info(LogCfgFnc_ENABLE, "[CMN_CFG]: iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success");
    mtc->setverdict(v_verdict1, "TCP or TLS handshake was successful.");
  }
  else if (cmd->TcpControlRes->ack == iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_failed)
  {
    Logging::info(LogCfgFnc_ENABLE, "[CMN_CFG]: iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_failed");
    mtc->setverdict(v_verdict2, "TCP or TLS handshake was not successful.");
  }
  Logging::debug(LogCfgFnc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
}
void Configuration_15118_2::f_SECC_CMN_PO_ShutdownConfiguration_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<System_SECC> &v_systemSECC)
{
  unmap(mtc->pt_HAL_61851_Port, v_systemSECC->pt_HAL_61851_Port);
  unmap(v_HAL_61851_Listener->pt_HAL_61851_Listener_Port, v_systemSECC->pt_HAL_61851_Listener_Port);
  unmap(mtc->pt_HAL_61851_Internal_Port, v_HAL_61851_Listener->pt_HAL_61851_Internal_Port);
  // reset shared_ptr and call destructor
  v_HAL_61851_Listener->kill();
  unmap(mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, v_systemSECC->pt_V2G_TCP_TLS_ALM_SECC_Port);
  unmap(mtc->pt_V2G_UDP_SDP_Port, v_systemSECC->pt_V2G_UDP_SDP_Port);
  if (PICS_CMN_CMN_CombinedTesting)
  {
    unmap(mtc->pt_SLAC_Port, v_systemSECC->pt_SLAC_Port);
  }
  Logging::debug(LogCfgFnc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
}
void Configuration_15118_2::f_SECC_PO_ShutdownConfiguration_002(std::shared_ptr<System_SECC> &v_systemSECC)
{
  if (mtc->pt_SLAC_Port != nullptr){
    unmap(mtc->pt_SLAC_Port, v_systemSECC->pt_SLAC_Port);
  }
  Logging::debug(LogCfgFnc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
}
