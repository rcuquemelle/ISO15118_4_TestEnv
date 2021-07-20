

#include "messages/ServicePaymentSelectionRes.h"
#include <string.h>

ServicePaymentSelectionRes::ServicePaymentSelectionRes()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_PAYMENT_SERVICE_SELECTION_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PaymentServiceSelectionRes_isUsed = 1u;
    init_iso1PaymentServiceSelectionResType(&mExiData.V2G_Message.Body.PaymentServiceSelectionRes);
}

ServicePaymentSelectionRes::ServicePaymentSelectionRes(std::shared_ptr<V2gExiMessage> &msg) : ServicePaymentSelectionRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

ServicePaymentSelectionRes::~ServicePaymentSelectionRes()
{
}

responseCodeType ServicePaymentSelectionRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.PaymentServiceSelectionRes.ResponseCode;
}

void ServicePaymentSelectionRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.PaymentServiceSelectionRes.ResponseCode = code;
    this->mResponseCode = code;
}
void ServicePaymentSelectionRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}", RESPONSE_CODE[this->getResponseCode()]));
    Logging::info(LogMsgDump_ENABLE, outstr);
}