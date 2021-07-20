#ifndef __PORTTYPE_H__
#define __PORTTYPE_H__
// port type: define kind of messages can be sent or receive by this port
#include "AsyncQueue.h"
#include "OperationQueue.h"
#include "fmt/core.h"
#include "functional"
#include "asiowrapper/memory.h"
#include "TestSystemLogging.h"

using BaseMsgQueue = MsgQueue<V2gTpMessage>;
using BaseAsyncQueueListener = AsyncQueueListener<V2gTpMessage>;
using BaseOpQueue = MsgQueue<BaseOperation>;
using BaseOpQueueListener = AsyncQueueListener<BaseOperation>;
class BasePort;
using MsgHandlerFunc = std::function<void(std::shared_ptr<V2gTpMessage>&, std::shared_ptr<BasePort>&)>;
using CmdHandlerFunc = std::function<void(std::shared_ptr<BaseOperation>&, std::shared_ptr<BasePort>&)>;

typedef enum {
  PortType_BASE = 0,
  PortType_TCP,
  PortType_UDP,
  PortType_61851,
  PortType_61851_LISTENER,
  PortType_SLAC,
  PortType_NULL
} PortType;

typedef enum {
  ReceiveType_NONE,
  ReceiveType_MSG_AVAILABLE,
  ReceiveType_UNEXPECTED_MSG,
  ReceiveType_UNEXPECTED_V2G_MSG,
  ReceiveType_UNEXPECTED_MSG_CONTENT,
  ReceiveType_NO_UDP_MSG,
  ReceiveType_NUM
} ReceiveMsgType;

typedef enum {
  ReceiveEventType_NONE,
  ReceiveEventType_EVENT_AVAILABLE,
  ReceiveEventType_NUM
} ReceiveEventType;

typedef enum {
  PortState_NONE,
  PortState_MAPPED,
  PortState_NUM
} PortStateType;

class BasePort: public std::enable_shared_from_this<BasePort>
{
public:
  std::shared_ptr<asio::io_service> _service;
  // send V2G msg to SUT queue
  std::shared_ptr<BaseMsgQueue> sendQueue;
  // receive V2G msg from SUT queue
  std::shared_ptr<BaseMsgQueue> receiveQueue;
  // status for receiveQueue
  ReceiveMsgType receiveQueueStatus;
  std::string_view receiveMsgName;

  // async V2G send queue listener
  std::shared_ptr<BaseAsyncQueueListener> asyncV2GQueueListener;

  // operation cmd queue
  std::shared_ptr<BaseOpQueue> cmdQueue;
  // operation event queue
  std::shared_ptr<BaseOpQueue> eventQueue;
  // status for eventQueue
  ReceiveEventType eventQueueStatus;

  // async cmd queue listener
  std::shared_ptr<BaseOpQueueListener> asyncCmdQueueListener;

  std::shared_ptr<MsgHandlerFunc> sendV2GHandler;
  std::shared_ptr<CmdHandlerFunc> cmdHandler;

public:
  BasePort(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2);
  BasePort(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<CmdHandlerFunc> &_h2);
  BasePort(const std::shared_ptr<asio::io_service>& service);
  ~BasePort();
  PortType pType;
  PortStateType pState;
  // operation:
  //    message-base: send, receive, trigger
  //    procedure-base: call, getcall, reply, raise, getreply, catch
  // examine top element of incoming port queues: check
  // controlling operation: clear, start, stop, halt, checkstate

  // ASYNCHRONOUS
  // Message-based communication is communication based on an asynchronous message exchange. Message-based
  // communication is non-blocking on the SEND operation, where processing in the SENDER continues immediately after the send operation occurs

