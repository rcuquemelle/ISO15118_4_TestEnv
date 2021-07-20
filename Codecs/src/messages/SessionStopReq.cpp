//
// Created by james on 30/10/2020.
//

#include "messages/SessionStopReq.h"

SessionStopReq::SessionStopReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_SESSION_STOP_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.SessionStopReq_isUsed = 1u;
    init_iso1SessionStopReqType(&mExiData.V2G_Message.Body.SessionStopReq);
}

void SessionStopReq::setChargingSession(chargingSessionType type)
{
    mExiData.V2G_Message.Body.SessionStopReq.ChargingSession = type;
    this->mChargingSession = type;
}

chargingSessionType SessionStopReq::getChargingSession()
{
    return mExiData.V2G_Message.Body.SessionStopReq.ChargingSession;
}
void SessionStopReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    const char *chargeSession[] = {
        [0] = "Terminate",
        [1] = "Pause"};
    outstr.append(fmt::format("  ChargingSession={}", chargeSession[this->getChargingSession()]));
    Logging::info(LogMsgDump_ENABLE, outstr);
}