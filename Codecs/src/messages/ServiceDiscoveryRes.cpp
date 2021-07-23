

#include <string.h>
#include "messages/ServiceDiscoveryRes.h"

ServiceDiscoveryRes::ServiceDiscoveryRes() : V2gExiMessage(V2gExiMessage::V2G_MSG_SERVICE_DISCOVERY_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.ServiceDiscoveryRes_isUsed = 1;
    init_iso1ServiceDiscoveryResType(&mExiData.V2G_Message.Body.ServiceDiscoveryRes);
}

ServiceDiscoveryRes::ServiceDiscoveryRes(std::shared_ptr<V2gExiMessage> &msg) : ServiceDiscoveryRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

ServiceDiscoveryRes::~ServiceDiscoveryRes()
{
}

responseCodeType ServiceDiscoveryRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.ServiceDiscoveryRes.ResponseCode;
}

void ServiceDiscoveryRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = code;
    this->mResponseCode = code;
}

PaymentOptionListType *ServiceDiscoveryRes::getPaymentOptionList()
{
    return &mExiData.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList;
}

void ServiceDiscoveryRes::setPaymentOptionList(PaymentOptionListType *list)
{
    if (nullptr != list)
    {
        mExiData.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.arrayLen = list->PaymentOption.arrayLen;
        for (int i = 0; i < list->PaymentOption.arrayLen; i++)
        {
            mExiData.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[i] = list->PaymentOption.array[i];
        }
        this->pPaymentOptionList = &mExiData.V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList;
    }
    else
    {
        this->pPaymentOptionList = nullptr;
    }
}

ChargeServiceType *ServiceDiscoveryRes::getChargeServiceType()
{
    return &mExiData.V2G_Message.Body.ServiceDiscoveryRes.ChargeService;
}

void ServiceDiscoveryRes::setChargeServiceType(ChargeServiceType *type)
{
    if (nullptr != type)
    {
        memcpy(&mExiData.V2G_Message.Body.ServiceDiscoveryRes.ChargeService, type, sizeof(ChargeServiceType));
        this->pChargeService = &mExiData.V2G_Message.Body.ServiceDiscoveryRes.ChargeService;
    }
    else
    {
        this->pChargeService = nullptr;
    }
}

ServiceListType *ServiceDiscoveryRes::getServiceList()
{
    if (mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList_isUsed == 1)
    {
        return &mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList;
    }
    else
    {
        return nullptr;
    }
}

void ServiceDiscoveryRes::setServiceList(ServiceListType *type)
{
    if (nullptr != type)
    {
        mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList_isUsed = 1;
        mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList.Service.arrayLen = type->Service.arrayLen;
        for (int i = 0; i < type->Service.arrayLen; i++)
        {
            memcpy(&mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList.Service.array[i], &type->Service.array[i], sizeof(struct iso1ServiceType));
        }
        this->pServiceList = &mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList;
    }
    else
    {
        this->pServiceList = nullptr;
    }
}
void ServiceDiscoveryRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));

    PaymentOptionListType *paymentList = this->getPaymentOptionList();
    std::string paymentStr = "";
    for (size_t i = 0; i < paymentList->PaymentOption.arrayLen; i++)
    {
        paymentStr.append(fmt::format("{}, ", PAYMENT[paymentList->PaymentOption.array[i]]));
    }
    if (paymentStr.size() > 2)
    {
        paymentStr.erase(paymentStr.size() - 2, 2);
    }
    outstr.append(fmt::format("  PaymentOptionList=[{}]\n", paymentStr));

    outstr.append(fmt::format("  ChargeService:\n{}\n", getStrChargeService(this->getChargeServiceType(), "    ")));

    if (mExiData.V2G_Message.Body.ServiceDiscoveryRes.ServiceList_isUsed == 1)
    {
        outstr.append("  ServiceList:\n");
        ServiceListType *serviceList = this->getServiceList();
        for (size_t i = 0; i < serviceList->Service.arrayLen; i++)
        {
            outstr.append(fmt::format("{0}\n", getStrService(&serviceList->Service.array[i], "    ")));
        }
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}