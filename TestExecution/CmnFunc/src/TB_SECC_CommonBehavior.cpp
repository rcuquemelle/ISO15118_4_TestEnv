#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "OperationQueue.h"
#include "TestSystemLogging.h"
TestBehavior_SECC_CommonBehavior::TestBehavior_SECC_CommonBehavior(const std::shared_ptr<SECC_Tester> &_mtc)
  :mtc(_mtc)
{
}

TestBehavior_SECC_CommonBehavior::~TestBehavior_SECC_CommonBehavior()
{
}

static bool a_SECC_processPLCLinkNotifications_001() {
  // check slac status
  return true;
}

// port.receive() shall popout queue and check message (if msg name incorrect set flag name, if msg content incorrect set content flag)
bool TestBehavior_SECC_CommonBehavior::a_SECC_Unexpected_Message_Content(verdict_val v_verdict,const std::string & v_message)
{
  // deserialize ok, compare opeartion failed
  // check receive flag == ReceiveType_UNEXPECTED_MSG_CONTENT
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(ReceiveType_UNEXPECTED_MSG_CONTENT))
  {
    // stop msg v2g msg timer
    this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
    // set verdict
    this->mtc->setverdict(v_verdict, v_message);
    return true;
  }
  else {
    return false;
  }
}
bool TestBehavior_SECC_CommonBehavior::a_SECC_Unexpected_Message_Content_002(verdict_val v_verdict,const std::string & v_message)
{
  // deserialize ok, compare opeartion failed
  // check receive flag == ReceiveType_UNEXPECTED_MSG_CONTENT
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(ReceiveType_MSG_AVAILABLE))
  {
    // stop msg v2g msg timer
    this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
    // set verdict
    this->mtc->setverdict(v_verdict, v_message);
    return true;
  }
  else {
    return false;
  }
}

// expected v2g type msg but receive handshake/sdp instead
bool TestBehavior_SECC_CommonBehavior::a_SECC_Unexpected_Message(verdict_val v_verdict,const std::string & v_message)
{
  // deserialize failed. i.e. receive V2G EXI incase waiting for appSupportProtocol or otherway
  // check receive flag == ReceiveType_UNEXPECTED_MSG
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(ReceiveType_UNEXPECTED_MSG))
  {
    this->mtc->setverdict(v_verdict, v_message);
    return true;
  }
  else {
    return false;
  }
}

// port.receive() shall popout queue and check message (if msg name incorrect set flag name, if msg content incorrect set content flag)
bool TestBehavior_SECC_CommonBehavior::a_SECC_Unexpected_V2G_Message(verdict_val v_verdict,const std::string & v_message)
{
  // deserialize ok, but message type not match expected V2G msg
  if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(ReceiveType_UNEXPECTED_V2G_MSG))
  {
    this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
    this->mtc->setverdict(v_verdict, fmt::format("{0} - {1}", v_message, this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName));
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = "";
    return true;
  }
  else {
    return false;
  }
}

// message request/response(pair) timeout
bool TestBehavior_SECC_CommonBehavior::a_SECC_Timeout(verdict_val v_verdict)
{
  if (this->mtc->tc_V2G_EVCC_Msg_Timer->timeout() && (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus == ReceiveType_NONE))
  {
    this->mtc->setverdict(v_verdict, "Nothing received. V2G_EVCC_Msg_Timer was triggered.");
    return true;
  }
  else {
    return false;
  }
}

// no sdp received
bool TestBehavior_SECC_CommonBehavior::a_No_SDP_Message(std::string v_message, verdict_val v_verdict)
{
  if (this->mtc->pt_V2G_UDP_SDP_Port->receive(ReceiveType_NO_UDP_MSG))
  {
    this->mtc->tc_EVCC_SDP_Timer->stop();
    this->mtc->setverdict(v_verdict, v_message);
    return true;
  }
  else {
    return false;
  }
}

