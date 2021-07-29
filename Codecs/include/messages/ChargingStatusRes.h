//
// Created by james on 19/10/2020.
//

#ifndef EVCC_CHARGINGSTATUSRES_H
#define EVCC_CHARGINGSTATUSRES_H

#include "../V2gExiMessage.h"

class ChargingStatusRes : public V2gExiMessage
{
public:
  ChargingStatusRes();
  ChargingStatusRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~ChargingStatusRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);

  std::string &getEVSEID();
  void setEVSEID(const std::string &id);

  uint16_t getSAScheduleTupleID();
  void setSAScheduleTupleID(uint16_t id);

  PhysicalValueType *getEVSEMaxCurrent();
  void setEVSEMaxCurrent(PhysicalValueType *maxCurrent);

  MeterInfoType *getMeterInfo();
  void setMeterInfo(MeterInfoType *meterInfo);

  int getReceiptRequired();
  void setReceiptRequired(int value);

  AC_EVSEStatusType *getACEVSEStatus();
  void setACEVSEStatus(AC_EVSEStatusType *status);
  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = specific;
  comparision_indicate_flag mEVSEID_flag = has_value;
  comparision_indicate_flag mSAScheduleTupleID_flag = has_value;
  comparision_indicate_flag pEVSEMaxCurrent_flag = omit;
  comparision_indicate_flag pMeterInfo_flag = omit;
  comparision_indicate_flag mReceiptRequired_flag = omit;
  comparision_indicate_flag pAC_EVSEStatus_flag = has_value;

  bool operator==(ChargingStatusRes &object_compare)
  {
    bool arr_result[7] = {true, true, true, true, true, true, true};
    bool final_result = true;
    AC_EVSEStatusType *pAC_EVSEStatusCmp = object_compare.getACEVSEStatus();
    MeterInfoType *pMeterInfoCmp = object_compare.getMeterInfo();
    PhysicalValueType *pEVSEMaxCurrentCmp = object_compare.getEVSEMaxCurrent();
    std::string mEVSEIDCmpStr = object_compare.getEVSEID();
    switch (this->pAC_EVSEStatus_flag)
    {
    case specific:
      if ((pAC_EVSEStatusCmp != nullptr) && (this->getACEVSEStatus() != nullptr))
      {
        arr_result[0] = (0 == memcmp(pAC_EVSEStatusCmp, this->getACEVSEStatus(), sizeof(AC_EVSEStatusType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pAC_EVSEStatusCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pMeterInfo_flag)
    {
    case specific:
      if ((pMeterInfoCmp != nullptr) && (this->getMeterInfo() != nullptr))
      {
        arr_result[1] = (0 == memcmp(pMeterInfoCmp, this->getMeterInfo(), sizeof(MeterInfoType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pMeterInfoCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pEVSEMaxCurrent_flag)
    {
    case specific:
      if ((pEVSEMaxCurrentCmp != nullptr) && (this->getEVSEMaxCurrent() != nullptr))
      {
        arr_result[2] = (0 == memcmp(pEVSEMaxCurrentCmp, this->getEVSEMaxCurrent(), sizeof(PhysicalValueType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pEVSEMaxCurrentCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mReceiptRequired_flag)
    {
    case specific:
      if (this->getReceiptRequired() != object_compare.getReceiptRequired())
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (object_compare.getReceiptRequired() == -1)
      {
        arr_result[3] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mSAScheduleTupleID_flag)
    {
    case specific:
      if (this->getSAScheduleTupleID() != object_compare.getSAScheduleTupleID())
      {
        arr_result[4] = false;
      }
      break;
    case has_value:
    case omit:
    default:
      break;
    }
    switch (this->mResponseCode_flag)
    {
    case specific:
      if (this->getResponseCode() != object_compare.getResponseCode())
      {
        arr_result[5] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[5] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mEVSEID_flag)
    {
    case specific:
      arr_result[6] = (0 == this->mEVSEID.compare(mEVSEIDCmpStr));
      break;
    case has_value:
      arr_result[6] = (0 != mEVSEIDCmpStr.size());
      break;
    case omit:
      break;
    default:
      break;
    }
    for (int i = 0; i < 7; i++)
    {
      if (arr_result[i] == false)
      {
        final_result = false;
        break;
      }
    }
    return final_result = true;
  }

private:
  std::string mEVSEID = "";
};

#endif //EVCC_CHARGINGSTATUSRES_H
