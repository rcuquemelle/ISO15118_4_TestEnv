

#include <string.h>
#include "messages/PowerDeliveryRes.h"

PowerDeliveryRes::PowerDeliveryRes() : V2gExiMessage(V2G_MSG_POWER_DELIVERY_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PowerDeliveryRes_isUsed = 1u;
    init_iso1PowerDeliveryResType(&mExiData.V2G_Message.Body.PowerDeliveryRes);
}

PowerDeliveryRes::PowerDeliveryRes(std::shared_ptr<V2gExiMessage> &msg) : PowerDeliveryRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

PowerDeliveryRes::~PowerDeliveryRes()
{
}

responseCodeType PowerDeliveryRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.PowerDeliveryRes.ResponseCode;
}

void PowerDeliveryRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.PowerDeliveryRes.ResponseCode = code;
    this->mResponseCode = code;
}

AC_EVSEStatusType *PowerDeliveryRes::getACEVSEStatus()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryRes::setACEVSEStatus(AC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus, status, sizeof(AC_EVSEStatusType));
        this->pAC_EVSEStatus = &mExiData.V2G_Message.Body.PowerDeliveryRes.AC_EVSEStatus;
    }
    else
    {
        this->pAC_EVSEStatus = nullptr;
    }
}

EVSEStatusType *PowerDeliveryRes::getEVSEStatus()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryRes.EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryRes.EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryRes::setEVSEStatus(EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.PowerDeliveryRes.EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryRes.EVSEStatus, status, sizeof(EVSEStatusType));
        this->pEVSEStatus = &mExiData.V2G_Message.Body.PowerDeliveryRes.EVSEStatus;
    }
    else
    {
        this->pEVSEStatus = nullptr;
    }
}

DC_EVSEStatusType *PowerDeliveryRes::getDCEVSEStatus()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        mExiData.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
        this->pDC_EVSEStatus = &mExiData.V2G_Message.Body.PowerDeliveryRes.DC_EVSEStatus;
    }
    else
    {
        this->pDC_EVSEStatus = nullptr;
    }
}

void PowerDeliveryRes::dumpMsg(void)
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