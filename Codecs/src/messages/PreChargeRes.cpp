

#include <string.h>
#include "messages/PreChargeRes.h"

PreChargeRes::PreChargeRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_PRE_CHARGE_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PreChargeRes_isUsed = 1u;
    init_iso1PreChargeResType(&mExiData.V2G_Message.Body.PreChargeRes);
}

PreChargeRes::PreChargeRes(std::shared_ptr<V2gExiMessage> &msg) : PreChargeRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

PreChargeRes::~PreChargeRes()
{
}

responseCodeType PreChargeRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.PreChargeRes.ResponseCode;
}

void PreChargeRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.PreChargeRes.ResponseCode = code;
    this->mResponseCode = code;
}

DC_EVSEStatusType *PreChargeRes::getDCEVSEStatus()
{
    return &mExiData.V2G_Message.Body.PreChargeRes.DC_EVSEStatus;
}

void PreChargeRes::setDCEVSEStatus(DC_EVSEStatusType *status)
{
    if (nullptr != status)
    {
        memcpy(&mExiData.V2G_Message.Body.PreChargeRes.DC_EVSEStatus, status, sizeof(DC_EVSEStatusType));
        this->pDC_EVSEStatus = &mExiData.V2G_Message.Body.PreChargeRes.DC_EVSEStatus;
    }
    else
    {
        this->pDC_EVSEStatus = nullptr;
    }
}

PhysicalValueType *PreChargeRes::getEVSEPresentVoltage()
{
    return &mExiData.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage;
}

void PreChargeRes::setEVSEPresentVoltage(PhysicalValueType *voltage)
{
    if (nullptr != voltage)
    {
        memcpy(&mExiData.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage, voltage, sizeof(PhysicalValueType));
        this->pEVSEPresentVoltage = &mExiData.V2G_Message.Body.PreChargeRes.EVSEPresentVoltage;
    }
    else
    {
        this->pEVSEPresentVoltage = nullptr;
    }
}
void PreChargeRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  EVSEPresentVoltage={0}V\n", getPhysicalValue(this->getEVSEPresentVoltage())));
    outstr.append(fmt::format("{0}", getStrDCEVSEStatus(this->getDCEVSEStatus(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}