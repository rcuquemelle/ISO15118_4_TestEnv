#include "SystemComponent.h"
#include "TestSystemLogging.h"
#include "TimerCfg.h"

// system component call to SUT Interface
// system component initialize SUT interface runtime environment (execution context)
// initialize SUT Interface IEC61851, SUT Interface ISO15118 (TCP, UDP)
// reading port(dequeue), push data to SUT Interface for async sending operation (this is event handler mapped to each port queue)
// receive data event from SUT interface, store to queue(enqueue)                (this is event handler mapped to each port queue)

// these port(queue)s are directly mapped to MainTestComponent and ParallelTestComponent

// test behavior shall run on(executed) MTC(send/receive data/set operation) and PTC(mornitoring 61851 event)

// port v2g msg queue handler: receive V2G msg from MTC -> serialize data to byte stream -> push to TCP/UDP interface
//                             receive byte stream data from TCP/UDP -> deserialize to V2G msg -> push to queue

// port cmd queue handler : receive command from MTC -> map to operation of system component
//                          event occur -> map to data struct msg and push to cmd queue

#define STC_V2G_UDP_SDP_SERVER 15118
#define STC_CLIENT_PORT 49153
// [V2G2-139] An SDP client shall send SECC Discovery Request message to the destination local-link multicast address (FF02::1) as defined in IETF RFC 4291.
#define STC_IPV6_MULTICAST_ADDRESS "ff02::01"
#define STC_IPV6_LISTEN_ADDRESS "::"

const char* TCP_CMD[] = {
  [static_cast<int>(iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPort)] = "e_getPort",
  [static_cast<int>(iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort)] = "e_disconnectPort",
  [static_cast<int>(iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus)] = "e_getPortStatus",
  [static_cast<int>(iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort)] = "e_connectPort"
};
const char* SLAC_CMD[] = {
  [en_DLINKCmdType::GET_DLINK_STATUS] = "GET_DLINK_STATUS",
  [en_DLINKCmdType::SET_DLINK_TERMINATE] = "SET_DLINK_TERMINATE",
  [en_DLINKCmdType::SET_DLINK_PAUSE] = "SET_DLINK_PAUSE"
};

const char* HAL_CMD[] = {
  [IEC_61851_States::A] = "A",
  [IEC_61851_States::B] = "B",
  [IEC_61851_States::C] = "C",
  [IEC_61851_States::D] = "D",
  [IEC_61851_States::E] = "E",
  [IEC_61851_States::F] = "F",
  [IEC_61851_States::NA] = "NA",
  [IEC_61851_States::none_] = "NONE"
};

