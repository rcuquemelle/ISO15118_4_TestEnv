

#include <string.h>
#include "messages/MeterReceiptReq.h"

#define SessionID_BYTES_SIZE 8
MeterReceiptReq::MeterReceiptReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_METERING_RECEIPT_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.MeteringReceiptReq_isUsed = 1u;
    init_iso1MeteringReceiptReqType(&mExiData.V2G_Message.Body.MeteringReceiptReq);
}

MeterReceiptReq::~MeterReceiptReq()
{
}

std::string MeterReceiptReq::getId(void)
{
    if (mExiData.V2G_Message.Body.MeteringReceiptReq.Id_isUsed == 1)
    {
        mId.assign(mExiData.V2G_Message.Body.MeteringReceiptReq.Id.characters, mExiData.V2G_Message.Body.MeteringReceiptReq.Id.charactersLen);
        return mId;
    }
    else
    {
        mId = "";
        return mId;
    }
}
void MeterReceiptReq::setId(const std::string &strId)
{
    mExiData.V2G_Message.Body.MeteringReceiptReq.Id_isUsed = 1;
    mExiData.V2G_Message.Body.MeteringReceiptReq.Id.charactersLen = strId.size();
    strncpy(mExiData.V2G_Message.Body.MeteringReceiptReq.Id.characters, strId.c_str(), strId.size());
    this->mId = strId;
}

void MeterReceiptReq::setFieldSessionID(const std::vector<uint8_t> &value)
{
    size_t len = 0;
    pSessionId.clear();
    if (value.size() > SessionID_BYTES_SIZE)
    {
        len = SessionID_BYTES_SIZE;
    }
    else
    {
        len = value.size();
    }
    for (size_t i = 0; i < len; i++)
    {
        pSessionId.push_back(value[i]);
        mExiData.V2G_Message.Body.MeteringReceiptReq.SessionID.bytes[i] = value[i];
    }
    mExiData.V2G_Message.Body.MeteringReceiptReq.SessionID.bytesLen = len;
}
std::vector<uint8_t> &MeterReceiptReq::getFieldSessionID(void)
{
    pSessionId.clear();
    for (size_t i = 0; i < mExiData.V2G_Message.Body.MeteringReceiptReq.SessionID.bytesLen; i++)
    {
        pSessionId.push_back(mExiData.V2G_Message.Body.MeteringReceiptReq.SessionID.bytes[i]);
    }
    return pSessionId;
}
uint16_t MeterReceiptReq::getSAScheduleTupleID()
{
    if (mExiData.V2G_Message.Body.MeteringReceiptReq.SAScheduleTupleID_isUsed == 1)
    {
        mSAScheduleTupleID = mExiData.V2G_Message.Body.MeteringReceiptReq.SAScheduleTupleID;
    }
    else
    {
        mSAScheduleTupleID = 0;
    }
    return mSAScheduleTupleID;
}

void MeterReceiptReq::setSAScheduleTupleID(uint16_t id)
{
    mExiData.V2G_Message.Body.MeteringReceiptReq.SAScheduleTupleID_isUsed = 1;
    mExiData.V2G_Message.Body.MeteringReceiptReq.SAScheduleTupleID = id;
    this->mSAScheduleTupleID = id;
}

MeterInfoType *MeterReceiptReq::getMeterInfo()
{
    return &mExiData.V2G_Message.Body.MeteringReceiptReq.MeterInfo;
}

void MeterReceiptReq::setMeterInfo(MeterInfoType *meter)
{
    if (nullptr != meter)
    {
        memcpy(&mExiData.V2G_Message.Body.MeteringReceiptReq.MeterInfo, meter, sizeof(MeterInfoType));
        pMeterInfo = &mExiData.V2G_Message.Body.MeteringReceiptReq.MeterInfo;
    }
    else
    {
        pMeterInfo = nullptr;
    }
}
void MeterReceiptReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    if (this->getId() != "")
    {
        outstr.append(fmt::format("  Id={}\n", this->getId()));
    }
    outstr.append(fmt::format("  SessionID={}\n", outHexString(this->getFieldSessionID())));
    outstr.append(fmt::format("  SAScheduleTupleID={}\n", getSAScheduleTupleID()));
    outstr.append(fmt::format("{}", getStrMeterInfo(this->getMeterInfo(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}