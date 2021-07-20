

#include "messages/ServiceDetailsReq.h"

ServiceDetailsReq::ServiceDetailsReq() : V2gExiMessage(V2gExiMessage::V2G_MSG_SERVICE_DETAILS_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ServiceDetailReq_isUsed = 1u;
    init_iso1ServiceDetailReqType(&mExiData.V2G_Message.Body.ServiceDetailReq);
}

ServiceDetailsReq::~ServiceDetailsReq()
{
}

int ServiceDetailsReq::getServiceID()
{
    return mExiData.V2G_Message.Body.ServiceDetailReq.ServiceID;
}

void ServiceDetailsReq::setServiceID(int id)
{
    mExiData.V2G_Message.Body.ServiceDetailReq.ServiceID = id;
    this->mServiceID = id;
}

void ServiceDetailsReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ServiceID={}", this->getServiceID()));
    Logging::info(LogMsgDump_ENABLE, outstr);
}