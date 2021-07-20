

#ifndef EVCC_PRECHARGEREQ_H
#define EVCC_PRECHARGEREQ_H

#include "../V2gExiMessage.h"

class PreChargeReq : public V2gExiMessage
{
public:
  PreChargeReq();
  virtual ~PreChargeReq();
  void dumpMsg(void) override;
  DC_EVStatusType *getDCEVStatus();
  void setDCEVStatus(DC_EVStatusType *status);
  PhysicalValueType *getEVTargetVoltage();
  void setEVTargetVoltage(PhysicalValueType *voltage);
  PhysicalValueType *getEVTargetCurrent();
  void setEVTargetCurrent(PhysicalValueType *voltage);

  comparision_indicate_flag pDC_EVStatus_flag = has_value;
  comparision_indicate_flag pEVTargetVoltage_flag = has_value;
  comparision_indicate_flag pEVTargetCurrent_flag = has_value;

  bool operator==(PreChargeReq &object_compare)
  {
    bool arr_result[3] = {true, true, true};
    bool final_result = true;

    DC_EVStatusType *pDC_EVStatusCmp = object_compare.getDCEVStatus();
    PhysicalValueType *pEVTargetVoltageCmp = object_compare.getEVTargetVoltage();
    PhysicalValueType *pEVTargetCurrentCmp = object_compare.getEVTargetCurrent();

    switch (this->pDC_EVStatus_flag)
    {
    case specific:
      if ((pDC_EVStatusCmp != nullptr) && (this->pDC_EVStatus != nullptr))
      {
        arr_result[0] = (0 == memcmp(pDC_EVStatusCmp, this->pDC_EVStatus, sizeof(DC_EVStatusType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pDC_EVStatusCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pEVTargetVoltage_flag)
    {
    case specific:
      if ((pEVTargetVoltageCmp != nullptr) && (this->pEVTargetVoltage != nullptr))
      {
        arr_result[1] = (0 == memcmp(pEVTargetVoltageCmp, this->pEVTargetVoltage, sizeof(PhysicalValueType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pEVTargetVoltageCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pEVTargetCurrent_flag)
    {
    case specific:
      if ((pEVTargetCurrentCmp != nullptr) && (this->pEVTargetCurrent != nullptr))
      {
        arr_result[2] = (0 == memcmp(pEVTargetCurrentCmp, this->pEVTargetCurrent, sizeof(PhysicalValueType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pEVTargetCurrentCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 1; i < 3; i++)
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
  DC_EVStatusType *pDC_EVStatus = nullptr;
  PhysicalValueType *pEVTargetVoltage = nullptr;
  PhysicalValueType *pEVTargetCurrent = nullptr;
};

#endif //EVCC_PRECHARGEREQ_H
