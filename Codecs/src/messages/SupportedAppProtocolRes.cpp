

#include "messages/SupportedAppProtocolRes.h"

const char *APP_RESP_CODE[] = {
    [0] = "OK_SuccessfulNegotiation",
    [1] = "OK_SuccessfulNegotiationWithMinorDeviation",
    [2] = "Failed_NoNegotiation"};

SupportedAppProtocolRes::SupportedAppProtocolRes() : V2gAppHandMessage(V2gAppHandMessage::V2G_SUPPORT_APP_PROTO_RES)
{
    mAppHandshakeData.supportedAppProtocolRes_isUsed = 1;
    init_appHandAnonType_supportedAppProtocolRes(&mAppHandshakeData.supportedAppProtocolRes);
}

SupportedAppProtocolRes::~SupportedAppProtocolRes()
{
}

appHandresponseCodeType SupportedAppProtocolRes::getResponseCode()
{
    return mAppHandshakeData.supportedAppProtocolRes.ResponseCode;
}
void SupportedAppProtocolRes::setResponseCode(appHandresponseCodeType code)
{
    mAppHandshakeData.supportedAppProtocolRes.ResponseCode = code;
    mResponseCode = code;
}

uint16_t SupportedAppProtocolRes::getSchemeID()
{
    return mAppHandshakeData.supportedAppProtocolRes.SchemaID;
}
void SupportedAppProtocolRes::setSchemeID(uint16_t id)
{
    mAppHandshakeData.supportedAppProtocolRes.SchemaID = id;
    mSchemaID = id;
}

void SupportedAppProtocolRes::dumpMsg(void)
{
    std::string outstr(fmt::format("{0}: ResponseCode={1}, SchemeID={2}", this->getMessageName(), APP_RESP_CODE[this->getResponseCode()], this->getSchemeID()));
    Logging::info(LogMsgDump_ENABLE, outstr);
}