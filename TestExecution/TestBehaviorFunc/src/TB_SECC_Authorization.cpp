#include "TB_SECC_Authorization.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TimerCfg.h"
#include "PIXITCfg.h"
#include "PICSCfg.h"
#include "V2gALMsg.h"
#include "TB_SECC_Msg.h"
#include "TestSystemLogging.h"

using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Timer_15118::Timer_par_15118;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace DataStructure_PIXIT_15118_2;
using namespace urn_iso_15118_2_2013_MsgDataTypes;
using namespace DataStructure_PICS_15118;

TestBehavior_SECC_Authorization::TestBehavior_SECC_Authorization(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_Authorization::~TestBehavior_SECC_Authorization()
{
}

static bool f_SECC_CMN_EIMIdentification(void)
{
  return true;
}

static void f_SECC_setEimStatus(bool val)
{
}

// EIM
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<AuthorizationRes>();

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);

  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::finished);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = specific;

  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mEVSEProcessing_flag = specific;

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  iso1Part4_EVSEProcessingType v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction;
  if ((PICS_SECC_CMN_EIMDone == iso1Part4_EIMDone::v2gAuthorization) || (!this->mtc->vc_testCaseSpecific))
  {
    // check EIM status
    (void)f_SECC_CMN_EIMIdentification();
  }

  auto receive_handler = [this, &v_eVSEprocessing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected[0]);
    std::shared_ptr<AuthorizationRes> cast_expected2 = std::dynamic_pointer_cast<AuthorizationRes>(expected[1]);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes message was correct.");
          if ((PICS_SECC_CMN_EIMDone == iso1Part4_EIMDone::v2gAuthorization) || (!this->mtc->vc_testCaseSpecific))
          {
            // set EIM status for state
            f_SECC_setEimStatus(true);
          }
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  while (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
      {
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received AuthorizationRes message, but with invalid data content."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Timeout(v_vct))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
      {
        this->mtc->setverdict(v_vct, "V2G_EVCC_Ongoing_Timer has expired. AuthorizationRes failed, EVSEProcessing = Finished was not sent in time.");
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
    }
    if (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction)
    {
      Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 0.1s wait ongoing_WaitingForCustomerInteraction"));
      PAsleep(0.1);
    }
  }
  return this->mtc->getverdict();
}

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_002(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> sendMsg2 = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  iso1Part4_EVSEProcessingType v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  int v_cnt = 1;
  std::string v_privateKey;

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationReq>(sendMsg2)->setSessionId(this->mtc->vc_SessionID);

  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::finished);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = specific;

  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mEVSEProcessing_flag = specific;

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this, &v_eVSEprocessing](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected[0]);
    std::shared_ptr<AuthorizationRes> cast_expected2 = std::dynamic_pointer_cast<AuthorizationRes>(expected[1]);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes message was correct.");
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_EVCC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Timeout);
          }
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  while (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
  {
    if (v_cnt == 1)
    {
      std::string msgname = "authorizationReq";
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
      if (isbound(this->mtc->vc_contractPrivateKey))
      {
        v_privateKey = this->mtc->vc_contractPrivateKey;
      }
      else
      {
        v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_VALID");
      }
      /* Signed header for msg*/
      SignatureType aSignature;
      BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
      md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_privateKey);
      // write signed header data
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    }
    else
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg2);
    }
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
    v_cnt = v_cnt + 1;
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
      {
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly  terminated by the SUT."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received AuthorizationRes message, but with invalid data content."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Timeout(v_vct))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->mtc->tc_V2G_EVCC_Ongoing_Timer->timeout())
      {
        this->mtc->setverdict(v_vct, "V2G_EVCC_Ongoing_Timer has expired. AuthorizationRes failed, EVSEProcessing = Finished was not sent in time.");
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
    }
    if (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
    {
      Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 0.1s wait ongoing P&C verify"));
      PAsleep(0.1);
    }
  }
  return this->mtc->getverdict();
}

