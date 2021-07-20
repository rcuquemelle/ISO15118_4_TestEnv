

#ifndef EVCC_CABLECHECKREQ_H
#define EVCC_CABLECHECKREQ_H

#include "../V2gExiMessage.h"

class CableCheckReq : public V2gExiMessage
{
public:
  CableCheckReq();
  virtual ~CableCheckReq();
  DC_EVStatusType *getDCEVStatus();
  void setDCEVStatus(DC_EVStatusType *status);
  void dumpMsg(void) override;
  comparision_indicate_flag pDC_EVStatus_flag = has_value;

  bool operator==(CableCheckReq &object_compare)
  {
    bool final_result = true;
    switch (this->pDC_EVStatus_flag)
    {
    case specific:
      final_result = (0 == memcmp(object_compare.getDCEVStatus(), this->getDCEVStatus(), sizeof(DC_EVStatusType)));
      break;
    case has_value:
    case omit:
    default:
      break;
    }
    return final_result;
  }
};

#endif //EVCC_CABLECHECKREQ_H
