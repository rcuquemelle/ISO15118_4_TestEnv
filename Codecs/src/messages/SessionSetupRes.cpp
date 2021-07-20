

#include <string.h>
#include "messages/SessionSetupRes.h"

#define EVSEID_CHARACTERS_SIZE 37

SessionSetupRes::SessionSetupRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_SESSION_SETUP_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.SessionSetupRes_isUsed = 1u;
    init_iso1SessionSetupResType(&mExiData.V2G_Message.Body.SessionSetupRes);
}

SessionSetupRes::SessionSetupRes(std::shared_ptr<V2gExiMessage> &msg) : SessionSetupRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

SessionSetupRes::~SessionSetupRes()
{
}

responseCodeType SessionSetupRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.SessionSetupRes.ResponseCode;
}

void SessionSetupRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.SessionSetupRes.ResponseCode = code;
    this->mResponseCode = code;
}

std::string& SessionSetupRes::getEVSEID()
{
    mEVSEID.assign((const char *)mExiData.V2G_Message.Body.SessionSetupRes.EVSEID.characters, mExiData.V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen);
    return mEVSEID;
}

void SessionSetupRes::setEVSEID(const std::string &id)
{
    mEVSEID = id;
    memcpy(mExiData.V2G_Message.Body.SessionSetupRes.EVSEID.characters, id.c_str(), id.size());
    mExiData.V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen = id.size();
}

uint64_t SessionSetupRes::getEVSETimeStamp()
{
    return mExiData.V2G_Message.Body.SessionSetupRes.EVSETimeStamp;
}

void SessionSetupRes::setEVSETimeStamp(uint64_t timestamp)
{
    mExiData.V2G_Message.Body.SessionSetupRes.EVSETimeStamp = timestamp;
    this->mTimeStamp = timestamp;
}
void SessionSetupRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n"
                              "  EVSEID={1}\n"
                              "  EVSETimeStamp={2}",
                              RESPONSE_CODE[this->getResponseCode()],
                              outHexString2(this->getEVSEID()),
                              this->getEVSETimeStamp()));
    Logging::info(LogMsgDump_ENABLE, outstr);
}