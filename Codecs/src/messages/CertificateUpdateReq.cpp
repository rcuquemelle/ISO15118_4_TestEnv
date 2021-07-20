#include "messages/CertificateUpdateReq.h"

CertificateUpdateReq::CertificateUpdateReq() 
  : V2gExiMessage(V2gExiMessage::V2G_MSG_CERTIFICATE_UPDATE_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CertificateUpdateReq_isUsed = 1;
    init_iso1CertificateUpdateReqType(&mExiData.V2G_Message.Body.CertificateUpdateReq);
}

CertificateUpdateReq::~CertificateUpdateReq()
{
}

void CertificateUpdateReq::dumpMsg(void) 
{
  
}