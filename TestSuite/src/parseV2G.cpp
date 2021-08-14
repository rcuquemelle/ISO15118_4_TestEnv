#include "runTC.h"
#include <time.h>
#include <regex>
#include "V2gSdpResMessage.h"
#include "V2gSdpMessage.h"
#include "V2gALMsg.h"

typedef std::map<std::string, std::shared_ptr<V2gExiMessage>> MapMsgType;
MapMsgType mapMsg;
template <typename T>
std::shared_ptr<V2gExiMessage> createT()
{
  return std::dynamic_pointer_cast<V2gExiMessage>(std::make_shared<T>());
}

int hexstring2arr(const char* ihexstring, int size, uint8_t* oarr)
{
  int i = 0, j = 0, pos = 0;
  uint8_t val = 0;
  while (i < size)
  {
    if (ihexstring[i] == ' ') {
      ++i;
      continue;
    }
    if (ihexstring[i] == '0' && ((ihexstring[i+1] == 'X') || (ihexstring[i+1] == 'x'))) {
      i += 2;
      continue;
    }
    if (('A' <= ihexstring[i]) && (ihexstring[i] <= 'F')) {
      val = ihexstring[i]-'A' + 10;
    }
    else if (('a' <= ihexstring[i]) && (ihexstring[i] <= 'f')) {
      val = ihexstring[i]-'a' + 10;
    }
    else if (('0' <= ihexstring[i]) && (ihexstring[i] <= '9')) {
      val = ihexstring[i]-'0';
    }
    else {
      Logging::error(0, fmt::format("Invalid hextring character {}", ihexstring[i]));
      i++;
      continue;
    }
    if (pos == 1){
      oarr[j] = oarr[j]*16 + val;
      fmt::print(fmt::format("{:02X} ", oarr[j]));
      pos = 0;
      j++;
    }
    else
    {
      oarr[j] = val;
      pos++;
    }
    i++;
  }
  std::cout << std::endl;
  return j;
}

