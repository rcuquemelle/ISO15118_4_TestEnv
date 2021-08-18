#include "V2gDataPrint.h"

const EnumMap EVSEPROCESSING({"Finished", "Ongoing", "Ongoing_WaitingForCustomerInteraction"});
const EnumMap EVSENOTIFICATION({"None", "StopCharging", "ReNegotiation"});
const EnumMap EVSEISOLATIONSTATUS({"Invalid", "Valid", "Warning", "Fault", "No_IMD"});
const EnumMap EVSESTATUSCODE({"EVSE_NotReady",
                              "EVSE_Ready",
                              "EVSE_Shutdown",
                              "EVSE_UtilityInterruptEvent",
                              "EVSE_IsolationMonitoringActive",
                              "EVSE_EmergencyShutdown",
                              "EVSE_Malfunction",
                              "Reserved_8",
                              "Reserved_9",
                              "Reserved_A",
                              "Reserved_B",
                              "Reserved_C"});
const EnumMap EVSTATUSCODE({"NO_ERROR",
                            "FAILED_RESSTemperatureInhibit",
                            "FAILED_EVShiftPosition",
                            "FAILED_ChargerConnectorLockFault",
                            "FAILED_EVRESSMalfunction",
                            "FAILED_ChargingCurrentdifferential",
                            "FAILED_ChargingVoltageOutOfRange",
                            "Reserved_A",
                            "Reserved_B",
                            "Reserved_C",
                            "FAILED_ChargingSystemIncompatibility",
                            "NoData"});
const EnumMap RESPONSE_CODE({"OK",
                             "OK_NewSessionEstablished",
                             "OK_OldSessionJoined",
                             "OK_CertificateExpiresSoon",
                             "FAILED",
                             "FAILED_SequenceError",
                             "FAILED_ServiceIDInvalid",
                             "FAILED_UnknownSession",
                             "FAILED_ServiceSelectionInvalid",
                             "FAILED_PaymentSelectionInvalid",
                             "FAILED_CertificateExpired",
                             "FAILED_SignatureError",
                             "FAILED_NoCertificateAvailable",
                             "FAILED_CertChainError",
                             "FAILED_ChallengeInvalid",
                             "FAILED_ContractCanceled",
                             "FAILED_WrongChargeParameter",
                             "FAILED_PowerDeliveryNotApplied",
                             "FAILED_TariffSelectionInvalid",
                             "FAILED_ChargingProfileInvalid",
                             "FAILED_MeteringSignatureNotValid",
                             "FAILED_NoChargeServiceSelected",
                             "FAILED_WrongEnergyTransferMode",
                             "FAILED_ContactorError",
                             "FAILED_CertificateNotAllowedAtThisEVSE",
                             "FAILED_CertificateRevoked"});
const EnumMap PAYMENT({"Contract", "ExternalPayment"});
const EnumMap SERVICE_CAT({"EVCharging", "Internet", "ContractCertificate", "OtherCustom"});
const EnumMap ENERGY_TRANSFER_MODE({"AC_single_phase_core", "AC_three_phase_core", "DC_core", "DC_extended", "DC_combo_core", "DC_unique"});
const EnumMap UNIT_TYPE({"h", "m", "s", "A", "V", "W", "Wh"});
const EnumMap CHARGE_PROGRESS({"Start", "Stop", "Renegotiate"});
const EnumMap COST_TYPE({"relativePricePercentage", "RenewableGenerationPercentage", "CarbonDioxideEmission"});

#if DEPLOY_ISO1_CODEC == SUPPORT_YES
#define SupportedEnergyTransferModeType_EnergyTransferMode_ARRAY_SIZE 7
#define ParameterSetType_Parameter_ARRAY_SIZE 17
#define ChargingProfileType_ProfileEntry_ARRAY_SIZE 25
#define PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE 6
#define SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE 4
#define ConsumptionCostType_Cost_ARRAY_SIZE 4
#define SalesTariffType_SalesTariffEntry_ARRAY_SIZE 6
#define SAScheduleListType_SAScheduleTuple_ARRAY_SIZE 4
#endif

