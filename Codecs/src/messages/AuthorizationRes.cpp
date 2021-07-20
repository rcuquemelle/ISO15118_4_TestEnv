

#include "messages/AuthorizationRes.h"

AuthorizationRes::AuthorizationRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_AUTHORIZATION_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.AuthorizationRes_isUsed = 1u;
    init_iso1AuthorizationResType(&mExiData.V2G_Message.Body.AuthorizationRes);
}

AuthorizationRes::AuthorizationRes(std::shared_ptr<V2gExiMessage> &msg) : AuthorizationRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

AuthorizationRes::~AuthorizationRes()
{
}

responseCodeType AuthorizationRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.AuthorizationRes.ResponseCode;
}
void AuthorizationRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.AuthorizationRes.ResponseCode = code;
}

EVSEProcessingType AuthorizationRes::getEVSEProcessing()
{
    return mExiData.V2G_Message.Body.AuthorizationRes.EVSEProcessing;
}

void AuthorizationRes::setEVSEProcessing(EVSEProcessingType proc)
{
    mExiData.V2G_Message.Body.AuthorizationRes.EVSEProcessing = proc;
}

void AuthorizationRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  EVSEProcessing={}", EVSEPROCESSING[this->getEVSEProcessing()]));
    Logging::info(LogMsgDump_ENABLE, outstr);
}