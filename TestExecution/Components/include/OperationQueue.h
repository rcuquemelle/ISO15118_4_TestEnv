#ifndef __OPERATIONQUEUE_H__
#define __OPERATIONQUEUE_H__
#include <utility>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "asiowrapper/asio.h"
#include "asiowrapper/service.h"
#include "fmt/core.h"
#include "TsDataType.h"

using namespace DataStructure_HAL_61851;
using namespace DataStructure_V2G_TCP_TLS_Port_Control;
using namespace DataStructure_SDP;
typedef enum {
  OpType_BASE = 0,
  OpType_TCP,
  OpType_UDP,
  OpType_61851,
  OpType_SLAC,
  OpType_NULL
} OpType;
// define operation mapping base on DataStructure of TsDataType
class BaseOperation {
public:
  BaseOperation(OpType _type){
    this->op = _type;
  }
  ~BaseOperation(){}
  OpType op;
  // send operation to queue: create BaseOperation object
  // set OpType: TCP = TcpControlReq/TcpControlRes
  // cmd
  // iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPort,
  // iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort,
  // iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus,
  // iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort
  std::shared_ptr<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq> TcpControlReq;
  // cmd. ack. result[portNumber, portStatus]
  std::shared_ptr<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes> TcpControlRes;
  // set OpType = 61851 HAL61851Req/HAL61851Res
  // set state IEC_61851_States
  std::shared_ptr<HAL_61851_Cmd> HAL61851Req;
  // state, eventtype, volt, pwmstatus, duty, freq
  std::shared_ptr<HAL_61851_Event> HAL61851Res;
  // SLAC operation
  std::shared_ptr<DLINKCmd> SLACReq;
  std::shared_ptr<DLINKEvent> SLACRes;
};

#endif // __OPERATIONQUEUE_H__