static float Pow(int v_multiplier);

std::string outHexString(const std::vector<uint8_t> &val)
{
  std::string temp;
  for (auto c = val.begin(); c != val.end(); c++)
  {
    temp.append(fmt::format("{:02X}", (uint8_t)(*c)));
  }
  return temp;
}
std::string outHexString(const uint8_t *arr, size_t len)
{
  std::string temp;
  for (size_t i = 0; i < len; i++)
  {
    temp.append(fmt::format("{:02X}", arr[i]));
  }
  return temp;
}
std::string outHexString2(const std::string &val)
{
  std::string temp;
  for (auto c = val.begin(); c != val.end(); c++)
  {
    temp.append(fmt::format("{:02X}", (uint8_t)(*c)));
  }
  return temp;
}
float getPhysicalValue(PhysicalValueType *v)
{
  float ret;
  if (v->Multiplier < 0)
  {
    ret = ((float)(v->Value) * (1.0 / (Pow(v->Multiplier * -1))));
  }
  else if (v->Multiplier > 0)
  {
    ret = ((float)(v->Value) * (Pow(v->Multiplier)));
  }
  else
  {
    ret = (float)(v->Value);
  }
  return ret;
}
std::string getStrPhysicalValue(PhysicalValueType *v)
{
  float ret;
  if (v->Multiplier < 0)
  {
    ret = ((float)(v->Value) * (1.0 / (Pow(v->Multiplier * -1))));
  }
  else if (v->Multiplier > 0)
  {
    ret = ((float)(v->Value) * (Pow(v->Multiplier)));
  }
  else
  {
    ret = (float)(v->Value);
  }
  return fmt::format("{0}{1}", ret, UNIT_TYPE[v->Unit]);
}

std::string getStrAppProtocol(appHandAppProtocolType *appProtocol, const std::string &indent)
{
  std::string temp;
  std::string proNameSpace = std::string(appProtocol->ProtocolNamespace.characters);
  temp = fmt::format("{0}>>ProtocolNamespace={1}\n"
                     "{0}VersionNumberMajor={2}\n"
                     "{0}VersionNumberMinor={3}\n"
                     "{0}SchemaID={4}\n"
                     "{0}Priority={5}",
                     indent, proNameSpace, appProtocol->VersionNumberMajor,
                     appProtocol->VersionNumberMinor, appProtocol->SchemaID,
                     appProtocol->Priority);
  return temp;
}

std::string getStrDCEVStatus(DC_EVStatusType *status, const std::string &indent)
{
  std::string temp;

  temp = fmt::format("{0}DC_EVStatus:\n"
                     "{0}  EVReady={1}\n"
                     "{0}  EVErrorCode={2}\n"
                     "{0}  EVRESSSOC={3}",
                     indent,
                     status->EVReady,
                     EVSTATUSCODE[status->EVErrorCode],
                     status->EVRESSSOC);
  return temp;
}

