#ifndef _PARALLELCOMPONENT_H_
#define _PARALLELCOMPONENT_H_
#include "PortType.h"
#include "IfRuntime.h"
#include "SeccBasicSignaling.h"
#include "PAInterface.h"

class HAL_61851_Listener : public std::enable_shared_from_this<HAL_61851_Listener> {
public:
  std::shared_ptr<CppCommon::Asio::Service> _ptrService;
  // ioService for port queue
  std::shared_ptr<asio::io_service> _ptrIOService;
  // runtime
  std::shared_ptr<IfRuntime> _pRuntime;
  verdicttype tc_verdict;
  // HAL_61851_Listener_Port
  std::shared_ptr<HAL_61851_Port> pt_HAL_61851_Listener_Port;
  std::shared_ptr<HAL_61851_Internal_Port> pt_HAL_61851_Internal_Port;

public:
  HAL_61851_Listener(const std::shared_ptr<IfRuntime>& runtime);
  HAL_61851_Listener() {};
  ~HAL_61851_Listener();
  bool create(std::string &component_name);
  // start test system  and await for input queue and event for output queue
  bool start(const std::shared_ptr<IfRuntime>& runtime);
  bool start();
  bool stop();
  void kill();
  // void cmdHandler(std::shared_ptr<BaseOperation> &item, std::shared_ptr<BasePort>& port);
};


#endif