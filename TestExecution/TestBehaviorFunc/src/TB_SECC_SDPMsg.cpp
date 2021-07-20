#include "TB_SECC_SDPMsg.h"
#include "V2gALMsg.h"
#include "V2gSdpMessage.h"
#include "V2gSdpResMessage.h"
#include "V2gTpMessage.h"
#include "TimerCfg.h"

using namespace Timer_15118::Timer_par_15118;
using namespace Timer_15118_2::Timer_par_15118_2;

verdict_val TestBehavior_SECC_SDP::f_SECC_CMN_TB_VTB_SDP_001(iso1Part4_Security_TYPE v_security, verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  int v_count = 0;
  // send SdpRequestMessage
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<V2gSdpMessage>();
  // expected SdpResponseMessage
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setSecurityType(v_security);
  std::static_pointer_cast<V2gSdpMessage>(sendMsg)->setTransportType(0x00);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setSecurityType(v_security);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setTransportType(0x00);

  auto receive_handler = [this, &v_count](std::shared_ptr<V2gTpMessage>& expected, std::shared_ptr<V2gTpMessage>& received)->bool{
    // store V2G_Port
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::dynamic_pointer_cast<V2gSdpResMessage>(received);
    if (cast_received->deserialize()){
      // stop SDP timer, compare expected receive SDP message
      this->mtc->tc_EVCC_SDP_Timer->stop();
      if (cast_expected->getSecurityType() == cast_received->getSecurityType()){
        asio::ip::address_v6::bytes_type ipAddr;
        this->mtc->vc_V2G_Port_PortNumber = cast_received->getSeccPort();
        cast_received->getSeccIpAddr((char *)ipAddr.data(), 16);
        // store Ipaddress
        this->mtc->vc_V2G_Port_IpAddress = asio::ip::make_address_v6(ipAddr).to_string();
        v_count = this->mtc->vc_maxRepetitionSDP;
        // store security type
        this->mtc->vc_Security = cast_received->getSecurityType();
        Logging::debug(LogTbFnc_ENABLE, fmt::format("[TB][SDP_001]: SECC IPV6: {0} | {1}", this->mtc->vc_V2G_Port_IpAddress, this->mtc->vc_V2G_Port_PortNumber));
        this->mtc->setverdict(pass, "SDP Response message was correct.");
      }
      else {
        v_count = this->mtc->vc_maxRepetitionSDP;
        this->mtc->setverdict(inconc, "SUT did not support the requested transmission security.");
      }
      return true;
    }
    else{
      return false;
    }
  };
  while (v_count < this->mtc->vc_maxRepetitionSDP)
  {
    this->mtc->pt_V2G_UDP_SDP_Port->send(sendMsg);
    v_count = v_count + 1;
    Logging::debug(LogTbFnc_ENABLE, fmt::format("[TB][SDP_001]: send SDP msg count {}", v_count));
    this->mtc->tc_EVCC_SDP_Timer->start(par_EVCC_SDP_Timeout);
    while(true)
    {
      if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, receive_handler)) {
        break;
      }
      if (this->mtc->tc_EVCC_SDP_Timer->timeout())
      {
        Logging::error(LogTbFnc_ENABLE, fmt::format("[TB][SDP_001]: SDP Request {} does not receive response in time", v_count));
        // send a new SDP request message if v_count < vc_maxRepetitionSDP
        if (v_count == this->mtc->vc_maxRepetitionSDP)
        {
          this->mtc->setverdict(v_vct, "SDP repetition maximum is reached. SDP process shall be stopped.");
        }
        break;
      }
      if (this->cmn->a_SECC_CommunicationSetup_Timeout(v_vct)){
        break;
      }
    }
  }
  return this->mtc->getverdict();
}