System_SECC::System_SECC(const std::shared_ptr<IfRuntime>& runtime, const std::string& _ipv6IF, const std::string &slacCfgFile) {
  this->ipv6IF = _ipv6IF;
  this->slacFile = slacCfgFile;
  // get CppCommon::Asio::Service
  this->_pRuntime = runtime;
  this->_ptrService = this->_pRuntime->getService();
  // get the working io_service(bound to another thread) for queue operation
  this->_ptrIOService = this->_ptrService->GetAsioService();
  // create BasicControlInterface
  this->_pBCIf = std::make_shared<SeccBasicSignaling>(this->_ptrService);
  this->_pPLC = std::make_shared<Plc>(slacCfgFile, _ipv6IF, this->_pBCIf, this->_ptrService, Timer_15118::Timer_par_15118::par_CMN_Intern_PTC_Timeout);
  // create TCP Interface
  this->_pTCPIf = std::make_shared<TCPAdapter>(this->_ptrService);
  // create UDP interface
  this->_pUDPIf = std::make_shared<EVCCUdpClient>(this->_ptrService, STC_IPV6_MULTICAST_ADDRESS, STC_V2G_UDP_SDP_SERVER, this->ipv6IF);
  this->_pUDPIf->SetupReuseAddress(true);
  this->pt_TCP_Param = nullptr;
  this->SLACInitFlag = false;
  Logging::debug(LogComponent_ENABLE, "[STC]: System SECC component created");
}
System_SECC::System_SECC(const std::shared_ptr<IfRuntime>& runtime, const std::string &ipv6_multicast, uint16_t port, const std::string& _ipv6IF, const std::string &slacCfgFile) {
  this->ipv6IF = _ipv6IF;
  this->slacFile = slacCfgFile;
  // get CppCommon::Asio::Service
  this->_pRuntime = runtime;
  this->_ptrService = this->_pRuntime->getService();
  // get the working io_service(bound to another thread) for queue operation
  this->_ptrIOService = this->_ptrService->GetAsioService();
  // create BasicControlInterface
  this->_pBCIf = std::make_shared<SeccBasicSignaling>(this->_ptrService);
  this->_pPLC = std::make_shared<Plc>(slacCfgFile, _ipv6IF, this->_pBCIf, this->_ptrService, Timer_15118::Timer_par_15118::par_CMN_Intern_PTC_Timeout);
  // create TCP Interface
  this->_pTCPIf = std::make_shared<TCPAdapter>(this->_ptrService);
  // create UDP interface
  this->_pUDPIf = std::make_shared<EVCCUdpClient>(this->_ptrService, ipv6_multicast, port, this->ipv6IF);
  this->_pUDPIf->SetupReuseAddress(true);
  this->pt_TCP_Param = nullptr;
  this->SLACInitFlag = false;
  Logging::debug(LogComponent_ENABLE, "[STC]: System SECC component created");
}
System_SECC::~System_SECC() {
  Logging::debug(LogComponent_ENABLE, "[STC]: System SECC component disposed");
  this->pt_V2G_TCP_TLS_ALM_SECC_Port.reset();
  this->pt_V2G_UDP_SDP_Port.reset();
  this->pt_HAL_61851_Port.reset();
  this->pt_HAL_61851_Listener_Port.reset();
  this->pt_SLAC_Port.reset();
  this->_pPLC.reset();
  this->_pBCIf.reset();
  this->_pTCPIf.reset();
  this->_pUDPIf.reset();
  this->pt_TCP_Param.reset();
}

