#ifndef _EVCC_UDP_CLIENT_H_
#define _EVCC_UDP_CLIENT_H_

#include "asiowrapper/udp_client.h"
#include "threads/thread.h"

#include <atomic>
#include <iostream>

typedef enum {
  en_UdpClientCallbackType_CONNECT=0,
  en_UdpClientCallbackType_DISCONNECT,
  en_UdpClientCallbackType_RECEIVE,
  en_UdpClientCallbackType_SENT,
  en_UdpClientCallbackType_ERROR,
  en_UdpClientCallbackType_NUM
} en_UdpClientCallbackType;
class onUdpClientEventType {
public:
  onUdpClientEventType(en_UdpClientCallbackType _type){
    type = _type;
  }
  onUdpClientEventType (onUdpClientEventType && ) = default;
  onUdpClientEventType (const onUdpClientEventType & ) = default;
  ~onUdpClientEventType(){}
  void setType(en_UdpClientCallbackType _type) {type = _type;}
  // connect/disconnect
  virtual void operator() () {}
  // receive
  virtual void operator() (const void* buffer, size_t size) {}
  // send
  virtual void operator() (size_t sent) {}
  // error
  virtual void operator() (int error, const std::string& category, const std::string& message) {}
  onUdpClientEventType & operator= ( const onUdpClientEventType & ) = default;
  onUdpClientEventType & operator= ( onUdpClientEventType && ) = default;
  en_UdpClientCallbackType type;
};

class EVCCUdpClient : public CppCommon::Asio::UDPClient
{
  public:
    //! Udp Client initialization
    EVCCUdpClient(const std::shared_ptr<CppCommon::Asio::Service>& service, const std::string& address, int port, const std::string &interface);

    ~EVCCUdpClient() {};
    bool sendMulticast(const void* buffer, size_t size);
    bool start();
    bool stop();
    void setEventCallBack(const std::shared_ptr<onUdpClientEventType>& eventHandler);
  protected:
    /* Handle client connected notification */
    void onConnected() override;

    /* Handle client disconnected notification */
    void onDisconnected() override;

    void onReceived(const asio::ip::udp::endpoint& endpoint, const void* buffer, size_t size) override;

    void onSent(const asio::ip::udp::endpoint& endpoint, size_t sent) override;

    void onError(int error, const std::string& category, const std::string& message) override;

  private:
    bool checkIpv6Address(const std::string& ipv6_address);
    std::atomic<bool> _stop;
    std::shared_ptr<onUdpClientEventType> _onEventHandler[en_UdpClientCallbackType_NUM];
};

#endif