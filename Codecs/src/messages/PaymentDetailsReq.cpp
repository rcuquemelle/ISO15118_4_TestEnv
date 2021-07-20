

#include <string.h>
#include "messages/PaymentDetailsReq.h"
#define eMAID_CHARACTERS_SIZE 16
PaymentDetailsReq::PaymentDetailsReq()
    : V2gExiMessage(V2gExiMessage::V2G_MSG_PAYMENT_DETAILS_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PaymentDetailsReq_isUsed = 1u;
    init_iso1PaymentDetailsReqType(&mExiData.V2G_Message.Body.PaymentDetailsReq);
}

PaymentDetailsReq::~PaymentDetailsReq()
{
}

std::string &PaymentDetailsReq::getEMAID()
{
    this->mEMAID.assign(mExiData.V2G_Message.Body.PaymentDetailsReq.eMAID.characters, mExiData.V2G_Message.Body.PaymentDetailsReq.eMAID.charactersLen);
    return this->mEMAID;
}

void PaymentDetailsReq::setEMAID(const std::string &emaid)
{
    size_t len;
    if (emaid.size() > eMAID_CHARACTERS_SIZE)
    {
        len = eMAID_CHARACTERS_SIZE;
    }
    else
    {
        len = emaid.size();
    }
    mExiData.V2G_Message.Body.PaymentDetailsReq.eMAID.charactersLen = len;
    memcpy(mExiData.V2G_Message.Body.PaymentDetailsReq.eMAID.characters, emaid.c_str(), len);
    this->mEMAID = emaid.substr(0, len);
}

CertificateChainType *PaymentDetailsReq::getContractCertChain()
{
    return &mExiData.V2G_Message.Body.PaymentDetailsReq.ContractSignatureCertChain;
}

void PaymentDetailsReq::setContractCertChain(CertificateChainType *chain)
{
    if (nullptr != chain)
    {
        memcpy(&mExiData.V2G_Message.Body.PaymentDetailsReq.ContractSignatureCertChain, chain, sizeof(CertificateChainType));
    }
    this->pContractSignatureCertChain = chain;
}
void PaymentDetailsReq::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  eMAID:{}\n", this->getEMAID()));
    outstr.append(fmt::format("{}", getStrContractCertChain(this->getContractCertChain(), "  ")));
    Logging::info(LogMsgDump_ENABLE, outstr);
}