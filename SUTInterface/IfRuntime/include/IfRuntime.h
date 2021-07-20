#ifndef _IFRUNTIME_H_
#define _IFRUNTIME_H_

#include "asiowrapper/service.h"

class IfRuntime
{
private:
  std::shared_ptr<CppCommon::Asio::Service> _service;
public:
  IfRuntime();
  IfRuntime(const IfRuntime&) = delete;
  IfRuntime(IfRuntime&&) = delete;
  ~IfRuntime();

  IfRuntime& operator=(const IfRuntime&) = delete;
  IfRuntime& operator=(IfRuntime&&) = delete;

  std::shared_ptr<CppCommon::Asio::Service> getService();
};

#endif