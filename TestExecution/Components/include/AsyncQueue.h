#ifndef __ASYNCQUEUE_H__
#define __ASYNCQUEUE_H__
#include <utility>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "asiowrapper/asio.h"
#include "asiowrapper/service.h"
#include "V2gAppHandMessage.h"
#include "V2gExiMessage.h"
#include "V2gSdpMessage.h"
#include "V2gSdpResMessage.h"
#include "V2gTpMessage.h"

#include "fmt/core.h"
// queue shall receive v2gtp msg(base class), dequeue/process(check child class) by async handler
// default containter type is queue
template<typename T>
class MsgQueue {
public:
  // typedef for value stored in queue
  // (need this so we can create an item with default ctor)
  using value_type = T;
  using ptr_type = std::shared_ptr<T>;

  // ctors,assign,dtor
  MsgQueue() = default;
  MsgQueue(MsgQueue const &) = delete;  // remove copy constructor
  MsgQueue(MsgQueue &&) = default;
  MsgQueue &operator=(MsgQueue const &) = delete;
  MsgQueue &operator=(MsgQueue &&) = default;
  ~MsgQueue() = default;

  // put a message into queue
  void enq(ptr_type t)
  {
    // mutex lock queue during enqueue
    std::lock_guard<std::mutex> lock(mtx);
    mQueue.push(t);
    // notify all other wait acquire mutex
    cndVar.notify_all();
  }
  // dequeue a message (return.first == false if deq() was disabled)
  std::pair<bool, ptr_type> deq()
  {
    // acquired mutex lock queue during dequeue
    std::unique_lock<std::mutex> lock(mtx);
    // block thread, wait until mtx available, if deq queue = enable(true) or queue has data(mQueue.empty==false), continue wait until lock release
    // cndVar.wait(lock, [&]() { return !deq_enabled || !mQueue.empty(); });

    // if deq is disabled(deq_enable = false) or queue is empty(mQueue.empty() = true) return false and empty type
    if (mQueue.empty()) {
      return std::make_pair(true, nullptr);
    }
    if (!deq_enabled) {
      return std::make_pair(false, nullptr);
    }
    // check if we have a message
    std::pair<bool, ptr_type> ret{std::make_pair(true, mQueue.front())};
    // remove first element
    mQueue.pop();
    cndVar.notify_all();
    // return data pair
    return ret;
  }
  // cancel deq operations (will also release blocking threads)
  void disable_deq(bool disable)
  {
    std::unique_lock<std::mutex> lock(mtx);
    // true = set deq_enabled = false(disable dequeue)
    deq_enabled = !disable;
    cndVar.notify_all();
  }
  // check if queue is empty
  bool empty() const
  {
    std::unique_lock<std::mutex> lock(mtx);
    cndVar.notify_all();
    return mQueue.empty();
  }
  void clear() {
    std::unique_lock<std::mutex> lock(mtx);
    while(false == mQueue.empty()) {
      mQueue.pop();
    }
    cndVar.notify_all();
  }
  uint32_t len() const
  {
    std::unique_lock<std::mutex> lock(mtx);
    return mQueue.size();
  }

private:
  mutable std::mutex mtx;
  mutable std::condition_variable cndVar;
  bool deq_enabled = true; // enable dequeue, false = disable
  // queue
  std::queue<ptr_type> mQueue;
};

// forward decl
class QueueListener;
template <typename Impl = QueueListener>
class QueueListenerService;

// io object
template <typename ServiceType, typename Queue>
class BaseQueueListener : public asio::basic_io_object<ServiceType>
{
public:
  // ctor
  explicit BaseQueueListener(const std::shared_ptr<asio::io_service> &service)
      // create basic_io_object with QueueListenerService
      : asio::basic_io_object<ServiceType>(*(service))
  {
  }
  // async deq operation
  template <typename Handler>
  void asyncDequeue(std::shared_ptr<Queue> q, Handler handler)
  {
    // call implementation of QueueListenerService
    (this->get_service()).callImpl(this->get_implementation(), q, handler);
  }
};

