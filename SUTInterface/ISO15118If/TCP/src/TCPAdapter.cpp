#include "TCPAdapter.h"
#include "TestSystemLogging.h"
TCPAdapter::TCPAdapter(const std::shared_ptr<CppCommon::Asio::Service>& service)
  : TCPClient(service, "", 0) {
  for (int i = 0; i < en_tcpAdapterCallbackType_NUM; i++) {
    this->_onEventHandler[i] = nullptr;
  }
}

TCPAdapter::~TCPAdapter() {
}

bool TCPAdapter::checkIpv6Address(const std::string& ipv6_address) {
  asio::error_code ec;
  asio::ip::make_address_v6(ipv6_address, ec);
  if(ec){
    this->_validSUTAddress = false;
    return false;
  }
  else {
    this->_validSUTAddress = true;
    return true;
  }
}

bool TCPAdapter::setSUTAddress(const std::string& ipv6_address, int port, const std::string &channel){
  // update SUTAddress ipv6 port|endpoint
  std::string ipv6 = fmt::format("{0}%{1}",ipv6_address, channel);
  if (this->checkIpv6Address(ipv6) && (0 <= port) && (65536 > port)) {
    this->_port = port;
    this->_address = ipv6;
    return true;
  }
  else {
    Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: Input ipv6 {0} port {1} is invalid",ipv6, port));
    return false;
  }
}

bool TCPAdapter::connect() {
  // if SUTAddress is configured and valid then call TCPClient.Connect
  if (this->_validSUTAddress) {
    this->SetupKeepAlive(true);
    if (true == this->ConnectAsync())
    {
      Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: try connected {0}-{1}",this->address(), this->port()));
      return true;
    }
    else
    {
      Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: already connected or is processing {0}-{1}",this->address(), this->port()));
      return false;
    }
  }
  else {
    return false;
  }
}

bool TCPAdapter::disconnect() {
  return this->DisconnectAsync();
}

size_t TCPAdapter::send(const void* buffer, size_t size){
  // call Send of TCPClient
  // no additional logic
  if (Logging::LogCfg.LogSutTCP == 0x1){
    std::string data_array;
    for (size_t i = 0; i < size; i++)
    {
      data_array.append(fmt::format("{:02X} ", ((char*)buffer)[i]));
    }
    // Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: send: {0} {1} | {2} | size {3}",this->endpoint().address().to_string(), this->endpoint().port(), data_array, size));
    Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: send: {}",data_array));
  }
  return this->Send(buffer, size, CppCommon::Timespan(std::chrono::seconds(60)));
}

// Component call sendAsync
bool TCPAdapter::sendAsync(const void* buffer, size_t size){
  if (Logging::LogCfg.LogSutTCP == 0x1){
    std::string data_array;
    for (size_t i = 0; i < size; i++)
    {
      data_array.append(fmt::format("{:02X} ", ((char*)buffer)[i]));
    }
    // Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: send: {0} {1} | {2} | size {3}",this->endpoint().address().to_string(), this->endpoint().port(), data_array, size));
    Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: send: {}",data_array));
  }
  return this->SendAsync(buffer, size);
}

size_t TCPAdapter::receive(void* buffer, size_t size){
  return this->Receive(buffer, size, CppCommon::Timespan(std::chrono::seconds(60)));
}

// call receive async
void TCPAdapter::receiveAsync(){
  this->TryReceive();
}

void TCPAdapter::setEventCallBack(const std::shared_ptr<onTCPAdapterEventType>& eventHandler) {
  this->_onEventHandler[eventHandler->type] = eventHandler;
}
void TCPAdapter::onConnected() {
  // call function object configured by Component setup
  Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: connected {0}-{1}",this->endpoint().address().to_string(), this->endpoint().port()));
  Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: start listening on {0} {1}", this->socket().local_endpoint().address().to_string(), this->socket().local_endpoint().port()));
  if (this->_onEventHandler[en_tcpAdapterCallbackType_CONNECT] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_CONNECT])();
}

void TCPAdapter::onDisconnected() {
  // call function object configured by Component setup
  Logging::debug(LogSutTCP_ENABLE, "[SUT_IF][ISO15118][TCP]: disconnect");
  if (this->_onEventHandler[en_tcpAdapterCallbackType_DISCONNECT] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_DISCONNECT])();
}

void TCPAdapter::onReceived(const void *buffer, size_t size) {
  // call function object configured by Component setup
  // TBD: should process size expected to receive before pass to callback
  if (Logging::LogCfg.LogSutTCP == 0x1){
    std::string data_array;
    for (size_t i = 0; i < size; i++)
    {
      data_array.append(fmt::format("{:02X} ", ((char*)buffer)[i]));
    }
    // Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: receive: {0} {1} | {2} | size {3}",this->endpoint().address().to_string(), this->endpoint().port(), data_array, size));
    Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: receive: {}",data_array));
  }
  if (this->_onEventHandler[en_tcpAdapterCallbackType_RECEIVE] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_RECEIVE])(buffer, size);
}

void TCPAdapter::onSent(size_t sent, size_t pending) {
  Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: send: {0} | pending: {1}", sent, pending));
  if (this->_onEventHandler[en_tcpAdapterCallbackType_SENT] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_SENT])(sent, pending);
}

void TCPAdapter::onEmpty() {
  if (this->_onEventHandler[en_tcpAdapterCallbackType_EMPTY] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_EMPTY])();
}

void TCPAdapter::onError(int error, const std::string& category, const std::string& message) {
  Logging::debug(LogSutTCP_ENABLE, fmt::format("[SUT_IF][ISO15118][TCP]: on error {0}, {1}, {2}", error, category , message));
  if (this->_onEventHandler[en_tcpAdapterCallbackType_ERROR] != nullptr)
    (*this->_onEventHandler[en_tcpAdapterCallbackType_ERROR])(error, category, message);
}