std::string getStrDCEVSEStatus(DC_EVSEStatusType *status, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}DC_EVSEStatus:\n"
                     "{0}  EVSEIsolationStatus={1}\n"
                     "{0}  EVSEStatusCode={2}\n"
                     "{0}  EVSENotification={3}",
                     indent,
                     EVSENOTIFICATION[status->EVSENotification],
                     EVSEISOLATIONSTATUS[status->EVSEIsolationStatus],
                     EVSESTATUSCODE[status->EVSEStatusCode]);
  return temp;
}
static float Pow(int v_multiplier)
{
  float ret = 10.0;
  for (int i = 0; i < v_multiplier - 1; i = i + 1)
  {
    ret = ret * 10.0;
  }
  return ret;
}
std::string getStrChargeService(ChargeServiceType *service, const std::string &indent)
{
  std::string temp;
  std::string service_name = "";
  if (service->ServiceName_isUsed == 1)
  {
    service_name.append(std::string(service->ServiceName.characters));
  }
  std::string service_scope = "";
  if (service->ServiceScope_isUsed == 1)
  {
    service_scope.append(std::string(service->ServiceScope.characters));
  }
  std::string supported_eng_tm = "";
  for (size_t i = 0; (i < service->SupportedEnergyTransferMode.EnergyTransferMode.arrayLen)&&(service->SupportedEnergyTransferMode.EnergyTransferMode.arrayLen<SupportedEnergyTransferModeType_EnergyTransferMode_ARRAY_SIZE); i++)
  {
    supported_eng_tm.append(fmt::format("{}, ", ENERGY_TRANSFER_MODE[service->SupportedEnergyTransferMode.EnergyTransferMode.array[i]]));
  }
  if (supported_eng_tm.size() > 2)
  {
    supported_eng_tm.erase(supported_eng_tm.size() - 2, 2);
  }
  temp = fmt::format("{0}ServiceID={1}\n"
                     "{0}ServiceName={2}\n"
                     "{0}ServiceCategory={3}\n"
                     "{0}ServiceScope={4}\n"
                     "{0}FreeService={5}\n"
                     "{0}SupportedEnergyTransferMode=[{6}]",
                     indent,
                     service->ServiceID,
                     service_name,
                     SERVICE_CAT[service->ServiceCategory],
                     service_scope,
                     service->FreeService,
                     supported_eng_tm);
  return temp;
}
std::string getStrService(ServiceType *service, const std::string &indent)
{
  std::string temp;
  std::string service_name = "";
  if (service->ServiceName_isUsed == 1)
  {
    service_name.append(std::string(service->ServiceName.characters));
  }
  std::string service_scope = "";
  if (service->ServiceScope_isUsed == 1)
  {
    service_scope.append(std::string(service->ServiceScope.characters));
  }
  temp = fmt::format("{0}>>ServiceID={1}\n"
                     "{0}ServiceName={2}\n"
                     "{0}ServiceCategory={3}\n"
                     "{0}ServiceScope={4}\n"
                     "{0}FreeService={5}",
                     indent,
                     service->ServiceID,
                     service_name,
                     SERVICE_CAT[service->ServiceCategory],
                     service_scope,
                     service->FreeService);
  return temp;
}
std::string getStrParam(ParameterSetType *param, const std::string &indent)
{
  std::string temp;
  std::string str_param = "";

  for (size_t i = 0; (i < param->Parameter.arrayLen)&&(param->Parameter.arrayLen<ParameterSetType_Parameter_ARRAY_SIZE); i++)
  {
    std::string param_name = std::string(param->Parameter.array[i].Name.characters);
    std::string param_type = "";
    std::string param_value = "";
    if (param->Parameter.array[i].boolValue_isUsed == 1)
    {
      param_type = "bool";
      param_value = fmt::format("{}", param->Parameter.array[i].boolValue);
    }
    else if (param->Parameter.array[i].byteValue_isUsed == 1)
    {
      param_type = "byte";
      param_value = fmt::format("{}", param->Parameter.array[i].byteValue);
    }
    else if (param->Parameter.array[i].shortValue_isUsed == 1)
    {
      param_type = "short";
      param_value = fmt::format("{}", param->Parameter.array[i].shortValue);
    }
    else if (param->Parameter.array[i].intValue_isUsed == 1)
    {
      param_type = "int";
      param_value = fmt::format("{}", param->Parameter.array[i].intValue);
    }
    else if (param->Parameter.array[i].physicalValue_isUsed == 1)
    {
      param_type = "Physical";
      param_value = fmt::format("{}", getStrPhysicalValue(&param->Parameter.array[i].physicalValue));
    }
    else if (param->Parameter.array[i].stringValue_isUsed == 1)
    {
      param_type = "string";
      std::string val = std::string(param->Parameter.array[i].stringValue.characters);
      param_value = fmt::format("{}", val);
    }
    str_param.append(fmt::format("{0}  Parameter{4}.Name={1}\n"
                                 "{0}  Parameter{4}.Type={2}\n"
                                 "{0}  Parameter{4}.Value={3}\n",
                                 indent,
                                 param_name,
                                 param_type,
                                 param_value,
                                 i));
  }
  str_param.pop_back();

  temp = fmt::format("{0}>>ParameterSetID={1}\n"
                     "{2}",
                     indent,
                     param->ParameterSetID,
                     str_param);
  return temp;
}
std::string getStrEVSEStatus(EVSEStatusType *status, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}EVSEStatus:\n"
                     "{0}  NotificationMaxDelay={1}\n"
                     "{0}  EVSENotification={2}",
                     indent,
                     status->NotificationMaxDelay,
                     EVSENOTIFICATION[status->EVSENotification]);
  return temp;
}
std::string getStrACEVSEStatus(AC_EVSEStatusType *status, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}AC_EVSEStatus:\n"
                     "{0}  NotificationMaxDelay={1}\n"
                     "{0}  EVSENotification={2}\n"
                     "{0}  RCD={3}",
                     indent,
                     status->NotificationMaxDelay,
                     EVSENOTIFICATION[status->EVSENotification],
                     status->RCD);
  return temp;
}
std::string getStrChargingProfile(ChargingProfileType *profile, const std::string &indent)
{
  std::string temp;
  std::string profile_list = "";
  for (size_t i = 0; (i < profile->ProfileEntry.arrayLen)&&(profile->ProfileEntry.arrayLen<ChargingProfileType_ProfileEntry_ARRAY_SIZE); i++)
  {
    profile_list.append(fmt::format("{0}  Profile[{1}]: Start={2}, MaxPower={3}",
                                    indent, i, profile->ProfileEntry.array[i].ChargingProfileEntryStart,
                                    getStrPhysicalValue(&profile->ProfileEntry.array[i].ChargingProfileEntryMaxPower)));
    if (profile->ProfileEntry.array[i].ChargingProfileEntryMaxNumberOfPhasesInUse_isUsed == 1)
    {
      profile_list.append(fmt::format(", MaxNumberOfPhasesInUse={}\n", profile->ProfileEntry.array[i].ChargingProfileEntryMaxNumberOfPhasesInUse));
    }
    else
    {
      profile_list.append("\n");
    }
  }
  if (profile_list != "")
  {
    profile_list.pop_back();
  }
  temp = fmt::format("{0}ChargingProfile:\n"
                     "{1}",
                     indent, profile_list);
  return temp;
}

