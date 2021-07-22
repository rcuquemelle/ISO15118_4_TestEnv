#include "runTC.h"
#include <time.h>
#include <regex>
#include "V2gSdpResMessage.h"
#include "V2gSdpMessage.h"
#include "V2gALMsg.h"
#include "PAInterface.h"

int main(int argc, const char *argv[])
{
  Logging::LogCfg.value = LogAll_ENABLE;
  Logging::setLogLevel(LOG_DEBUG);
  Logging::setLogOutput(LOG_OUT_CONSOLE);

  IfRuntime rm;
  auto service = rm.getService();
  PATimerManager tm(service);
  std::shared_ptr<PATimer> t1 = tm.createTimer("local", 15);
  std::atomic<bool> end_flag = false;
  service->Dispatch([&t1, &end_flag]() {
    while (end_flag == false)
    {
      t1->start();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      t1->start();
      if (t1->running())
      {
        Logging::info(0,"Timer running");
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      t1->stop();
    }
   });

  while(t1->running());
  Logging::info(0,"Timer stop");
  std::cin.get();

  // std::vector<uint8_t> sessionid{1, 2, 3, 4, 5, 6, 7, 8};
  // std::vector<uint8_t> challenge{2, 3, 4, 5,1};
  // std::shared_ptr<AuthorizationReq> msgReq1 = std::make_shared<AuthorizationReq>();
  // msgReq1->setSessionId(sessionid);
  // msgReq1->setGenChallenge(challenge);
  // msgReq1->setId("testid");
  // msgReq1->serialize();
  // msgReq1->deserialize();

  // std::shared_ptr<AuthorizationRes> msgRes1 = std::make_shared<AuthorizationRes>();
  // msgRes1->setSessionId(sessionid);
  // msgRes1->setEVSEProcessing((EVSEProcessingType)1);
  // msgRes1->setResponseCode((responseCodeType)6);
  // msgRes1->serialize();
  // msgRes1->deserialize();

  // DC_EVStatusType dcevStatus = {.EVReady = 1, .EVErrorCode = (DC_EVErrorCodeType)1, .EVRESSSOC=20};
  // std::shared_ptr<CableCheckReq> msgReq2 = std::make_shared<CableCheckReq>();
  // msgReq2->setSessionId(sessionid);
  // msgReq2->setDCEVStatus(&dcevStatus);
  // msgReq2->serialize();
  // msgReq2->deserialize();

  // DC_EVSEStatusType dcevseStatus = {.NotificationMaxDelay = 10, .EVSENotification=(EVSENotificationType)2, .EVSEIsolationStatus=iso1isolationLevelType_No_IMD, .EVSEIsolationStatus_isUsed = 1, .EVSEStatusCode = iso1DC_EVSEStatusCodeType_EVSE_IsolationMonitoringActive};
  // std::shared_ptr<CableCheckRes> msgRes2 = std::make_shared<CableCheckRes>();
  // msgRes2->setSessionId(sessionid);
  // msgRes2->setResponseCode((responseCodeType)7);
  // msgRes2->setDCEVSEStatus(&dcevseStatus);
  // msgRes2->setEVSEProcessing((EVSEProcessingType)2);
  // msgRes2->serialize();
  // msgRes2->deserialize();

  // std::shared_ptr<ChargeParameterDiscoveryReq> msgReq3 = std::make_shared<ChargeParameterDiscoveryReq>();
  // EVChargeParameterType evcharge = {.DepartureTime = 100, .DepartureTime_isUsed = 1};
  // AC_EVChargeParameterType ac_evcharge = {.DepartureTime = 12, .DepartureTime_isUsed = 1, .EAmount = {.Multiplier = 1, .Unit = iso1unitSymbolType_Wh, .Value = 12},
  // .EVMaxVoltage = {.Multiplier = 1, .Unit = iso1unitSymbolType_V, .Value = 54},
  // .EVMaxCurrent = {.Multiplier = 1, .Unit = iso1unitSymbolType_A, .Value = 22},
  // .EVMinCurrent = {.Multiplier = 1, .Unit = iso1unitSymbolType_A, .Value = 2}};
  // DC_EVChargeParameterType dc_evcharge = {.DepartureTime = 100, .DepartureTime_isUsed = 1, .DC_EVStatus={.EVReady = 1, .EVErrorCode = iso1DC_EVErrorCodeType_Reserved_B, .EVRESSSOC= 40},
  // .EVMaximumCurrentLimit={.Multiplier = 0, .Unit = iso1unitSymbolType_A, .Value = 54},
  // .EVMaximumPowerLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 54},
  // .EVMaximumPowerLimit_isUsed=1,
  // .EVMaximumVoltageLimit = {.Multiplier = 0, .Unit = iso1unitSymbolType_V, .Value = 666},
  // .EVEnergyCapacity={.Multiplier = 2, .Unit = iso1unitSymbolType_Wh, .Value = 24},
  // .EVEnergyCapacity_isUsed = 1,
  // .EVEnergyRequest = {.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 22},
  // .EVEnergyRequest_isUsed = 1,
  // .FullSOC = 100, .FullSOC_isUsed = 1, .BulkSOC=70, .BulkSOC_isUsed = 1};
  // msgReq3->setSessionId(sessionid);
  // msgReq3->setMaxEntriesSAScheduleTuple(5);
  // msgReq3->setEnergyTransferModeReq(iso1EnergyTransferModeType_DC_combo_core);
  // msgReq3->setACEVChargeParamter(&ac_evcharge);
  // msgReq3->serialize();
  // msgReq3->deserialize();
  
  // msgReq3 = std::make_shared<ChargeParameterDiscoveryReq>();
  // msgReq3->setSessionId(sessionid);
  // msgReq3->setMaxEntriesSAScheduleTuple(34);
  // msgReq3->setDCEVChargeParamter(&dc_evcharge);
  // msgReq3->setEnergyTransferModeReq(iso1EnergyTransferModeType_AC_three_phase_core);
  // msgReq3->serialize();
  // msgReq3->deserialize();

  // std::shared_ptr<ChargeParameterDiscoveryRes> msgRes3 = std::make_shared<ChargeParameterDiscoveryRes>();
  // msgRes3->setResponseCode((responseCodeType)8);
  // msgRes3->setSessionId(sessionid);
  // msgRes3->setEVSEProcessing(iso1EVSEProcessingType_Ongoing_WaitingForCustomerInteraction);
  // SAScheduleListType schedule;
  // schedule.SAScheduleTuple.arrayLen = 2;
  // schedule.SAScheduleTuple.array[0].SAScheduleTupleID = 1;
  // schedule.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.arrayLen = 2;
  // schedule.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[0] = {.TimeInterval={0}, .TimeInterval_isUsed=1,.RelativeTimeInterval={.start=1, .duration=10, .duration_isUsed=1},
  // .RelativeTimeInterval_isUsed=1, .PMax={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 22}};
  // schedule.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[1] = {.TimeInterval={0}, .TimeInterval_isUsed=0,.RelativeTimeInterval={.start=11, .duration=42, .duration_isUsed=1},
  // .RelativeTimeInterval_isUsed=1, .PMax={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 25}};
  // schedule.SAScheduleTuple.array[0].SalesTariff_isUsed = 0;

  // schedule.SAScheduleTuple.array[1].SAScheduleTupleID = 2;
  // schedule.SAScheduleTuple.array[1].PMaxSchedule.PMaxScheduleEntry.arrayLen = 2;
  // schedule.SAScheduleTuple.array[1].PMaxSchedule.PMaxScheduleEntry.array[0] = {.TimeInterval={0}, .TimeInterval_isUsed=1,.RelativeTimeInterval={.start=1, .duration=10, .duration_isUsed=1},
  // .RelativeTimeInterval_isUsed=1, .PMax={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 22}};
  // schedule.SAScheduleTuple.array[1].PMaxSchedule.PMaxScheduleEntry.array[1] = {.TimeInterval={0}, .TimeInterval_isUsed=1,.RelativeTimeInterval={.start=11, .duration=42, .duration_isUsed=1},
  // .RelativeTimeInterval_isUsed=1, .PMax={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 25}};

  // schedule.SAScheduleTuple.array[1].SalesTariff_isUsed = 1;
  // std::string tariff_id = "ididid";
  // strcpy(schedule.SAScheduleTuple.array[1].SalesTariff.Id.characters,tariff_id.data());
  // schedule.SAScheduleTuple.array[1].SalesTariff.Id.charactersLen = tariff_id.size();
  // schedule.SAScheduleTuple.array[1].SalesTariff.Id_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffDescription_isUsed = 1;
  // std::string tariff_des = "this is tariff";
  // strcpy(schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffDescription.characters,tariff_des.data());
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffDescription.charactersLen = tariff_des.size();
  // schedule.SAScheduleTuple.array[1].SalesTariff.NumEPriceLevels_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.NumEPriceLevels = 9;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.arrayLen = 2;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].TimeInterval = {0};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].TimeInterval_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].RelativeTimeInterval = {.start=1, .duration=42, .duration_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].RelativeTimeInterval_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].EPriceLevel = 11;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].EPriceLevel_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.arrayLen = 2;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[0].startValue = {.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 25};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[0].Cost.arrayLen = 2;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[0].Cost.array[0] = {.costKind = iso1costKindType_RenewableGenerationPercentage, .amount=11,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[0].Cost.array[1] = {.costKind = iso1costKindType_CarbonDioxideEmission, .amount=2,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[1].startValue = {.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 99};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[1].Cost.arrayLen = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[0].ConsumptionCost.array[1].Cost.array[0] = {.costKind = iso1costKindType_relativePricePercentage, .amount=69,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].TimeInterval = {0};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].TimeInterval_isUsed = 0;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].RelativeTimeInterval = {.start=55, .duration=42, .duration_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].RelativeTimeInterval_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].EPriceLevel = 22;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].EPriceLevel_isUsed = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.arrayLen = 1;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.array[0].startValue = {.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 25};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.array[0].Cost.arrayLen = 3;
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.array[0].Cost.array[0] = {.costKind = iso1costKindType_RenewableGenerationPercentage, .amount=11,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.array[0].Cost.array[1] = {.costKind = iso1costKindType_CarbonDioxideEmission, .amount=2,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};
  // schedule.SAScheduleTuple.array[1].SalesTariff.SalesTariffEntry.array[1].ConsumptionCost.array[0].Cost.array[2] = {.costKind = iso1costKindType_relativePricePercentage, .amount=3,
  // .amountMultiplier=1, .amountMultiplier_isUsed=1};

  // msgRes3->setSAScheduleList(&schedule);
  // EVSEChargeParameterType evsecharge = {.noContent = 0};
  // // msgRes3->setEVSEChargeParameter(&evsecharge);
  // AC_EVSEChargeParameterType ac_evsecharge = {.AC_EVSEStatus={.NotificationMaxDelay=122, .EVSENotification=iso1EVSENotificationType_ReNegotiation, .RCD=220},
  // .EVSENominalVoltage={.Multiplier = 0, .Unit = iso1unitSymbolType_V, .Value = 222},
  // .EVSEMaxCurrent={.Multiplier = 2, .Unit = iso1unitSymbolType_A, .Value = 11}};
  // // msgRes3->setACEVSEChargeParameter(&ac_evsecharge);
  // DC_EVSEChargeParameterType dc_evsecharge = {.DC_EVSEStatus={.NotificationMaxDelay=1, .EVSENotification=iso1EVSENotificationType_StopCharging,.EVSEIsolationStatus=iso1isolationLevelType_Fault, .EVSEIsolationStatus_isUsed=1,.EVSEStatusCode=iso1DC_EVSEStatusCodeType_EVSE_Malfunction},
  // .EVSEMaximumCurrentLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_A, .Value = 1},
  // .EVSEMaximumPowerLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 221},
  // .EVSEMaximumVoltageLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_V, .Value = 66},
  // .EVSEMinimumCurrentLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_A, .Value = 22},
  // .EVSEMinimumVoltageLimit={.Multiplier = 2, .Unit = iso1unitSymbolType_V, .Value = 22},
  // .EVSECurrentRegulationTolerance={.Multiplier = 2, .Unit = iso1unitSymbolType_A, .Value = 1},
  // .EVSECurrentRegulationTolerance_isUsed=1,
  // .EVSEPeakCurrentRipple={.Multiplier = 2, .Unit = iso1unitSymbolType_A, .Value = 2},
  // .EVSEEnergyToBeDelivered={.Multiplier = 2, .Unit = iso1unitSymbolType_W, .Value = 22},
  // .EVSEEnergyToBeDelivered_isUsed=1
  // };
  // msgRes3->setDCEVSEChargeParameter(&dc_evsecharge);
  // msgRes3->serialize();
  // msgRes3->deserialize();

  // std::shared_ptr<ChargingStatusReq> msgReq4 = std::make_shared<ChargingStatusReq>();
  // msgReq4->setSessionId(sessionid);
  // msgReq4->serialize();
  // msgReq4->deserialize();

  // std::shared_ptr<ChargingStatusRes> msgRes4 = std::make_shared<ChargingStatusRes>();
  // msgRes4->setSessionId(sessionid);
  // msgRes4->setResponseCode((responseCodeType)9);
  // msgRes4->setEVSEID("iasdqw");
  // msgRes4->setSAScheduleTupleID(12);
  // PhysicalValueType evsemaxcurrent = {.Multiplier=1, .Unit=iso1unitSymbolType_A, .Value=22};
  // msgRes4->setEVSEMaxCurrent(&evsemaxcurrent);
  // MeterInfoType meter;
  // std::string meterid = "asda";
  // strcpy(meter.MeterID.characters, meterid.c_str());
  // meter.MeterID.charactersLen = meterid.size();
  // meter.MeterReading = 1122131;
  // meter.MeterReading_isUsed = 1;
  // meter.SigMeterReading.bytesLen = sessionid.size();
  // memcpy(meter.SigMeterReading.bytes, sessionid.data(), sessionid.size());
  // meter.SigMeterReading_isUsed = 1;
  // meter.MeterStatus = 12;
  // meter.MeterStatus_isUsed = 1;
  // meter.TMeter_isUsed = 1;
  // meter.TMeter = 122;
  // msgRes4->setMeterInfo(&meter);
  // msgRes4->setReceiptRequired(69);
  // AC_EVSEStatusType ac_evsestatus = {.NotificationMaxDelay=21,.EVSENotification=iso1EVSENotificationType_StopCharging,.RCD=21};
  // msgRes4->setACEVSEStatus(&ac_evsestatus);
  // msgRes4->serialize();
  // msgRes4->deserialize();

  // std::shared_ptr<CurrentDemandReq> msgReq5 = std::make_shared<CurrentDemandReq>();
  // msgReq5->setSessionId(sessionid);
  // DC_EVStatusType dc_evstatus = {.EVReady=1,.EVErrorCode=iso1DC_EVErrorCodeType_Reserved_A, .EVRESSSOC=30};
  // PhysicalValueType voltage = {.Multiplier=1, .Unit=iso1unitSymbolType_V, .Value=69};
  // PhysicalValueType current = {.Multiplier=1, .Unit=iso1unitSymbolType_A, .Value=69};
  // PhysicalValueType power = {.Multiplier=1, .Unit=iso1unitSymbolType_W, .Value=69};
  // PhysicalValueType time = {.Multiplier=1, .Unit=iso1unitSymbolType_h, .Value=69};
  // msgReq5->setDcEvStatus(&dc_evstatus);
  // msgReq5->setEvTargetCurrent(&current);
  // msgReq5->setEvTargetVoltage(&voltage);
  // msgReq5->setEvMaxVoltageLimit(&voltage);
  // msgReq5->setEvMaxCurrentLimit(&current);
  // msgReq5->setEvMaxPowerLimit(&power);
  // msgReq5->setBulkChargeCompleteStatus(true);
  // msgReq5->setChargingCompleteStatus(true);
  // msgReq5->setBulkChargeRemainTime(&time);
  // msgReq5->setFullChargeRemainTime(&time);
  // msgReq5->serialize();
  // msgReq5->deserialize();

  // std::shared_ptr<CurrentDemandRes> msgRes5 = std::make_shared<CurrentDemandRes>();
  // msgRes5->setSessionId(sessionid);
  // msgRes5->setResponseCode((responseCodeType)10);
  // msgRes5->setDCEVSEStatus(&dcevseStatus);
  // msgRes5->setEVSEPresentVoltage(&voltage);
  // msgRes5->setEVSEPresentCurrent(&current);
  // msgRes5->setEVSECurrentLimitArchived(true);
  // msgRes5->setEVSEVoltageLimitArchived(true);
  // msgRes5->setEVSEPowerLimitAchieved(false);
  // msgRes5->setEVSEMaximumVoltageLimit(&voltage);
  // msgRes5->setEVSEMaximumCurrentLimit(&current);
  // msgRes5->setEVSEMaximumPowerLimit(&power);
  // msgRes5->setEVSEID("evseid");
  // msgRes5->setSAScheduleTupleID(69);
  // msgRes5->setReceiptRequired(true);
  // msgRes5->serialize();
  // msgRes5->deserialize();

  // std::shared_ptr<MeterReceiptReq> msgReq6 = std::make_shared<MeterReceiptReq>();
  // msgReq6->setSessionId(sessionid);
  // msgReq6->setId("klas");
  // msgReq6->setFieldSessionID(sessionid);
  // msgReq6->setSAScheduleTupleID(69);
  // msgReq6->setMeterInfo(&meter);
  // msgReq6->serialize();
  // msgReq6->deserialize();


  // std::shared_ptr<MeterReceiptRes> msgRes6 = std::make_shared<MeterReceiptRes>();
  // msgRes6->setSessionId(sessionid);
  // msgRes6->setResponseCode((responseCodeType)11);
  // msgRes6->setDCEVSEStatus(&dcevseStatus);
  // msgRes6->serialize();
  // msgRes6->deserialize();

  // std::shared_ptr<PaymentDetailsReq> msgReq7 = std::make_shared<PaymentDetailsReq>();
  // msgReq7->setSessionId(sessionid);
  // msgReq7->setEMAID("alsijd");
  // CertificateChainType chain;
  // strcpy(chain.Id.characters, "123");
  // chain.Id.charactersLen = 4;
  // chain.Id_isUsed = 1;
  // memcpy(chain.Certificate.bytes, sessionid.data(), sessionid.size());
  // chain.Certificate.bytesLen = sessionid.size();
  // chain.SubCertificates_isUsed = 1;
  // chain.SubCertificates.Certificate.arrayLen = 1;
  // chain.SubCertificates.Certificate.array[0].bytesLen = sessionid.size();
  // memcpy(chain.SubCertificates.Certificate.array[0].bytes, sessionid.data(), sessionid.size());
  // msgReq7->setContractCertChain(&chain);
  // msgReq7->serialize();
  // msgReq7->deserialize();

  // std::shared_ptr<PaymentDetailsRes> msgRes7 = std::make_shared<PaymentDetailsRes>();
  // msgRes7->setSessionId(sessionid);
  // msgRes7->setResponseCode((responseCodeType)12);
  // msgRes7->setGenChallenge(sessionid);
  // msgRes7->setEVSETimeStamp(6969);
  // msgRes7->serialize();
  // msgRes7->deserialize();


  // std::shared_ptr<PowerDeliveryReq> msgReq8 = std::make_shared<PowerDeliveryReq>();
  // msgReq8->setSessionId(sessionid);
  // msgReq8->setChargeProgress((chargeProgressType)2);
  // msgReq8->setSAScheduleTupleID(69);
  // ChargingProfileType profile;
  // ProfileEntryType entry = {.ChargingProfileEntryStart=69, .ChargingProfileEntryMaxPower={.Multiplier=2, .Unit=iso1unitSymbolType_W, .Value=3},.ChargingProfileEntryMaxNumberOfPhasesInUse = 3, .ChargingProfileEntryMaxNumberOfPhasesInUse_isUsed = 1};
  // profile.ProfileEntry.arrayLen = 7;
  // for (size_t i = 0; i < 7; i++)
  // {
  //   memcpy(&profile.ProfileEntry.array[i], &entry, sizeof(entry));
  // }
  // DC_EVPowerDeliveryParameterType dc_evpower;
  // dc_evpower.BulkChargingComplete = 1;
  // dc_evpower.BulkChargingComplete_isUsed = 1;
  // dc_evpower.ChargingComplete = 1;
  // memcpy(&dc_evpower.DC_EVStatus, &dcevStatus, sizeof(dcevStatus));
  // msgReq8->setChargingProfile(&profile);
  // msgReq8->setDCEVPowerDeliveryParameter(&dc_evpower);
  // msgReq8->serialize();
  // msgReq8->deserialize();

  // std::shared_ptr<PowerDeliveryRes> msgRes8 = std::make_shared<PowerDeliveryRes>();
  // msgRes8->setSessionId(sessionid);
  // msgRes8->setACEVSEStatus(&ac_evsestatus);
  // msgRes8->setResponseCode((responseCodeType)13);
  // msgRes8->serialize();
  // msgRes8->deserialize();


  // std::shared_ptr<PreChargeReq> msgReq9 = std::make_shared<PreChargeReq>();
  // msgReq9->setSessionId(sessionid);
  // msgReq9->setDCEVStatus(&dcevStatus);
  // msgReq9->setEVTargetCurrent(&current);
  // msgReq9->setEVTargetVoltage(&voltage);
  // msgReq9->serialize();
  // msgReq9->deserialize();

  // std::shared_ptr<PreChargeRes> msgRes9 = std::make_shared<PreChargeRes>();
  // msgRes9->setSessionId(sessionid);
  // msgRes9->setResponseCode((responseCodeType)14);
  // msgRes9->setDCEVSEStatus(&dcevseStatus);
  // msgRes9->setEVSEPresentVoltage(&voltage);
  // msgRes9->serialize();
  // msgRes9->deserialize();

}