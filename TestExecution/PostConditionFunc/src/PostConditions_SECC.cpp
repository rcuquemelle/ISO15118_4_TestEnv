#include "PostConditions_SECC.h"
#include "Common_Cfg.h"
#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"
#include "TsDataType.h"
#include "PAInterface.h"
#include "TB_SECC_SDPMsg.h"
#include "TB_SECC_V2GTP.h"
#include "TestSystemLogging.h"
#include "CommonLib.h"

using namespace Timer_15118::Timer_par_15118;

void PostConditions_SECC_15118_2::f_SECC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener)
{
  // stop PTC operation
  v_HAL_61851_Listener->stop();
  Logging::debug(LogPosFnc_ENABLE, "[POST_CND]: stop HAL Listener");
  // v_HAL_61851_Listener->start(f_SECC_HAL61851Listener(false)); //??
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->clear();
  Logging::debug(LogPosFnc_ENABLE, "[POST_CND]: clear tcp port");
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // deactivate(vc_Default_SDP_Message);
  auto receive_handler = [this](std::shared_ptr<BaseOperation>& expected, std::shared_ptr<BaseOperation>& received)->bool{
    if (expected->TcpControlRes->result.portStatus.closed == received->TcpControlRes->result.portStatus.closed){
      Logging::info(LogPosFnc_ENABLE, "[POST_CND]: TCP connection is closed");
      return true;
    }
    return false;
  };
  // check if TCP port is mapped and not closed
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->checkstate(PortState_MAPPED) && (!this->mtc->vc_isTcpPortClosed))
  {
    Logging::debug(LogPosFnc_ENABLE, "[POST_CND]: CLOSE TCP PORT");
    std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
    std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);
    sendCmd->TcpControlReq = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq>();
    sendCmd->TcpControlReq->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
    expectedRes->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
    expectedRes->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
    expectedRes->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
    expectedRes->TcpControlRes->result.portStatus.closed = true;
    // send command to close port
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
    while(true)
    {
      // check if port send back status closed port
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedRes, receive_handler))
      {
        break;
      }
    }
  }
  else {
    Logging::info(LogPosFnc_ENABLE, "[POST_CND]: TCP connection is closed");
  }
  // internal port between mtc and ptc
  this->mtc->pt_HAL_61851_Internal_Port->clear();
  // change bc to state A
  f_SECC_changeValidStateCondition(A);
  // check frequency back to 0
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  // check duty back to 100
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  f_SECC_setState(this->systemSECC, A, v_HAL_61851_Listener);
  PAsleep(par_CMN_waitForNextHAL);

  this->mtc->pt_HAL_61851_Port->clear();
  f_SECC_setProximity(0);
  v_HAL_61851_Listener->stop();

  // stop all timer by call to global timer management
  this->mtc->pt_TimerManager->killall();
  Logging::info(LogPosFnc_ENABLE, "[POST_CND]: Sec timer started");
  PAsleep(par_SECC_waitForNextTC);
  Logging::info(LogPosFnc_ENABLE, "[POST_CND]: Sec timer stopped");
  Logging::debug(LogPosFnc_ENABLE, "[POST_CND]: f_SECC_CMN_PO_InitialState_001");
}