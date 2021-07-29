

#ifndef EVCC_CHARGEPARAMETERDISCOVERYRES_H
#define EVCC_CHARGEPARAMETERDISCOVERYRES_H

#include "../V2gExiMessage.h"

class ChargeParameterDiscoveryRes : public V2gExiMessage
{
public:
  ChargeParameterDiscoveryRes();
  ChargeParameterDiscoveryRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~ChargeParameterDiscoveryRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);
  EVSEProcessingType getEVSEProcessing();
  void setEVSEProcessing(EVSEProcessingType proc);
  SAScheduleListType *getSAScheduleList();
  void setSAScheduleList(SAScheduleListType *schedule);
  AC_EVSEChargeParameterType *getACEVSEChargeParamter();
  void setACEVSEChargeParameter(AC_EVSEChargeParameterType *params);
  DC_EVSEChargeParameterType *getDCEVSEChargeParamter();
  void setDCEVSEChargeParameter(DC_EVSEChargeParameterType *params);
  EVSEChargeParameterType *getEVSEChargeParamter();
  void setEVSEChargeParameter(EVSEChargeParameterType *params);
  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = specific;
  comparision_indicate_flag mEVSEProcessing_flag = specific;
  comparision_indicate_flag pSASchedules_flag = omit;
  comparision_indicate_flag pAC_EVSEChargeParameter_flag = omit;
  comparision_indicate_flag pDC_EVSEChargeParameter_flag = omit;
  comparision_indicate_flag pEVSEChargeParameter_flag = omit;

  bool operator==(ChargeParameterDiscoveryRes &object_compare)
  {
    bool arr_result[6] = {true, true, true, true, true, true};
    bool final_result = true;

    SAScheduleListType *pSASchedulesCmp = object_compare.getSAScheduleList();
    AC_EVSEChargeParameterType *pAC_EVSEChargeParameterCmp = object_compare.getACEVSEChargeParamter();
    DC_EVSEChargeParameterType *pDC_EVSEChargeParameterCmp = object_compare.getDCEVSEChargeParamter();
    EVSEChargeParameterType *pEVSEChargeParameterCmp = object_compare.getEVSEChargeParamter();

    switch (this->pSASchedules_flag)
    {
    case specific:
      if ((pSASchedulesCmp != nullptr) && (this->pSASchedules != nullptr))
      {
        arr_result[0] = (0 == memcmp(pSASchedulesCmp, this->pSASchedules, sizeof(SAScheduleListType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pSASchedulesCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pAC_EVSEChargeParameter_flag)
    {
    case specific:
      if ((pAC_EVSEChargeParameterCmp != nullptr) && (this->pAC_EVSEChargeParameter != nullptr))
      {
        arr_result[1] = (0 == memcmp(pAC_EVSEChargeParameterCmp, this->pAC_EVSEChargeParameter, sizeof(AC_EVSEChargeParameterType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pAC_EVSEChargeParameterCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pDC_EVSEChargeParameter_flag)
    {
    case specific:
      if ((pDC_EVSEChargeParameterCmp != nullptr) && (this->pDC_EVSEChargeParameter != nullptr))
      {
        arr_result[2] = (0 == memcmp(pDC_EVSEChargeParameterCmp, this->pDC_EVSEChargeParameter, sizeof(DC_EVSEChargeParameterType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pDC_EVSEChargeParameterCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pEVSEChargeParameter_flag)
    {
    case specific:
      if ((pEVSEChargeParameterCmp != nullptr) && (this->pEVSEChargeParameter != nullptr))
      {
        arr_result[3] = (0 == memcmp(pEVSEChargeParameterCmp, this->pEVSEChargeParameter, sizeof(EVSEChargeParameterType)));
      }
      else
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (pEVSEChargeParameterCmp == nullptr)
      {
        arr_result[3] = false;
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
        arr_result[4] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[4] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mEVSEProcessing_flag)
    {
    case specific:
      if (this->mEVSEProcessing != object_compare.getEVSEProcessing())
      {
        arr_result[5] = false;
      }
      break;
    case has_value:
      if (object_compare.getEVSEProcessing() > 2)
      {
        arr_result[5] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 6; i++)
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
  responseCodeType mResponseCode = (responseCodeType)26;
  EVSEProcessingType mEVSEProcessing = (EVSEProcessingType)3;
  SAScheduleListType *pSASchedules = nullptr;
  AC_EVSEChargeParameterType *pAC_EVSEChargeParameter = nullptr;
  DC_EVSEChargeParameterType *pDC_EVSEChargeParameter = nullptr;
  EVSEChargeParameterType *pEVSEChargeParameter = nullptr;
};

#endif //EVCC_CHARGEPARAMETERDISCOVERYRES_H
