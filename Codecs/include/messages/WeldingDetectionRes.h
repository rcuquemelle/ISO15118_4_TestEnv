

#ifndef EVCC_WELDINGDETECTIONRES_H
#define EVCC_WELDINGDETECTIONRES_H

#include "../V2gExiMessage.h"

class WeldingDetectionRes : public V2gExiMessage
{
public:
  WeldingDetectionRes();
  WeldingDetectionRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~WeldingDetectionRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);
  DC_EVSEStatusType *getDCEVSEStatus();
  void setDCEVSEStatus(DC_EVSEStatusType *status);
  PhysicalValueType *getEVSEPresentVoltage();
  void setEVSEPresentVoltage(PhysicalValueType *voltage);
  void dumpMsg(void) override;

  comparision_indicate_flag pEVSEPresentVoltage_flag = has_value;
  comparision_indicate_flag pDC_EVSEStatus_flag = has_value;
  comparision_indicate_flag mResponseCode_flag = specific;

  bool operator==(WeldingDetectionRes &object_compare)
  {
    bool arr_result[3] = {true, true, true};
    bool final_result = true;
    PhysicalValueType *pEVSEPresentVoltageCmp = object_compare.getEVSEPresentVoltage();
    DC_EVSEStatusType *pDC_EVSEStatusCmp = object_compare.getDCEVSEStatus();

    switch (this->pEVSEPresentVoltage_flag)
    {
    case specific:
      if ((pEVSEPresentVoltageCmp != nullptr) && (this->pEVSEPresentVoltage != nullptr))
      {
        arr_result[0] = (0 == memcmp(pEVSEPresentVoltageCmp, this->pEVSEPresentVoltage, sizeof(PhysicalValueType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pEVSEPresentVoltageCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pDC_EVSEStatus_flag)
    {
    case specific:
      if ((pDC_EVSEStatusCmp != nullptr) && (this->pDC_EVSEStatus != nullptr))
      {
        arr_result[1] = (0 == memcmp(pDC_EVSEStatusCmp, this->pDC_EVSEStatus, sizeof(PhysicalValueType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pDC_EVSEStatusCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mResponseCode_flag)
    {
    case specific:
      if (this->mResponseCode != object_compare.getResponseCode())
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 3; i++)
    {
      if (arr_result[i] == false)
      {
        final_result = false;
        break;
      }
    }
    return final_result;
  }

private:
  PhysicalValueType *pEVSEPresentVoltage = nullptr;
  DC_EVSEStatusType *pDC_EVSEStatus = nullptr;
  responseCodeType mResponseCode = (responseCodeType)26;
};

#endif //EVCC_WELDINGDETECTIONRES_H