int main(int argc, const char *argv[])
{
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(LOG_DEBUG);
  Logging::setLogOutput(LOG_OUT_CONSOLE);
  std::string msg_type = argv[1];
  std::string str_val = argv[2];
  uint8_t data_arr[255] = {0};

  if (msg_type == "AuthorizationReq")
    mapMsg["AuthorizationReq"] = createT<AuthorizationReq>();
  if (msg_type == "AuthorizationRes")
    mapMsg["AuthorizationRes"] = createT<AuthorizationRes>();
  if (msg_type == "CableCheckReq")
    mapMsg["CableCheckReq"] = createT<CableCheckReq>();
  if (msg_type == "CableCheckRes")
    mapMsg["CableCheckRes"] = createT<CableCheckRes>();
  if (msg_type == "ChargeParameterDiscoveryReq")
    mapMsg["ChargeParameterDiscoveryReq"] = createT<ChargeParameterDiscoveryReq>();
  if (msg_type == "ChargeParameterDiscoveryRes")
    mapMsg["ChargeParameterDiscoveryRes"] = createT<ChargeParameterDiscoveryRes>();
  if (msg_type == "ChargingStatusReq")
    mapMsg["ChargingStatusReq"] = createT<ChargingStatusReq>();
  if (msg_type == "ChargingStatusRes")
    mapMsg["ChargingStatusRes"] = createT<ChargingStatusRes>();
  if (msg_type == "CurrentDemandReq")
    mapMsg["CurrentDemandReq"] = createT<CurrentDemandReq>();
  if (msg_type == "CurrentDemandRes")
    mapMsg["CurrentDemandRes"] = createT<CurrentDemandRes>();
  if (msg_type == "MeterReceiptReq")
    mapMsg["MeterReceiptReq"] = createT<MeterReceiptReq>();
  if (msg_type == "MeterReceiptRes")
    mapMsg["MeterReceiptRes"] = createT<MeterReceiptRes>();
  if (msg_type == "PaymentDetailsReq")
    mapMsg["PaymentDetailsReq"] = createT<PaymentDetailsReq>();
  if (msg_type == "PaymentDetailsRes")
    mapMsg["PaymentDetailsRes"] = createT<PaymentDetailsRes>();
  if (msg_type == "PowerDeliveryReq")
    mapMsg["PowerDeliveryReq"] = createT<PowerDeliveryReq>();
  if (msg_type == "PowerDeliveryRes")
    mapMsg["PowerDeliveryRes"] = createT<PowerDeliveryRes>();
  if (msg_type == "PreChargeReq")
    mapMsg["PreChargeReq"] = createT<PreChargeReq>();
  if (msg_type == "PreChargeRes")
    mapMsg["PreChargeRes"] = createT<PreChargeRes>();
  if (msg_type == "ServiceDetailsReq")
    mapMsg["ServiceDetailsReq"] = createT<ServiceDetailsReq>();
  if (msg_type == "ServiceDetailsRes")
    mapMsg["ServiceDetailsRes"] = createT<ServiceDetailsRes>();
  if (msg_type == "ServiceDiscoveryReq")
    mapMsg["ServiceDiscoveryReq"] = createT<ServiceDiscoveryReq>();
  if (msg_type == "ServiceDiscoveryRes")
    mapMsg["ServiceDiscoveryRes"] = createT<ServiceDiscoveryRes>();
  if (msg_type == "ServicePaymentSelectionReq")
    mapMsg["ServicePaymentSelectionReq"] = createT<ServicePaymentSelectionReq>();
  if (msg_type == "ServicePaymentSelectionRes")
    mapMsg["ServicePaymentSelectionRes"] = createT<ServicePaymentSelectionRes>();
  if (msg_type == "SessionSetupReq")
    mapMsg["SessionSetupReq"] = createT<SessionSetupReq>();
  if (msg_type == "SessionSetupRes")
      mapMsg["SessionSetupRes"] = createT<SessionSetupRes>();
  if (msg_type == "SessionStopReq")
    mapMsg["SessionStopReq"] = createT<SessionStopReq>();
  if (msg_type == "SessionStopRes")
      mapMsg["SessionStopRes"] = createT<SessionStopRes>();
  if (msg_type == "WeldingDetectionReq")
    mapMsg["WeldingDetectionReq"] = createT<WeldingDetectionReq>();
  if (msg_type == "WeldingDetectionRes")
      mapMsg["WeldingDetectionRes"] = createT<WeldingDetectionRes>();

  int data_len = hexstring2arr(str_val.c_str(), str_val.length(), data_arr);

  if (msg_type == "V2gSdpMessage") {
    std::shared_ptr<V2gSdpMessage> sdp = std::make_shared<V2gSdpMessage>();
    sdp->setMessage((const char *)data_arr, data_len);
    sdp->deserialize();
    sdp->serialize();
    exit(0);
  }
  if (msg_type == "V2gSdpResMessage") {
    std::shared_ptr<V2gSdpResMessage> sdp = std::make_shared<V2gSdpResMessage>();
    sdp->setMessage((const char *)data_arr, data_len);
    sdp->deserialize();
    sdp->serialize();
    exit(0);
  }
  if (msg_type == "SupportedAppProtocolReq") {
    std::shared_ptr<SupportedAppProtocolReq> apphandshake = std::make_shared<SupportedAppProtocolReq>();
    apphandshake->setMessage((const char *)data_arr, data_len);
    apphandshake->deserialize();
    apphandshake->serialize();
    exit(0);
  }
  if (msg_type == "SupportedAppProtocolRes") {
    std::shared_ptr<SupportedAppProtocolRes> apphandshake = std::make_shared<SupportedAppProtocolRes>();
    apphandshake->setMessage((const char *)data_arr, data_len);
    apphandshake->deserialize();
    apphandshake->serialize();
    exit(0);
  }


  if (mapMsg.size() != 0) {
    mapMsg[msg_type]->setMessage((const char *)data_arr, data_len);
    mapMsg[msg_type]->deserialize();
    mapMsg[msg_type]->serialize();
    exit(0);
  }
  else {
    Logging::error(0 , "input msg name is incorrect");
  }
}