#ifndef __COMMON_CFG_H__
#define __COMMON_CFG_H__
#include "PortType.h"
#include "MainTestComponent.h"
#include "ParallelTestComponent.h"
#include "SystemComponent.h"
#include "TestSystemLogging.h"

class Configuration_15118_2: public std::enable_shared_from_this<Configuration_15118_2> {
public:
  Configuration_15118_2(std::shared_ptr<SECC_Tester>& _mtc);
  ~Configuration_15118_2();
  void f_SECC_CMN_PR_InitConfiguration_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<System_SECC> &systemSECC);
  void f_SECC_CMN_PR_InitConfiguration_002(std::shared_ptr<System_SECC> &systemSECC, verdict_val v_verdict1, verdict_val v_verdict2);
  void f_SECC_CMN_PO_ShutdownConfiguration_001(std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener, std::shared_ptr<System_SECC> &v_systemSECC);
  void f_SECC_PO_ShutdownConfiguration_002(std::shared_ptr<System_SECC> &v_systemSECC);
  std::shared_ptr<SECC_Tester> mtc;
};
template<typename PORT_TYPE>
void map(PORT_TYPE &portDest, PORT_TYPE &portSrc) {
  if (portSrc != nullptr){
    portDest = portSrc;
    portDest->pState = PortState_MAPPED;
    portSrc->pState = PortState_MAPPED;
  }
  else {
    Logging::error(LogCfgFnc_ENABLE, "Source port is nullptr, invalid mapping");
  }
}
// // connect "(" ComponentRef ":" Port "," ComponentRef ":" Port ")"
template<typename PORT_TYPE>
void unmap(PORT_TYPE &portDest, PORT_TYPE &portSrc) {
  portDest = nullptr;
  portSrc->pState = PortState_NONE;
}
template<typename PORT_TYPE>
void connect(PORT_TYPE &portDest, PORT_TYPE &portSrc) {
  if (portSrc != nullptr){
    portDest = portSrc;
    portDest->pState = PortState_MAPPED;
    portSrc->pState = PortState_MAPPED;
  }
  else {
    Logging::error(LogCfgFnc_ENABLE, "Source port is nullptr, invalid connect");
  }
}
template<typename PORT_TYPE>
void disconnect(PORT_TYPE &portDest, PORT_TYPE &portSrc) {
  portDest = nullptr;
  portSrc->pState = PortState_NONE;
}
#endif // __COMMON_CFG_H__