// test SUT after failed CommunicationSetupTimer, it shall not response to SDP request
verdict_val TestBehavior_SECC_SDP::f_SECC_CMN_TB_VTB_SDP_002(iso1Part4_Security_TYPE v_security)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  while(true)
  {
    if (this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->timeout()){
      break;
    }
    if(this->mtc->pt_V2G_UDP_SDP_Port->receive()) {
      Logging::debug(LogTbFnc_ENABLE, "[TB][SDP_002]: FAIL - No SDP message was expected when wait for Communication timeout");
      this->mtc->setverdict(fail, "No SDP message was expected.");
      break;
    }
  }
  this->mtc->tc_EVCC_SDP_Timer->start(par_EVCC_SDP_Timeout);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<V2gSdpMessage>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();
  std::static_pointer_cast<V2gSdpResMessage>(sendMsg)->setSecurityType(v_security);
  std::static_pointer_cast<V2gSdpResMessage>(sendMsg)->setTransportType(0x00);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setSecurityType(v_security);
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setTransportType(0x00);
  auto receive_handler = [this](std::shared_ptr<V2gTpMessage>& expected, std::shared_ptr<V2gTpMessage>& received) -> bool{
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::dynamic_pointer_cast<V2gSdpResMessage>(received);
    if(cast_received->deserialize()){
      // check deserialize ok, then valid SDP respond message
      this->mtc->tc_EVCC_SDP_Timer->stop();
      Logging::debug(LogTbFnc_ENABLE, "[TB][SDP_002]: FAIL -Received SDP msg when wait for Communication timeout");
      this->mtc->setverdict(fail, "The SUT did not stop the SDP server.");
      return true;
    }
    else {
      return false;
    }
  };
  this->mtc->pt_V2G_UDP_SDP_Port->send(sendMsg);
  while(true)
  {
    // fail if receive valid sdp reponse message
    if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, receive_handler)){
      break;
    }
    // pass if no sdp response message receive
    if (this->mtc->tc_EVCC_SDP_Timer->timeout()) {
      Logging::debug(LogTbFnc_ENABLE, "[TB][SDP_002]: PASS -Communication timeout occur");
      this->mtc->setverdict(pass, "No SDP response was received. The SUT has stopped the SDP server.");
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SDP::f_SECC_CMN_TB_VTB_SDP_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  int v_count = 0;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<V2gSdpMessage>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<V2gSdpResMessage>();
  std::static_pointer_cast<V2gSdpResMessage>(sendMsg)->setSecurityType(0x00); // TLS
  std::static_pointer_cast<V2gSdpResMessage>(sendMsg)->setTransportType(0x00); // TCP
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setSecurityType(0x10); // expected no TLS
  std::static_pointer_cast<V2gSdpResMessage>(expectedMsg)->setTransportType(0x00);
  auto receive_handler = [this, &v_count](std::shared_ptr<V2gTpMessage>& expected, std::shared_ptr<V2gTpMessage>& received)->bool{
    // if compare msg correct
    std::shared_ptr<V2gSdpResMessage> cast_expected = std::dynamic_pointer_cast<V2gSdpResMessage>(expected);
    std::shared_ptr<V2gSdpResMessage> cast_received = std::dynamic_pointer_cast<V2gSdpResMessage>(received);
    if(cast_received->deserialize()){
      this->mtc->tc_EVCC_SDP_Timer->stop();
      if ((cast_received->getSecurityType() == cast_expected->getSecurityType()) &&
          (cast_received->getTransportType() == cast_expected->getTransportType())){
        asio::ip::address_v6::bytes_type ipAddr;
        this->mtc->vc_V2G_Port_PortNumber = cast_received->getSeccPort();
        cast_received->getSeccIpAddr((char *)ipAddr.data(), 16);
        // store Ipaddress
        this->mtc->vc_V2G_Port_IpAddress = asio::ip::make_address_v6(ipAddr).to_string();
        this->mtc->vc_Security = cast_received->getSecurityType();
        v_count = this->mtc->vc_maxRepetitionSDP;
        Logging::debug(LogTbFnc_ENABLE, fmt::format("[TB][SDP_003]: SECC IPV6: {0} | {1}", this->mtc->vc_V2G_Port_IpAddress, this->mtc->vc_V2G_Port_PortNumber));
        this->mtc->setverdict(pass, "SDP Response message was correct.");
      }
      else {
        v_count = this->mtc->vc_maxRepetitionSDP;
        this->mtc->setverdict(inconc, "SUT supports the requested transmission security 'secured with TLS'. Check the PIXIT configuration.");
      }
      return true;
    }
    else{
      return false;
    }
  };
  while (v_count < this->mtc->vc_maxRepetitionSDP)
  {
    this->mtc->tc_EVCC_SDP_Timer->start(par_EVCC_SDP_Timeout);
    this->mtc->pt_V2G_UDP_SDP_Port->send(sendMsg);
    v_count = v_count + 1;
    while(true)
    {
      if (this->mtc->pt_V2G_UDP_SDP_Port->receive(expectedMsg, receive_handler)){
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
      if (this->cmn->a_SECC_CommunicationSetup_Timeout(fail)){
        break;
      }
    }
  }
  return this->mtc->getverdict();
}