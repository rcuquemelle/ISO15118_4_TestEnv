#ifndef __CURRENT_DEMAND_RES_H_
#define __CURRENT_DEMAND_RES_H_

#include <string.h>
#include "../V2gExiMessage.h"

class CurrentDemandRes : public V2gExiMessage
{
public:
    CurrentDemandRes();
    CurrentDemandRes(std::shared_ptr<V2gExiMessage> &msg);
    virtual ~CurrentDemandRes();

    responseCodeType getResponseCode(void);
    void setResponseCode(responseCodeType resp);

    DC_EVSEStatusType *getDCEVSEStatus(void);
    void setDCEVSEStatus(DC_EVSEStatusType *status);

    PhysicalValueType *getEVSEPresentVoltage(void);
    void setEVSEPresentVoltage(PhysicalValueType *value);

    PhysicalValueType *getEVSEPresentCurrent();
    void setEVSEPresentCurrent(PhysicalValueType *value);

    bool getEVSECurrentLimitArchived(void);
    void setEVSECurrentLimitArchived(bool value);

    bool getEVSEVoltageLimitArchived(void);
    void setEVSEVoltageLimitArchived(bool value);

    bool getEVSEPowerLimitAchieved(void);
    void setEVSEPowerLimitAchieved(bool value);

    PhysicalValueType *getEVSEMaximumVoltageLimit();
    void setEVSEMaximumVoltageLimit(PhysicalValueType *value);

    PhysicalValueType *getEVSEMaximumCurrentLimit();
    void setEVSEMaximumCurrentLimit(PhysicalValueType *value);

    PhysicalValueType *getEVSEMaximumPowerLimit();
    void setEVSEMaximumPowerLimit(PhysicalValueType *value);

    std::string &getEVSEID(void);
    void setEVSEID(const std::string &id);

    uint8_t getSAScheduleTupleID(void);
    void setSAScheduleTupleID(uint8_t id);

    MeterInfoType *getMeterInfo(void);
    void setMeterInfo(MeterInfoType *value);

    int getReceiptRequired(void);
    void setReceiptRequired(bool value);

    void dumpMsg(void) override;
    comparision_indicate_flag mResponseCode_flag = specific;
    comparision_indicate_flag pDCEVSEStatus_flag = has_value;
    comparision_indicate_flag pEVSEPresentVoltage_flag = has_value;
    comparision_indicate_flag pEVSEPresentCurrent_flag = has_value;
    comparision_indicate_flag mEVSECurrentLimitArchived_flag = has_value;
    comparision_indicate_flag mEVSEVoltageLimitArchived_flag = has_value;
    comparision_indicate_flag mEVSEPowerLimitAchieved_flag = has_value;
    comparision_indicate_flag pEVSEMaximumVoltageLimit_flag = omit;
    comparision_indicate_flag pEVSEMaximumCurrentLimit_flag = omit;
    comparision_indicate_flag pEVSEMaximumPowerLimit_flag = omit;
    comparision_indicate_flag pEVSEID_flag = has_value;
    comparision_indicate_flag mSAScheduleTupleID_flag = has_value;
    comparision_indicate_flag pMeterInfo_flag = omit;
    comparision_indicate_flag mReceiptRequired_flag = omit;

    bool operator==(CurrentDemandRes &object_compare)
    {
        bool result = true;
        result &= !((this->mResponseCode_flag == specific) && (this->getResponseCode() != object_compare.getResponseCode()));
        result &= !((this->mEVSECurrentLimitArchived_flag == specific) && (this->getEVSECurrentLimitArchived() != object_compare.getEVSECurrentLimitArchived()));
        result &= !((this->mEVSEVoltageLimitArchived_flag == specific) && (this->getEVSEVoltageLimitArchived() != object_compare.getEVSEVoltageLimitArchived()));
        result &= !((this->mEVSEPowerLimitAchieved_flag == specific) && (this->getEVSEPowerLimitAchieved() != object_compare.getEVSEPowerLimitAchieved()));
        result &= !((this->mSAScheduleTupleID_flag == specific) && (this->getSAScheduleTupleID() != object_compare.getSAScheduleTupleID()));
        result &= !((this->mReceiptRequired_flag == specific) && (this->getReceiptRequired() != object_compare.getReceiptRequired()));

        switch (this->pDCEVSEStatus_flag)
        {
        case specific:
        {
            if ((nullptr != this->getDCEVSEStatus()) && (nullptr != object_compare.getDCEVSEStatus()))
            {
                result &= (0 == memcmp(this->getDCEVSEStatus(), object_compare.getDCEVSEStatus(), sizeof(DC_EVSEStatusType)));
            }
            else
            {
                result &= false;
            }
            break;
        }
        case has_value:
        {
            result &= (nullptr != object_compare.getDCEVSEStatus());
            break;
        }
        case omit:
        default:
            break;
        }
        switch (this->pEVSEID_flag)
        {
        case specific:
        {
            result &= (0 == (this->getEVSEID()).compare(object_compare.getEVSEID()));
            break;
        }
        case has_value:
        {
            result &= (object_compare.getEVSEID().size() != 0);
            break;
        }
        case omit:
        default:
            break;
        }
        switch (this->pMeterInfo_flag)
        {
        case specific:
        {
            if ((nullptr != this->getMeterInfo()) && (nullptr != object_compare.getMeterInfo()))
            {
                result &= (0 == memcmp(this->getMeterInfo(), object_compare.getMeterInfo(), sizeof(MeterInfoType)));
            }
            else
            {
                result &= false;
            }
            break;
        }
        case has_value:
        {
            result &= (nullptr != object_compare.getMeterInfo());
            break;
        }
        case omit:
        default:
            break;
        }
        comparision_indicate_flag temp_arr[5] = {pEVSEPresentVoltage_flag, pEVSEPresentCurrent_flag, pEVSEMaximumVoltageLimit_flag, pEVSEMaximumCurrentLimit_flag, pEVSEMaximumPowerLimit_flag};
        PhysicalValueType *temp_arr2[5] = {object_compare.getEVSEPresentVoltage(), object_compare.getEVSEPresentCurrent(), object_compare.getEVSEMaximumVoltageLimit(),
                                           object_compare.getEVSEMaximumCurrentLimit(), object_compare.getEVSEMaximumPowerLimit()};
        PhysicalValueType *temp_arr3[5] = {this->getEVSEPresentVoltage(), this->getEVSEPresentCurrent(), this->getEVSEMaximumVoltageLimit(),
                                           this->getEVSEMaximumCurrentLimit(), this->getEVSEMaximumPowerLimit()};
        for (uint8_t i = 0; i < 5; i++)
        {
            switch (temp_arr[i])
            {
            case specific:
            {
                if ((nullptr != temp_arr3[i]) && (nullptr != temp_arr2[i]))
                {
                    result &= (0 == memcmp(temp_arr3[i], temp_arr2[i], sizeof(PhysicalValueType)));
                }
                else
                {
                    result &= false;
                }
            }
            break;
            case has_value:
            {
                result &= (nullptr != temp_arr3[i]);
            }
            break;
            case omit:
            default:
                break;
            }
        }
        return result;
    }

private:
    std::string mEVSEID;
};

#endif //__CURRENT_DEMAND_RES_H_