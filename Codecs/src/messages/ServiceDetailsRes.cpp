

#include <string.h>
#include "messages/ServiceDetailsRes.h"

ServiceDetailsRes::ServiceDetailsRes() : V2gExiMessage(V2gExiMessage::V2G_MSG_SERVICE_DETAILS_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ServiceDetailRes_isUsed = 1u;
    init_iso1ServiceDetailResType(&mExiData.V2G_Message.Body.ServiceDetailRes);
}

ServiceDetailsRes::ServiceDetailsRes(std::shared_ptr<V2gExiMessage> &msg) : ServiceDetailsRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

ServiceDetailsRes::~ServiceDetailsRes()
{
}

responseCodeType ServiceDetailsRes::getResponseCode(void)
{
    return mExiData.V2G_Message.Body.ServiceDetailRes.ResponseCode;
}

void ServiceDetailsRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.ServiceDetailRes.ResponseCode = code;
    mResponseCode = code;
}

ServiceParameterListType *ServiceDetailsRes::getServiceParamterList(void)
{
    if (mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList;
    }
    else
    {
        return nullptr;
    }
}

void ServiceDetailsRes::setServiceParamterList(ServiceParameterListType *list)
{
    if (nullptr != list)
    {
        mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList, list, sizeof(ServiceParameterListType));
        this->pServiceParameterList = &mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList;
    }
    else
    {
        this->pServiceParameterList = nullptr;
    }
}

int ServiceDetailsRes::getServiceID()
{
    return mExiData.V2G_Message.Body.ServiceDetailRes.ServiceID;
}

void ServiceDetailsRes::setServiceID(int id)
{
    mExiData.V2G_Message.Body.ServiceDetailRes.ServiceID = id;
    this->mServiceID = id;
}

void ServiceDetailsRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  ServiceID={0}\n", this->getServiceID()));
    if (mExiData.V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed == 1)
    {
        ServiceParameterListType *paramList = this->getServiceParamterList();
        outstr.append("  ServiceParameterList:\n");
        for (size_t i = 0; i < paramList->ParameterSet.arrayLen; i++)
        {
            outstr.append(fmt::format("{}\n", getStrParam(&paramList->ParameterSet.array[i], "    ")));
        }
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}