// timeout when wating for SDP msg
bool TestBehavior_SECC_CommonBehavior::a_SECC_SDP_Timeout(verdict_val v_verdict)
{
  if (this->mtc->tc_EVCC_SDP_Timer->timeout())
  {
    this->mtc->setverdict(v_verdict, "Nothing received. tc_EVCC_SDP_Timer was triggered.");
    return true;
  }
  else {
    return false;
  }
}
bool TestBehavior_SECC_CommonBehavior::a_SDP_Message()
{
  // Sender_IPaddress_TYPE v_sut_ipAddress;
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();

  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setIpV6Addr(this->mtc->vc_V2G_Port_IpAddress);
  auto compare_handler = [this](std::shared_ptr<V2gTpMessage>& expected, std::shared_ptr<V2gTpMessage>& received) -> bool {
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::make_shared<V2gSdpResMessage>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    cast_received->deserialize();
    char expected_ip[16];
    char receive_ip[16];
    cast_received->getSeccIpAddr(receive_ip,16);
    cast_expected->getSeccIpAddr(expected_ip, 16);
    if (!memcmp(expected_ip, receive_ip, 16))
    {
      this->mtc->setverdict(fail, "SDPMessage was received, but not expected.");
      return true;
    }
    else
    {
      return false;
    }
  };
  while (true){
    if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, compare_handler)) {
      return true;
    }
    else {
      return false;
    }
  }
}
bool TestBehavior_SECC_CommonBehavior::a_SECC_CommunicationSetup_Timeout(verdict_val v_verdict)
{
  if (this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->timeout())
  {
    this->mtc->setverdict(v_verdict, "Nothing received. V2G_EVCC_CommunicationSetup_Timer was triggered.");
    return true;
  }
  else {
    return false;
  }
}
bool TestBehavior_SECC_CommonBehavior::a_SECC_TCPConnection_Status_Listener(verdict_val v_verdict,const std::string & v_message)
{
  std::shared_ptr<BaseOperation> expectedEvent = std::make_shared<BaseOperation>(OpType_TCP);
  expectedEvent->TcpControlRes = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes>();
  expectedEvent->TcpControlRes->ack = iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE::e_success;
  expectedEvent->TcpControlRes->command = iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_disconnectPort;
  expectedEvent->TcpControlRes->result.portStatus.closed = true;
  auto compare_handler = [this, &v_verdict, &v_message](std::shared_ptr<BaseOperation>& expect, std::shared_ptr<BaseOperation>& event)-> bool {
    bool result = false;
    if ((expect->TcpControlRes != nullptr) && (event->TcpControlRes != nullptr)) {
      if ((expect->TcpControlRes->ack == event->TcpControlRes->ack) &&
        (expect->TcpControlRes->command == event->TcpControlRes->command) &&
        (expect->TcpControlRes->result.portStatus.closed == event->TcpControlRes->result.portStatus.closed)){
          result = true;
        }
      else {
        result = false;
      }
    }
    else{
      result = false;
    }
    if (result == true) {
      this->mtc->setverdict(v_verdict, v_message);
      this->mtc->vc_isTcpPortClosed = true;
    }
    return result;
  };
  return (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedEvent, compare_handler));
}
bool TestBehavior_SECC_CommonBehavior::a_SECC_TCP_Connection_Termination_Timeout()
{
  // TODO: add checking TCPPort to makesure no msg is available??
  if (this->mtc->tc_CMN_TCP_Connection_Termination_Timer->timeout())
  {
    this->mtc->setverdict(fail, "TCP connection was >>NOT<< terminated by the SUT, tc_CMN_TCP_Connection_Termination_Timer was triggered.");
    return true;
  }
  else {
    return false;
  }
}
bool TestBehavior_SECC_CommonBehavior::isError()
{
  // deserialize receive msg failed -> incorrect expected msg type -> set error
  // this->mtc->setverdict(error);
  if (this->mtc->getverdict() == error)
  {
    return true;
  }
  return false;
}
bool TestBehavior_SECC_CommonBehavior::f_SECC_startSleepingPhase(float v_time)
{
  bool rst = false;
  std::shared_ptr<PATimer> t_sleep = this->mtc->pt_TimerManager->createTimer("local", v_time);
  t_sleep->start();
  while(true)
  {
    if (t_sleep->timeout()){
      Logging::info(LogCmnFnc_ENABLE, "Sleeping phase was terminated by the Test System.");
      this->mtc->pt_TimerManager->popTimer("local");
      rst = true;
      break;
    }
    if (a_SECC_processPLCLinkNotifications_001()) {
      rst = true;
      break;
    }
    if (this->mtc->pt_SLAC_Port->receive())
    {
      this->mtc->setverdict(fail, "Invalid message was received within sleeping phase on port 'pt_SLAC_Port'.");
      rst = true;
      break;
    }
    if (this->mtc->pt_V2G_UDP_SDP_Port->receive())
    {
      this->mtc->setverdict(fail, "Invalid message was received within sleeping phase on port 'pt_V2G_UDP_SDP_Port'.");
      rst = true;
      break;
    }
  }
  return rst;
}