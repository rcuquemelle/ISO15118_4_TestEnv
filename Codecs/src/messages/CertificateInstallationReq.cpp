
#include "messages/CertificateInstallationReq.h"

CertificateInstallationReq::CertificateInstallationReq() 
  : V2gExiMessage(V2gExiMessage::V2G_MSG_CERTIFICATE_INSTALLATION_REQ)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CertificateInstallationReq_isUsed = 1;
    init_iso1CertificateInstallationReqType(&mExiData.V2G_Message.Body.CertificateInstallationReq);
}

CertificateInstallationReq::~CertificateInstallationReq()
{
}

void CertificateInstallationReq::dumpMsg(void) 
{
}