// typedef for using standard service object
template<typename T>
using AsyncQueueListener = BaseQueueListener<QueueListenerService<>, MsgQueue<T>>;

// asio service class for asyn queue listener IO object
template <typename Impl>
class QueueListenerService : public asio::io_service::service
{
public:
  // required to have id of service
  static asio::io_service::id id;
  // ctor
  explicit QueueListenerService(asio::io_service &io_service)
      : asio::io_service::service(io_service)
  {
  }
  // dtor
  ~QueueListenerService()
  {
  }
  // get a typedef  for implementation
  using implementation_type = std::shared_ptr<Impl>;

  // mandatory (construct an implementation object)
  void construct(implementation_type &impl)
  {
    impl.reset(new Impl(this->get_io_context()));
  }
  // mandatory (destroy an implementation object)
  void destroy(implementation_type &impl)
  {
    impl.reset();
  }
  // async sync deq operation QueueListener = impl
  template <typename Handler, typename Queue>
  void callImpl(implementation_type &impl, std::shared_ptr<Queue> q, Handler handler)
  {
    // this is a non-blocking operation so we are OK calling impl object in this thread
    impl->async_deq(impl, q, handler);
  }

private:
  // shutdown service (required)
  void shutdown_service()
  {
  }
};
// definition of id of service (required)
template <typename Impl>
asio::io_service::id QueueListenerService<Impl>::id;

// queue listener implementation object
class QueueListener
{
public:
  // ctor (set up work queue for io_service so we don't bail out when executing run())
  QueueListener(asio::io_service &io_service)
      : post_io_service(io_service),
        impl_work(new asio::io_service::work(post_io_service))
  {
  }
  // dtor (clear work queue, stop io service and join thread)
  ~QueueListener()
  {
    impl_work.reset(nullptr);
  }

public:
  // deque message (post request to thread)
  template <typename Handler, typename Queue>
  void async_deq(std::shared_ptr<QueueListener> impl, std::shared_ptr<Queue> tq, Handler handler)
  {
    post_io_service.post(deq_operation<Handler, Queue>(impl, post_io_service, tq, handler));
  }

private:
  // private data
  // Asio service
  asio::io_service &post_io_service;
  std::unique_ptr<asio::io_service::work> impl_work;
  // function object calling blocking deq() on queue/ implementation
  template <typename Handler, typename Queue>
  class deq_operation
  {
  public:
    // ctor
    deq_operation(std::shared_ptr<QueueListener> impl, asio::io_service &io_service, std::shared_ptr<Queue> tq, Handler handler)
        : _wimpl(impl), _io_service(io_service), _work(io_service), _tq(tq), _handler(handler)
    {
    }
    // function calling implementation object - runs in the thread created in ctor
    void operator()()
    {
      // make sure implementation object is still valid
      std::shared_ptr<QueueListener> impl{_wimpl.lock()};
      // fmt::print("[ASYNC] operator call\r\n");
      // if valid, go ahead and do blocking call on queue, otherwise post aborted message
      if (impl)
      {
        // dequeue
        std::pair<bool, typename Queue::ptr_type> ret{_tq->deq()};
        asio::error_code ec = (!ret.first ? asio::error::operation_aborted : asio::error_code());
        if (ret.second == nullptr) {
          ec = asio::error::try_again;
        }
        // fmt::print("[ASYNC] dequeue call handler {}\r\n", ret.first);
        _handler(ec, ret.second);
        // this->_io_service.post(asio::detail::bind_handler(_handler, ec, ret.second));
      }
      else
      {
        // fmt::print("[ASYNC] operation abort\r\n");
        _handler(asio::error::operation_aborted, nullptr);
        // this->_io_service.post(asio::detail::bind_handler(_handler, asio::error::operation_aborted, nullptr));
      }
    }

  private:
    std::weak_ptr<QueueListener> _wimpl;
    asio::io_service &_io_service;
    asio::io_service::work _work;
    std::shared_ptr<Queue> _tq;
    Handler _handler;
  };
};

#endif // __ASYNCQUEUE_H__