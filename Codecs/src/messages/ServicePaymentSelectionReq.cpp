

#include <string.h>
#include "messages/ServicePaymentSelectionReq.h"

ServicePaymentSelectionReq::ServicePaymentSelectionReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_PAYMENT_SERVICE_SELECTION_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PaymentServiceSelectionReq_isUsed = 1;
    init_iso1PaymentServiceSelectionReqType(&mExiData.V2G_Message.Body.PaymentServiceSelectionReq);
}

ServicePaymentSelectionReq::~ServicePaymentSelectionReq()
{
}

paymentOptionType ServicePaymentSelectionReq::getSelectedPaymentOption()
{
    return mExiData.V2G_Message.Body.PaymentServiceSelectionReq.SelectedPaymentOption;
}

void ServicePaymentSelectionReq::setSelectedPaymentOption(paymentOptionType payment)
{
    mExiData.V2G_Message.Body.PaymentServiceSelectionReq.SelectedPaymentOption = payment;
    this->mSelectedPaymentOption = payment;
}

SelectedServiceListType *ServicePaymentSelectionReq::getSelectedServiceList()
{
    return &mExiData.V2G_Message.Body.PaymentServiceSelectionReq.SelectedServiceList;
}

void ServicePaymentSelectionReq::setSelectedServiceList(SelectedServiceListType *list)
{
    if (nullptr != list)
    {
        memcpy(&mExiData.V2G_Message.Body.PaymentServiceSelectionReq.SelectedServiceList, list, sizeof(SelectedServiceListType));
        this->pSelectedServiceList = &mExiData.V2G_Message.Body.PaymentServiceSelectionReq.SelectedServiceList;
    }
    else
    {
        this->pSelectedServiceList = nullptr;
    }
}
void ServicePaymentSelectionReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  SelectedPaymentOption={}\n", PAYMENT[this->getSelectedPaymentOption()]));
    SelectedServiceListType *servList = this->getSelectedServiceList();
    if (servList->SelectedService.arrayLen > 0)
    {
        outstr.append("  SelectedServiceList:\n");
        for (size_t i = 0; i < servList->SelectedService.arrayLen; i++)
        {
            outstr.append(fmt::format("    ServiceID={0}, ParameterSetID={1}\n", servList->SelectedService.array[i].ServiceID, servList->SelectedService.array[i].ParameterSetID));
        }
    }
    outstr.pop_back();
    Logging::info(LogMsgDump_ENABLE, outstr);
}