#include "IfRuntime.h"
#include <thread>
#include "TestSystemLogging.h"
// handle creation asio io context for SUT Interface runtime

// post, dispatch, defer function object api
#define THREAD_DIV 2
IfRuntime::IfRuntime() {
  // get number of available hw thread
  auto numthread = (int)(std::thread::hardware_concurrency()/THREAD_DIV);
  if (numthread >= 0) {
    // create Service with threads num and enable thread pool
    this->_service = std::make_shared<CppCommon::Asio::Service>(int(numthread), false);
    if (this->_service->Start(true)){
      Logging::debug(LogRunEnv_ENABLE, "[SUT_IF][RUNTIME]: Service started");
    }
  }
}

IfRuntime::~IfRuntime() {
  this->_service->Stop();
  while(this->_service->IsStarted()){}
}

std::shared_ptr<CppCommon::Asio::Service> IfRuntime::getService() {
  return this->_service;
}