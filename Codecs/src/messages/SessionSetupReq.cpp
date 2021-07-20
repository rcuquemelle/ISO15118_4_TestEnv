

#include <string.h>
#include "messages/SessionSetupReq.h"

#define EVCCID_BYTES_SIZE 6

SessionSetupReq::SessionSetupReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_SESSION_SETUP_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.SessionSetupReq_isUsed = 1u;
    init_iso1SessionSetupReqType(&mExiData.V2G_Message.Body.SessionSetupReq);
}

SessionSetupReq::SessionSetupReq(std::shared_ptr<V2gExiMessage> &msg) : SessionSetupReq()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

std::vector<uint8_t>& SessionSetupReq::getEVCCID(void)
{
    this->mEVCCID.clear();
    for (size_t i = 0; i < mExiData.V2G_Message.Body.SessionSetupReq.EVCCID.bytesLen; i++)
    {
        this->mEVCCID.push_back(mExiData.V2G_Message.Body.SessionSetupReq.EVCCID.bytes[i]);
    }
    return this->mEVCCID;
}

void SessionSetupReq::setEVCCID(const std::vector<uint8_t> &evccid)
{
    size_t len = 0;
    this->mEVCCID.clear();
    if (evccid.size() > EVCCID_BYTES_SIZE)
    {
        len = EVCCID_BYTES_SIZE;
    }
    else
    {
        len = evccid.size();
    }
    for (size_t i = 0; i < len; i++)
    {
        this->mEVCCID.push_back(evccid[i]);
        mExiData.V2G_Message.Body.SessionSetupReq.EVCCID.bytes[i] = evccid[i];
    }
    mExiData.V2G_Message.Body.SessionSetupReq.EVCCID.bytesLen = len;
}
void SessionSetupReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  EVCCID={0}", outHexString(this->getEVCCID())));
    Logging::info(LogMsgDump_ENABLE, outstr);
}