  // SYNCHRONOUS
  // The RECEIVER is blocked on the receive operation until it processes the received message.

protected:
  // default implementation handle shall output 2 param error code and Queue item
  void sendV2GQueueHandler(const asio::error_code &ec, std::shared_ptr<V2gTpMessage> item, std::shared_ptr<BaseAsyncQueueListener> AsyncQListener, std::shared_ptr<BaseMsgQueue> queue) {
    if (!ec) {
      // call send msg handler for dequeued item
      if (this->sendV2GHandler) {
        auto self = this->shared_from_this();
        Logging::debug(LogComponent_ENABLE, fmt::format("[PORT]:{} V2g queue handler call", pType));
        (*(this->sendV2GHandler))(item, self);
      }
      AsyncQListener->asyncDequeue(queue, std::bind(&BasePort::sendV2GQueueHandler, this, std::placeholders::_1, std::placeholders::_2, AsyncQListener, queue));
    }
    else if (ec == asio::error::try_again) {
      AsyncQListener->asyncDequeue(queue, std::bind(&BasePort::sendV2GQueueHandler, this, std::placeholders::_1, std::placeholders::_2, AsyncQListener, queue));
    }
    else {
      Logging::error(LogComponent_ENABLE, fmt::format("[PORT]: MSG Queue cancel {}", ec.message()));
    }
  }

  // call parent function which handle the command operation
  void sendCmdQueueHandler(const asio::error_code &ec, std::shared_ptr<BaseOperation> item,\
    std::shared_ptr<BaseOpQueueListener> AsyncQListener, std::shared_ptr<BaseOpQueue> queue) {
    if (!ec) {
      if (this->cmdHandler) {
        auto self = this->shared_from_this();
        Logging::debug(LogComponent_ENABLE, fmt::format("[PORT]:{} CMD queue handler call",pType));
        (*(this->cmdHandler))(item, self);
      }
      AsyncQListener->asyncDequeue(queue, std::bind(&BasePort::sendCmdQueueHandler, this, std::placeholders::_1, std::placeholders::_2, AsyncQListener, queue));
    }
    else if (ec == asio::error::try_again) {
      AsyncQListener->asyncDequeue(queue, std::bind(&BasePort::sendCmdQueueHandler, this, std::placeholders::_1, std::placeholders::_2, AsyncQListener, queue));
    }
    else {
      Logging::error(LogComponent_ENABLE, fmt::format("[PORT]: CMD Queue cancel {}", ec.message()));
    }
  }

public:
  // enqueue receive message to receive queue
  void setMsg(std::shared_ptr<V2gTpMessage>& msg) {
    if (this->receiveQueue != nullptr){
      this->receiveQueue->enq(msg);
      this->receiveQueueStatus = ReceiveType_MSG_AVAILABLE;
    }
  }
  // enqueue event to event queue
  void setEvent(std::shared_ptr<BaseOperation>& action) {
    if (this->eventQueue != nullptr){
      this->eventQueue->enq(action);
      this->eventQueueStatus = ReceiveEventType_EVENT_AVAILABLE;
    }
  }
  void clear() {
    if (this->sendQueue != nullptr) {
      this->sendQueue->clear();
    }
    if (this->receiveQueue != nullptr){
      this->receiveQueue->clear();
    }
    if (this->cmdQueue != nullptr) {
      this->cmdQueue->clear();
    }
    if (this->eventQueue != nullptr) {
      this->eventQueue->clear();
    }
    this->eventQueueStatus = ReceiveEventType_NONE;
    this->receiveQueueStatus = ReceiveType_NONE;
  }
  // push v2g message to send v2g msg queue
  void send(const std::shared_ptr<V2gTpMessage>& msg) {
    if(nullptr != this->sendQueue) {
      this->sendQueue->enq(msg);
      this->receiveQueueStatus = ReceiveType_NONE;
    }
  }
  // push cmd action to cmd queue
  void send(std::shared_ptr<BaseOperation>& action) {
    if(nullptr != this->cmdQueue) {
      this->cmdQueue->enq(action);
      this->eventQueueStatus = ReceiveEventType_NONE;
    }
  }

