

#ifndef EVCC_SERVICEDETAILSRES_H
#define EVCC_SERVICEDETAILSRES_H

#include "../V2gExiMessage.h"

class ServiceDetailsRes : public V2gExiMessage
{
public:
  ServiceDetailsRes();
  ServiceDetailsRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~ServiceDetailsRes();

  responseCodeType getResponseCode(void);
  void setResponseCode(responseCodeType code);

  ServiceParameterListType *getServiceParamterList(void);
  void setServiceParamterList(ServiceParameterListType *list);

  int getServiceID();
  void setServiceID(int id);
  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = specific;
  comparision_indicate_flag mServiceID_flag = has_value;
  comparision_indicate_flag pServiceParameterList_flag = omit;

  bool operator==(ServiceDetailsRes &object_compare)
  {
    bool arr_result[3] = {true, true, true};
    bool final_result = true;
    ServiceParameterListType *pServiceParameterListCmp = object_compare.getServiceParamterList();
    switch (this->pServiceParameterList_flag)
    {
    case specific:
      if ((pServiceParameterListCmp != nullptr) && (this->pServiceParameterList != nullptr))
      {
        arr_result[0] = (0 == memcmp(pServiceParameterListCmp, this->pServiceParameterList, sizeof(ServiceParameterListType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pServiceParameterListCmp == nullptr)
      {
        arr_result[0] = false;
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
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mServiceID_flag)
    {
    case specific:
      if (this->mServiceID != object_compare.getServiceID())
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
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
  uint16_t mServiceID = 0;
  responseCodeType mResponseCode = (responseCodeType)26;
  ServiceParameterListType *pServiceParameterList = nullptr;
};

#endif //EVCC_SERVICEDETAILSRES_H
