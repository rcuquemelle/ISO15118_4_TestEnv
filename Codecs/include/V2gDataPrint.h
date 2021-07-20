#ifndef __V2GDATAPRINT_H__
#define __V2GDATAPRINT_H__

#include "TestSystemLogging.h"
#include "V2gCodecs.h"

class EnumMap
{
private:
  std::vector<std::string> table;
  std::string error_string;
public:
  EnumMap(const std::vector<std::string> &input_table)
    : table(input_table)
  {
    error_string = "OUT_OF_RANGE";
  }
  ~EnumMap(){}
  const std::string& operator[](ssize_t idx) const
  {
    if ((idx < 0) || ((size_t)idx > table.size()))
    {
      return error_string;
    }
    else
    {
      return table[idx];
    }
  }
};

extern const EnumMap EVSEPROCESSING;
extern const EnumMap RESPONSE_CODE;
extern const EnumMap PAYMENT;
extern const EnumMap SERVICE_CAT;
extern const EnumMap ENERGY_TRANSFER_MODE;
extern const EnumMap UNIT_TYPE;
extern const EnumMap CHARGE_PROGRESS;

extern std::string getStrPhysicalValue(PhysicalValueType *v);
extern float getPhysicalValue(PhysicalValueType *v);
extern std::string outHexString(const uint8_t *arr, size_t len);
extern std::string outHexString(const std::vector<uint8_t> &val);
extern std::string outHexString2(const std::string &val);
extern std::string getStrAppProtocol(appHandAppProtocolType *appProtocol, const std::string &indent);
extern std::string getStrChargeService(ChargeServiceType *service, const std::string &indent);
extern std::string getStrService(ServiceType *service, const std::string &indent);
extern std::string getStrParam(ParameterSetType *param, const std::string &indent);

extern std::string getStrEVStatus(EVStatusType *status, const std::string &indent);
extern std::string getStrDCEVStatus(DC_EVStatusType *status, const std::string &indent);

extern std::string getStrEVSEStatus(EVSEStatusType *status, const std::string &indent);
extern std::string getStrACEVSEStatus(AC_EVSEStatusType *status, const std::string &indent);
extern std::string getStrDCEVSEStatus(DC_EVSEStatusType *status, const std::string &indent);

extern std::string getStrChargingProfile(ChargingProfileType *profile, const std::string &indent);

extern std::string getStrEVPowerDeliveryParameter(EVPowerDeliveryParameterType *param, const std::string &indent);
extern std::string getStrDCEVPowerDeliveryParameter(DC_EVPowerDeliveryParameterType *param, const std::string &indent);

extern std::string getStrContractCertChain(CertificateChainType *chain, const std::string &indent);
extern std::string getStrMeterInfo(MeterInfoType *meter, const std::string &indent);
extern std::string getStrSAScheduleList(SAScheduleListType *schedule, const std::string &indent);

extern std::string getStrEVSEChargeParameter(EVSEChargeParameterType *charge_param, const std::string& indent);
extern std::string getStrACEVSEChargeParameter(AC_EVSEChargeParameterType *charge_param, const std::string& indent);
extern std::string getStrDCEVSEChargeParameter(DC_EVSEChargeParameterType *charge_param, const std::string& indent);

extern std::string getStrEVChargeParameter(EVChargeParameterType *charge_param, const std::string& indent);
extern std::string getStrACEVChargeParameter(AC_EVChargeParameterType *charge_param, const std::string& indent);
extern std::string getStrDCEVChargeParameter(DC_EVChargeParameterType *charge_param, const std::string& indent);

#endif // __V2GDATAPRINT_H__