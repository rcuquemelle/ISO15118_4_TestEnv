

#include <string.h>
#include "messages/PowerDeliveryReq.h"

PowerDeliveryReq::PowerDeliveryReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_POWER_DELIVERY_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PowerDeliveryReq_isUsed = 1u;
    init_iso1PowerDeliveryReqType(&mExiData.V2G_Message.Body.PowerDeliveryReq);
}

PowerDeliveryReq::~PowerDeliveryReq()
{
}

chargeProgressType PowerDeliveryReq::getChargeProgress()
{
    return mExiData.V2G_Message.Body.PowerDeliveryReq.ChargeProgress;
}
void PowerDeliveryReq::setChargeProgress(chargeProgressType progress)
{
    mExiData.V2G_Message.Body.PowerDeliveryReq.ChargeProgress = progress;
    this->mchargeProgress = progress;
}

uint16_t PowerDeliveryReq::getSAScheduleTupleID()
{
    return mExiData.V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID;
}
void PowerDeliveryReq::setSAScheduleTupleID(uint16_t tupleId)
{
    mExiData.V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID = tupleId;
    this->mSAScheduleTupleID = tupleId;
}

DC_EVPowerDeliveryParameterType *PowerDeliveryReq::getDCEVPowerDeliveryParameter()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryReq::setDCEVPowerDeliveryParameter(DC_EVPowerDeliveryParameterType *params)
{
    if (nullptr != params)
    {
        mExiData.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryReq.DC_EVPowerDeliveryParameter, params, sizeof(DC_EVPowerDeliveryParameterType));
    }
}

EVPowerDeliveryParameterType *PowerDeliveryReq::getEVPowerDeliveryParameter()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryReq::setEVPowerDeliveryParameter(EVPowerDeliveryParameterType *params)
{
    if (nullptr != params)
    {
        mExiData.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryReq.EVPowerDeliveryParameter, params, sizeof(EVPowerDeliveryParameterType));
    }
}

ChargingProfileType *PowerDeliveryReq::getChargingProfile()
{
    if (mExiData.V2G_Message.Body.PowerDeliveryReq.ChargingProfile_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.PowerDeliveryReq.ChargingProfile;
    }
    else
    {
        return nullptr;
    }
}
void PowerDeliveryReq::setChargingProfile(ChargingProfileType *profile)
{
    if (nullptr != profile)
    {
        mExiData.V2G_Message.Body.PowerDeliveryReq.ChargingProfile_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.PowerDeliveryReq.ChargingProfile, profile, sizeof(ChargingProfileType));
    }
}

void PowerDeliveryReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ChargeProgress={0}\n"
                              "  SAScheduleTupleID={1}\n",
                              CHARGE_PROGRESS[this->getChargeProgress()],
                              this->getSAScheduleTupleID()));
    if (nullptr != this->getChargingProfile())
    {
        outstr.append(fmt::format("{}\n", getStrChargingProfile(this->getChargingProfile(), "  ")));
    }
    if (nullptr != this->getEVPowerDeliveryParameter())
    {
        outstr.append(fmt::format("{}\n", getStrEVPowerDeliveryParameter(this->getEVPowerDeliveryParameter(), "  ")));
    }
    if (nullptr != this->getDCEVPowerDeliveryParameter())
    {
        outstr.append(fmt::format("{}\n", getStrDCEVPowerDeliveryParameter(this->getDCEVPowerDeliveryParameter(), "  ")));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}