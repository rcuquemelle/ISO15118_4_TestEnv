

#ifndef EVCC_POWERDELIVERYREQ_H
#define EVCC_POWERDELIVERYREQ_H

#include "../V2gExiMessage.h"

class PowerDeliveryReq : public V2gExiMessage
{
public:
  PowerDeliveryReq();
  virtual ~PowerDeliveryReq();
  void dumpMsg(void) override;
  chargeProgressType getChargeProgress();
  void setChargeProgress(chargeProgressType progress);

  uint16_t getSAScheduleTupleID();
  void setSAScheduleTupleID(uint16_t tupleId);

  ChargingProfileType *getChargingProfile();
  void setChargingProfile(ChargingProfileType *profile);

  DC_EVPowerDeliveryParameterType *getDCEVPowerDeliveryParameter();
  void setDCEVPowerDeliveryParameter(DC_EVPowerDeliveryParameterType *params);

  EVPowerDeliveryParameterType *getEVPowerDeliveryParameter();
  void setEVPowerDeliveryParameter(EVPowerDeliveryParameterType *params);

  comparision_indicate_flag mchargeProgress_flag = has_value;
  comparision_indicate_flag mSAScheduleTupleID_flag = has_value;
  comparision_indicate_flag pChargingProfile_flag = has_value;
  comparision_indicate_flag pDC_EVPowerDeliveryParameter_flag = has_value;
  comparision_indicate_flag pEVPowerDeliveryParameter_flag = omit;

  bool operator==(PowerDeliveryReq &object_compare)
  {
    bool arr_result[5] = {true, true, true, true, true};
    bool final_result = true;

    ChargingProfileType *pChargingProfileCmp = object_compare.getChargingProfile();
    DC_EVPowerDeliveryParameterType *pDC_EVPowerDeliveryParameterCmp = object_compare.getDCEVPowerDeliveryParameter();
    EVPowerDeliveryParameterType *pEVPowerDeliveryParameterCmp = object_compare.getEVPowerDeliveryParameter();

    switch (this->mchargeProgress_flag)
    {
    case specific:
      if (this->mchargeProgress != object_compare.getChargeProgress())
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (object_compare.getChargeProgress() > 2)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pChargingProfile_flag)
    {
    case specific:
      if ((pChargingProfileCmp != nullptr) && (this->getChargingProfile() != nullptr))
      {
        arr_result[1] = (0 == memcmp(pChargingProfileCmp, this->getChargingProfile(), sizeof(ChargingProfileType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (pChargingProfileCmp == nullptr)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pDC_EVPowerDeliveryParameter_flag)
    {
    case specific:
      if ((pDC_EVPowerDeliveryParameterCmp != nullptr) && (this->getDCEVPowerDeliveryParameter() != nullptr))
      {
        arr_result[2] = (0 == memcmp(pDC_EVPowerDeliveryParameterCmp, this->getDCEVPowerDeliveryParameter(), sizeof(DC_EVPowerDeliveryParameterType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pDC_EVPowerDeliveryParameterCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
      break;
    default:
      break;
    }
    switch (this->pEVPowerDeliveryParameter_flag)
    {
    case specific:
      if ((pEVPowerDeliveryParameterCmp != nullptr) && (this->getEVPowerDeliveryParameter() != nullptr))
      {
        arr_result[2] = (0 == memcmp(pEVPowerDeliveryParameterCmp, this->getEVPowerDeliveryParameter(), sizeof(EVPowerDeliveryParameterType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pEVPowerDeliveryParameterCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mSAScheduleTupleID_flag)
    {
    case specific:
      if (this->mSAScheduleTupleID != object_compare.getSAScheduleTupleID())
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (object_compare.getSAScheduleTupleID() == 0)
      {
        arr_result[3] = false;
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

private:
  chargeProgressType mchargeProgress = (chargeProgressType)3;
  uint16_t mSAScheduleTupleID = 0;
};

#endif //EVCC_POWERDELIVERYREQ_H
