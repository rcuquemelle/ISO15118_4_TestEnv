

#include <string.h>
#include "messages/CableCheckReq.h"

CableCheckReq::CableCheckReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_CABLE_CHECK_REQ){
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    init_iso1CableCheckReqType(&mExiData.V2G_Message.Body.CableCheckReq);
    mExiData.V2G_Message.Body.CableCheckReq_isUsed = 1u;
}

CableCheckReq::~CableCheckReq() {
}

DC_EVStatusType* CableCheckReq::getDCEVStatus() {
    return &mExiData.V2G_Message.Body.CableCheckReq.DC_EVStatus;
}
void CableCheckReq::setDCEVStatus(DC_EVStatusType *status) {
    if (nullptr != status)
        memcpy(&mExiData.V2G_Message.Body.CableCheckReq.DC_EVStatus, status, sizeof(DC_EVStatusType));
}

void CableCheckReq::dumpMsg(void){
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("{}", getStrDCEVStatus(this->getDCEVStatus(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}