#include "TB_SECC_SupportedAppProtocol.h"
#include "TB_SECC_CommonBehavior.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TimerCfg.h"
#include "PIXITCfg.h"
#include "PICSCfg.h"
#include "V2gALMsg.h"

using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Timer_15118::Timer_par_15118;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;

static std::shared_ptr<appHandAppProtocolType> md_CMN_CMN_AppProtocolType_001(std::string xmlnamespace, uint32_t major_ver, uint32_t minor_ver, uint8_t schemeID, uint8_t priority);
static std::shared_ptr<appHandAnonType_supportedAppProtocolReq> md_CMN_CMN_SupportedAppProtocolReq_001(std::shared_ptr<appHandAppProtocolType> protocol);

static std::shared_ptr<appHandAppProtocolType> md_CMN_CMN_AppProtocolType_001(std::string xmlnamespace, uint32_t major_ver, uint32_t minor_ver, uint8_t schemeID, uint8_t priority)
{
  std::shared_ptr<appHandAppProtocolType> val = std::shared_ptr<appHandAppProtocolType>(new appHandAppProtocolType);
  val->VersionNumberMajor = major_ver;
  val->VersionNumberMinor = minor_ver;
  val->SchemaID = schemeID;
  val->Priority = priority;
  strcpy(val->ProtocolNamespace.characters, xmlnamespace.data());
  val->ProtocolNamespace.charactersLen = xmlnamespace.length();
  return val;
}

static std::shared_ptr<appHandAnonType_supportedAppProtocolReq> md_CMN_CMN_SupportedAppProtocolReq_001(std::shared_ptr<appHandAppProtocolType> protocol)
{
  std::shared_ptr<appHandAnonType_supportedAppProtocolReq> val(new appHandAnonType_supportedAppProtocolReq);
  val->AppProtocol.arrayLen = 1;
  memcpy(&val->AppProtocol.array[0], protocol.get(), sizeof(appHandAppProtocolType));
  return val;
}

TestBehavior_SECC_SupportedAppProtocol::TestBehavior_SECC_SupportedAppProtocol(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}
TestBehavior_SECC_SupportedAppProtocol::~TestBehavior_SECC_SupportedAppProtocol()
{
}