std::string getStrEVPowerDeliveryParameter(EVPowerDeliveryParameterType *param, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}EVPowerDeliveryParameter: Empty", indent);
  return temp;
}

std::string getStrDCEVPowerDeliveryParameter(DC_EVPowerDeliveryParameterType *param, const std::string &indent)
{
  std::string temp;
  std::string charging_status_flag = "";
  std::string sub_indent = indent + "  ";
  if (param->BulkChargingComplete_isUsed == 1)
  {
    charging_status_flag.append(fmt::format("{0}BulkChargingComplete={1}\n", sub_indent, param->BulkChargingComplete));
  }
  charging_status_flag.append(fmt::format("{0}ChargingComplete={1}", sub_indent, param->ChargingComplete));
  temp = fmt::format("{0}DC_EVPowerDeliveryParameter:\n"
                     "{1}\n"
                     "{2}",
                     indent,
                     getStrDCEVStatus(&param->DC_EVStatus, sub_indent),
                     charging_status_flag);
  return temp;
}

std::string getStrContractCertChain(CertificateChainType *chain, const std::string &indent)
{
  std::string temp = "";
  std::string id_cert = "";
  std::string sub_cert = "";
  if (chain->Id_isUsed == 1)
  {
    id_cert.append(fmt::format("{0}  Id={1}\n", indent, std::string(chain->Id.characters)));
  }
  id_cert.append(fmt::format("{0}  Certificate={1}\n",
                             indent,
                             outHexString(chain->Certificate.bytes, chain->Certificate.bytesLen)));

  if (chain->SubCertificates_isUsed == 1)
  {
    sub_cert.append(fmt::format("{0}  SubCertificates:\n", indent));
    for (size_t i = 0; i < chain->SubCertificates.Certificate.arrayLen; i++)
    {
      sub_cert.append(fmt::format("{0}    Certificate[{1}]={2}\n",
                                  indent, i,
                                  outHexString(chain->SubCertificates.Certificate.array[i].bytes, chain->SubCertificates.Certificate.array[i].bytesLen)));
    }
  }
  temp = fmt::format("{0}ContractSignatureCertChain:\n"
                     "{1}",
                     indent, id_cert);
  if (sub_cert.size() != 0)
  {
    sub_cert.pop_back();
    temp.append(sub_cert);
  }
  return temp;
}