bool System_SECC::start() {
  auto self(this->shared_from_this());
  // create TCP port/ UDP port/ HAL61851 port for System Interface Component.
  static auto h1 = std::make_shared<MsgHandlerFunc>(std::bind(&System_SECC::sendTCPMsgHandler, this, std::placeholders::_1, std::placeholders::_2));
  static auto h2 = std::make_shared<MsgHandlerFunc>(std::bind(&System_SECC::sendUDPMsgHandler, this, std::placeholders::_1, std::placeholders::_2));
  static auto h3 = std::make_shared<CmdHandlerFunc>(std::bind(&System_SECC::cmdHandler, this, std::placeholders::_1, std::placeholders::_2));

  this->pt_V2G_TCP_TLS_ALM_SECC_Port = std::make_shared<V2G_TCP_TLS_ALM_SECC_Port>(this->_ptrIOService, h1, h3);
  this->pt_V2G_UDP_SDP_Port = std::make_shared<V2G_UDP_SDP_Port>(this->_ptrIOService, h2, h3);
  this->pt_HAL_61851_Port = std::make_shared<HAL_61851_Port>(this->_ptrIOService, h3);
  this->pt_HAL_61851_Listener_Port = std::make_shared<HAL_61851_Port>(this->_ptrIOService, h3);
  this->pt_SLAC_Port = std::make_shared<SLAC_Port>(this->_ptrIOService, h3);

  // create TCP handler object
  this->_on15118TcpConnect = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_CONNECT, self);
  this->_on15118TcpDisconnect = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_DISCONNECT, self);
  this->_on15118TcpEmpty = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_EMPTY, self);
  this->_on15118TcpReceive = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_RECEIVE, self);
  this->_on15118TcpSent = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_SENT, self);
  this->_on15118TcpError = std::make_shared<on15118TCPEvent>(en_tcpAdapterCallbackType_ERROR, self);
  // add TCP handler object to TCP interface
  this->_pTCPIf->setEventCallBack(this->_on15118TcpConnect);
  this->_pTCPIf->setEventCallBack(this->_on15118TcpDisconnect);
  this->_pTCPIf->setEventCallBack(this->_on15118TcpEmpty);
  this->_pTCPIf->setEventCallBack(this->_on15118TcpReceive);
  this->_pTCPIf->setEventCallBack(this->_on15118TcpSent);
  this->_pTCPIf->setEventCallBack(this->_on15118TcpError);

  this->_on15118UDPConnect = std::make_shared<on15118UDPEvent>(en_UdpClientCallbackType_CONNECT, self);
  this->_on15118UDPDisconnect = std::make_shared<on15118UDPEvent>(en_UdpClientCallbackType_DISCONNECT, self);
  this->_on15118UDPReceive = std::make_shared<on15118UDPEvent>(en_UdpClientCallbackType_RECEIVE, self);
  this->_on15118UDPSent = std::make_shared<on15118UDPEvent>(en_UdpClientCallbackType_SENT, self);
  this->_on15118UDPError = std::make_shared<on15118UDPEvent>(en_UdpClientCallbackType_ERROR, self);
  this->_pUDPIf->setEventCallBack(this->_on15118UDPConnect);
  this->_pUDPIf->setEventCallBack(this->_on15118UDPDisconnect);
  this->_pUDPIf->setEventCallBack(this->_on15118UDPReceive);
  this->_pUDPIf->setEventCallBack(this->_on15118UDPSent);
  this->_pUDPIf->setEventCallBack(this->_on15118UDPError);
  this->_onSLACEvent = std::make_shared<onSLACEvent>(self);
  this->_pPLC->setEventCallBack(this->_onSLACEvent);
  this->_pPLC->init(true);

  // create HAL61851 handler object
  this->_on61851Event = std::make_shared<onHAL61851Event>(self);
  this->_pBCIf->setEventCallBack(this->_on61851Event);
  this->_pBCIf->start();
  Logging::debug(LogComponent_ENABLE, "[STC]: System SECC component started");
  return true;
}

bool System_SECC::create(std::string &component_name)
{
  // nothings
  return true;
}

bool System_SECC::stop()
{
  this->_pPLC->stop();
  this->_pBCIf->stop();
  (void)this->_pTCPIf->disconnect();
  (void)this->_pUDPIf->stop();
  Logging::debug(LogComponent_ENABLE, "[STC]: Logical link leave, stop TCP, UDP");
  return true;
}

void System_SECC::kill()
{
  // kill system secc object (destructor)
}
void System_SECC::sendTCPMsgHandler(std::shared_ptr<V2gTpMessage> &item, std::shared_ptr<BasePort>& port) {
  bool valid_msg = false;
  char *stream_data;
  ssize_t stream_len;
  if (item->ALMsgType == ALM_HAND_SHAKE) {
    // cast to V2gAppHandMessage -> serialize to get byte stream data
    std::shared_ptr<V2gAppHandMessage> ptrMsg = std::dynamic_pointer_cast<V2gAppHandMessage>(item);
    // serialize data
    valid_msg = (ptrMsg != nullptr);
    if (valid_msg) {
      Logging::info(LogComponent_ENABLE, "[STC]: Send SupportedAppProtocolRequest message");
      ptrMsg->serialize();
      stream_len = ptrMsg->getBufferPtr(&stream_data);
    }
  }
  else if (item->ALMsgType == ALM_EXI) {
    // serialize V2G ALMsg to data stream and send to TCP
    std::shared_ptr<V2gExiMessage> ptrMsg =  std::dynamic_pointer_cast<V2gExiMessage>(item);
    valid_msg = (ptrMsg != nullptr);
    if (valid_msg) {
      Logging::info(LogComponent_ENABLE, fmt::format("[STC]: Send {} message", ptrMsg->getTypeName()));
      ptrMsg->serialize();
      stream_len = ptrMsg->getBufferPtr(&stream_data);
    }
  }
  else {
    Logging::error(LogComponent_ENABLE, "[STC]: Required ALM_EXI|ALM_HANDSHAKE Msg to send on TCP port");
    // incorrect msg type send to TCP interface
  }
  if (valid_msg) {
    this->_pTCPIf->sendAsync(stream_data, stream_len);
  }
}