verdict_val TestBehavior_SECC_SupportedAppProtocol::f_SECC_CMN_TB_VTB_SupportedAppProtocol_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SupportedAppProtocolReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SupportedAppProtocolRes>();

  std::shared_ptr<appHandAnonType_supportedAppProtocolReq> appProtocols = md_CMN_CMN_SupportedAppProtocolReq_001(md_CMN_CMN_AppProtocolType_001(
      this->mtc->vc_Supported_ISO_Namespace, this->mtc->vc_versionNumberMajor, this->mtc->vc_versionNumberMinor, 10, 2));
  std::static_pointer_cast<SupportedAppProtocolReq>(sendMsg)->setSupportedAppProtocolsReq(appProtocols.get());

  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->setResponseCode(appHandresponseCodeType_OK_SuccessfulNegotiation);
  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->mResponseCode_flag = has_value;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SupportedAppProtocolRes> cast_expected = std::dynamic_pointer_cast<SupportedAppProtocolRes>(expected);
    std::shared_ptr<SupportedAppProtocolRes> cast_received = std::make_shared<SupportedAppProtocolRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      // check response code
      if (appHandresponseCodeType_Failed_NoNegotiation != cast_received->getResponseCode())
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_001]: PASS - receive correct response");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
        if (appHandresponseCodeType_OK_SuccessfulNegotiation == cast_received->getResponseCode())
        {
          this->mtc->setverdict(pass, "SupportedAppProtocolRes message was correct.");
          return true;
        }
        else
        {
          this->mtc->setverdict(pass, "SupportedAppProtocolRes message was correct. Minor version deviation was detected.");
          return true;
        }
      }
      else
      {
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_001]: FAIL - msg content is different from expected value");
        // correct message name but content(body) is not match with expected.
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
        return false;
      }
    }
    else
    {
      // failed deserialize, msg is not SupportedAppProtocolRes
      Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_001]: FAIL - can not deserialize msg from receive data");
      // set verdict to error -> failed session(message sequence failed)
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq);
  while (true)
  {
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(v_vct, "V2G_Message received, but SupportedAppProtocolRes was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received SupportedAppProtocolRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SupportedAppProtocol::f_SECC_CMN_TB_VTB_SupportedAppProtocol_002(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SupportedAppProtocolReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SupportedAppProtocolRes>();
  std::shared_ptr<appHandAnonType_supportedAppProtocolReq> appProtocols = md_CMN_CMN_SupportedAppProtocolReq_001(md_CMN_CMN_AppProtocolType_001(
      "urn:iso:15118:2:2014:MsgDef", 3, this->mtc->vc_versionNumberMinor, 1, 1));
  std::static_pointer_cast<SupportedAppProtocolReq>(sendMsg)->setSupportedAppProtocolsReq(appProtocols.get());
  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->setResponseCode(appHandresponseCodeType_Failed_NoNegotiation);
  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->mResponseCode_flag = specific;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SupportedAppProtocolRes> cast_expected = std::dynamic_pointer_cast<SupportedAppProtocolRes>(expected);
    std::shared_ptr<SupportedAppProtocolRes> cast_received = std::make_shared<SupportedAppProtocolRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (*cast_expected == *cast_received)
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_002]: PASS - SupportedAppProtocolRes message was correct. Protocol handshake failed");
        this->mtc->setverdict(pass, "SupportedAppProtocolRes message was correct. Protocol handshake failed");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
        return true;
      }
      else
      {
        // correct message name but content(body) is not match with expected.
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_002]: FAIL - msg content is different from expected value");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
        return false;
      }
    }
    else
    {
      // set verdict to error -> failed session(message sequence failed)
      Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_002]: FAIL - can not deserialize msg from receive data");
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq);
  while (true)
  {
    // check if secc oscillator pwm is shutdown
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      // turn of tcp interface
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        // if secc pwm not off check it again? TODO: check if logic is in while loop?
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
        }
        if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
        {
          // if tcp if is off but oscillator of secc still output pwm, push error
          if (isShutdownOSC == false)
          {
            Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
          }
          this->mtc->pt_HAL_61851_Internal_Port->clear();
          break;
        }
        // still receive v2g msg
        if (this->cmn->a_SECC_Unexpected_Message_Content_002(v_vct, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
        {
          break;
        }
        if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
        {
          break;
        }
      }
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(v_vct, "V2G_Message received, but SupportedAppRes was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received SupportedAppRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
    if (this->cmn->a_SECC_CommunicationSetup_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SupportedAppProtocol::f_SECC_CMN_TB_VTB_SupportedAppProtocol_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<BaseOperation> expectedRes = std::make_shared<BaseOperation>(OpType_TCP);
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
  // Wait until sequence timeout in SUT should expire
  t_wait->start(par_V2G_SECC_Sequence_Timeout - par_CMN_Transmission_Delay);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
  while (true)
  {
    if (t_wait->timeout())
    {
      break;
    }
  }
  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
    {
      if (isShutdownOSC == false)
      {
        Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
      }
      this->mtc->pt_HAL_61851_Internal_Port->clear();
      break;
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
    {
      break;
    }
    if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_SupportedAppProtocol::f_SECC_CMN_TB_VTB_SupportedAppProtocol_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<SupportedAppProtocolReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<SupportedAppProtocolRes>();
  std::shared_ptr<appHandAnonType_supportedAppProtocolReq> appProtocols = md_CMN_CMN_SupportedAppProtocolReq_001(md_CMN_CMN_AppProtocolType_001(
      this->mtc->vc_Supported_ISO_Namespace, this->mtc->vc_versionNumberMajor, this->mtc->vc_versionNumberMinor, 10, 2));
  std::static_pointer_cast<SupportedAppProtocolReq>(sendMsg)->setSupportedAppProtocolsReq(appProtocols.get());
  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->setResponseCode(appHandresponseCodeType_OK_SuccessfulNegotiationWithMinorDeviation);
  std::static_pointer_cast<SupportedAppProtocolRes>(expectedMsg)->mResponseCode_flag = specific;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<SupportedAppProtocolRes> cast_expected = std::dynamic_pointer_cast<SupportedAppProtocolRes>(expected);
    std::shared_ptr<SupportedAppProtocolRes> cast_received = std::make_shared<SupportedAppProtocolRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (*cast_expected == *cast_received)
      {
        this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_004]: PASS - receive correct response");
        this->mtc->setverdict(pass, "SupportedAppProtocolRes message was correct. Minor version deviation was detected.");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
        return true;
      }
      else
      {
        // correct message name but content(body) is not match with expected.
        Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_004]: FAIL - msg content is different from expected value");
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
        return false;
      }
    }
    else
    {
      // set verdict to error -> failed session(message sequence failed)
      Logging::debug(LogTbFnc_ENABLE, "[TB][SupportedAppProtocol_004]: FAIL - can not deserialize msg from receive data");
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->vc_versionNumberMinor = PIXIT_SECC_CMN_VersionNumberMinor + 1;
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_SupportedAppProtocolReq);
  if (this->mtc->vc_versionNumberMinor < this->mtc->vc_versionNumberMajor)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
      {
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly  by the SUT."))
      {
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(fail, "V2G_Message received, but SupportedAppProtocolRes was expected."))
        {
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received SupportedAppProtocolRes message, but with invalid data content."))
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
  }
  else
  {
    this->mtc->setverdict(inconc, "The selected VersionNumberMinor is not smaller than VersionNumberMajor.");
  }
  return this->mtc->getverdict();
}