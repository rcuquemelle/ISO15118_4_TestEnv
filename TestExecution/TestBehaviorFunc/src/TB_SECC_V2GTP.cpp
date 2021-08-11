#include "TB_SECC_V2GTP.h"
#include "V2gALMsg.h"
#include "V2gSdpMessage.h"
#include "V2gSdpResMessage.h"
#include "V2gTpMessage.h"
#include "TimerCfg.h"
using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_2::Timer_par_15118_2;
#define SECURITY_TLS 0x00 // secured with TLS
// 0x01-0x0F = reserved
#define SECURITY_NONE 0x10 // No transport layer security
// 0x11-0xFF = reserved
#define TRANSPORT_TCP 0x00 // TCP
// 0x01-0x0F = reserved
#define TRANSPORT_UDP 0x10 // reserved for UDP
// 0x11-0xFF = reserved
#define TP_VER 0x01
#define TP_VER_INVERSE 0xFE
#define TP_PAYLOAD_V2G 0x8001
#define TP_PAYLOAD_SDPREQ 0x9000
#define TP_PAYLOAD_SDPRES 0x9001

verdict_val TestBehavior_SECC_V2GTPSessionSetup::f_SECC_CMN_TB_VTB_V2GTPSessionSetup_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // send session setup request msg
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionSetupReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionSetupRes>();
  // md_CMN_V2GTP_header_TYPE_001('01'H,'FE'H,'8001'H, omit)
  sendMsg->setTPVersion(TP_VER, TP_VER_INVERSE);
  sendMsg->setPayloadType(TP_PAYLOAD_V2G);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setEVCCID(this->mtc->vc_eVCCID);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mEVSEID_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mResponseCode_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mTimeStamp_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionSetupRes> cast_expected = std::dynamic_pointer_cast<SessionSetupRes>(expected);
    std::shared_ptr<SessionSetupRes> cast_received = std::make_shared<SessionSetupRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    // check if deserialize is valid?
    if (cast_received->deserialize())
    {
      char V2GTPHeader[8];
      cast_received->getHeader(V2GTPHeader);
      if ((V2GTPHeader[0] == TP_VER) && (V2GTPHeader[1] == TP_VER_INVERSE) && (cast_received->getPayloadType() == TP_PAYLOAD_V2G)
        && (cast_received->getPayloadLength() != 0)) {
        // compare cast_received and cast_expected
        if ((*cast_expected) == (*cast_received))
        {
          // pass v2g session setup is ok
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "V2GTP (SessionSetupRes) message was correct.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // invalid receive message content - not match with expected
          // -> set receive msg queue status to unexpected content
          // a_SECC_Unexpected_Message_Content shall check status for this value
          Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SessionSetupRes) with invalid body content");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else {
        Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SessionSetupRes) with invalid header content");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
        return false;
      }
    }
    else
    {
      Logging::error(LogTbFnc_ENABLE, "Receive messsage but failed to deserialize, might not be V2G msg");
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  // start msg timer for session setup request message
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
  while (true)
  {
    // check the received msg
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received anything, but not the expected V2GTP message."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}
verdict_val TestBehavior_SECC_V2GTPSessionSetup::f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(iso1Part4_V2GTP_header_TYPE v_v2gtpHeader)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SessionSetupReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SessionSetupRes>();
  // set ALM header session id
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  // set ALM SessionSetupReq message body content EVCCID value
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setEVCCID(this->mtc->vc_eVCCID);
  // serialize data to byte stream to remove payload length later
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->serialize();
  // set tp header version
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setTPVersion(v_v2gtpHeader.protocolVersion, v_v2gtpHeader.invProtocolVersion);
  // set tp header payload type
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setPayloadType(v_v2gtpHeader.payloadType);
  // set tp header payload length
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->setPayloadLength(v_v2gtpHeader.payloadLength);
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->dumpTpHeader();
  std::static_pointer_cast<SessionSetupReq>(sendMsg)->dumpMsg();
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mEVSEID_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mResponseCode_flag = has_value;
  std::static_pointer_cast<SessionSetupRes>(expectedMsg)->mTimeStamp_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SessionSetupRes> cast_expected = std::dynamic_pointer_cast<SessionSetupRes>(expected);
    std::shared_ptr<SessionSetupRes> cast_received = std::make_shared<SessionSetupRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);

    if (cast_received->deserialize())
    {
      char V2GTPHeader[8];
      cast_received->getHeader(V2GTPHeader);
      if ((V2GTPHeader[0] == TP_VER) && (V2GTPHeader[1] == TP_VER_INVERSE) && (cast_received->getPayloadType() == TP_PAYLOAD_V2G)
        && (cast_received->getPayloadLength() != 0)) {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(fail, "Invalid V2GTP header was not ignored.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SessionSetupRes) with invalid body content");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else {
        Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SessionSetupRes) with invalid header content");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
        return false;
      }
    }
    else
    {
      Logging::error(LogTbFnc_ENABLE, "Receive messsage but failed to deserialize, might not be V2G msg");
      return false;
    }
  };
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SessionSetupReq);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received anything, but not the expected V2GTP message."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(pass))
    {
      this->mtc->setverdict(pass, "Invalid V2GTP header was ignored.");
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// send SDP msg, repeat for num
verdict_val TestBehavior_SECC_V2GTPSDP::f_SECC_CMN_TB_VTB_V2GTPSDP_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  int v_count = 0;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<V2gSdpMessage>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();
  sendMsg->setTPVersion(TP_VER, TP_VER_INVERSE);
  sendMsg->setPayloadType(TP_PAYLOAD_SDPREQ);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setSecurityType(SECURITY_NONE);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setTransportType(TRANSPORT_TCP);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setSecurityType(SECURITY_NONE);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setTransportType(TRANSPORT_TCP);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mIpV6Addr_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mPort_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mSecurity_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mTransport_flag = has_value;
  auto receive_handler = [this, &v_count](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    // compare
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::make_shared<V2gSdpResMessage>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      char V2GTPHeader[8];
      cast_received->getHeader(V2GTPHeader);
      if ((V2GTPHeader[0] == TP_VER) && (V2GTPHeader[1] == TP_VER_INVERSE) && (cast_received->getPayloadType() == TP_PAYLOAD_SDPRES)
        && (cast_received->getPayloadLength() == 20)) {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_EVCC_SDP_Timer->stop();
          asio::ip::address_v6::bytes_type ipAddr = asio::ip::address_v6::bytes_type();
          this->mtc->vc_V2G_Port_PortNumber = cast_received->getSeccPort();
          cast_received->getSeccIpAddr((char *)ipAddr.data(), 16);
          // store Ipaddress
          this->mtc->vc_V2G_Port_IpAddress = asio::ip::make_address_v6(ipAddr).to_string();
          v_count = this->mtc->vc_maxRepetitionSDP;
          this->mtc->setverdict(pass, "V2GTP Header message was correct. (SDP Response Message).");
          this->mtc->pt_V2G_UDP_SDP_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SDP) with invalid body content");
          return false;
        }
      }
      else {
        Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SDP) with invalid header content");
        return false;
      }
    }
    else
    {
      Logging::error(LogTbFnc_ENABLE, "Receive messsage but failed to deserialize, might not be V2G msg");
      return false;
    }
  };
  // send sdp msg max vc_maxRepetitionSDP time
  while (v_count < this->mtc->vc_maxRepetitionSDP)
  {
    this->mtc->tc_EVCC_SDP_Timer->start(par_EVCC_SDP_Timeout);
    this->mtc->pt_V2G_UDP_SDP_Port->send(sendMsg);
    v_count = v_count + 1;
    while (true)
    {
      if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, receive_handler))
      {
        break;
      }
      if (this->mtc->tc_EVCC_SDP_Timer->timeout())
      {
        // send a new SDP request message if v_count < vc_maxRepetitionSDP
        if (v_count == this->mtc->vc_maxRepetitionSDP)
        {
          this->mtc->setverdict(fail, "SDP repetition maximum is reached. SDP process shall be stopped.");
        }
        break;
      }
      if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
      {
        break;
      }
    }
  }
  return this->mtc->getverdict();
}
verdict_val TestBehavior_SECC_V2GTPSDP::f_SECC_CMN_TB_VTB_V2GTPSDP_002(iso1Part4_V2GTP_header_TYPE v_v2gtpHeader)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<V2gSdpMessage>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setSecurityType(SECURITY_NONE);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setTransportType(TRANSPORT_TCP);
  // serialize data then change the header value
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->serialize();
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setTPVersion(v_v2gtpHeader.protocolVersion, v_v2gtpHeader.invProtocolVersion);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setPayloadType(v_v2gtpHeader.payloadType);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setPayloadLength(v_v2gtpHeader.payloadLength);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->dumpTpHeader();
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->dumpMsg();
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setSecurityType(SECURITY_NONE);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setTransportType(TRANSPORT_TCP);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mIpV6Addr_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mPort_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mSecurity_flag = has_value;
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->mTransport_flag = has_value;
  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::dynamic_pointer_cast<V2gSdpResMessage>(received);
    // expected invalid SDP msg shall be ignore
    if (cast_received->deserialize())
    {
      char V2GTPHeader[8];
      cast_received->getHeader(V2GTPHeader);
      if ((V2GTPHeader[0] == TP_VER) && (V2GTPHeader[1] == TP_VER_INVERSE) && (cast_received->getPayloadType() == TP_PAYLOAD_SDPRES)
        && (cast_received->getPayloadLength() == 20)) {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_EVCC_SDP_Timer->stop();
          this->mtc->setverdict(fail, "Invalid V2GTP header was not ignored.");
          this->mtc->pt_V2G_UDP_SDP_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SDP) with invalid body content");
          this->mtc->setverdict(fail, "Invalid V2GTP header was not ignored.");
          return true;
        }
      }
      else {
        Logging::error(LogTbFnc_ENABLE, "Receive messsage V2GTP(SDP) with invalid header content");
        this->mtc->setverdict(fail, "Invalid V2GTP header was not ignored.");
        return true;
      }
    }
    else
    {
      Logging::error(LogTbFnc_ENABLE, "Receive messsage but failed to deserialize, might not be V2G msg");
      return false;
    }
  };
  this->mtc->tc_EVCC_SDP_Timer->start(par_EVCC_SDP_Timeout);
  this->mtc->pt_V2G_UDP_SDP_Port->send(sendMsg);
  while (true)
  {
    if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, receive_handler))
    {
      break;
    }
    if (this->mtc->tc_EVCC_SDP_Timer->timeout())
    {
      this->mtc->setverdict(pass, "Invalid V2GTP header was ignored.");
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}