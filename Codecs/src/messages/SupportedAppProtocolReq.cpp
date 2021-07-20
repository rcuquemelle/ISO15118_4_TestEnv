

#include "messages/SupportedAppProtocolReq.h"

#define AppProtocol_ARRAY_SIZE 5

SupportedAppProtocolReq::SupportedAppProtocolReq() : V2gAppHandMessage(V2gAppHandMessage::V2G_SUPPORT_APP_PROTO_REQ)
{
  mAppHandshakeData.supportedAppProtocolReq_isUsed = 1;
    init_appHandAnonType_supportedAppProtocolReq(&mAppHandshakeData.supportedAppProtocolReq);
}

SupportedAppProtocolReq::~SupportedAppProtocolReq()
{
}

appHand_SupportedAppProtocolReq *SupportedAppProtocolReq::getSupportedAppProtocolsReq(void)
{
  if (mAppHandshakeData.supportedAppProtocolReq_isUsed == 1)
  {
    return &mAppHandshakeData.supportedAppProtocolReq;
  }
  else
  {
    return nullptr;
  }
}
void SupportedAppProtocolReq::setSupportedAppProtocolsReq(appHand_SupportedAppProtocolReq *pSupportedAppReq)
{
  if (nullptr != pSupportedAppReq)
  {
    mAppHandshakeData.supportedAppProtocolReq_isUsed = 1;
    memcpy(&mAppHandshakeData.supportedAppProtocolReq, pSupportedAppReq, sizeof(appHand_SupportedAppProtocolReq));
    this->pSupportedAppProtocolReq = &mAppHandshakeData.supportedAppProtocolReq;
  }
  else
  {
    this->pSupportedAppProtocolReq = nullptr;
  }
}

void SupportedAppProtocolReq::setAppProtocol(appHandAppProtocolType *appProtol)
{
  uint16_t len = mAppHandshakeData.supportedAppProtocolReq.AppProtocol.arrayLen;
  if (len < AppProtocol_ARRAY_SIZE)
  {
    memcpy(&mAppHandshakeData.supportedAppProtocolReq.AppProtocol.array[len], appProtol, sizeof(appHandAppProtocolType));
    mAppHandshakeData.supportedAppProtocolReq.AppProtocol.arrayLen++;
  }
}

appHandAppProtocolType *SupportedAppProtocolReq::getAppProtocol(uint8_t idx)
{
  if (idx < mAppHandshakeData.supportedAppProtocolReq.AppProtocol.arrayLen)
  {
    return &mAppHandshakeData.supportedAppProtocolReq.AppProtocol.array[idx];
  }
  else
  {
    return nullptr;
  }
}

void SupportedAppProtocolReq::dumpMsg(void)
{
  std::string outstr = fmt::format("{}:\n", this->getMessageName());
  for (size_t i = 0; i < mAppHandshakeData.supportedAppProtocolReq.AppProtocol.arrayLen; i++)
  {
    outstr.append(fmt::format("{}\n", getStrAppProtocol(this->getAppProtocol(i), "  ")));
  }
  outstr.pop_back();
  Logging::info(LogMsgDump_ENABLE, outstr);
}