// EIM & PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();

  std::static_pointer_cast<ServiceDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SequenceError);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pChargeService_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pServiceList_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pPaymentOptionList_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServiceDiscoveryRes> cast_expected = std::dynamic_pointer_cast<ServiceDiscoveryRes>(expected);
    std::shared_ptr<ServiceDiscoveryRes> cast_received = std::make_shared<ServiceDiscoveryRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "ServiceDiscoveryRes with responseCode 'fAILED_SequenceError' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// EIM
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  bool isShutdownOSC = false;

  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = omit;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes with responseCode 'fAILED_UnknownSession' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  bool isShutdownOSC = false;
  std::string v_privateKey;

  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = omit;
  std::string msgname = "authorizationReq";
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
  if (isbound(this->mtc->vc_contractPrivateKey))
  {
    v_privateKey = this->mtc->vc_contractPrivateKey;
  }
  else
  {
    v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_VALID");
  }
  /* Signed header for msg*/
  SignatureType aSignature;
  BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
  md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_privateKey);
  // write signed header data
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes with responseCode 'fAILED_UnknownSession' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  bool isShutdownOSC = false;
  std::string v_privateKey;

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_ChallengeInvalid);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  // get invalid challenge value
  this->mtc->vc_GenChallenge = fx_generateGenChallenge();
  std::string msgname = "authorizationReq";
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
  if (isbound(this->mtc->vc_contractPrivateKey)) {
    v_privateKey = this->mtc->vc_contractPrivateKey;
  }
  else {
    v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_VALID");
  }
  BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
  /* Signed header for msg*/
  SignatureType aSignature;
  md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_privateKey);
  // write signed header data
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes with responseCode 'fAILED_ChallengeInvalid' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  bool isShutdownOSC = false;
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

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SignatureError);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);

  std::string msgname = "authorizationReq";
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
  // // load wrong private key
  std::string v_invalidPrivateKey = fx_loadPrivateKey("CRT_OEM_LEAF_VALID");
  BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
  /* Signed header for msg*/
  SignatureType aSignature;
  md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_invalidPrivateKey);
  // write signed header data
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes with responseCode 'fAILED_SignatureError' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  bool isShutdownOSC = false;
  std::string v_privateKey;

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SignatureError);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = omit;

  f_SECC_setIsConfirmationFlagDC();
  f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  std::string msgname = "authorizationReq";
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
  if (isbound(this->mtc->vc_contractPrivateKey))
  {
    v_privateKey = this->mtc->vc_contractPrivateKey;
  }
  else
  {
    v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_VALID");
  }
  BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
  /* Signed header for msg*/
  SignatureType aSignature;
  md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_privateKey);
  // write signed header data
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);
  // change genChallenge
  this->mtc->vc_GenChallenge = fx_generateGenChallenge();
  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->setverdict(pass, "AuthorizationRes with responseCode 'fAILED_SignatureError' is successful.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
  while (true)
  {
    if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
    {
      isShutdownOSC = true;
    }
    if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendCmd);
      this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
      while (true)
      {
        if (isShutdownOSC == false)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
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
      break;
    }
    if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
    {
      break;
    }
    if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(fail))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

// EIM
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<AuthorizationRes>();
  iso1Part4_EVSEProcessingType v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction;
  bool isShutdownOSC = false;

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::finished);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = specific;

  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mEVSEProcessing_flag = specific;

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected[0]);
    std::shared_ptr<AuthorizationRes> cast_expected2 = std::dynamic_pointer_cast<AuthorizationRes>(expected[1]);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(inconc, "No EIM authorization was initiated before.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_SECC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_SECC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Performance_Timeout - par_CMN_Transmission_Delay);
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return false;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  while (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->mtc->tc_V2G_SECC_Ongoing_Timer->timeout())
      {
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
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
    }
    if (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction)
    {
      Logging::info(LogTbFnc_ENABLE, fmt::format("[TB][{0:s}]: {1}", __FUNCTION__, "sleep 0.1s wait ongoing_WaitingForCustomerInteraction"));
      PAsleep(0.1);
    }
  }
  return this->mtc->getverdict();
}

