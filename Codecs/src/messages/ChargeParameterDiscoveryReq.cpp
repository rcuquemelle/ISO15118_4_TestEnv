

#include <string.h>
#include "messages/ChargeParameterDiscoveryReq.h"

ChargeParameterDiscoveryReq::ChargeParameterDiscoveryReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_CHARGE_PARAMETER_DISCOVERY_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed = 1u;
    init_iso1ChargeParameterDiscoveryReqType(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq);
}

ChargeParameterDiscoveryReq::~ChargeParameterDiscoveryReq()
{
}

void ChargeParameterDiscoveryReq::setMaxEntriesSAScheduleTuple(uint16_t number)
{
    ChargeParameterDiscoveryReqType *req = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq;
    req->MaxEntriesSAScheduleTuple_isUsed = 1;
    req->MaxEntriesSAScheduleTuple = number;
}
int ChargeParameterDiscoveryReq::getMaxEntriesSAScheduleTuple()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.MaxEntriesSAScheduleTuple_isUsed == 1)
    {
        return mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.MaxEntriesSAScheduleTuple;
    }
    else
    {
        return -1;
    }
}

EnergyTransferModeType ChargeParameterDiscoveryReq::getEnergyTransferModeReq()
{
    return mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.RequestedEnergyTransferMode;
}
void ChargeParameterDiscoveryReq::setEnergyTransferModeReq(EnergyTransferModeType mode)
{
    mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.RequestedEnergyTransferMode = mode;
}

EVChargeParameterType *ChargeParameterDiscoveryReq::getEVChargeParameter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.EVChargeParameter_isUsed == 1)
    {
        ChargeParameterDiscoveryReqType *req = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq;
        return &req->EVChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryReq::setEVChargeParamter(EVChargeParameterType *params)
{
    ChargeParameterDiscoveryReqType *req = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq;
    if (nullptr != params)
    {
        req->EVChargeParameter_isUsed = 1;
        memcpy(&req->EVChargeParameter, params, sizeof(EVChargeParameterType));
    }
}

AC_EVChargeParameterType *ChargeParameterDiscoveryReq::getACEVChargeParameter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryReq::setACEVChargeParamter(AC_EVChargeParameterType *params)
{
    ChargeParameterDiscoveryReqType *req = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq;
    if (nullptr != params)
    {
        req->AC_EVChargeParameter_isUsed = 1;
        memcpy(&req->AC_EVChargeParameter, params, sizeof(AC_EVChargeParameterType));
    }
}

DC_EVChargeParameterType *ChargeParameterDiscoveryReq::getDCEVChargeParameter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryReq::setDCEVChargeParamter(DC_EVChargeParameterType *params)
{
    ChargeParameterDiscoveryReqType *req = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq;
    if (nullptr != params)
    {
        req->DC_EVChargeParameter_isUsed = 1;
        memcpy(&req->DC_EVChargeParameter, params, sizeof(DC_EVChargeParameterType));
    }
}

void ChargeParameterDiscoveryReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    if (this->getMaxEntriesSAScheduleTuple() != -1)
    {
        outstr.append(fmt::format("  MaxEntriesSAScheduleTuple={}\n", this->getMaxEntriesSAScheduleTuple()));
    }
    outstr.append(fmt::format("  RequestedEnergyTransferMode={}\n", ENERGY_TRANSFER_MODE[this->getEnergyTransferModeReq()]));
    if (nullptr != this->getEVChargeParameter())
    {
        outstr.append(fmt::format("{}\n", getStrEVChargeParameter(this->getEVChargeParameter(), "  ")));
    }
    if (nullptr != this->getACEVChargeParameter())
    {
        outstr.append(fmt::format("{}\n", getStrACEVChargeParameter(this->getACEVChargeParameter(), "  ")));
    }
    if (nullptr != this->getDCEVChargeParameter())
    {
        outstr.append(fmt::format("{}\n", getStrDCEVChargeParameter(this->getDCEVChargeParameter(), "  ")));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}