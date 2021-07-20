// QUEUE implementation
#include "PortType.h"
#include "TestSystemLogging.h"

// base port with both MsgHandler and CmdHandler Listener handler function
BasePort::BasePort(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2)
  : sendV2GHandler(_h1), cmdHandler(_h2) {
  this->_service = service;

  this->receiveQueueStatus = ReceiveType_NONE;
  this->receiveMsgName = "";
  this->sendQueue = std::make_shared<BaseMsgQueue>();
  this->receiveQueue = std::make_shared<BaseMsgQueue>();
  this->asyncV2GQueueListener = std::make_shared<BaseAsyncQueueListener>(this->_service);
  this->asyncV2GQueueListener->asyncDequeue(this->sendQueue,\
    std::bind(&BasePort::sendV2GQueueHandler, this, std::placeholders::_1, std::placeholders::_2, this->asyncV2GQueueListener, this->sendQueue));

  this->eventQueueStatus = ReceiveEventType_NONE;
  this->cmdQueue = std::make_shared<BaseOpQueue>();
  this->eventQueue = std::make_shared<BaseOpQueue>();
  this->asyncCmdQueueListener = std::make_shared<BaseOpQueueListener>(this->_service);
  this->asyncCmdQueueListener->asyncDequeue(this->cmdQueue,\
    std::bind(&BasePort::sendCmdQueueHandler, this, std::placeholders::_1, std::placeholders::_2, this->asyncCmdQueueListener, this->cmdQueue));
}

// base port with CmdHandler listener function
BasePort::BasePort(const std::shared_ptr<asio::io_service>& service,\
    std::shared_ptr<CmdHandlerFunc> &_h2) : cmdHandler(_h2) {
  this->_service = service;
  this->sendQueue = nullptr;
  this->receiveQueue = nullptr;
  this->cmdQueue = std::make_shared<BaseOpQueue>();
  this->eventQueue = std::make_shared<BaseOpQueue>();
  this->asyncCmdQueueListener = std::make_shared<BaseOpQueueListener>(this->_service);
  this->asyncCmdQueueListener->asyncDequeue(this->cmdQueue,\
    std::bind(&BasePort::sendCmdQueueHandler, this, std::placeholders::_1, std::placeholders::_2, this->asyncCmdQueueListener, this->cmdQueue));
}

// base port only listen for event
BasePort::BasePort(const std::shared_ptr<asio::io_service>& service) {
  this->_service = service;
  this->sendQueue = nullptr;
  this->receiveQueue = nullptr;
  this->cmdQueue = nullptr;
  this->eventQueue = std::make_shared<BaseOpQueue>();
}

// destructor/ disable queue
BasePort::~BasePort()
{
  // stop async queue listener
  if (this->sendQueue != nullptr){
    this->sendQueue->disable_deq(true);
  }
  if (this->receiveQueue != nullptr) {
    this->receiveQueue->disable_deq(true);
  }
  if (this->cmdQueue != nullptr) {
    this->cmdQueue->disable_deq(true);
  }
  if (this->eventQueue != nullptr) {
    this->eventQueue->disable_deq(true);
  }
}

/***************** TCP Port definition ******************/
V2G_TCP_TLS_ALM_SECC_Port::V2G_TCP_TLS_ALM_SECC_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2)
  : BasePort(service, _h1, _h2) {
    pType = PortType_TCP;
    Logging::debug(LogComponent_ENABLE, "[PORT]: TCP Port created");
}
V2G_TCP_TLS_ALM_SECC_Port::~V2G_TCP_TLS_ALM_SECC_Port() {
  Logging::debug(LogComponent_ENABLE, "[PORT]: TCP Port disposed");
}

V2G_UDP_SDP_Port::V2G_UDP_SDP_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2)
  : BasePort(service, _h1, _h2) {
    pType = PortType_UDP;
    Logging::debug(LogComponent_ENABLE, "[PORT]: UDP Port created");
}

V2G_UDP_SDP_Port::~V2G_UDP_SDP_Port() {
  Logging::debug(LogComponent_ENABLE, "[PORT]: UDP Port disposed");
}

HAL_61851_Port::HAL_61851_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<CmdHandlerFunc> &_h2) : BasePort(service, _h2) {
  pType = PortType_61851;
  Logging::debug(LogComponent_ENABLE, "[PORT]: HAL61851 Port created");
}

HAL_61851_Port::~HAL_61851_Port() {
  Logging::debug(LogComponent_ENABLE, "[PORT]: HAL61851 Port disposed");
}

HAL_61851_Internal_Port::HAL_61851_Internal_Port(const std::shared_ptr<asio::io_service>& service) : BasePort(service) {
  pType = PortType_61851_LISTENER;
  Logging::debug(LogComponent_ENABLE, "[PORT]: HAL61851 Listener Port created");
}

HAL_61851_Internal_Port::~HAL_61851_Internal_Port() {
  Logging::debug(LogComponent_ENABLE, "[PORT]: HAL61851 Listener Port disposed");
}

SLAC_Port::SLAC_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<CmdHandlerFunc> &_h2): BasePort(service, _h2){
  pType = PortType_SLAC;
  Logging::debug(LogComponent_ENABLE, "[PORT]: SLAC Port created");
}

SLAC_Port::~SLAC_Port(){
  Logging::debug(LogComponent_ENABLE, "[PORT]: SLAC Port disposed");
}