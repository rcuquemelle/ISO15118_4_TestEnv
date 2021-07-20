

#ifndef EVCC_WELDINGDETECTIONREQ_H
#define EVCC_WELDINGDETECTIONREQ_H

#include "../V2gExiMessage.h"

class WeldingDetectionReq : public V2gExiMessage
{
public:
  WeldingDetectionReq();
  virtual ~WeldingDetectionReq();
  void dumpMsg(void) override;

  void setDCEVStatus(DC_EVStatusType *status);
  DC_EVStatusType *getDCEVStatus();

  comparision_indicate_flag pDC_EVStatus_flag = has_value;

  bool operator==(WeldingDetectionReq &object_compare)
  {
    DC_EVStatusType *pDC_EVStatusCmp = object_compare.getDCEVStatus();
    bool final_result = true;
    switch (this->pDC_EVStatus_flag)
    {
    case specific:
      if ((pDC_EVStatusCmp != nullptr) && (this->pDC_EVStatus != nullptr))
      {
        final_result = (0 == memcmp(pDC_EVStatusCmp, this->pDC_EVStatus, sizeof(PhysicalValueType)));
      }
      else
      {
        final_result = false;
      }
      break;
    case has_value:
      if (pDC_EVStatusCmp == nullptr)
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
  DC_EVStatusType *pDC_EVStatus = nullptr;
};

#endif //EVCC_WELDINGDETECTIONREQ_H