  // receive expected message and call compare handler
  template<typename Func>
  bool receive(std::shared_ptr<V2gTpMessage>& compareMsg, Func& handler) {
    if (false == this->receiveQueue->empty()) {
      std::pair<bool, BaseMsgQueue::ptr_type> ret {this->receiveQueue->deq()};
      // queue item available
      if (ret.first && (ret.second != nullptr)) {
        return handler(compareMsg, ret.second);
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  template<typename Func>
  bool receive(std::vector<std::shared_ptr<V2gTpMessage>>& compareMsgList, Func& handler) {
    if (false == this->receiveQueue->empty()) {
      std::pair<bool, BaseMsgQueue::ptr_type> ret {this->receiveQueue->deq()};
      // queue item available
      if (ret.first && (ret.second != nullptr)) {
        return handler(compareMsgList, ret.second);
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  // receive expected response cmd and call compare handler
  template<typename Func>
  bool receive(std::shared_ptr<BaseOperation>& compareMsg, Func& handler) {
    if (false == this->eventQueue->empty()) {
      std::pair<bool, BaseOpQueue::ptr_type> ret {this->eventQueue->deq()};
      if (ret.first && (ret.second != nullptr)) {
        return handler(compareMsg, ret.second);
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  // checking status of receive queue and call handler function
  template<typename Func>
  bool receive(ReceiveMsgType status, Func& handler) {
    if (status == receiveQueueStatus) {
      return handler();
    }
    else {
      return false;
    }
  }

  // checking status of receive queue and call handler function
  template<typename Func>
  bool receive(ReceiveEventType status, Func& handler) {
    if (status == eventQueueStatus) {
      return handler();
    }
    else {
      return false;
    }
  }

  // checking status of receive queue and call handler function
  template<typename Func>
  bool receive(Func& handler) {
    if (false == this->receiveQueue->empty()) {
      std::pair<bool, BaseMsgQueue::ptr_type> ret {this->receiveQueue->deq()};
      // queue item available
      if (ret.first && (ret.second != nullptr)) {
        return handler(ret.second);
      }
      else {
        return false;
      }
    }
    else {
      return false;
    }
  }

  bool receive() {
    if (false == this->receiveQueue->empty()) {
      (void)this->receiveQueue->deq();
      return true;
    }
    else {
      return false;
    }
  }

  bool receive(ReceiveMsgType status) {
    bool result = (status == receiveQueueStatus);
    if (true == result){
      receiveQueueStatus = ReceiveType_NONE;
    }
    return result;
  }
  bool checkstate(PortStateType type) {
    return (type == pState);
  }
};

// send receive V2G-Application Layer Messages(ALM) or supportedAppProtocol msgs
class V2G_TCP_TLS_ALM_SECC_Port : public BasePort
{
  // queue listener
public:
  V2G_TCP_TLS_ALM_SECC_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2);
  ~V2G_TCP_TLS_ALM_SECC_Port();
};

// send receive SDP messages via UDP
class V2G_UDP_SDP_Port : public BasePort
{

public:
  V2G_UDP_SDP_Port(const std::shared_ptr<asio::io_service>& service,  std::shared_ptr<MsgHandlerFunc> &_h1, std::shared_ptr<CmdHandlerFunc> &_h2);
  ~V2G_UDP_SDP_Port();
};

// send receive messages to IEC61851 communication unit
// communication unit shall interpret messages and set corresponding signal to SUT
class HAL_61851_Port : public BasePort
{
public:
  HAL_61851_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<CmdHandlerFunc> &_h2);
  ~HAL_61851_Port();
};

// synchronize the status of IEC61851 PWM signal between MTC and PTC
class HAL_61851_Internal_Port : public BasePort
{

public:
  HAL_61851_Internal_Port(const std::shared_ptr<asio::io_service>& service);
  ~HAL_61851_Internal_Port();
};

// send SLAC message to SUT though SLACIf cmd
// receive SLAC status from SLACIf
class SLAC_Port : public BasePort
{
public:
  SLAC_Port(const std::shared_ptr<asio::io_service>& service, std::shared_ptr<CmdHandlerFunc> &_h2);
  ~SLAC_Port();
};

#endif // __PORTTYPE_H__