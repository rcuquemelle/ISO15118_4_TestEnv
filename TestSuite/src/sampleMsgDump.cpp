#include "runTC.h"
#include <time.h>
#include <regex>
#include "V2gSdpResMessage.h"
#include "V2gSdpMessage.h"
#include "V2gALMsg.h"
#include "asiowrapper/asio.h"

int main(int argc, const char *argv[])
{
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(LOG_INFO);
  Logging::setLogOutput(LOG_OUT_CONSOLE);

  std::shared_ptr<V2gSdpResMessage> resSDP = std::make_shared<V2gSdpResMessage>("fe80::c9ae:71e8:9922:a05a", 9000, 0x01, 0x00);
  std::shared_ptr<V2gSdpMessage> reqSDP = std::make_shared<V2gSdpMessage>(0x00, 0x00);
  reqSDP->serialize();
  reqSDP->deserialize();
  resSDP->serialize();
  resSDP->deserialize();

  std::shared_ptr<WeldingDetectionRes> resMSG = std::make_shared<WeldingDetectionRes>();
  std::vector<uint8_t> ssID = {0, 1, 2, 3, 4, 5, 6, 7};
  resMSG->setSessionId(ssID);
  NotificationType noti;
  noti.FaultCode = iso1faultCodeType_UnknownError;
  std::string faultmsg =  "error faultcode";
  strcpy(noti.FaultMsg.characters,faultmsg.data());
  noti.FaultMsg.charactersLen = faultmsg.size();
	noti.FaultMsg_isUsed = 1;
  resMSG->setNotification(&noti);
  // msg->setSignature(SignatureType* sig);
  resMSG->setResponseCode((responseCodeType)iso1Part4_ResponseCodeType::oK);
  DC_EVSEStatusType status;
  status.NotificationMaxDelay = 10;
	status.EVSENotification = iso1EVSENotificationType_StopCharging;
	status.EVSEIsolationStatus = iso1isolationLevelType_Fault;
	status.EVSEIsolationStatus_isUsed = 1;
	status.EVSEStatusCode = iso1DC_EVSEStatusCodeType_EVSE_Malfunction;
  resMSG->setDCEVSEStatus(&status);
  PhysicalValueType presentVoltage = {.Multiplier = 0, .Unit = iso1unitSymbolType_V, .Value=200};
  resMSG->setSessionId(ssID);
  resMSG->setEVSEPresentVoltage(&presentVoltage);
  resMSG->serialize();
  resMSG->deserialize();

  std::shared_ptr<WeldingDetectionReq> reqMSG = std::make_shared<WeldingDetectionReq>();
  DC_EVStatusType status1;
  status1.EVReady = 1;
	status1.EVErrorCode = iso1DC_EVErrorCodeType_FAILED_EVShiftPosition;
	status1.EVRESSSOC = 50;
  reqMSG->setSessionId(ssID);
  reqMSG->setDCEVStatus(&status1);
  reqMSG->serialize();
  reqMSG->deserialize();

  std::shared_ptr<SupportedAppProtocolRes> resAPP = std::make_shared<SupportedAppProtocolRes>();
  resAPP->setResponseCode((appHandresponseCodeType)1);
  resAPP->setSchemeID(12);
  resAPP->serialize();
  resAPP->deserialize();

  std::shared_ptr<SupportedAppProtocolReq> reqAPP = std::make_shared<SupportedAppProtocolReq>();
  appHandAppProtocolType protocol;
  std::string namespace1 = "urn:iso:15118:2:2013:MsgDef";
  std::string namespace2 = "urn:din:70121:2012:MsgDef";
  strcpy(protocol.ProtocolNamespace.characters, namespace1.data());
  protocol.ProtocolNamespace.charactersLen = namespace1.size();
  protocol.VersionNumberMajor = 1;
  protocol.VersionNumberMinor = 0;
  protocol.SchemaID = 1;
  protocol.Priority = 1;
  reqAPP->setAppProtocol(&protocol);
  strcpy(protocol.ProtocolNamespace.characters, namespace2.data());
  protocol.ProtocolNamespace.charactersLen = namespace1.size();
  protocol.VersionNumberMajor = 2;
  protocol.VersionNumberMinor = 2;
  protocol.SchemaID = 2;
  protocol.Priority = 4;
  reqAPP->setAppProtocol(&protocol);
  reqAPP->serialize();
  reqAPP->deserialize();

  std::shared_ptr<SessionStopReq> reqMSG1 = std::make_shared<SessionStopReq>();
  reqMSG1->setChargingSession((chargingSessionType)1);
  reqMSG1->setSessionId(ssID);
  reqMSG1->serialize();
  reqMSG1->deserialize();

  std::shared_ptr<SessionStopRes> resMSG1 = std::make_shared<SessionStopRes>();
  resMSG1->setSessionId(ssID);
  resMSG1->setResponseCode((responseCodeType)1);
  resMSG1->serialize();
  resMSG1->deserialize();

  std::shared_ptr<SessionSetupReq> reqMSG2 = std::make_shared<SessionSetupReq>();
  std::vector<uint8_t> evccid = {1, 2, 3, 5, 6, 22};
  reqMSG2->setEVCCID(evccid);
  reqMSG2->setSessionId(ssID);
  reqMSG2->serialize();
  reqMSG2->deserialize();

  std::shared_ptr<SessionSetupRes> resMSG2 = std::make_shared<SessionSetupRes>();
  resMSG2->setResponseCode((responseCodeType)2);
  resMSG2->setSessionId(ssID);
  resMSG2->setEVSEID("x22.a;sd");
  resMSG2->setEVSETimeStamp(123145);
  resMSG2->serialize();
  resMSG2->deserialize();

  std::shared_ptr<ServicePaymentSelectionReq> reqMSG3 = std::make_shared<ServicePaymentSelectionReq>();
  reqMSG3->setSessionId(ssID);
  reqMSG3->setSelectedPaymentOption((paymentOptionType)1);
  SelectedServiceListType serList;
  serList.SelectedService.arrayLen=2;
  serList.SelectedService.array[0] = {.ServiceID = 1, .ParameterSetID=2, .ParameterSetID_isUsed=1};
  serList.SelectedService.array[1] = {.ServiceID = 10, .ParameterSetID=32, .ParameterSetID_isUsed=0};
  reqMSG3->setSelectedServiceList(&serList);
  reqMSG3->serialize();
  reqMSG3->deserialize();

  std::shared_ptr<ServicePaymentSelectionRes> resMSG3 = std::make_shared<ServicePaymentSelectionRes>();
  resMSG3->setSessionId(ssID);
  resMSG3->setResponseCode((responseCodeType)3);
  resMSG3->serialize();
  resMSG3->deserialize();

  std::shared_ptr<ServiceDiscoveryReq> reqMSG4 = std::make_shared<ServiceDiscoveryReq>();
  reqMSG4->setSessionId(ssID);
  reqMSG4->setServiceCategory((serviceCategoryType)2);
  reqMSG4->setServiceScope("https://www.testdomain.com");
  reqMSG4->serialize();
  reqMSG4->deserialize();

  std::shared_ptr<ServiceDiscoveryRes> resMSG4 = std::make_shared<ServiceDiscoveryRes>();
  resMSG4->setSessionId(ssID);
  PaymentOptionListType payment;
  payment.PaymentOption.arrayLen = 2;
  payment.PaymentOption.array[0] = (paymentOptionType)0;
  payment.PaymentOption.array[1] = (paymentOptionType)1;
  resMSG4->setPaymentOptionList(&payment);
  ChargeServiceType chargeService;
  chargeService.ServiceID = 1;
  chargeService.ServiceCategory = iso1serviceCategoryType_EVCharging;
  chargeService.FreeService = 1;
  chargeService.ServiceName_isUsed = 1;
  std::string ser_name = "charging service";
  strcpy(chargeService.ServiceName.characters, ser_name.data());
  chargeService.ServiceName.charactersLen = ser_name.size();
  chargeService.ServiceScope_isUsed = 1;
  std::string ser_scope= "https://charging_abc.com";
  strcpy(chargeService.ServiceScope.characters, ser_scope.data());
  chargeService.ServiceScope.charactersLen = ser_scope.size();
  chargeService.SupportedEnergyTransferMode.EnergyTransferMode.arrayLen = 6;
  for (size_t i = 0; i < chargeService.SupportedEnergyTransferMode.EnergyTransferMode.arrayLen; i++)
  {
    chargeService.SupportedEnergyTransferMode.EnergyTransferMode.array[i] = (EnergyTransferModeType)i;
  }
  resMSG4->setChargeServiceType(&chargeService);
  resMSG4->setResponseCode((responseCodeType)4);
  ServiceListType service_list;
  service_list.Service.arrayLen = 1;
  service_list.Service.array[0].ServiceID = 69;
  service_list.Service.array[0].ServiceCategory = iso1serviceCategoryType_ContractCertificate;
  service_list.Service.array[0].FreeService = 0;
  resMSG4->setServiceList(&service_list);
  resMSG4->serialize();
  resMSG4->deserialize();

  std::shared_ptr<ServiceDetailsReq> reqMSG5 = std::make_shared<ServiceDetailsReq>();
  reqMSG5->setSessionId(ssID);
  reqMSG5->setServiceID(99);
  reqMSG5->serialize();
  reqMSG5->deserialize();

  std::shared_ptr<ServiceDetailsRes> resMSG5 = std::make_shared<ServiceDetailsRes>();
  resMSG5->setSessionId(ssID);
  ServiceParameterListType paramList;
  paramList.ParameterSet.arrayLen = 2;
  paramList.ParameterSet.array[0].ParameterSetID = 12;
  paramList.ParameterSet.array[0].Parameter.arrayLen = 2;
  strcpy(paramList.ParameterSet.array[0].Parameter.array[0].Name.characters, "testparam1");
  paramList.ParameterSet.array[0].Parameter.array[0].Name.charactersLen = 10;
  paramList.ParameterSet.array[0].Parameter.array[0].boolValue_isUsed = 1;
  paramList.ParameterSet.array[0].Parameter.array[0].boolValue = 1;
  strcpy(paramList.ParameterSet.array[0].Parameter.array[1].Name.characters, "testparam2");
  paramList.ParameterSet.array[0].Parameter.array[1].Name.charactersLen = 10;
  paramList.ParameterSet.array[0].Parameter.array[1].intValue_isUsed = 1;
  paramList.ParameterSet.array[0].Parameter.array[1].intValue = 69;

  paramList.ParameterSet.array[1].ParameterSetID = 11;
  paramList.ParameterSet.array[1].Parameter.arrayLen = 2;
  strcpy(paramList.ParameterSet.array[1].Parameter.array[0].Name.characters, "testparam3");
  paramList.ParameterSet.array[1].Parameter.array[0].Name.charactersLen = 10;
  paramList.ParameterSet.array[1].Parameter.array[0].physicalValue_isUsed = 1;
  paramList.ParameterSet.array[1].Parameter.array[0].physicalValue.Multiplier=1;
  paramList.ParameterSet.array[1].Parameter.array[0].physicalValue.Value= 20;
  paramList.ParameterSet.array[1].Parameter.array[0].physicalValue.Unit=iso1unitSymbolType_W;
  strcpy(paramList.ParameterSet.array[1].Parameter.array[1].Name.characters, "testparam4");
  paramList.ParameterSet.array[1].Parameter.array[1].Name.charactersLen = 10;
  paramList.ParameterSet.array[1].Parameter.array[1].stringValue_isUsed = 1;
  strcpy(paramList.ParameterSet.array[1].Parameter.array[1].stringValue.characters, "valuestring");
  paramList.ParameterSet.array[1].Parameter.array[1].stringValue.charactersLen = 11;

  resMSG5->setServiceParamterList(&paramList);
  resMSG5->setServiceID(69);
  resMSG5->setResponseCode((responseCodeType)5);
  resMSG5->serialize();
  resMSG5->deserialize();
}