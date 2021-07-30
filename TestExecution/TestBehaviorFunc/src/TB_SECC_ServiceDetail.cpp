#include "TB_SECC_ServiceDetail.h"
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

static void f_checkServiceType(std::shared_ptr<SECC_Tester> &_mtc, ServiceType &v_service, verdict_val &v_vct);
static void f_checkServiceParameterList(std::shared_ptr<SECC_Tester> &_mtc, ServiceParameterListType &v_serviceParameterList, ServiceType &v_service, verdict_val &v_vct);
static bool f_checkServiceCategory(std::shared_ptr<SECC_Tester> &_mtc, const serviceCategoryType &v_serviceCategory, ServiceListType &service_list);

TestBehavior_SECC_ServiceDetail::TestBehavior_SECC_ServiceDetail(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_ServiceDetail::~TestBehavior_SECC_ServiceDetail()
{
}

verdict_val TestBehavior_SECC_ServiceDetail::f_SECC_CMN_TB_VTB_ServiceDetail_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  int counter = 0;
  bool v_result = true;
  ServiceType v_service;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDetailsReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDetailsRes>();
  std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mServiceID_flag = specific;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->pServiceParameterList_flag = omit;

  auto receive_handler = [this, &v_service, &v_vct, &counter](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServiceDetailsRes> cast_expected = std::dynamic_pointer_cast<ServiceDetailsRes>(expected);
    std::shared_ptr<ServiceDetailsRes> cast_received = std::make_shared<ServiceDetailsRes>();
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
          ServiceParameterListType *v_serviceParameterList = cast_received->getServiceParamterList();
          if (v_serviceParameterList != nullptr)
          {
            f_checkServiceParameterList(this->mtc, *v_serviceParameterList, v_service, v_vct);
          }
          else
          {
            this->mtc->setverdict(fail, "ServiceDetailRes message does not return ServiceParamterList or ServiceParamterList_isUsed = false");
          }
          if (this->mtc->getverdict() == pass)
          {
            this->mtc->setverdict(pass, "ServiceDetailRes message was correct.");
          }
          counter = counter + 1;
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
        // not expected receive msg type
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

  // check if vc_serviceList is available
  if (ispresent(this->mtc->vc_serviceList))
  {
    if (PIXIT_SECC_CMN_InternetAccess == DataStructure_PIXIT_15118_2::iso1Part4_InternetAccess::internetAccess)
    {
      // check if iso1serviceCategoryType_Internet is available in list of supported service
      v_result = f_checkServiceCategory(this->mtc, (serviceCategoryType)iso1Part4_ServiceCategoryType::internet, this->mtc->vc_serviceList);
    }
    if (v_result)
    {
      while (counter < this->mtc->vc_serviceList.Service.arrayLen)
      {
        memcpy(&v_service, &this->mtc->vc_serviceList.Service.array[counter], sizeof(ServiceType));
        f_checkServiceType(this->mtc, v_service, v_vct);
        std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setServiceID(v_service.ServiceID);
        std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->setServiceID(v_service.ServiceID);
        if (this->mtc->getverdict() == pass)
        {
          this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ServiceDetailReq);
          this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
          while (true)
          {
            if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(expectedMsg, receive_handler))
            {
              break;
            }
            if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
            {
              counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
              break;
            }
            if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
            {
              counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
              break;
            }
            if (this->cmn->isError())
            {
              if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
              {
                counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
                break;
              }
            }
            if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received ServiceDetailRes message, but with invalid data content."))
            {
              counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
              break;
            }
            if (this->cmn->a_SECC_Timeout(v_vct))
            {
              counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
              break;
            }
          }
        }
        else
        {
          counter = this->mtc->vc_serviceList.Service.arrayLen + 1;
        }
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "A serviceList is not available.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ServiceDetail::f_SECC_CMN_TB_VTB_ServiceDetail_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
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
        // not expected receive msg type
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
  if (ispresent(this->mtc->vc_serviceList))
  {
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ServiceDetailReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ServiceDetailRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "A serviceList is not available.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ServiceDetail::f_SECC_CMN_TB_VTB_ServiceDetail_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDetailsReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDetailsRes>();
  auto randomSessionID = f_rnd_SessionID(1, 429496);
  std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setSessionId(randomSessionID);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_UnknownSession);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mServiceID_flag = omit;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->pServiceParameterList_flag = omit;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServiceDetailsRes> cast_expected = std::dynamic_pointer_cast<ServiceDetailsRes>(expected);
    std::shared_ptr<ServiceDetailsRes> cast_received = std::make_shared<ServiceDetailsRes>();
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
          this->mtc->setverdict(pass, "ServiceDetailRes with responseCode 'fAILED_UnknownSession' is successful.");
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
        // not expected receive msg type
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
  if (ispresent(this->mtc->vc_serviceList))
  {
    std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setServiceID(this->mtc->vc_serviceList.Service.array[0].ServiceID);
    this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(sendMsg);
    this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ServiceDetailReq);
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
      if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ServiceDetailRes message, but with invalid data content."))
      {
        break;
      }
      if (this->cmn->a_SECC_Timeout(fail))
      {
        break;
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "A serviceList is not available.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ServiceDetail::f_SECC_CMN_TB_VTB_ServiceDetail_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  int v_invalidServiceID = 65535;
  bool isInvalid;
  bool isShutdownOSC = false;
  std::shared_ptr<V2gTpMessage> sendMsg = std::make_shared<ServiceDetailsReq>();
  std::shared_ptr<V2gTpMessage> expectedMsg = std::make_shared<ServiceDetailsRes>();
  std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDetailsReq>(sendMsg)->setServiceID(v_invalidServiceID);
  std::static_pointer_cast<ServiceDetailsReq>(expectedMsg)->setSessionId(this->mtc->vc_SessionID);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::fAILED_ServiceIDInvalid);
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mResponseCode_flag = specific;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->mServiceID_flag = omit;
  std::static_pointer_cast<ServiceDetailsRes>(expectedMsg)->pServiceParameterList_flag = omit;

  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);

  auto receive_handler = [this](std::shared_ptr<V2gTpMessage> &expected, std::shared_ptr<V2gTpMessage> &received) -> bool
  {
    std::shared_ptr<ServiceDetailsRes> cast_expected = std::dynamic_pointer_cast<ServiceDetailsRes>(expected);
    std::shared_ptr<ServiceDetailsRes> cast_received = std::make_shared<ServiceDetailsRes>();
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
          this->mtc->setverdict(pass, "ServiceDetailRes with responseCode 'fAILED_ServiceIDInvalid' is successful.");
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
        // not expected receive msg type
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
  if (ispresent(this->mtc->vc_serviceList))
  {
    isInvalid = f_checkInvalidServiceID(this->mtc, v_invalidServiceID, this->mtc->vc_serviceList);
    if (isInvalid)
    {
      this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_ServiceDetailReq);
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
        if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received ServiceDetailRes message, but with invalid data content."))
        {
          break;
        }
        if (this->cmn->a_SECC_Timeout(fail))
        {
          break;
        }
      }
    }
  }
  else
  {
    this->mtc->setverdict(inconc, "A serviceList is not available.");
  }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_ServiceDetail::f_SECC_CMN_TB_VTB_ServiceDetail_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  bool isShutdownOSC = false;
  std::shared_ptr<BaseOperation> sendCmd = std::make_shared<BaseOperation>(OpType_TCP);
  md_CMN_CMN_tcpTlsStatusReq_001(sendCmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE::e_getPortStatus);
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

static void f_checkServiceType(std::shared_ptr<SECC_Tester> &_mtc, ServiceType &v_service, verdict_val &v_vct)
{
  if (v_service.ServiceID == 1)
  {
    _mtc->setverdict(v_vct, "Service Id '1' is reserved for the service category 'EVcharging'.");
  }
  else if (v_service.ServiceID == 2)
  {
    // ServiceID 2 for Certificate update/installation
    if (v_service.ServiceCategory != (serviceCategoryType)iso1Part4_ServiceCategoryType::contractCertificate)
    {
      _mtc->setverdict(v_vct, "Invalid service category was used.");
    }
  }
  else if (v_service.ServiceID == 3)
  {
    // ServiceID 3 for Internet Access
    if (v_service.ServiceCategory != (serviceCategoryType)iso1Part4_ServiceCategoryType::internet)
    {
      _mtc->setverdict(v_vct, "Invalid service category was used.");
    }
  }
  else if (v_service.ServiceID == 4)
  {
    // ServiceID 4 for other value added service
    if (v_service.ServiceCategory != (serviceCategoryType)iso1Part4_ServiceCategoryType::otherCustom)
    {
      _mtc->setverdict(v_vct, "Invalid service category was used.");
    }
  }
  else
  {
    Logging::info(LogTbFnc_ENABLE, "Unknown service type was used.");
    Logging::info(LogTbFnc_ENABLE, fmt::format("Service ID: {}", (v_service.ServiceID)));
    Logging::info(LogTbFnc_ENABLE, fmt::format("Service Name: {}", f_toString(v_service.ServiceName.characters)));
    Logging::info(LogTbFnc_ENABLE, fmt::format("Service Category: {}", v_service.ServiceCategory));
  }
}

static void f_checkServiceParameterList(std::shared_ptr<SECC_Tester> &_mtc, ServiceParameterListType &v_serviceParameterList, ServiceType &v_service, verdict_val &v_vct)
{
  if (v_service.ServiceID == 2)
  {
    // Certificate update/installation
    for (int i = 0; i < v_serviceParameterList.ParameterSet.arrayLen; i = i + 1)
    {
      if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 1)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Service")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Service) was used for the parameter serviceID equals to 2 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "Installation")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 2 and 'parameterSetID' equals to 1.");
        }
      }
      else if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 2)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Service")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Service) was used for the parameter serviceID equals to 2 and 'parameterSetID' equals to 2.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "Update")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 2 and 'parameterSetID' equals to 2.");
        }
      }
    }
  }
  if (v_service.ServiceID == 3)
  {
    // Internet Access
    for (int i = 0; i < v_serviceParameterList.ParameterSet.arrayLen; i = i + 1)
    {
      if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 1)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Protocol")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Protocol) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "ftp")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].Name.characters) != "Port")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Port) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].intValue != 20)
        {
          _mtc->setverdict(v_vct, "Invalid intValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
        }
      }
      if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 2)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Protocol")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Protocol) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "ftp")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].Name.characters) != "Port")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Port) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].intValue != 21)
        {
          _mtc->setverdict(v_vct, "Invalid intValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
        }
      }
      if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 3)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Protocol")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Protocol) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "http")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].Name.characters) != "Port")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Port) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].intValue != 80)
        {
          _mtc->setverdict(v_vct, "Invalid intValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
        }
      }
      if (v_serviceParameterList.ParameterSet.array[i].ParameterSetID == 4)
      {
        if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].Name.characters) != "Protocol")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Protocol) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[0].stringValue.characters) != "https")
        {
          _mtc->setverdict(v_vct, "Invalid stringValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (f_toString(v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].Name.characters) != "Port")
        {
          _mtc->setverdict(v_vct, "Invalid ParameterName (Port) was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
          break;
        }
        else if (v_serviceParameterList.ParameterSet.array[i].Parameter.array[1].intValue != 443)
        {
          _mtc->setverdict(v_vct, "Invalid intValue was used for the parameter serviceID equals to 3 and 'parameterSetID' equals to 1.");
        }
      }
    }
  }
}

static bool f_checkServiceCategory(std::shared_ptr<SECC_Tester> &_mtc, const serviceCategoryType &v_serviceCategory, ServiceListType &service_list)
{
  for (int i = 0; i < service_list.Service.arrayLen; i = i + 1)
  {
    if (v_serviceCategory == service_list.Service.array[i].ServiceCategory)
    {
      return true;
    }
  }
  _mtc->setverdict(inconc, "Selected serviceCategory could not be found within serviceList.");
  return false;
}