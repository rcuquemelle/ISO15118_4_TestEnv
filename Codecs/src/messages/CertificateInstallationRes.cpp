#include "messages/CertificateInstallationRes.h"

CertificateInstallationRes::CertificateInstallationRes() 
  : V2gExiMessage(V2gExiMessage::V2G_MSG_CERTIFICATE_INSTALLATION_RES)
{
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    mExiData.V2G_Message.Body.CertificateInstallationRes_isUsed = 1;
    init_iso1CertificateInstallationResType(&mExiData.V2G_Message.Body.CertificateInstallationRes);
}

CertificateInstallationRes::CertificateInstallationRes(std::shared_ptr<V2gExiMessage> &msg) 
  : CertificateInstallationRes()
{
  memcpy(&mExiData, msg->getExiData(), sizeof(mExiData));
}
CertificateInstallationRes::~CertificateInstallationRes()
{
}

void CertificateInstallationRes::dumpMsg(void) 
{
  
}