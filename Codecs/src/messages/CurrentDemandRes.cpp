#include <math.h>
#include "messages/CurrentDemandRes.h"

#define DATA_16_BITS_VALUE_MAX (uint16_t)(0xFFFF)

CurrentDemandRes::CurrentDemandRes() : V2gExiMessage(V2gExiMessage::V2G_MSG_CURRENT_DEMAND_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CurrentDemandRes_isUsed = 1u;
    init_iso1CurrentDemandResType(&mExiData.V2G_Message.Body.CurrentDemandRes);
}

CurrentDemandRes::CurrentDemandRes(std::shared_ptr<V2gExiMessage> &msg) : CurrentDemandRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

CurrentDemandRes::~CurrentDemandRes()
{
}

void CurrentDemandRes::setResponseCode(responseCodeType resp)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.ResponseCode = resp;
}
responseCodeType CurrentDemandRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.CurrentDemandRes.ResponseCode;
}

void CurrentDemandRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
}
DC_EVSEStatusType *CurrentDemandRes::getDCEVSEStatus()
{
    return &mExiData.V2G_Message.Body.CurrentDemandRes.DC_EVSEStatus;
}

void CurrentDemandRes::setEVSEPresentVoltage(PhysicalValueType *value)
{
    if (nullptr != value)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage, value, sizeof(PhysicalValueType));
}
PhysicalValueType *CurrentDemandRes::getEVSEPresentVoltage(void)
{
    return &mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPresentVoltage;
}

void CurrentDemandRes::setEVSEPresentCurrent(PhysicalValueType *value)
{
    if (nullptr != value)
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent, value, sizeof(PhysicalValueType));
}
PhysicalValueType *CurrentDemandRes::getEVSEPresentCurrent()
{
    return &mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPresentCurrent;
}

void CurrentDemandRes::setEVSECurrentLimitArchived(bool value)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.EVSECurrentLimitAchieved = value;
}
bool CurrentDemandRes::getEVSECurrentLimitArchived(void)
{
    return mExiData.V2G_Message.Body.CurrentDemandRes.EVSECurrentLimitAchieved;
}

void CurrentDemandRes::setEVSEVoltageLimitArchived(bool value)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.EVSEVoltageLimitAchieved = value;
}
bool CurrentDemandRes::getEVSEVoltageLimitArchived(void)
{
    return mExiData.V2G_Message.Body.CurrentDemandRes.EVSEVoltageLimitAchieved;
}

void CurrentDemandRes::setEVSEPowerLimitAchieved(bool value)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPowerLimitAchieved = value;
}
bool CurrentDemandRes::getEVSEPowerLimitAchieved(void)
{
    return mExiData.V2G_Message.Body.CurrentDemandRes.EVSEPowerLimitAchieved;
}

void CurrentDemandRes::setEVSEMaximumVoltageLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumVoltageLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumVoltageLimit, value, sizeof(PhysicalValueType));
    }
}
PhysicalValueType *CurrentDemandRes::getEVSEMaximumVoltageLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumVoltageLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumVoltageLimit;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandRes::setEVSEMaximumCurrentLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumCurrentLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumCurrentLimit, value, sizeof(PhysicalValueType));
    }
}
PhysicalValueType *CurrentDemandRes::getEVSEMaximumCurrentLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumCurrentLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumCurrentLimit;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandRes::setEVSEMaximumPowerLimit(PhysicalValueType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumPowerLimit_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumPowerLimit, value, sizeof(PhysicalValueType));
    }
}
PhysicalValueType *CurrentDemandRes::getEVSEMaximumPowerLimit()
{
    if (mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumPowerLimit_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandRes.EVSEMaximumPowerLimit;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandRes::setEVSEID(const std::string &id)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.EVSEID.charactersLen = id.size();
    memcpy(mExiData.V2G_Message.Body.CurrentDemandRes.EVSEID.characters, id.c_str(), id.size());
    this->mEVSEID = id;
}
std::string &CurrentDemandRes::getEVSEID(void)
{
    this->mEVSEID.assign((const char *)mExiData.V2G_Message.Body.CurrentDemandRes.EVSEID.characters, mExiData.V2G_Message.Body.CurrentDemandRes.EVSEID.charactersLen);
    return this->mEVSEID;
}

void CurrentDemandRes::setSAScheduleTupleID(uint8_t id)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.SAScheduleTupleID = id;
}
uint8_t CurrentDemandRes::getSAScheduleTupleID(void)
{
    return mExiData.V2G_Message.Body.CurrentDemandRes.SAScheduleTupleID;
}