void System_SECC::sendUDPMsgHandler(std::shared_ptr<V2gTpMessage> &item, std::shared_ptr<BasePort>& port) {
  char *stream_data;
  ssize_t stream_len;
  if (item->ALMsgType == ALM_SDP_REQ) {
    if (this->_pUDPIf->IsConnected()){
      std::shared_ptr<V2gSdpMessage> ptrSdpReqMsg = std::dynamic_pointer_cast<V2gSdpMessage>(item);
      if (ptrSdpReqMsg != nullptr) {
        Logging::info(LogComponent_ENABLE, "[STC]: Send SDP Request message");
        ptrSdpReqMsg->serialize();
        stream_len = ptrSdpReqMsg->getBufferPtr(&stream_data);
        if (!(this->_pUDPIf->sendMulticast(stream_data, stream_len))){
          Logging::error(LogComponent_ENABLE, "[STC]: Send SDP Request message FAILED");
        }
      }
    }
  }
  else {
    Logging::error(LogComponent_ENABLE, "[STC]: Required SDP Request Msg to send on UDP port");
  }
}

void System_SECC::cmdHandler(std::shared_ptr<BaseOperation> &item, std::shared_ptr<BasePort>& port) {
  // mapping command operation and send to each interface
  switch (port->pType){
    case PortType_TCP:
    {
      if (item->op == OpType_TCP) {
        if (item->TcpControlReq != nullptr) {
          std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
          Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: TCP command {}", TCP_CMD[static_cast<int>(item->TcpControlReq->command)]));
          switch (item->TcpControlReq->command){
            case iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPort:{
              responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
              responseEvent->TcpControlRes->result.portStatus.closed = !(this->_pTCPIf->IsConnected());
              responseEvent->TcpControlRes->result.portNumber.intValue = this->_pTCPIf->port();
              responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPort;
              responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
              this->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
              break;
            }
            case iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort:{
              (void)this->_pTCPIf->disconnect();
              break;
            }
            case iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus:{
              responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
              responseEvent->TcpControlRes->result.portStatus.closed = !(this->_pTCPIf->IsConnected());
              responseEvent->TcpControlRes->result.portNumber.intValue = this->_pTCPIf->port();
              responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus;
              responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
              this->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
              break;
            }
            case iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort:{
              // set SUT address then call connect
              if (true == this->_pTCPIf->setSUTAddress(this->pt_TCP_Param->seccIpaddress, pt_TCP_Param->seccPort, this->ipv6IF)){
                (void)this->_pTCPIf->connect();
              }
              break;
            }
          }
        }
        else {
          Logging::error(LogComponent_ENABLE, "[STC]: TCP operation cmd is NULL");
        }
      }
      else {
        Logging::error(LogComponent_ENABLE, "[STC]: Incorrect operation type send to TCP port");
      }
      break;
    }
    case PortType_UDP:
    {
      Logging::debug(LogComponent_ENABLE, "[STC]: UDP operation cmd");
      if (item->op == OpType_TCP){
        // process cmd
      }
      else {
        Logging::error(LogComponent_ENABLE, "[STC]: Incorrect operation type send to UDP port");
      }
      // UDP command operation
      break;
    }
    case PortType_61851:
    {
      if (item->op == OpType_61851) {
        if (item->HAL61851Req != nullptr) {
          Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: Request HAL61851 set state {}", HAL_CMD[item->HAL61851Req->cmd]));
          this->_pBCIf->setState(item->HAL61851Req->cmd);
        }
        else {
          Logging::error(LogComponent_ENABLE, "[STC]: HAL61851 operation cmd is NULL");
        }
      }
      else {
        Logging::error(LogComponent_ENABLE, "[STC]: Incorrect operation type send to HAL61851 port");
      }
      break;
    }
    case PortType_SLAC:
    {
      if (OpType_SLAC == item->op) {
        if (item->SLACReq != nullptr) {
          std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_SLAC);
          Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SLAC command {}", SLAC_CMD[static_cast<int>(item->SLACReq->cmd)]));
          switch (item->SLACReq->cmd)
          {
            case en_DLINKCmdType::GET_DLINK_STATUS:
            {
              responseEvent->SLACRes = std::make_shared<DLINKEvent>();
              responseEvent->SLACRes->event = (en_DLINKEventType)this->_pPLC->getState();
              this->pt_SLAC_Port->setEvent(responseEvent);
              break;
            }
            case en_DLINKCmdType::SET_DLINK_TERMINATE:
            {
              this->_pPLC->stop();
              break;
            }
            case en_DLINKCmdType::SET_DLINK_CLOSE_FD:
            {
              this->_pPLC->close_interface();
              break;
            }
            case en_DLINKCmdType::SET_DLINK_PAUSE:
            {
              this->_pPLC->pause();
              break;
            }
            default:
              break;
          }
        }
        else {
          Logging::error(LogComponent_ENABLE, "[STC]: SLAC operation cmd is NULL");
        }
      }
      else {
        Logging::error(LogComponent_ENABLE, "[STC]: Incorrect operation type send to SLAC port");
      }
      break;
    }
    default:
      break;
  }
}

