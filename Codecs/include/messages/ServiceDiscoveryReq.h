

#ifndef EVCC_SERVICEDISCOVERYREQ_H
#define EVCC_SERVICEDISCOVERYREQ_H

#include "../V2gExiMessage.h"

class ServiceDiscoveryReq : public V2gExiMessage
{
public:
  ServiceDiscoveryReq();
  virtual ~ServiceDiscoveryReq();
  void dumpMsg(void) override;
  /* Service service category other than charging service */
  void setServiceCategory(serviceCategoryType category);
  serviceCategoryType getServiceCategory();

  void setServiceScope(const std::string &scope);
  std::string &getServiceCope();

  /* service scope flag */
  comparision_indicate_flag mServiceScope_flag = omit;
  /* service category flag */
  comparision_indicate_flag mServiceCategory_flag = omit;

  bool operator==(ServiceDiscoveryReq &object_compare)
  {
    bool final_result = true;
    bool arr_result[2] = {true, true};
    std::string mServiceScopeCmp = object_compare.getServiceCope();
    switch (this->mServiceScope_flag)
    {
    case specific:
      arr_result[0] = (0 == this->mServiceScope.compare(mServiceScopeCmp));
      break;
    case has_value:
      if (mServiceScopeCmp == "")
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mServiceCategory_flag)
    {
    case specific:
      if (this->mServiceCategory != object_compare.getServiceCategory())
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if ((object_compare.getServiceCategory() != iso1serviceCategoryType_ContractCertificate) && (object_compare.getServiceCategory() != iso1serviceCategoryType_Internet) && (object_compare.getServiceCategory() != iso1serviceCategoryType_OtherCustom))
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 2; i++)
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
  std::string mServiceScope = "";
  serviceCategoryType mServiceCategory = iso1serviceCategoryType_EVCharging;
};

#endif //EVCC_SERVICEDISCOVERYREQ_H
