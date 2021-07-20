//
// Created by james on 19/10/2020.
//

#include <string.h>
#include "messages/ChargingStatusRes.h"

ChargingStatusRes::ChargingStatusRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_CHARGING_STATUS_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ChargingStatusRes_isUsed = 1u;
    init_iso1ChargingStatusResType(&mExiData.V2G_Message.Body.ChargingStatusRes);
}

ChargingStatusRes::ChargingStatusRes(std::shared_ptr<V2gExiMessage> &msg) : ChargingStatusRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

ChargingStatusRes::~ChargingStatusRes()
{
}

responseCodeType ChargingStatusRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.ChargingStatusRes.ResponseCode;
}
void ChargingStatusRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.ChargingStatusRes.ResponseCode = code;
}

std::string &ChargingStatusRes::getEVSEID()
{
    mEVSEID.assign(mExiData.V2G_Message.Body.ChargingStatusRes.EVSEID.characters, mExiData.V2G_Message.Body.ChargingStatusRes.EVSEID.charactersLen);
    return mEVSEID;
}
void ChargingStatusRes::setEVSEID(const std::string &id)
{
    mExiData.V2G_Message.Body.ChargingStatusRes.EVSEID.charactersLen = id.size();
    memcpy(mExiData.V2G_Message.Body.ChargingStatusRes.EVSEID.characters, id.c_str(),
           mExiData.V2G_Message.Body.ChargingStatusRes.EVSEID.charactersLen);
    this->mEVSEID = id;
}

uint16_t ChargingStatusRes::getSAScheduleTupleID()
{
    return mExiData.V2G_Message.Body.ChargingStatusRes.SAScheduleTupleID;
}
void ChargingStatusRes::setSAScheduleTupleID(uint16_t id)
{
    mExiData.V2G_Message.Body.ChargingStatusRes.SAScheduleTupleID = id;
}

PhysicalValueType *ChargingStatusRes::getEVSEMaxCurrent()
{
    if (mExiData.V2G_Message.Body.ChargingStatusRes.EVSEMaxCurrent_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargingStatusRes.EVSEMaxCurrent;
    }
    else
    {
        return nullptr;
    }
}
void ChargingStatusRes::setEVSEMaxCurrent(PhysicalValueType *maxCurrent)
{
    if (nullptr != maxCurrent)
    {
        mExiData.V2G_Message.Body.ChargingStatusRes.EVSEMaxCurrent_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargingStatusRes.EVSEMaxCurrent, maxCurrent, sizeof(PhysicalValueType));
    }
}

MeterInfoType *ChargingStatusRes::getMeterInfo()
{
    if (mExiData.V2G_Message.Body.ChargingStatusRes.MeterInfo_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargingStatusRes.MeterInfo;
    }
    else
    {
        return nullptr;
    }
}

void ChargingStatusRes::setMeterInfo(MeterInfoType *meterInfo)
{
    if (nullptr != meterInfo)
    {
        mExiData.V2G_Message.Body.ChargingStatusRes.MeterInfo_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargingStatusRes.MeterInfo, meterInfo, sizeof(MeterInfoType));
    }
}

int ChargingStatusRes::getReceiptRequired()
{
    if (mExiData.V2G_Message.Body.ChargingStatusRes.ReceiptRequired_isUsed == 1)
    {
        return mExiData.V2G_Message.Body.ChargingStatusRes.ReceiptRequired;
    }
    else
    {
        return -1;
    }
}

void ChargingStatusRes::setReceiptRequired(int value)
{
    mExiData.V2G_Message.Body.ChargingStatusRes.ReceiptRequired_isUsed = 1;
    mExiData.V2G_Message.Body.ChargingStatusRes.ReceiptRequired = value;
}

AC_EVSEStatusType *ChargingStatusRes::getACEVSEStatus()
{
    return &mExiData.V2G_Message.Body.ChargingStatusRes.AC_EVSEStatus;
}
void ChargingStatusRes::setACEVSEStatus(AC_EVSEStatusType *status)
{
    if (nullptr != status)
        memcpy(&mExiData.V2G_Message.Body.ChargingStatusRes.AC_EVSEStatus, status, sizeof(AC_EVSEStatusType));
}

void ChargingStatusRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  EVSEID={}\n", this->getEVSEID()));
    outstr.append(fmt::format("  SAScheduleTupleID={}\n", this->getSAScheduleTupleID()));
    outstr.append(fmt::format("{}\n", getStrACEVSEStatus(this->getACEVSEStatus(), "  ")));
    if (nullptr != this->getEVSEMaxCurrent())
    {
        outstr.append(fmt::format("  EVSEMaxCurrent={}\n", getStrPhysicalValue(this->getEVSEMaxCurrent())));
    }
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