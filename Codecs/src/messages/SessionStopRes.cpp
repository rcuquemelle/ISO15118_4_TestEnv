//
// Created by james on 30/10/2020.
//

#include "messages/SessionStopRes.h"

SessionStopRes::SessionStopRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_SESSION_STOP_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.SessionStopRes_isUsed = 1u;
    init_iso1SessionStopResType(&mExiData.V2G_Message.Body.SessionStopRes);
}

SessionStopRes::SessionStopRes(std::shared_ptr<V2gExiMessage> &msg) : SessionStopRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

SessionStopRes::~SessionStopRes()
{
}

responseCodeType SessionStopRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.SessionStopRes.ResponseCode;
}

void SessionStopRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.SessionStopRes.ResponseCode = code;
    this->mResponseCode = code;
}
void SessionStopRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}", RESPONSE_CODE[this->getResponseCode()]));
    Logging::info(LogMsgDump_ENABLE, outstr);
}