

#include "messages/PaymentDetailsRes.h"

#define GenChallenge_BYTES_SIZE 16

PaymentDetailsRes::PaymentDetailsRes() : V2gExiMessage(V2gExiMessage::V2G_MSG_PAYMENT_DETAILS_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.PaymentDetailsRes_isUsed = 1u;
    init_iso1PaymentDetailsResType(&mExiData.V2G_Message.Body.PaymentDetailsRes);
}

PaymentDetailsRes::PaymentDetailsRes(std::shared_ptr<V2gExiMessage> &msg) : PaymentDetailsRes()
{
    memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

PaymentDetailsRes::~PaymentDetailsRes()
{
}

responseCodeType PaymentDetailsRes::getResponseCode()
{
    return mExiData.V2G_Message.Body.PaymentDetailsRes.ResponseCode;
}

void PaymentDetailsRes::setResponseCode(responseCodeType code)
{
    mExiData.V2G_Message.Body.PaymentDetailsRes.ResponseCode = code;
    this->mResponseCode = code;
}

std::vector<uint8_t>& PaymentDetailsRes::getGenChallenge(void)
{
    this->pGenChallenge.clear();
    for (size_t i = 0; i < mExiData.V2G_Message.Body.PaymentDetailsRes.GenChallenge.bytesLen; i++)
    {
        this->pGenChallenge.push_back(mExiData.V2G_Message.Body.PaymentDetailsRes.GenChallenge.bytes[i]);
    }
    return this->pGenChallenge;
}

void PaymentDetailsRes::setGenChallenge(const std::vector<uint8_t> &challenge)
{
    size_t len = 0;
    this->pGenChallenge.clear();
    if (challenge.size() > GenChallenge_BYTES_SIZE)
    {
        len = GenChallenge_BYTES_SIZE;
    }
    else
    {
        len = challenge.size();
    }
    for (size_t i = 0; i < len; i++)
    {
        this->pGenChallenge.push_back(challenge[i]);
        mExiData.V2G_Message.Body.PaymentDetailsRes.GenChallenge.bytes[i] = challenge[i];
    }
    mExiData.V2G_Message.Body.PaymentDetailsRes.GenChallenge.bytesLen = len;
}

int64_t PaymentDetailsRes::getEVSETimeStamp()
{
    return mExiData.V2G_Message.Body.PaymentDetailsRes.EVSETimeStamp;
}
void PaymentDetailsRes::setEVSETimeStamp(int64_t timestamp)
{
    mExiData.V2G_Message.Body.PaymentDetailsRes.EVSETimeStamp = timestamp;
    this->mEVSETimeStamp = timestamp;
}
void PaymentDetailsRes::dumpMsg(void)
{
    std::string outstr = getHeaderStr();
    outstr.append(fmt::format("  ResponseCode={0}\n", RESPONSE_CODE[this->getResponseCode()]));
    outstr.append(fmt::format("  GenChallenge={0}\n", outHexString(this->getGenChallenge())));
    outstr.append(fmt::format("  EVSETimeStamp={0}", this->getEVSETimeStamp()));
    Logging::info(LogMsgDump_ENABLE, outstr);
}