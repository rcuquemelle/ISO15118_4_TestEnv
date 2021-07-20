#include "TB_SECC_PaymentServiceSelection.h"
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

TestBehavior_SECC_PaymentServiceSelection::TestBehavior_SECC_PaymentServiceSelection(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_PaymentServiceSelection::~TestBehavior_SECC_PaymentServiceSelection()
{
}

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  paymentOptionType selPaymentOption;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServicePaymentSelectionReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServicePaymentSelectionRes>();

  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
  {
    selPaymentOption = (paymentOptionType)iso1Part4_PaymentOptionType::contract;
  }
  else
  {
    selPaymentOption = (paymentOptionType)iso1Part4_PaymentOptionType::externalPayment;
  }
  std::shared_ptr<SelectedServiceListType> servicelist = std::shared_ptr<SelectedServiceListType>(new SelectedServiceListType);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedPaymentOption(selPaymentOption);
  // service id = 1 equal charging
  init_iso1SelectedServiceListType(servicelist.get());
  servicelist->SelectedService.array[0].ServiceID = 1;
  servicelist->SelectedService.arrayLen = 1;
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedServiceList(servicelist.get());
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->mResponseCode_flag = specific;

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServicePaymentSelectionRes> cast_expected = std::dynamic_pointer_cast<ServicePaymentSelectionRes>(expected);
    std::shared_ptr<ServicePaymentSelectionRes> cast_received = std::make_shared<ServicePaymentSelectionRes>();
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
          this->mtc->setverdict(pass, "PaymentServiceSelectionRes message was correct.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
    if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
    {
      break;
    }
    if (this->cmn->isError())
    {
      if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
      {
        break;
      }
    }
    if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received PaymentServiceSelectionRes message, but with invalid data content."))
    {
      break;
    }
    if (this->cmn->a_SECC_Timeout(v_vct))
    {
      break;
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  std::vector<uint8_t> sessionID = this->mtc->vc_SessionID;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDiscoveryReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDiscoveryRes>();
  std::static_pointer_cast<ServiceDiscoveryReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_SequenceError);
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pChargeService_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pServiceList_flag = omit;
  std::static_pointer_cast<ServiceDiscoveryRes>(expectedMsg)->pPaymentOptionList_flag = omit;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

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
  this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentServiceSelectionRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  paymentOptionType selPaymentOption;
  std::vector<uint8_t> sessionID = this->mtc->vc_SessionID;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServicePaymentSelectionReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServicePaymentSelectionRes>();

  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
  {
    selPaymentOption = iso1paymentOptionType_Contract;
  }
  else
  {
    selPaymentOption = iso1paymentOptionType_ExternalPayment;
  }
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedPaymentOption(selPaymentOption);
  std::shared_ptr<SelectedServiceListType> servicelist = std::shared_ptr<SelectedServiceListType>(new SelectedServiceListType);
  servicelist->SelectedService.array[0].ServiceID = 1;
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedServiceList(servicelist.get());
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->mResponseCode_flag = specific;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServicePaymentSelectionRes> cast_expected = std::dynamic_pointer_cast<ServicePaymentSelectionRes>(expected);
    std::shared_ptr<ServicePaymentSelectionRes> cast_received = std::make_shared<ServicePaymentSelectionRes>();
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
          this->mtc->setverdict(pass, "PaymentServiceSelectionRes with responseCode 'fAILED_UnknownSession' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentServiceSelectionRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  paymentOptionType selPaymentOption;
  uint16_t v_invalidServiceID = 65535;
  bool isInvalid;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServicePaymentSelectionReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServicePaymentSelectionRes>();

  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
  {
    selPaymentOption = iso1paymentOptionType_Contract;
  }
  else
  {
    selPaymentOption = iso1paymentOptionType_ExternalPayment;
  }
  isInvalid = f_checkInvalidServiceID(this->mtc, v_invalidServiceID, this->mtc->vc_serviceList);

  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedPaymentOption(selPaymentOption);
  std::shared_ptr<SelectedServiceListType> servicelist = std::shared_ptr<SelectedServiceListType>(new SelectedServiceListType);
  servicelist->SelectedService.array[0].ServiceID = v_invalidServiceID;
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedServiceList(servicelist.get());
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_ServiceSelectionInvalid);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->mResponseCode_flag = specific;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServicePaymentSelectionRes> cast_expected = std::dynamic_pointer_cast<ServicePaymentSelectionRes>(expected);
    std::shared_ptr<ServicePaymentSelectionRes> cast_received = std::make_shared<ServicePaymentSelectionRes>();
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
          this->mtc->setverdict(pass, "PaymentServiceSelectionRes with responseCode 'fAILED_ServiceSelectionInvalid' is successful.");
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
  if (isInvalid)
  {
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentServiceSelectionRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  paymentOptionType selPaymentOption;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServicePaymentSelectionReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServicePaymentSelectionRes>();
  if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
  {
    selPaymentOption = iso1paymentOptionType_Contract;
  }
  else
  {
    selPaymentOption = iso1paymentOptionType_ExternalPayment;
  }
  this->mtc->vc_ServiceId = 2;

  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedPaymentOption(selPaymentOption);
  std::shared_ptr<SelectedServiceListType> servicelist = std::shared_ptr<SelectedServiceListType>(new SelectedServiceListType);
  servicelist->SelectedService.array[0].ServiceID = this->mtc->vc_ServiceId;
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedServiceList(servicelist.get());
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_NoChargeServiceSelected);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->mResponseCode_flag = specific;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServicePaymentSelectionRes> cast_expected = std::dynamic_pointer_cast<ServicePaymentSelectionRes>(expected);
    std::shared_ptr<ServicePaymentSelectionRes> cast_received = std::make_shared<ServicePaymentSelectionRes>();
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
          this->mtc->setverdict(pass, "PaymentServiceSelectionRes with responseCode 'fAILED_NoChargeServiceSelected' is successful.");
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
  this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
    if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentServiceSelectionRes message, but with invalid data content."))
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

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
  // Wait until sequence timeout in SUT should expire
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
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

verdict_val TestBehavior_SECC_PaymentServiceSelection::f_SECC_CMN_TB_VTB_PaymentServiceSelection_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  paymentOptionType selPaymentOption;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServicePaymentSelectionReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServicePaymentSelectionRes>();
  if (this->mtc->vc_paymentOptionList.PaymentOption.arrayLen == 1)
  {
    if (PICS_CMN_CMN_IdentificationMode == DataStructure_PICS_15118::iso1Part4_IdentificationMode::pnC)
    {
      if (this->mtc->vc_paymentOptionList.PaymentOption.array[0] != iso1paymentOptionType_Contract)
      {
        this->mtc->setverdict(inconc, "Invalid payment option was selected.");
      }
      else
      {
        selPaymentOption = iso1paymentOptionType_ExternalPayment;
      }
    }
    else
    {
      if (this->mtc->vc_paymentOptionList.PaymentOption.array[0] != iso1paymentOptionType_ExternalPayment)
      {
        this->mtc->setverdict(inconc, "Invalid payment option was selected.");
      }
      else
      {
        selPaymentOption = iso1paymentOptionType_Contract;
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "The SUT has provided more than one payment option.");
  }

  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedPaymentOption(selPaymentOption);
  std::shared_ptr<SelectedServiceListType> servicelist = std::shared_ptr<SelectedServiceListType>(new SelectedServiceListType);
  servicelist->SelectedService.array[0].ServiceID = 1;
  std::static_pointer_cast<ServicePaymentSelectionReq>(sendMsg)->setSelectedServiceList(servicelist.get());
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_PaymentSelectionInvalid);
  std::static_pointer_cast<ServicePaymentSelectionRes>(expectedMsg)->mResponseCode_flag = specific;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServicePaymentSelectionRes> cast_expected = std::dynamic_pointer_cast<ServicePaymentSelectionRes>(expected);
    std::shared_ptr<ServicePaymentSelectionRes> cast_received = std::make_shared<ServicePaymentSelectionRes>();
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
          this->mtc->setverdict(pass, "PaymentServiceSelectionRes with responseCode 'fAILED_PaymentSelectionInvalid' is successful.");
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
  if (this->mtc->getverdict() == pass)
  {
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentServiceSelectionReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentServiceSelectionRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  return this->mtc->getverdict();
}