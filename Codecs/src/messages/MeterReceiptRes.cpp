

#include <string.h>
#include "messages/MeterReceiptRes.h"

MeterReceiptRes::MeterReceiptRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_METERING_RECEIPT_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.MeteringReceiptRes_isUsed = 1u;
    init_iso1MeteringReceiptResType(&mExiData.V2G_Message.Body.MeteringReceiptRes);
}

MeterReceiptRes::MeterReceiptRes(std::shared_ptr<V2gExiMessage> &msg) : MeterReceiptRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

MeterReceiptRes::~MeterReceiptRes()
{
}

responseCodeType MeterReceiptRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.MeteringReceiptRes.ResponseCode;
}

void MeterReceiptRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.MeteringReceiptRes.ResponseCode = code;
    mResponseCode = code;
}

AC_EVSEStatusType *MeterReceiptRes::getACEVSEStatus()
{
    if (mExiData.V2G_Message.Body.MeteringReceiptRes.AC_EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.MeteringReceiptRes.AC_EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}

void MeterReceiptRes::setACEVSEStatus(AC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.MeteringReceiptRes.AC_EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.MeteringReceiptRes.AC_EVSEStatus, status, sizeof(AC_EVSEStatusType));
        this->pAC_EVSEStatus = &mExiData.V2G_Message.Body.MeteringReceiptRes.AC_EVSEStatus;
    }
    else
    {
        this->pAC_EVSEStatus = nullptr;
    }
}

DC_EVSEStatusType *MeterReceiptRes::getDCEVSEStatus()
{
    if (mExiData.V2G_Message.Body.MeteringReceiptRes.DC_EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.MeteringReceiptRes.DC_EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}
void MeterReceiptRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.MeteringReceiptRes.DC_EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.MeteringReceiptRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
        this->pDC_EVSEStatus = &mExiData.V2G_Message.Body.MeteringReceiptRes.DC_EVSEStatus;
    }
    else
    {
        this->pDC_EVSEStatus = nullptr;
    }
}

EVSEStatusType *MeterReceiptRes::getEVSEStatus()
{
    if (mExiData.V2G_Message.Body.MeteringReceiptRes.EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.MeteringReceiptRes.EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}
void MeterReceiptRes::setEVSEStatus(EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.MeteringReceiptRes.EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.MeteringReceiptRes.EVSEStatus, status, sizeof(EVSEStatusType));
        this->pEVSEStatus = &mExiData.V2G_Message.Body.MeteringReceiptRes.EVSEStatus;
    }
    else
    {
        this->pEVSEStatus = nullptr;
    }
}
void MeterReceiptRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    if (nullptr != this->getEVSEStatus())
    {
        outstr.append(fmt::format("{}\n", getStrEVSEStatus(this->getEVSEStatus(), "  ")));
    }
    if (nullptr != this->getACEVSEStatus())
    {
        outstr.append(fmt::format("{}\n", getStrACEVSEStatus(this->getACEVSEStatus(), "  ")));
    }
    if (nullptr != this->getDCEVSEStatus())
    {
        outstr.append(fmt::format("{}\n", getStrDCEVSEStatus(this->getDCEVSEStatus(), "  ")));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}