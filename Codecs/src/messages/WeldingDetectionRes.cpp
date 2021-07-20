

#include <string.h>
#include "messages/WeldingDetectionRes.h"

WeldingDetectionRes::WeldingDetectionRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_WELDING_DETECTION_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.WeldingDetectionRes_isUsed = 1u;
    init_iso1WeldingDetectionResType(&mExiData.V2G_Message.Body.WeldingDetectionRes);
}

WeldingDetectionRes::WeldingDetectionRes(std::shared_ptr<V2gExiMessage> &msg) : WeldingDetectionRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

WeldingDetectionRes::~WeldingDetectionRes()
{
}

void WeldingDetectionRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.WeldingDetectionRes.ResponseCode = code;
    this->mResponseCode = code;
}
responseCodeType WeldingDetectionRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.WeldingDetectionRes.ResponseCode;
}

void WeldingDetectionRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        memcpy(&mExiData.V2G_Message.Body.WeldingDetectionRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
        this->pDC_EVSEStatus = &mExiData.V2G_Message.Body.WeldingDetectionRes.DC_EVSEStatus;
    }
    else
    {
        this->pDC_EVSEStatus = nullptr;
    }
}
DC_EVSEStatusType *WeldingDetectionRes::getDCEVSEStatus()
{
    return &mExiData.V2G_Message.Body.WeldingDetectionRes.DC_EVSEStatus;
}

void WeldingDetectionRes::setEVSEPresentVoltage(PhysicalValueType *voltage)
{
    if (nullptr != voltage)
    {
        memcpy(&mExiData.V2G_Message.Body.WeldingDetectionRes.EVSEPresentVoltage, voltage, sizeof(PhysicalValueType));
        this->pEVSEPresentVoltage = &mExiData.V2G_Message.Body.WeldingDetectionRes.EVSEPresentVoltage;
    }
    else
    {
        this->pEVSEPresentVoltage = nullptr;
    }
}
PhysicalValueType *WeldingDetectionRes::getEVSEPresentVoltage()
{
    return &mExiData.V2G_Message.Body.WeldingDetectionRes.EVSEPresentVoltage;
}

void WeldingDetectionRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  EVSEPresentVoltage={0}V\n", getPhysicalValue(this->getEVSEPresentVoltage())));
    outstr.append(fmt::format("{0}", getStrDCEVSEStatus(this->getDCEVSEStatus(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}