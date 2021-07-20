#include "messages/CertificateUpdateRes.h"

CertificateUpdateRes::CertificateUpdateRes() 
  : V2gExiMessage(V2gExiMessage::V2G_MSG_CERTIFICATE_UPDATE_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CertificateUpdateRes_isUsed = 1;
    init_iso1CertificateUpdateResType(&mExiData.V2G_Message.Body.CertificateUpdateRes);
}

CertificateUpdateRes::CertificateUpdateRes(std::shared_ptr<V2gExiMessage> &msg)
  : CertificateUpdateRes()
{
  memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}

CertificateUpdateRes::~CertificateUpdateRes()
{
}

void CertificateUpdateRes::dumpMsg(void) 
{
  
}