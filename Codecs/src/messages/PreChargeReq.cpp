

#include <string.h>
#include "messages/PreChargeReq.h"

PreChargeReq::PreChargeReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_PRE_CHARGE_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PreChargeReq_isUsed = 1u;
    init_iso1PreChargeReqType(&mExiData.V2G_Message.Body.PreChargeReq);
}

PreChargeReq::~PreChargeReq()
{
}

DC_EVStatusType *PreChargeReq::getDCEVStatus()
{
    return &mExiData.V2G_Message.Body.PreChargeReq.DC_EVStatus;
}

void PreChargeReq::setDCEVStatus(DC_EVStatusType *status)
{
    if (nullptr != status)
    {
        memcpy(&mExiData.V2G_Message.Body.PreChargeReq.DC_EVStatus, status, sizeof(DC_EVStatusType));
        this->pDC_EVStatus = &mExiData.V2G_Message.Body.PreChargeReq.DC_EVStatus;
    }
    else
    {
        this->pDC_EVStatus = nullptr;
    }
}

PhysicalValueType *PreChargeReq::getEVTargetVoltage()
{
    return &mExiData.V2G_Message.Body.PreChargeReq.EVTargetVoltage;
}

void PreChargeReq::setEVTargetVoltage(PhysicalValueType *voltage)
{
    if (nullptr != voltage)
    {
        memcpy(&mExiData.V2G_Message.Body.PreChargeReq.EVTargetVoltage, voltage, sizeof(PhysicalValueType));
        this->pEVTargetVoltage = &mExiData.V2G_Message.Body.PreChargeReq.EVTargetVoltage;
    }
    else
    {
        this->pEVTargetVoltage = nullptr;
    }
}

PhysicalValueType *PreChargeReq::getEVTargetCurrent()
{
    return &mExiData.V2G_Message.Body.PreChargeReq.EVTargetCurrent;
}

void PreChargeReq::setEVTargetCurrent(PhysicalValueType *current)
{
    if (nullptr != current)
    {
        memcpy(&mExiData.V2G_Message.Body.PreChargeReq.EVTargetCurrent, current, sizeof(PhysicalValueType));
        this->pEVTargetCurrent = &mExiData.V2G_Message.Body.PreChargeReq.EVTargetCurrent;
    }
    else
    {
        this->pEVTargetCurrent = nullptr;
    }
}
void PreChargeReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  EVTargetVoltage={0}\n", getStrPhysicalValue(this->getEVTargetVoltage())));
    outstr.append(fmt::format("  EVTargetCurrent={0}\n", getStrPhysicalValue(this->getEVTargetCurrent())));
    outstr.append(fmt::format("{0}", getStrDCEVStatus(this->getDCEVStatus(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}