//
// Created by james on 19/10/2020.
//

#include "messages/ChargingStatusReq.h"

ChargingStatusReq::ChargingStatusReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_CHARGING_STATUS_REQ) {
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ChargingStatusReq_isUsed = 1u;
    init_iso1ChargingStatusReqType(&mExiData.V2G_Message.Body.ChargingStatusReq);
}

ChargingStatusReq::~ChargingStatusReq() {
}
void ChargingStatusReq::dumpMsg(void){
    std::string outstr = getHeaderStr();
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}