std::string getStrMeterInfo(MeterInfoType *meter, const std::string &indent)
{
  std::string temp;
  std::string meter_id(meter->MeterID.characters, meter->MeterID.charactersLen);
  std::string other_field = "";
  if (meter->MeterReading_isUsed == 1)
  {
    other_field.append(fmt::format("{0}  MeterReading={1}\n", indent, meter->MeterReading));
  }
  if (meter->SigMeterReading_isUsed == 1)
  {
    other_field.append(fmt::format("{0}  SigMeterReading={1}\n", indent, outHexString(meter->SigMeterReading.bytes, meter->SigMeterReading.bytesLen)));
  }
  if (meter->MeterStatus_isUsed == 1)
  {
    other_field.append(fmt::format("{0}  MeterStatus={1}\n", indent, meter->MeterStatus));
  }
  if (meter->TMeter_isUsed == 1)
  {
    other_field.append(fmt::format("{0}  TMeter={1}\n", indent, meter->TMeter));
  }
  temp = fmt::format("{0}MeterInfo:\n"
                     "{0}  MeterId={1}\n"
                     "{2}",
                     indent, meter_id, other_field);
  if (other_field != "")
  {
    temp.pop_back();
  }
  else
  {
    temp.pop_back();
    temp.pop_back();
  }
  return temp;
}

std::string getStrEVStatus(EVStatusType *status, const std::string &indent)
{
  std::string temp(fmt::format("{0}EVStatus={1}", indent, ""));
  return temp;
}