// PnC
verdict_val TestBehavior_SECC_Authorization::f_SECC_CMN_TB_VTB_Authorization_011()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> sendMsg2 = std::make_shared<AuthorizationReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<AuthorizationRes>();
  std::shared_ptr<V2gTpMessage> expectedMsg2 = std::make_shared<AuthorizationRes>();
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  iso1Part4_EVSEProcessingType v_eVSEprocessing = iso1Part4_EVSEProcessingType::ongoing;
  int v_cnt = 1;
  std::string v_privateKey;
  bool isShutdownOSC = false;

  std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationReq>(sendMsg2)->setSessionId(this->mtc->vc_SessionID);

  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::finished);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg)->mEVSEProcessing_flag = specific;

  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->setEVSEProcessing((EVSEProcessingType)iso1Part4_EVSEProcessingType::ongoing_WaitingForCustomerInteraction);
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mResponseCode_flag = specific;
  std::static_pointer_cast<AuthorizationRes>(expectedMsg2)->mEVSEProcessing_flag = specific;

  std::vector<std::shared_ptr<V2gTpMessage>> expectedMsgList = {expectedMsg, expectedMsg2};

  auto receive_handler = [this](std::vector<std::shared_ptr<V2gTpMessage>> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<AuthorizationRes> cast_expected = std::dynamic_pointer_cast<AuthorizationRes>(expected[0]);
    std::shared_ptr<AuthorizationRes> cast_expected2 = std::dynamic_pointer_cast<AuthorizationRes>(expected[1]);
    std::shared_ptr<AuthorizationRes> cast_received = std::make_shared<AuthorizationRes>();
    char *receive_data;
    auto size = received->getBufferPtr(&receive_data);
    cast_received->setMessage(receive_data, size);
    if (cast_received->deserialize())
    {
      if (cast_expected->getType() == cast_received->getType())
      {
        if ((*cast_expected) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          this->mtc->tc_V2G_EVCC_Ongoing_Timer->stop();
          this->mtc->setverdict(inconc, "No authorization should be triggered by the SUT before.");
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return true;
        }
        else if ((*cast_expected2) == (*cast_received))
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
          if (this->mtc->tc_V2G_SECC_Ongoing_Timer->running() == false)
          {
            this->mtc->tc_V2G_SECC_Ongoing_Timer->start(par_V2G_EVCC_Ongoing_Performance_Timeout - par_CMN_Transmission_Delay);
          }
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_NONE;
          return false;
        }
        else
        {
          // correct message name but content(body) is not match with expected.
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG_CONTENT;
          return false;
        }
      }
      else
      {
        // bot expected receive msg type
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_V2G_MSG;
        this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveMsgName = cast_received->getTypeName();
        return false;
      }
    }
    else
    {
      // deserialize failed -> not EXI message -> possible supportedAppProtocol msg
      this->mtc->setverdict(error, "Deserialize message failed, received message is not V2G Application msg");
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receiveQueueStatus = ReceiveType_UNEXPECTED_MSG;
      return false;
    }
  };

  while (v_eVSEprocessing == iso1Part4_EVSEProcessingType::ongoing)
  {
    if (v_cnt == 1)
    {
      std::string msgname = "authorizationReq";
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setId(msgname);
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setGenChallenge(this->mtc->vc_GenChallenge);
      if (isbound(this->mtc->vc_contractPrivateKey))
      {
        v_privateKey = this->mtc->vc_contractPrivateKey;
      }
      else
      {
        v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_VALID");
      }
      BodyType *myAuthorizationBodyType = &(std::static_pointer_cast<AuthorizationReq>(sendMsg)->getExiData())->V2G_Message.Body;
      /* Signed header for msg*/
      SignatureType aSignature;
      md_CMN_Signature_001(aSignature, md_CMN_SignedInfoType_001(msgname, f_generateDigestFromBodyType(myAuthorizationBodyType)), v_privateKey);
      // write signed header data
      std::static_pointer_cast<AuthorizationReq>(sendMsg)->setSignature(&aSignature);
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    }
    else
    {
      this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg2);
    }
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_AuthorizationReq);
    v_cnt = v_cnt + 1;
    while (true)
    {
      if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsgList, receive_handler))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->isError())
      {
        if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
        {
          v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
          break;
        }
      }
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received AuthorizationRes message, but with invalid data content."))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
      if (this->mtc->tc_V2G_SECC_Ongoing_Timer->timeout())
      {
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
        v_eVSEprocessing = iso1Part4_EVSEProcessingType::finished;
        break;
      }
    }
  }
  return this->mtc->getverdict();
}