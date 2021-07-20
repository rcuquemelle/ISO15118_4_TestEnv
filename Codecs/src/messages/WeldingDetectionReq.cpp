

#include <string.h>
#include "messages/WeldingDetectionReq.h"

WeldingDetectionReq::WeldingDetectionReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_WELDING_DETECTION_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.WeldingDetectionReq_isUsed = 1u;
    init_iso1WeldingDetectionReqType(&mExiData.V2G_Message.Body.WeldingDetectionReq);
}

WeldingDetectionReq::~WeldingDetectionReq()
{
}

void WeldingDetectionReq::setDCEVStatus(DC_EVStatusType *status)
{
    if (nullptr != status)
    {
        memcpy(&mExiData.V2G_Message.Body.WeldingDetectionReq.DC_EVStatus, status, sizeof(DC_EVStatusType));
        this->pDC_EVStatus = &mExiData.V2G_Message.Body.WeldingDetectionReq.DC_EVStatus;
    }
    else
    {
        this->pDC_EVStatus = nullptr;
    }
}
DC_EVStatusType *WeldingDetectionReq::getDCEVStatus()
{
    return &mExiData.V2G_Message.Body.WeldingDetectionReq.DC_EVStatus;
}

void WeldingDetectionReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("{0}", getStrDCEVStatus(this->getDCEVStatus(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}