std::string getStrPMaxSchedule(PMaxScheduleType *pmax, const std::string &indent)
{
  //PMaxSchedule:
  //  PMaxScheduleEntry[]
  //    TimeInterval
  //    RelativeTimeInterval: start, duration
  //    PMax
  std::string temp = fmt::format("{0}PMaxSchedule:\n",indent);
  for (size_t i = 0; (i < pmax->PMaxScheduleEntry.arrayLen)&&(pmax->PMaxScheduleEntry.arrayLen<PMaxScheduleType_PMaxScheduleEntry_ARRAY_SIZE); i++)
  {
    std::string time_str = "";
    if (pmax->PMaxScheduleEntry.array[i].TimeInterval_isUsed == 1)
    {
      time_str.append(fmt::format("TimeInterval={0} | ", pmax->PMaxScheduleEntry.array[i].TimeInterval.noContent));
    }
    if (pmax->PMaxScheduleEntry.array[i].RelativeTimeInterval_isUsed == 1)
    {
      time_str.append(fmt::format("RelativeTimeInterval: start={0}", pmax->PMaxScheduleEntry.array[i].RelativeTimeInterval.start));
      if (pmax->PMaxScheduleEntry.array[i].RelativeTimeInterval.duration_isUsed == 1)
      {
        time_str.append(fmt::format(", duration={0}", pmax->PMaxScheduleEntry.array[i].RelativeTimeInterval.duration));
      }
    }
    temp.append(fmt::format("{0}  PMaxScheduleEntry[{1}]:\n", indent, i));
    if (time_str.size() != 0)
    {
      temp.append(fmt::format("{0}    {1}\n", indent, time_str));
    }
    temp.append(fmt::format("{0}    PMax={1}\n", indent, getStrPhysicalValue(&pmax->PMaxScheduleEntry.array[i].PMax)));
  }
  temp.pop_back();
  return temp;
}
std::string getStrCost(CostType *cost)
{
  float ret;
  if (cost->amountMultiplier < 0)
  {
    ret = ((float)(cost->amount) * (1.0 / (Pow(cost->amountMultiplier * -1))));
  }
  else if (cost->amountMultiplier > 0)
  {
    ret = ((float)(cost->amount) * (Pow(cost->amountMultiplier)));
  }
  else
  {
    ret = (float)(cost->amount);
  }
  return fmt::format("{0}{1}", ret, COST_TYPE[cost->costKind]);
}
std::string getStrTariffEntry(SalesTariffEntryType *tariff_entry, const std::string &indent)
{
  // TimeInterval
  // RelativeTimeInterval
  // EPriceLevel
  // ConsumptionCost[]: startValue, Cost[]
  std::string temp("");
  std::string time_str("");
  if (tariff_entry->TimeInterval_isUsed == 1)
  {
    time_str.append(fmt::format("TimeInterval={0} | ", tariff_entry->TimeInterval.noContent));
  }
  if (tariff_entry->RelativeTimeInterval_isUsed == 1)
  {
    time_str.append(fmt::format("RelativeTimeInterval: start={0}", tariff_entry->RelativeTimeInterval.start));
    if (tariff_entry->RelativeTimeInterval.duration_isUsed == 1)
    {
      time_str.append(fmt::format(", {0}", tariff_entry->RelativeTimeInterval.duration));
    }
  }
  if (time_str.size() != 0)
  {
    temp.append(fmt::format("{0}{1}\n", indent, time_str));
  }
  if (tariff_entry->EPriceLevel_isUsed == 1)
  {
    temp.append(fmt::format("{0}EPriceLevel={1}\n", indent, tariff_entry->EPriceLevel));
  }
  for (size_t i = 0; (i < tariff_entry->ConsumptionCost.arrayLen)&&(tariff_entry->ConsumptionCost.arrayLen<SalesTariffEntryType_ConsumptionCost_ARRAY_SIZE); i++)
  {
    std::string cost_arr = "";
    for (size_t j = 0; (j < tariff_entry->ConsumptionCost.array[i].Cost.arrayLen)&&(tariff_entry->ConsumptionCost.array[i].Cost.arrayLen<ConsumptionCostType_Cost_ARRAY_SIZE); j++)
    {
      cost_arr.append(fmt::format("{}, ", getStrCost(&tariff_entry->ConsumptionCost.array[i].Cost.array[j])));
    }
    if (cost_arr.size() > 2)
    {
      cost_arr.pop_back();
      cost_arr.pop_back();
    }
    temp.append(fmt::format("{0}ConsumptionCost[{1}]: startValue={2}, Cost=[{3}]\n",
                            indent, i,
                            getStrPhysicalValue(&tariff_entry->ConsumptionCost.array[i].startValue), cost_arr));
  }
  temp.pop_back();
  return temp;
}
std::string getStrSalesTariff(SalesTariffType *sale_tariff, const std::string &indent)
{
  //SalesTariff:
  //  SalesTariffID=
  //  Id=
  //  SalesTariffDescription=
  //  NumEPriceLevels=
  //  SalesTariffEntry[]
  //    TimeInterval
  //    RelativeTimeInterval
  //    EPriceLevel
  //    ConsumptionCost[]: startValue, Cost[]
  std::string temp;
  temp.append(fmt::format("{0}SaleTariff:\n"
                          "{0}  SalesTariffID={1}\n",
                          indent, sale_tariff->SalesTariffID));
  if (sale_tariff->Id_isUsed == 1)
  {
    temp.append(fmt::format("{0}  Id={1}\n", indent, std::string(sale_tariff->Id.characters)));
  }
  if (sale_tariff->SalesTariffDescription_isUsed == 1)
  {
    temp.append(fmt::format("{0}  SalesTariffDescription={1}\n", indent, std::string(sale_tariff->SalesTariffDescription.characters)));
  }
  if (sale_tariff->NumEPriceLevels_isUsed == 1)
  {
    temp.append(fmt::format("{0}  NumEPriceLevels={1}\n", indent, sale_tariff->NumEPriceLevels));
  }
  for (size_t i = 0; (i < sale_tariff->SalesTariffEntry.arrayLen)&&(sale_tariff->SalesTariffEntry.arrayLen<SalesTariffType_SalesTariffEntry_ARRAY_SIZE); i++)
  {
    temp.append(fmt::format("{0}  SalesTariffEntry[{1}]:\n"
                            "{2}\n", indent, i, getStrTariffEntry(&sale_tariff->SalesTariffEntry.array[i], fmt::format("{0}    ", indent))));
  }
  temp.pop_back();
  return temp;
}

