

#include <string.h>
#include "messages/CableCheckRes.h"

CableCheckRes::CableCheckRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_CABLE_CHECK_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CableCheckRes_isUsed = 1;
    init_iso1CableCheckResType(&mExiData.V2G_Message.Body.CableCheckRes);
}

CableCheckRes::CableCheckRes(std::shared_ptr<V2gExiMessage> &msg) : CableCheckRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

CableCheckRes::~CableCheckRes()
{
}

responseCodeType CableCheckRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.CableCheckRes.ResponseCode;
}

void CableCheckRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.CableCheckRes.ResponseCode = code;
}

DC_EVSEStatusType *CableCheckRes::getDCEVSEStatus()
{
    return &mExiData.V2G_Message.Body.CableCheckRes.DC_EVSEStatus;
}

void CableCheckRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        memcpy(&mExiData.V2G_Message.Body.CableCheckRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
    }
}

EVSEProcessingType CableCheckRes::getEVSEProcessing()
{
    return mExiData.V2G_Message.Body.CableCheckRes.EVSEProcessing;
}

void CableCheckRes::setEVSEProcessing(EVSEProcessingType proc)
{
    mExiData.V2G_Message.Body.CableCheckRes.EVSEProcessing = proc;
}

void CableCheckRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("{}\n", getStrDCEVSEStatus(this->getDCEVSEStatus(), "  ")));
    outstr.append(fmt::format("  EVSEProcessing={}", EVSEPROCESSING[this->getEVSEProcessing()]));
    Logging::info(LogMsgDump_ENABLE, outstr);
}