void CurrentDemandRes::setMeterInfo(MeterInfoType *value)
{
    if (nullptr != value)
    {
        mExiData.V2G_Message.Body.CurrentDemandRes.MeterInfo_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.CurrentDemandRes.MeterInfo, value, sizeof(MeterInfoType));
    }
}
MeterInfoType *CurrentDemandRes::getMeterInfo(void)
{
    if (mExiData.V2G_Message.Body.CurrentDemandRes.MeterInfo_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.CurrentDemandRes.MeterInfo;
    }
    else
    {
        return nullptr;
    }
}

void CurrentDemandRes::setReceiptRequired(bool value)
{
    mExiData.V2G_Message.Body.CurrentDemandRes.ReceiptRequired_isUsed = 1;
    mExiData.V2G_Message.Body.CurrentDemandRes.ReceiptRequired = value;
}
int CurrentDemandRes::getReceiptRequired(void)
{
    if (mExiData.V2G_Message.Body.CurrentDemandRes.ReceiptRequired_isUsed == 1)
    {
        return mExiData.V2G_Message.Body.CurrentDemandRes.ReceiptRequired;
    }
    else
    {
        return -1;
    }
}
void CurrentDemandRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("{}\n", getStrDCEVSEStatus(this->getDCEVSEStatus(), "  ")));
    outstr.append(fmt::format("  EVSEPresentVoltage={}\n", getStrPhysicalValue(this->getEVSEPresentVoltage())));
    outstr.append(fmt::format("  EVSEPresentCurrent={}\n", getStrPhysicalValue(this->getEVSEPresentCurrent())));
    outstr.append(fmt::format("  EVSECurrentLimitAchieved={0}\n"
                              "  EVSEVoltageLimitAchieved={1}\n"
                              "  EVSEPowerLimitAchieved={2}\n",
                              this->getEVSECurrentLimitArchived(),
                              this->getEVSEVoltageLimitArchived(),
                              this->getEVSEPowerLimitAchieved()));
    if (nullptr != this->getEVSEMaximumVoltageLimit())
    {
        outstr.append(fmt::format("  EVSEMaximumVoltageLimit={}\n", getStrPhysicalValue(this->getEVSEMaximumVoltageLimit())));
    }
    if (nullptr != this->getEVSEMaximumCurrentLimit())
    {
        outstr.append(fmt::format("  EVSEMaximumCurrentLimit={}\n", getStrPhysicalValue(this->getEVSEMaximumCurrentLimit())));
    }
    if (nullptr != this->getEVSEMaximumPowerLimit())
    {
        outstr.append(fmt::format("  EVSEMaximumPowerLimit={}\n", getStrPhysicalValue(this->getEVSEMaximumPowerLimit())));
    }
    outstr.append(fmt::format("  EVSEID={}\n", this->getEVSEID()));
    outstr.append(fmt::format("  SAScheduleTupleID={}\n", this->getSAScheduleTupleID()));
    if (nullptr != this->getMeterInfo())
    {
        outstr.append(fmt::format("{}\n", getStrMeterInfo(this->getMeterInfo(), "  ")));
    }
    if (-1 != this->getReceiptRequired())
    {
        outstr.append(fmt::format("  ReceiptRequired={}\n", this->getReceiptRequired()));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}