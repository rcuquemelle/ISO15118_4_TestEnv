#ifndef _PAINTERFACE_H_
#define _PAINTERFACE_H_
// Timer and external function
#include <vector>
#include <thread>
#include <atomic>
#include "asiowrapper/service.h"
#include "asiowrapper/timer.h"

typedef enum enPATimerState{
  PENDING,
  EXECUTE,
  COMPLETED
} enPATimerStateType;

typedef void (*NotifyTimeout)(bool);

class PATimer : public CppCommon::Asio::Timer {
private:
  // timeout value in micro second
  uint64_t tmOutVal;
  // timer state
  // time id
  std::string id;
  // timeout flag
  std::atomic<bool> tmOutFlag;
  std::atomic<enPATimerStateType> state;
  std::vector<NotifyTimeout> funcList;
public:
  PATimer(const std::string &_id, float timeout_value, const std::shared_ptr<CppCommon::Asio::Service>& service);
  ~PATimer();
  void _clean(float timeout_value);
  void _clean();
  std::string &getId();
  void start();
  void start(float value);
  void stop();
  bool running();
  float read();
  bool timeout();
  bool wait_timeout();
  void setNotifyFunc(NotifyTimeout func) {
    this->funcList.push_back(func);
  }
  enPATimerStateType getState();
protected:
  void onTimer(bool canceled) override;
};


class PATimerManager {
// this class shall handle all timer in async timer thread
// create timer object, push to list, execute timer, cancel
private:
  // asyn io context for timer execution
  std::shared_ptr<CppCommon::Asio::Service> _service;
  // timer list
  std::vector<std::shared_ptr<PATimer>> tm_list;
public:
  PATimerManager(const std::shared_ptr<CppCommon::Asio::Service>& service);
  ~PATimerManager();
  std::shared_ptr<PATimer> createTimer(const std::string &timer_id, float timeout_value);
  bool popTimer(const std::string &timer_id);
  void killall();
};

extern void PAsleep(float val);
#endif
