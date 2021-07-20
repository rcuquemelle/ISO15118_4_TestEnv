#include "ParallelTestComponent.h"
#include "TestSystemLogging.h"
// call to system component v_HAL_61851_Listener
HAL_61851_Listener::HAL_61851_Listener(const std::shared_ptr<IfRuntime>& runtime)
{
  this->_pRuntime = runtime;
  this->_ptrService = this->_pRuntime->getService();
  // get the working io_service(bound to another thread) for queue operation
  this->_ptrIOService = this->_ptrService->GetAsioService();
  Logging::debug(LogComponent_ENABLE, "[PTC]: Parallel Test component created");
}

HAL_61851_Listener::~HAL_61851_Listener()
{
  Logging::debug(LogComponent_ENABLE, "[PTC]: Parallel Test component disposed");
}

bool HAL_61851_Listener::create(std::string &component_name)
{
  // nothings
  return true;
}

bool HAL_61851_Listener::start()
{
  this->pt_HAL_61851_Listener_Port = nullptr;
  this->pt_HAL_61851_Internal_Port = std::make_shared<HAL_61851_Internal_Port>(this->_ptrIOService);
  return true;
}

bool HAL_61851_Listener::stop()
{
  return true;
}

void HAL_61851_Listener::kill()
{
  // kill ptc object (destructor)
}
