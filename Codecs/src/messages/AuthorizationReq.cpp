

#include <string.h>
#include "messages/AuthorizationReq.h"

#define GenChallenge_BYTES_SIZE 16

AuthorizationReq::AuthorizationReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_AUTHORIZATION_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.AuthorizationReq_isUsed = 1u;
    init_iso1AuthorizationReqType(&mExiData.V2G_Message.Body.AuthorizationReq);
}

AuthorizationReq::~AuthorizationReq()
{
}

std::vector<uint8_t> *AuthorizationReq::getGenChallenge(void)
{
    if (this->mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge_isUsed == 1)
    {
        this->pGenChallenge.clear();
        for (size_t i = 0; i < mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge.bytesLen; i++)
        {
            this->pGenChallenge.push_back(mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge.bytes[i]);
        }
        return &this->pGenChallenge;
    }
    else
    {
        return nullptr;
    }
}
void AuthorizationReq::setGenChallenge(const std::vector<uint8_t> &challenge)
{
    size_t len = 0;
    this->pGenChallenge.clear();
    if (challenge.size() > GenChallenge_BYTES_SIZE)
    {
        len = GenChallenge_BYTES_SIZE;
    }
    else
    {
        len = challenge.size();
    }
    for (size_t i = 0; i < len; i++)
    {
        this->pGenChallenge.push_back(challenge[i]);
        mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge.bytes[i] = challenge[i];
    }
    mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge.bytesLen = len;
    mExiData.V2G_Message.Body.AuthorizationReq.GenChallenge_isUsed = 1;
}

std::string &AuthorizationReq::getId()
{
    if (mExiData.V2G_Message.Body.AuthorizationReq.Id_isUsed == 1)
    {
        mId.assign(mExiData.V2G_Message.Body.AuthorizationReq.Id.characters, mExiData.V2G_Message.Body.AuthorizationReq.Id.charactersLen);
    }
    else
    {
        mId = "";
    }
    return mId;
}
void AuthorizationReq::setId(const std::string &id)
{
    mExiData.V2G_Message.Body.AuthorizationReq.Id_isUsed = 1;
    mExiData.V2G_Message.Body.AuthorizationReq.Id.charactersLen = id.size();
    memcpy(mExiData.V2G_Message.Body.AuthorizationReq.Id.characters, id.c_str(),
           mExiData.V2G_Message.Body.AuthorizationReq.Id.charactersLen);
    this->mId = id;
}

void AuthorizationReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    if ("" != this->getId())
    {
        outstr.append(fmt::format("  Id={}\n", this->getId()));
    }
    if (nullptr != this->getGenChallenge())
    {
        outstr.append(fmt::format("  GenChallenge={}", outHexString(*this->getGenChallenge())));
    }
    Logging::info(LogMsgDump_ENABLE, outstr);
}