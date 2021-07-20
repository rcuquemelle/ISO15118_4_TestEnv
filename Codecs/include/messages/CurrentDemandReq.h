#ifndef __CURRENT_DEMAND_REQ_H_
#define __CURRENT_DEMAND_REQ_H_

#include "../V2gExiMessage.h"

class CurrentDemandReq : public V2gExiMessage
{
public:
    CurrentDemandReq();
    CurrentDemandReq(std::shared_ptr<V2gExiMessage> &msg);
    virtual ~CurrentDemandReq();

    DC_EVStatusType *getDcEvStatus();
    void setDcEvStatus(DC_EVStatusType *status);

    PhysicalValueType *getEvTargetCurrent();
    void setEvTargetCurrent(PhysicalValueType *current);

    PhysicalValueType *getEvTargetVoltage();
    void setEvTargetVoltage(PhysicalValueType *voltage);

    PhysicalValueType *getEvMaxVoltageLimit();
    void setEvMaxVoltageLimit(PhysicalValueType *value);

    PhysicalValueType *getEvMaxCurrentLimit();
    void setEvMaxCurrentLimit(PhysicalValueType *value);

    PhysicalValueType *getEvMaxPowerLimit();
    void setEvMaxPowerLimit(PhysicalValueType *value);

    int getBulkChargeCompleted();
    void setBulkChargeCompleteStatus(bool status);

    bool getChargingCompleted();
    void setChargingCompleteStatus(bool status);

    void setBulkChargeRemainTime(PhysicalValueType *time);
    PhysicalValueType *getBulkChargeRemainTime();

    void setFullChargeRemainTime(PhysicalValueType *time);
    PhysicalValueType *getFullChargeRemainTime();

    void dumpMsg(void) override;

    comparision_indicate_flag pDcEvStatus_flag = has_value;
    comparision_indicate_flag pEvTargetCurrent_flag = has_value;
    comparision_indicate_flag pEvTargetVoltage_flag = has_value;
    comparision_indicate_flag mEvMaxVoltageLimit_flag = omit;
    comparision_indicate_flag mEvMaxCurrentLimit_flag = omit;
    comparision_indicate_flag mEvMaxPowerLimit_flag = omit;
    comparision_indicate_flag mBulkChargeCompleted_flag = omit;
    comparision_indicate_flag mChargingCompleted_flag = specific;
    comparision_indicate_flag mBulkChargeRemainTime_flag = omit;
    comparision_indicate_flag mFullChargeRemainTime_flag = omit;

    bool operator==(CurrentDemandReq &object_compare)
    {
        bool result = true;
        result &= !((this->mBulkChargeCompleted_flag == specific) && (this->getBulkChargeCompleted() != object_compare.getBulkChargeCompleted()));
        result &= !((this->mChargingCompleted_flag == specific) && (this->getChargingCompleted() != object_compare.getChargingCompleted()));

        switch (this->pDcEvStatus_flag)
        {
        case specific:
            result &= (0 == memcmp(this->getDcEvStatus(), object_compare.getDcEvStatus(), sizeof(DC_EVStatusType)));
            break;
        case has_value:
            result &= (nullptr != object_compare.getDcEvStatus());
            break;
        case omit:
        default:
            break;
        }
#define SIZE_FLAG_ARR 7
        comparision_indicate_flag temp_arr[SIZE_FLAG_ARR] = {pEvTargetCurrent_flag, pEvTargetVoltage_flag,
                                                             mEvMaxVoltageLimit_flag, mEvMaxCurrentLimit_flag,
                                                             mEvMaxPowerLimit_flag, mBulkChargeRemainTime_flag,
                                                             mFullChargeRemainTime_flag};
        PhysicalValueType *temp_arr2[SIZE_FLAG_ARR] = {object_compare.getEvTargetCurrent(),
                                                       object_compare.getEvTargetVoltage(), object_compare.getEvMaxVoltageLimit(),
                                                       object_compare.getEvMaxCurrentLimit(), object_compare.getEvMaxPowerLimit(),
                                                       object_compare.getBulkChargeRemainTime(), object_compare.getFullChargeRemainTime()};
        PhysicalValueType *temp_arr3[SIZE_FLAG_ARR] = {this->getEvTargetCurrent(),
                                                       this->getEvTargetVoltage(), this->getEvMaxVoltageLimit(),
                                                       this->getEvMaxCurrentLimit(), this->getEvMaxPowerLimit(),
                                                       this->getBulkChargeRemainTime(), this->getFullChargeRemainTime()};
        for (uint8_t i = 0; i < SIZE_FLAG_ARR; i++)
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
};

#endif //__CURRENT_DEMAND_REQ_H_
