#ifndef _TCPADAPTER_H_
#define _TCPADAPTER_H_

#include "asiowrapper/tcp_client.h"
#include "boost/function.hpp"
typedef enum {
  en_tcpAdapterCallbackType_CONNECT,
  en_tcpAdapterCallbackType_DISCONNECT,
  en_tcpAdapterCallbackType_RECEIVE,
  en_tcpAdapterCallbackType_SENT,
  en_tcpAdapterCallbackType_EMPTY,
  en_tcpAdapterCallbackType_ERROR,
  en_tcpAdapterCallbackType_NUM
} en_tcpAdapterCallbackType;
class onTCPAdapterEventType {
public:
  onTCPAdapterEventType(en_tcpAdapterCallbackType _type){
    type = _type;
  }
  onTCPAdapterEventType (onTCPAdapterEventType && ) = default;
  onTCPAdapterEventType (const onTCPAdapterEventType & ) = default;
  ~onTCPAdapterEventType(){}
  void setType(en_tcpAdapterCallbackType _type) {type = _type;}
  virtual void operator() () {}
  virtual void operator() (const void *buffer, size_t size) {}
  virtual void operator() (size_t sent, size_t pending) {}
  virtual void operator() (int error, const std::string& category, const std::string& message) {}
  onTCPAdapterEventType & operator= ( const onTCPAdapterEventType & ) = default;
  onTCPAdapterEventType & operator= ( onTCPAdapterEventType && ) = default;
  en_tcpAdapterCallbackType type;
};
class TCPAdapter : public CppCommon::Asio::TCPClient
{
public:
  TCPAdapter(const std::shared_ptr<CppCommon::Asio::Service>& service);
  virtual ~TCPAdapter();
  bool setSUTAddress(const std::string& ipv6_address, int port, const std::string &channel);
  bool connect();
  bool disconnect();
  size_t send(const void* buffer, size_t size);
  bool sendAsync(const void* buffer, size_t size);
  size_t receive(void* buffer, size_t size);
  void receiveAsync();
  // Component define callback function to handle TCP event
  // then push to TCPAdapter by setEventCallBack function
  void setEventCallBack(const std::shared_ptr<onTCPAdapterEventType>& eventHandler);

protected:
  void onConnected() override;
  void onDisconnected() override;
  void onReceived(const void *buffer, size_t size) override;
  void onSent(size_t sent, size_t pending) override;
  void onEmpty() override;
  void onError(int error, const std::string& category, const std::string& message) override;

private:
  bool checkIpv6Address(const std::string& ipv6_address);
  bool _validSUTAddress;
  std::shared_ptr<onTCPAdapterEventType> _onEventHandler[en_tcpAdapterCallbackType_NUM];
};

#endif