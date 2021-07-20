#ifndef _SYSTEMCOMPONENT_H_
#define _SYSTEMCOMPONENT_H_

#include "PortType.h"
#include "IfRuntime.h"
#include "TCPAdapter.h"
#include "EVCCUdpClient.h"
#include "SeccBasicSignaling.h"
#include "pev.h"
class System_SECC;
// event handler type for HAL61851 Basic Communication
class onHAL61851Event: public onBCEventType {
private:
  std::shared_ptr<System_SECC> parent;
public:
  onHAL61851Event(std::shared_ptr<System_SECC>& _parent) : onBCEventType() {parent = _parent;}
  void operator() (en_BCEventType event) override;
};

// event handler from SLAC interface
class onSLACEvent: public onSLACEventType {
private:
  std::shared_ptr<System_SECC> parent;
public:
  onSLACEvent(std::shared_ptr<System_SECC>& _parent) : onSLACEventType() {parent = _parent;}
  void operator() (pevStateType event) override;
};
// event handler type type for TCP interface
class on15118TCPEvent: public onTCPAdapterEventType {
private:
  std::shared_ptr<System_SECC> parent;
public:
  on15118TCPEvent(en_tcpAdapterCallbackType _type, std::shared_ptr<System_SECC>& _parent)
  : onTCPAdapterEventType(_type) {parent = _parent;}
  // connect/disconnect/empty
  void operator() () override;
  // receive
  void operator() (const void *buffer, size_t size) override;
  // sent
  void operator() (size_t sent, size_t pending) override;
  // error
  void operator() (int error, const std::string& category, const std::string& message) override;
};

// event handler for UDP interface
class on15118UDPEvent: public onUdpClientEventType {
private:
  std::shared_ptr<System_SECC> parent;
public:
  on15118UDPEvent(en_UdpClientCallbackType _type, std::shared_ptr<System_SECC>& _parent)
  : onUdpClientEventType(_type) {parent = _parent;}
  // connect/disconnect
  void operator() () override;
  // receive
  void operator() (const void* buffer, size_t size) override;
  // sent
  void operator() (size_t sent) override;
  // error
  void operator() (int error, const std::string& category, const std::string& message) override;
};

class System_SECC : public std::enable_shared_from_this<System_SECC> {
private:
  // port queue | these port shall be mapped to MTC and PTC (passing ptr)
  // data shall be dequeue and enqueue(on event) to these port
  // V2G_TCP_TLS_ALM_SECC_Port    |
  // V2G_UDP_SDP_Port             | SEND:    Enqueue from MTC(send), Dequeue from STC
  // HAL_61851_Port               | RECEIVE: Dequeue from MTC(receive), Enqueue from STC
  // HAL_61851_Listener_Port      | Enqueue from STC, Dequeue from PTC(receive)
  std::shared_ptr<CppCommon::Asio::Service> _ptrService;
  // runtime
  std::shared_ptr<IfRuntime> _pRuntime;
  // ioService for port queue
  std::shared_ptr<asio::io_service> _ptrIOService;

  // event handler for HAL61851
  std::shared_ptr<onHAL61851Event> _on61851Event;
  // event handler for SLAC
  std::shared_ptr<onSLACEvent> _onSLACEvent;
  // event handler for TCP
  std::shared_ptr<on15118TCPEvent> _on15118TcpConnect;
  std::shared_ptr<on15118TCPEvent> _on15118TcpDisconnect;
  std::shared_ptr<on15118TCPEvent> _on15118TcpEmpty;
  std::shared_ptr<on15118TCPEvent> _on15118TcpReceive;
  std::shared_ptr<on15118TCPEvent> _on15118TcpSent;
  std::shared_ptr<on15118TCPEvent> _on15118TcpError;
  // event handler for UDP
  std::shared_ptr<on15118UDPEvent> _on15118UDPConnect;
  std::shared_ptr<on15118UDPEvent> _on15118UDPDisconnect;
  std::shared_ptr<on15118UDPEvent> _on15118UDPReceive;
  std::shared_ptr<on15118UDPEvent> _on15118UDPSent;
  std::shared_ptr<on15118UDPEvent> _on15118UDPError;
public:
  std::string ipv6IF;
  std::string slacFile;
  // TCP Adapter
  std::shared_ptr<TCPAdapter> _pTCPIf;
  // UDP Adapter
  std::shared_ptr<EVCCUdpClient> _pUDPIf;
  // IEC61851 Adapter
  std::shared_ptr<SeccBasicSignaling> _pBCIf;
  // SLAC Adapter
  std::shared_ptr<Plc> _pPLC;
  
  // TCP port <> mtc
  std::shared_ptr<V2G_TCP_TLS_ALM_SECC_Port> pt_V2G_TCP_TLS_ALM_SECC_Port;
  // UDP port <> mtc
  std::shared_ptr<V2G_UDP_SDP_Port> pt_V2G_UDP_SDP_Port;
  // HAL_61851_Port <> mtc
  std::shared_ptr<HAL_61851_Port> pt_HAL_61851_Port;
  // HAL_61851_Listener_Port <> ptc
  std::shared_ptr<HAL_61851_Port> pt_HAL_61851_Listener_Port;
  // SLAC_Port <> mtc
  std::shared_ptr<SLAC_Port> pt_SLAC_Port;

  std::shared_ptr<iso1Part4_V2G_TCP_TLS_Parameter> pt_TCP_Param;

  bool SLACInitFlag;

public:
  System_SECC(const std::shared_ptr<IfRuntime>& runtime, const std::string& _ipv6IF, const std::string &slacCfgFile);
  System_SECC(const std::shared_ptr<IfRuntime>& runtime, const std::string &ipv6_multicast, uint16_t port, const std::string& _ipv6IF, const std::string &slacCfgFile);
  ~System_SECC();
  bool create(std::string &component_name);
  // start test system  and await for input queue and event for output queue
  bool start();
  bool stop();
  void kill();
  // operation: create, start, running, alive, done, killed, stop, kill
  void sendTCPMsgHandler(std::shared_ptr<V2gTpMessage> &item, std::shared_ptr<BasePort>& port);
  void sendUDPMsgHandler(std::shared_ptr<V2gTpMessage> &item, std::shared_ptr<BasePort>& port);
  void cmdHandler(std::shared_ptr<BaseOperation> &item, std::shared_ptr<BasePort>& port);
};

#endif
