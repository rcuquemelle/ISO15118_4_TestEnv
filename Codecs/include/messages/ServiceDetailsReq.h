

#ifndef EVCC_SERVICEDETAILSREQ_H
#define EVCC_SERVICEDETAILSREQ_H

#include "../V2gExiMessage.h"

class ServiceDetailsReq : public V2gExiMessage
{
public:
  ServiceDetailsReq();
  virtual ~ServiceDetailsReq();
  void dumpMsg(void) override;
  int getServiceID();
  void setServiceID(int id);

  comparision_indicate_flag mServiceID_flag = has_value;

  bool operator==(ServiceDetailsReq &object_compare)
  {
    bool final_result = true;
    switch (this->mServiceID_flag)
    {
    case specific:
      if (this->mServiceID != object_compare.getServiceID())
      {
        final_result = false;
      }
      break;
    case has_value:
      if (object_compare.getServiceID() == 0)
      {
        final_result = false;
      }
      break;
    case omit:
    default:
      break;
    }
    return final_result;
  }

private:
  uint16_t mServiceID = 0;
};

#endif //EVCC_SERVICEDETAILSREQ_H
