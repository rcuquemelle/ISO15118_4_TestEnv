#include "messages/CurrentDemandReq.h"

CurrentDemandReq::CurrentDemandReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_CURRENT_DEMAND_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CurrentDemandReq_isUsed = 1u;
    init_iso1CurrentDemandReqType(&mExiData.V2G_Message.Body.CurrentDemandReq);
}
CurrentDemandReq::CurrentDemandReq(std::shared_ptr<V2gExiMessage> &msg) : CurrentDemandReq()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}
CurrentDemandReq::~CurrentDemandReq()
{
}

DC_EVStatusType *CurrentDemandReq::getDcEvStatus()
{
    return &mExiData.V2G_Message.Body.CurrentDemandReq.DC_EVStatus;
}
void CurrentDemandReq::setDcEvStatus(DC_EVStatusType *status)
{
    if (nullptr != status)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.DC_EVStatus, status, sizeof(DC_EVStatusType));
}

PhysicalValueType *CurrentDemandReq::getEvTargetCurrent()
{
    return &mExiData.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent;
}
void CurrentDemandReq::setEvTargetCurrent(PhysicalValueType *current)
{
    if (nullptr != current)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.EVTargetCurrent, current, sizeof(PhysicalValueType));
}

PhysicalValueType *CurrentDemandReq::getEvTargetVoltage()
{
    return &mExiData.V2G_Message.Body.CurrentDemandReq.EVTargetVoltage;
}
void CurrentDemandReq::setEvTargetVoltage(PhysicalValueType *voltage)
{
    if (nullptr != voltage)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.EVTargetVoltage, voltage, sizeof(PhysicalValueType));
}

PhysicalValueType *CurrentDemandReq::getEvMaxVoltageLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumVoltageLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumVoltageLimit;
    }
    else
    {
        return nullptr;
    }
}
void CurrentDemandReq::setEvMaxVoltageLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumVoltageLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumVoltageLimit, value, sizeof(PhysicalValueType));
    }
}

PhysicalValueType *CurrentDemandReq::getEvMaxCurrentLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumCurrentLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumCurrentLimit;
    }
    else
    {
        return nullptr;
    }
}
void CurrentDemandReq::setEvMaxCurrentLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumCurrentLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumCurrentLimit, value, sizeof(PhysicalValueType));
    }
}

PhysicalValueType *CurrentDemandReq::getEvMaxPowerLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumPowerLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumPowerLimit;
    }
    else
    {
        return nullptr;
    }
}
void CurrentDemandReq::setEvMaxPowerLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumPowerLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.EVMaximumPowerLimit, value, sizeof(PhysicalValueType));
    }
}

int CurrentDemandReq::getBulkChargeCompleted()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete_isUsed == 1)
    {
        return mExiData.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete;
    }
    else
    {
        return -1;
    }
}
void CurrentDemandReq::setBulkChargeCompleteStatus(bool status)
{
    mExiData.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete_isUsed = 1;
    mExiData.V2G_Message.Body.CurrentDemandReq.BulkChargingComplete = status;
}

bool CurrentDemandReq::getChargingCompleted()
{
    return mExiData.V2G_Message.Body.CurrentDemandReq.ChargingComplete;
}
void CurrentDemandReq::setChargingCompleteStatus(bool status)
{
    mExiData.V2G_Message.Body.CurrentDemandReq.ChargingComplete = status;
}

void CurrentDemandReq::setBulkChargeRemainTime(PhysicalValueType *time)
{
    if (nullptr != time)
    {
        mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC, time, sizeof(PhysicalValueType));
    }
}
PhysicalValueType *CurrentDemandReq::getBulkChargeRemainTime()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToBulkSoC;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandReq::setFullChargeRemainTime(PhysicalValueType *time)
{
    if (nullptr != time)
    {
        mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC, time, sizeof(PhysicalValueType));
    }
}
PhysicalValueType *CurrentDemandReq::getFullChargeRemainTime()
{
    if (mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandReq.RemainingTimeToFullSoC;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("{}\n", getStrDCEVStatus(this->getDcEvStatus(), "  ")));
    outstr.append(fmt::format("  EVTargetCurrent={}\n"
                              "  EVTargetVoltage={}\n",
                              getStrPhysicalValue(this->getEvTargetCurrent()),
                              getStrPhysicalValue(this->getEvTargetVoltage())));
    if (nullptr != this->getEvMaxCurrentLimit())
    {
        outstr.append(fmt::format("  EVMaximumCurrentLimit={}\n",
                                  getStrPhysicalValue(this->getEvMaxCurrentLimit())));
    }
    if (nullptr != this->getEvMaxVoltageLimit())
    {
        outstr.append(fmt::format("  EVMaximumVoltageLimit={}\n",
                                  getStrPhysicalValue(this->getEvMaxVoltageLimit())));
    }
    if (nullptr != this->getEvMaxPowerLimit())
    {
        outstr.append(fmt::format("  EVMaximumPowerLimit={}\n",
                                  getStrPhysicalValue(this->getEvMaxPowerLimit())));
    }
    if (-1 != this->getBulkChargeCompleted())
    {
        outstr.append(fmt::format("  BulkChargingComplete={}\n", this->getBulkChargeCompleted()));
    }
    outstr.append(fmt::format("  ChargingComplete={}\n", this->getChargingCompleted()));
    if (nullptr != this->getBulkChargeRemainTime())
    {
        outstr.append(fmt::format("  RemainingTimeToBulkSoC={}\n",
                                  getStrPhysicalValue(this->getBulkChargeRemainTime())));
    }
    if (nullptr != this->getFullChargeRemainTime())
    {
        outstr.append(fmt::format("  RemainingTimeToFullSoC={}\n",
                                  getStrPhysicalValue(this->getFullChargeRemainTime())));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}