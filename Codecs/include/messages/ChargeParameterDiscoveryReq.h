

#ifndef EVCC_CHARGEPARAMETERDISCOVERYREQ_H
#define EVCC_CHARGEPARAMETERDISCOVERYREQ_H

#include "../V2gExiMessage.h"

class ChargeParameterDiscoveryReq : public V2gExiMessage
{
public:
  ChargeParameterDiscoveryReq();
  virtual ~ChargeParameterDiscoveryReq();
  void dumpMsg(void) override;

  void setMaxEntriesSAScheduleTuple(uint16_t number);
  int getMaxEntriesSAScheduleTuple();

  void setEnergyTransferModeReq(EnergyTransferModeType mode);
  EnergyTransferModeType getEnergyTransferModeReq();

  void setEVChargeParamter(EVChargeParameterType *params);
  EVChargeParameterType *getEVChargeParameter();

  void setACEVChargeParamter(AC_EVChargeParameterType *params);
  AC_EVChargeParameterType *getACEVChargeParameter();

  void setDCEVChargeParamter(DC_EVChargeParameterType *params);
  DC_EVChargeParameterType *getDCEVChargeParameter();

  comparision_indicate_flag mMaxEntriesSAScheduleTuple_flag = omit;
  comparision_indicate_flag mRequestedEnergyTransferMode_flag = has_value;
  comparision_indicate_flag pEVChargeParameter_flag = omit;
  comparision_indicate_flag pAC_EVChargeParameter_flag = omit;
  comparision_indicate_flag pDC_EVChargeParameter_flag = omit;

  bool operator==(ChargeParameterDiscoveryReq &object_compare)
  {
    bool arr_result[5] = {true, true, true, true, true};
    bool final_result = true;

    EVChargeParameterType *pEVChargeParameterCmp = object_compare.getEVChargeParameter();
    AC_EVChargeParameterType *pAC_EVChargeParameterCmp = object_compare.getACEVChargeParameter();
    DC_EVChargeParameterType *pDC_EVChargeParameterCmp = object_compare.getDCEVChargeParameter();

    switch (this->pEVChargeParameter_flag)
    {
    case specific:
      if ((pEVChargeParameterCmp != nullptr) && (this->getEVChargeParameter() != nullptr))
      {
        arr_result[0] = (0 == memcmp(pEVChargeParameterCmp, this->getEVChargeParameter(), sizeof(EVChargeParameterType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pEVChargeParameterCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pAC_EVChargeParameter_flag)
    {
    case specific:
      if ((pAC_EVChargeParameterCmp != nullptr) && (this->getACEVChargeParameter() != nullptr))
      {
        arr_result[1] = (0 == memcmp(pAC_EVChargeParameterCmp, this->getACEVChargeParameter(), sizeof(AC_EVChargeParameterType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pAC_EVChargeParameterCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pDC_EVChargeParameter_flag)
    {
    case specific:
      if ((pDC_EVChargeParameterCmp != nullptr) && (this->getDCEVChargeParameter() != nullptr))
      {
        arr_result[2] = (0 == memcmp(pDC_EVChargeParameterCmp, this->getDCEVChargeParameter(), sizeof(DC_EVChargeParameterType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pDC_EVChargeParameterCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mRequestedEnergyTransferMode_flag)
    {
    case specific:
      if (this->getEnergyTransferModeReq() != object_compare.getEnergyTransferModeReq())
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (object_compare.getEnergyTransferModeReq() > 6)
      {
        arr_result[3] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mMaxEntriesSAScheduleTuple_flag)
    {
    case specific:
      if (this->getMaxEntriesSAScheduleTuple() != object_compare.getMaxEntriesSAScheduleTuple())
      {
        arr_result[4] = false;
      }
      break;
    case has_value:
      if (object_compare.getMaxEntriesSAScheduleTuple() != -1)
      {
        arr_result[4] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 5; i++)
    {
      if (arr_result[i] == false)
      {
        final_result = false;
        break;
      }
    }
    return final_result;
  }
};

#endif //EVCC_CHARGEPARAMETERDISCOVERYREQ_H