void onSLACEvent::operator() (pevStateType event) {
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_SLAC);
  responseEvent->SLACRes = std::make_shared<DLINKEvent>();
  if (event < pevStateType_MAX) {
    responseEvent->SLACRes->event = (en_DLINKEventType)event;
    this->parent->pt_SLAC_Port->setEvent(responseEvent);
    Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SLAC Event receive {}", event));
  }
  else {
    Logging::error(LogComponent_ENABLE, fmt::format("[STC]: Incorrect SLAC event receive {}", event));
  }
}

/* Event from 61851 - notify to pt_HAL_61851_Listener_Port */
void onHAL61851Event::operator()(en_BCEventType event)
{
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_61851);
  responseEvent->HAL61851Res = std::make_shared<HAL_61851_Event>();
  responseEvent->HAL61851Res->type = event;
  responseEvent->HAL61851Res->state = this->parent->_pBCIf->getState();
  responseEvent->HAL61851Res->VoltLevel = this->parent->_pBCIf->getVoltLevel();
  responseEvent->HAL61851Res->PWMStatus = this->parent->_pBCIf->getPWMStatus();
  responseEvent->HAL61851Res->PWMDuty = this->parent->_pBCIf->getPWMDuty();
  responseEvent->HAL61851Res->PWMFreq = this->parent->_pBCIf->getPWMFreq();
  this->parent->pt_HAL_61851_Listener_Port->setEvent(responseEvent);
  Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SUT 61851: State={0}, Volt={1}, PWM status={2}, PWM Duty={3}, PWM Freq={4}", responseEvent->HAL61851Res->state,\
    responseEvent->HAL61851Res->VoltLevel, responseEvent->HAL61851Res->PWMStatus, responseEvent->HAL61851Res->PWMDuty, responseEvent->HAL61851Res->PWMFreq));
}