std::string getStrSAScheduleList(SAScheduleListType *schedule, const std::string &indent)
{
  std::string temp;
  std::string schedule_tuple = "";
  //  SAScheduleList:
  //     SAScheduleTuple[]
  //       SAScheduleTupleID
  //       PMaxSchedule
  //       SalesTariff
  for (size_t i = 0; (i < schedule->SAScheduleTuple.arrayLen)&&(schedule->SAScheduleTuple.arrayLen<SAScheduleListType_SAScheduleTuple_ARRAY_SIZE); i++)
  {
    std::string pmax_str = getStrPMaxSchedule(&schedule->SAScheduleTuple.array[i].PMaxSchedule, fmt::format("{0}    ", indent));
    schedule_tuple.append(fmt::format("{0}  SAScheduleTuple[{1}]:\n"
                                      "{0}    SAScheduleTupleID={2}\n",
                                      indent, i, schedule->SAScheduleTuple.array[i].SAScheduleTupleID));
    if (pmax_str.size() != 0)
    {
      schedule_tuple.append(fmt::format("{}\n", pmax_str));
    }
    std::string sale_tariff_str;
    if (schedule->SAScheduleTuple.array[i].SalesTariff_isUsed == 1)
    {
      sale_tariff_str.append(getStrSalesTariff(&schedule->SAScheduleTuple.array[i].SalesTariff, fmt::format("{0}    ", indent)));
    }
    if (sale_tariff_str.size() != 0)
    {
      schedule_tuple.append(fmt::format("{}\n",sale_tariff_str));
    }
  }
  temp = fmt::format("{0}SAScheduleList:\n"
                     "{1}",
                     indent, schedule_tuple);
  temp.pop_back();
  return temp;
}

std::string getStrEVSEChargeParameter(EVSEChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}EVSEChargeParameter: Empty", indent);
  return temp;
}
std::string getStrACEVSEChargeParameter(AC_EVSEChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp = fmt::format("{0}AC_EVSEChargeParameter:\n"
                                 "{0}  EVSENominalVoltage={1}\n"
                                 "{0}  EVSEMaxCurrent={2}\n"
                                 "{3}",
                                 indent,
                                 getStrPhysicalValue(&charge_param->EVSENominalVoltage),
                                 getStrPhysicalValue(&charge_param->EVSEMaxCurrent),
                                 getStrACEVSEStatus(&charge_param->AC_EVSEStatus, fmt::format("{0}  ", indent)));
  return temp;
}
std::string getStrDCEVSEChargeParameter(DC_EVSEChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp;
  temp = fmt::format("{0}DC_EVSEChargeParameter:\n"
                     "{1}\n"
                     "{0}  EVSEMaximumCurrentLimit={2}\n"
                     "{0}  EVSEMaximumVoltageLimit={3}\n"
                     "{0}  EVSEMaximumPowerLimit={4}\n"
                     "{0}  EVSEMinimumCurrentLimit={5}\n"
                     "{0}  EVSEMinimumVoltageLimit={6}\n"
                     "{0}  EVSEPeakCurrentRipple={7}\n",
                     indent,
                     getStrDCEVSEStatus(&charge_param->DC_EVSEStatus, fmt::format("{0}  ", indent)),
                     getStrPhysicalValue(&charge_param->EVSEMaximumCurrentLimit),
                     getStrPhysicalValue(&charge_param->EVSEMaximumVoltageLimit),
                     getStrPhysicalValue(&charge_param->EVSEMaximumPowerLimit),
                     getStrPhysicalValue(&charge_param->EVSEMinimumCurrentLimit),
                     getStrPhysicalValue(&charge_param->EVSEMinimumVoltageLimit),
                     getStrPhysicalValue(&charge_param->EVSEPeakCurrentRipple));
  if (charge_param->EVSECurrentRegulationTolerance_isUsed == 1)
  {
    temp.append(fmt::format("{0}  EVSECurrentRegulationTolerance={1}\n", indent, getStrPhysicalValue(&charge_param->EVSECurrentRegulationTolerance)));
  }
  if (charge_param->EVSEEnergyToBeDelivered_isUsed == 1)
  {
    temp.append(fmt::format("{0}  EVSEEnergyToBeDelivered={1}\n", indent,  getStrPhysicalValue(&charge_param->EVSEEnergyToBeDelivered)));
  }
  temp.pop_back();
  return temp;
}

