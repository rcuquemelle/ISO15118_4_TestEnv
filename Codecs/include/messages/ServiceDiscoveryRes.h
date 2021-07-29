

#ifndef EVCC_SERVICEDISCOVERYRES_H
#define EVCC_SERVICEDISCOVERYRES_H

#include "../V2gExiMessage.h"

class ServiceDiscoveryRes : public V2gExiMessage
{
public:
  ServiceDiscoveryRes();
  ServiceDiscoveryRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~ServiceDiscoveryRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);

  PaymentOptionListType *getPaymentOptionList();
  void setPaymentOptionList(PaymentOptionListType *list);

  ChargeServiceType *getChargeServiceType();
  void setChargeServiceType(ChargeServiceType *type);

  ServiceListType *getServiceList();
  void setServiceList(ServiceListType *type);
  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = specific;
  comparision_indicate_flag pServiceList_flag = omit;
  comparision_indicate_flag pChargeService_flag = has_value;
  comparision_indicate_flag pPaymentOptionList_flag = has_value;

  bool operator==(ServiceDiscoveryRes &object_compare)
  {
    bool arr_result[4] = {true, true, true, true};
    bool final_result = true;

    ServiceListType *pServiceListCmp = object_compare.getServiceList();
    ChargeServiceType *pChargeServiceCmp = object_compare.getChargeServiceType();
    PaymentOptionListType *pPaymentOptionListCmp = object_compare.getPaymentOptionList();

    switch (this->pServiceList_flag)
    {
    case specific:
      if ((pServiceListCmp != nullptr) && (this->pServiceList != nullptr))
      {
        arr_result[0] = (0 == memcmp(pServiceListCmp, this->pServiceList, sizeof(ServiceListType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pServiceListCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->pChargeService_flag)
    {
    case specific:
      if ((pChargeServiceCmp != nullptr) && (this->pChargeService != nullptr))
      {
        arr_result[1] = (0 == memcmp(pChargeServiceCmp, this->pChargeService, sizeof(ServiceListType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pChargeServiceCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->pPaymentOptionList_flag)
    {
    case specific:
      if ((pPaymentOptionListCmp != nullptr) && (this->pPaymentOptionList != nullptr))
      {
        arr_result[2] = (0 == memcmp(pPaymentOptionListCmp, this->pPaymentOptionList, sizeof(ServiceListType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pPaymentOptionListCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->mResponseCode_flag)
    {
    case specific:
      if (object_compare.getResponseCode() != this->mResponseCode)
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > (responseCodeType)25)
      {
        arr_result[3] = false;
      } 
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 4; i++)
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
  ServiceListType *pServiceList = nullptr;
  ChargeServiceType *pChargeService = nullptr;
  PaymentOptionListType *pPaymentOptionList = nullptr;
  responseCodeType mResponseCode = (responseCodeType)26;
};

#endif //EVCC_SERVICEDISCOVERYRES_H