// event for connect/disconnect TCP
void on15118TCPEvent::operator()() {
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
  switch (this->type){
    case en_tcpAdapterCallbackType_CONNECT: {
      // push event to event queue
      this->parent->_pTCPIf->receiveAsync();
      responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
      responseEvent->TcpControlRes->result.portStatus.closed = !(this->parent->_pTCPIf->IsConnected());
      responseEvent->TcpControlRes->result.portNumber.intValue = this->parent->_pTCPIf->port();
      responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_connectPort;
      responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
      this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
      Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SUT TCP {0} - {1} connected",this->parent->_pTCPIf->address(), this->parent->_pTCPIf->port()));
      break;
    }
    case en_tcpAdapterCallbackType_DISCONNECT: {
      responseEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
      responseEvent->TcpControlRes->result.portStatus.closed = !(this->parent->_pTCPIf->IsConnected());
      responseEvent->TcpControlRes->result.portNumber.intValue = this->parent->_pTCPIf->port();
      responseEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
      responseEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
      this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setEvent(responseEvent);
      Logging::debug(LogComponent_ENABLE, fmt::format("[STC]: SUT TCP {0} - {1} disconnected",this->parent->_pTCPIf->address(), this->parent->_pTCPIf->port()));
      break;
    }
    case en_tcpAdapterCallbackType_EMPTY: {
      // Logging::debug(LogComponent_ENABLE, "Empty event TCP");
      break;
    }
    default:
      break;
  }
}

// TCP receive event receive handler
void on15118TCPEvent::operator()(const void *buffer, size_t size) {
  std::shared_ptr<V2gTpMessage> recMsg = std::make_shared<V2gTpMessage>();
  // push data to recMsg
  recMsg->setMessage((const char*)buffer, size);
  // update to port queue
  this->parent->pt_V2G_TCP_TLS_ALM_SECC_Port->setMsg(recMsg);
  Logging::debug(LogComponent_ENABLE, "[STC]: Store receive msg to port queue");
}

// TCP interface sent event handler
void on15118TCPEvent::operator()(size_t sent, size_t pending) {
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
}

// TCP interface error event handler
void on15118TCPEvent::operator()(int error, const std::string& category, const std::string& message) {
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_TCP);
  // process tcp error
  // connected error/ disconnected error/ send error/ receive error/ connection abort ?
  Logging::error(LogComponent_ENABLE, fmt::format("[STC]: SUT TCP Error {0} - {1} disconnected", category, message));
}

void on15118UDPEvent::operator()()
{
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_UDP);
  switch (this->type) {
    case en_UdpClientCallbackType_CONNECT:
    {
      Logging::info(LogComponent_ENABLE, fmt::format("[STC]: SUT UDP {0} - {1} connected",this->parent->_pUDPIf->endpoint().address().to_string(), this->parent->_pUDPIf->endpoint().port()));
      break;
    }
    case en_UdpClientCallbackType_DISCONNECT:
    {
      Logging::info(LogComponent_ENABLE, fmt::format("[STC]: SUT UDP {0} - {1} disconnected",this->parent->_pUDPIf->endpoint().address().to_string(), this->parent->_pUDPIf->endpoint().port()));
      break;
    }
    default:
      break;
  }
}

void on15118UDPEvent::operator()(const void* buffer, size_t size)
{
  // receive sdp message in UDP interface
  std::shared_ptr<V2gTpMessage> recMsg = std::make_shared<V2gSdpResMessage>();
  recMsg->setMessage((const char*)buffer, size);
  this->parent->pt_V2G_UDP_SDP_Port->setMsg(recMsg);
}

void on15118UDPEvent::operator()(size_t sent)
{
  // send sdp message successful
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_UDP);
}

void on15118UDPEvent::operator()(int error, const std::string& category, const std::string& message)
{
  std::shared_ptr<BaseOperation> responseEvent = std::make_shared<BaseOperation>(OpType_UDP);
  Logging::error(LogComponent_ENABLE, fmt::format("[STC]: SUT UDP Error {0} - {1} - {2} disconnected", error, category, message));
}