std::string getStrEVChargeParameter(EVChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp = fmt::format("{0}EVChargeParameter:\n", indent);
  if (charge_param->DepartureTime_isUsed == 1)
  {
    temp.append(fmt::format("{0}  DepartureTime={1}\n", indent, charge_param->DepartureTime));
  }
  temp.pop_back();
  return temp;
}
std::string getStrACEVChargeParameter(AC_EVChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp = fmt::format("{0}AC_EVChargeParameter:\n", indent);
  if (charge_param->DepartureTime_isUsed == 1)
  {
    temp.append(fmt::format("{0}  DepartureTime={1}\n", indent, charge_param->DepartureTime));
  }
  temp.append(fmt::format("{0}  EAmount={1}\n"
                          "{0}  EVMaxVoltage={2}\n"
                          "{0}  EVMaxCurrent={3}\n"
                          "{0}  EVMinCurrent={4}\n",
                          indent,
                          getStrPhysicalValue(&charge_param->EAmount),
                          getStrPhysicalValue(&charge_param->EVMaxVoltage),
                          getStrPhysicalValue(&charge_param->EVMaxCurrent),
                          getStrPhysicalValue(&charge_param->EVMinCurrent)));
  temp.pop_back();
  return temp;
}
std::string getStrDCEVChargeParameter(DC_EVChargeParameterType *charge_param, const std::string &indent)
{
  std::string temp = fmt::format("{0}DC_EVChargeParameter:\n", indent);
  if (charge_param->DepartureTime_isUsed == 1)
  {
    temp.append(fmt::format("{0}  DepartureTime={1}\n", indent, charge_param->DepartureTime));
  }
  temp.append(fmt::format("{0}\n"
                          "{1}  EVMaximumCurrentLimit={2}\n"
                          "{1}  EVMaximumVoltageLimit={3}\n",
                          getStrDCEVStatus(&charge_param->DC_EVStatus, fmt::format("{0}  ", indent)),
                          indent,
                          getStrPhysicalValue(&charge_param->EVMaximumCurrentLimit),
                          getStrPhysicalValue(&charge_param->EVMaximumVoltageLimit)));
  if (charge_param->EVMaximumPowerLimit_isUsed == 1)
  {
    temp.append(fmt::format("{0}  EVMaximumPowerLimit={1}\n", indent, getStrPhysicalValue(&charge_param->EVMaximumPowerLimit)));
  }
  if (charge_param->EVEnergyCapacity_isUsed == 1)
  {
    temp.append(fmt::format("{0}  EVEnergyCapacity={1}\n", indent, getStrPhysicalValue(&charge_param->EVEnergyCapacity)));
  }
  if (charge_param->EVEnergyRequest_isUsed == 1)
  {
    temp.append(fmt::format("{0}  EVEnergyRequest={1}\n", indent, getStrPhysicalValue(&charge_param->EVEnergyRequest)));
  }
  if (charge_param->BulkSOC_isUsed == 1)
  {
    temp.append(fmt::format("{0}  BulkSOC={1}\n", indent, charge_param->BulkSOC));
  }
  if (charge_param->FullSOC_isUsed == 1)
  {
    temp.append(fmt::format("{0}  FullSOC={1}\n", indent, charge_param->FullSOC));
  }
  temp.pop_back();
  return temp;
}