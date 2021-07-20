

#include <string.h>
#include "messages/ChargeParameterDiscoveryRes.h"

ChargeParameterDiscoveryRes::ChargeParameterDiscoveryRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_CHARGE_PARAMETER_DISCOVERY_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed = 1u;
    init_iso1ChargeParameterDiscoveryResType(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes);
}

ChargeParameterDiscoveryRes::ChargeParameterDiscoveryRes(std::shared_ptr<V2gExiMessage> &msg) : ChargeParameterDiscoveryRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

ChargeParameterDiscoveryRes::~ChargeParameterDiscoveryRes()
{
}

responseCodeType ChargeParameterDiscoveryRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.ResponseCode;
}

void ChargeParameterDiscoveryRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.ResponseCode = code;
    this->mResponseCode = code;
}

EVSEProcessingType ChargeParameterDiscoveryRes::getEVSEProcessing()
{
    return mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEProcessing;
}
void ChargeParameterDiscoveryRes::setEVSEProcessing(EVSEProcessingType proc)
{
    mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEProcessing = proc;
    this->mEVSEProcessing = proc;
}

SAScheduleListType *ChargeParameterDiscoveryRes::getSAScheduleList()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryRes::setSAScheduleList(SAScheduleListType *schedule)
{
    if (schedule != nullptr)
    {
        mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList, schedule, sizeof(iso1SAScheduleListType));
        this->pSASchedules = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList;
    }
    else
    {
        this->pSASchedules = nullptr;
    }
}

AC_EVSEChargeParameterType *ChargeParameterDiscoveryRes::getACEVSEChargeParamter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryRes::setACEVSEChargeParameter(AC_EVSEChargeParameterType *params)
{
    if (nullptr != params)
    {
        mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter, params, sizeof(AC_EVSEChargeParameterType));
        this->pAC_EVSEChargeParameter = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter;
    }
    else
    {
        this->pAC_EVSEChargeParameter = nullptr;
    }
}

DC_EVSEChargeParameterType *ChargeParameterDiscoveryRes::getDCEVSEChargeParamter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryRes::setDCEVSEChargeParameter(DC_EVSEChargeParameterType *params)
{
    if (nullptr != params)
    {
        mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter, params, sizeof(DC_EVSEChargeParameterType));
        this->pDC_EVSEChargeParameter = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.DC_EVSEChargeParameter;
    }
    else
    {
        this->pDC_EVSEChargeParameter = nullptr;
    }
}

EVSEChargeParameterType *ChargeParameterDiscoveryRes::getEVSEChargeParamter()
{
    if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter;
    }
    else
    {
        return nullptr;
    }
}
void ChargeParameterDiscoveryRes::setEVSEChargeParameter(EVSEChargeParameterType *params)
{
    if (nullptr != params)
    {
        mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter, params, sizeof(EVSEChargeParameterType));
        this->pEVSEChargeParameter = &mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter;
    }
    else
    {
        this->pEVSEChargeParameter = nullptr;
    }
}
void ChargeParameterDiscoveryRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  EVSEProcessing={}\n", EVSEPROCESSING[this->getEVSEProcessing()]));
    if (nullptr != this->getSAScheduleList())
    {
        outstr.append(fmt::format("{}\n", getStrSAScheduleList(this->getSAScheduleList(), "  ")));
    }
    if (nullptr != this->getEVSEChargeParamter())
    {
        outstr.append(fmt::format("{}\n", getStrEVSEChargeParameter(this->getEVSEChargeParamter(), "  ")));
    }
    if (nullptr != this->getACEVSEChargeParamter())
    {
        outstr.append(fmt::format("{}\n", getStrACEVSEChargeParameter(this->getACEVSEChargeParamter(), "  ")));
    }
    if (nullptr != this->getDCEVSEChargeParamter())
    {
        outstr.append(fmt::format("{}\n", getStrDCEVSEChargeParameter(this->getDCEVSEChargeParamter(), "  ")));
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}