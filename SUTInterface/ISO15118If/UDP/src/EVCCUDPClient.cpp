#include "EVCCUdpClient.h"
#include "time/timespan.h"
#include "TestSystemLogging.h"

//! Udp Client initialization
// V2G_UDP_SDP_CLIENT UDP (unicast) Port number in the
// range of Dynamic Ports (49152-65535) as defined in IETF RFC 6335.
// SDP client source port at the EVCC
// V2G_UDP_SDP_SERVER UDP
// SECC shall receive local-link IP multicast message on port 15118 (multicast)
// 15118 SDP server port which accepts UDP packets with a local-link IP multicast destination address.
EVCCUdpClient::EVCCUdpClient(const std::shared_ptr<CppCommon::Asio::Service>& service, const std::string& address, int port, const std::string &interface)
  : UDPClient(service, "ff02::01%eth1", 15118){
  this->_stop = true;
  std::string ep_address = fmt::format("{0}%{1}",address, interface);
  this->set_endpoint(ep_address, port);
  // Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: create udp {0} {1}",this->endpoint().address().to_string(), this->endpoint().port()));
}

bool EVCCUdpClient::checkIpv6Address(const std::string& ipv6_address)
{
  asio::error_code ec;
  asio::ip::make_address_v6(ipv6_address, ec);
  if(ec){
    return false;
  }
  else {
    return true;
  }
}

bool EVCCUdpClient::sendMulticast(const void* buffer, size_t size)
{
  if (Logging::LogCfg.LogSutUDP == 0x1){
    std::string data_array;
    for (size_t i = 0; i < size; i++)
    {
      if (i == (size-1)){
        data_array.append(fmt::format("{:#04x}", ((char*)buffer)[i]));
      }
      else {
        data_array.append(fmt::format("{:#04x}-", ((char*)buffer)[i]));
      }
    }
    Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: send multicast: {0} {1} | {2} | size {3}",this->endpoint().address().to_string(), this->endpoint().port(), data_array, size));
  }
  return this->SendAsync(buffer, size);
}

bool EVCCUdpClient::start()
{
  this->_stop = false;
  if (this->Connect()){
    Logging::debug(LogSutUDP_ENABLE, "[SUT_IF][ISO15118][UDP]: UDP client connected");
    return true;
  }
  else{
    Logging::debug(LogSutUDP_ENABLE, "[SUT_IF][ISO15118][UDP]: UDP client connect failed");
    return false;
  }
}

bool EVCCUdpClient::stop(){
  this->_stop = true;
  return this->Disconnect();
}

void EVCCUdpClient::setEventCallBack(const std::shared_ptr<onUdpClientEventType>& eventHandler)
{
  this->_onEventHandler[eventHandler->type] = eventHandler;
}

void EVCCUdpClient::onError(int error, const std::string& category, const std::string& message)
{
  Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: on error {0}, {1}, {2}", error, category, message));
  if (this->_onEventHandler[en_UdpClientCallbackType_ERROR] != nullptr){
    (*this->_onEventHandler[en_UdpClientCallbackType_ERROR])(error, category, message);
  }
}

void EVCCUdpClient::onSent(const asio::ip::udp::endpoint& endpoint, size_t sent)
{
  Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: {0} - {1} on sent {2} byte", endpoint.address().to_string(), endpoint.port(), sent));
  if (this->_stop == false){
    this->ReceiveAsync();
  }
  if (this->_onEventHandler[en_UdpClientCallbackType_SENT] != nullptr){
    (*this->_onEventHandler[en_UdpClientCallbackType_SENT])(sent);
  }
}

void EVCCUdpClient::onReceived(const asio::ip::udp::endpoint& endpoint, const void* buffer, size_t size)
{
  std::string addr = endpoint.address().to_string();
  if (Logging::LogCfg.LogSutUDP == 0x1){
    std::string data_array;
    for (size_t i = 0; i < size; i++)
    {
      if (i == (size-1)){
        data_array.append(fmt::format("{:#04x}", ((char*)buffer)[i]));
      }
      else {
        data_array.append(fmt::format("{:#04x}-", ((char*)buffer)[i]));
      }
    }
    Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: on receive {0} {1}| {2} | {3}", addr, endpoint.port(), data_array, size));
  }
  if (addr != this->endpoint().address().to_string()){
    if (this->_onEventHandler[en_UdpClientCallbackType_RECEIVE] != nullptr){
        (*this->_onEventHandler[en_UdpClientCallbackType_RECEIVE])(buffer, size);
      }
  }
  if (this->_stop == false){
    ReceiveAsync();
  }
}

/* Handle client disconnected notification */
void EVCCUdpClient::onDisconnected()
{
  Logging::debug(LogSutUDP_ENABLE, "[SUT_IF][ISO15118][UDP]: on disconnect");
  if (this->_onEventHandler[en_UdpClientCallbackType_DISCONNECT] != nullptr){
    this->_stop = true;
    (*this->_onEventHandler[en_UdpClientCallbackType_DISCONNECT])();
  }
}

/* Handle client connected notification */
void EVCCUdpClient::onConnected()
{
  Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: start listening on {0} {1}", this->socket().local_endpoint().address().to_string(), this->socket().local_endpoint().port()));
  Logging::debug(LogSutUDP_ENABLE, fmt::format("[SUT_IF][ISO15118][UDP]: multicast msg on {0} {1}", this->endpoint().address().to_string(), this->endpoint().port()));
  if (this->_onEventHandler[en_UdpClientCallbackType_CONNECT] != nullptr){
    (*this->_onEventHandler[en_UdpClientCallbackType_CONNECT])();
  }
}