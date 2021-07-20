#include "PAInterface.h"
#include "TestSystemLogging.h"

void PAsleep(float val)
{
  uint64_t temp = val * 1000000;
  std::this_thread::sleep_for(std::chrono::microseconds(temp));
}
PATimerManager::PATimerManager(const std::shared_ptr<CppCommon::Asio::Service> &service)
{
  this->_service = service;
}
PATimerManager::~PATimerManager()
{
  for (auto &&i : this->tm_list)
  {
    i = nullptr;
  }
}

std::shared_ptr<PATimer> PATimerManager::createTimer(const std::string &timer_id, float timeout_value)
{
  std::shared_ptr<PATimer> pTimer = nullptr;
  for (auto tm = this->tm_list.begin(); tm != this->tm_list.end(); tm++)
  {
    if (timer_id.compare((*tm)->getId()) == 0)
    {
      pTimer = *tm;
    }
  }
  if (pTimer != nullptr)
  {
    pTimer->_clean(timeout_value);
  }
  else
  {
    pTimer = std::make_shared<PATimer>(timer_id, timeout_value, this->_service);
    this->tm_list.push_back(pTimer);
  }
  return pTimer;
}

bool PATimerManager::popTimer(const std::string &timer_id)
{
  for (auto tm = this->tm_list.begin(); tm != this->tm_list.end(); tm++)
  {
    if (timer_id.compare((*tm)->getId()) == 0)
    {
      if (enPATimerState::EXECUTE == (*tm)->getState())
      {
        (*tm)->stop();
      }
      this->tm_list.erase(tm);
      return true;
    }
  }
  return false;
}

void PATimerManager::killall()
{
  for (auto &&timer : this->tm_list)
  {
    timer->stop();
    timer->_clean();
  }
}

PATimer::PATimer(const std::string &_id, float timeout_value, const std::shared_ptr<CppCommon::Asio::Service> &service) : CppCommon::Asio::Timer(service)
{
  this->tmOutFlag = false;
  this->tmOutVal = timeout_value * 1000000;
  this->id = _id;
  Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {0} CREATED", this->id));
}

PATimer::~PATimer()
{
  Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {0} DELETED", this->id));
}
std::string &PATimer::getId()
{
  return this->id;
}
void PATimer::_clean(float timeout_value)
{
  this->tmOutVal = timeout_value * 1000000;
  this->tmOutFlag = false;
  this->state = enPATimerState::PENDING;
  this->Setup(CppCommon::Timespan::microseconds(this->tmOutVal));
}

void PATimer::_clean()
{
  this->tmOutFlag = false;
  this->state = enPATimerState::PENDING;
  this->Setup(CppCommon::Timespan::microseconds(this->tmOutVal));
}

void PATimer::start()
{
  if (this->state != enPATimerState::EXECUTE)
  {
    this->Setup(CppCommon::Timespan::microseconds(this->tmOutVal));
    this->state = enPATimerState::EXECUTE;
    this->tmOutFlag = false;
    this->WaitAsync();
    Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {} START", this->id));
  }
}

void PATimer::start(float value)
{
  if (this->state != enPATimerState::EXECUTE)
  {
    this->tmOutVal = value * 1000000;
    this->Setup(CppCommon::Timespan::microseconds(this->tmOutVal));
    this->state = enPATimerState::EXECUTE;
    this->tmOutFlag = false;
    this->WaitAsync();
    Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {0} START", this->id));
  }
}

void PATimer::stop()
{
  if (enPATimerState::EXECUTE == this->state)
  {
    this->Cancel();
  }
  // while (this->state == enPATimerState::EXECUTE)
  // {
  //   std::this_thread::sleep_for(asio::chrono::milliseconds(10));
  // }
  this->tmOutFlag = false;
}

bool PATimer::timeout()
{
  return this->tmOutFlag;
}

bool PATimer::wait_timeout()
{
  this->start();
  while (this->state != enPATimerState::COMPLETED)
  {
    std::this_thread::sleep_for(asio::chrono::milliseconds(10));
  }
  bool temp = this->tmOutFlag;
  this->_clean();
  Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: WAIT {} TIMEOUT COMPLETED", this->id));
  return temp;
}
enPATimerStateType PATimer::getState()
{
  return this->state;
}
bool PATimer::running()
{
  return (this->state == enPATimerState::EXECUTE);
}

float PATimer::read()
{
  CppCommon::Timespan temp = this->expire_timespan();
  return (((float)temp.microseconds()) / 1000000.0);
}

void PATimer::onTimer(bool canceled)
{
  if (!canceled)
  {
    // timeout (async callback success)
    this->tmOutFlag = true;
    this->state = enPATimerState::COMPLETED;
    for (auto &&func : this->funcList)
    {
      func(this->tmOutFlag);
    }
    Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {} TIMEOUT", this->id));
  }
  else
  {
    // cancelled
    this->tmOutFlag = false;
    this->state = enPATimerState::COMPLETED;
    Logging::debug(LogPAIf_ENABLE, fmt::format("[TIMER]: {} CANCELED", this->id));
  }
}