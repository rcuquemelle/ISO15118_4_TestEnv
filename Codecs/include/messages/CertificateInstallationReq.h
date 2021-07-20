#ifndef __CERTIFICATEINSTALLATIONREQ_H__
#define __CERTIFICATEINSTALLATIONREQ_H__

#include "../V2gExiMessage.h"

class CertificateInstallationReq: public V2gExiMessage
{
public:
  CertificateInstallationReq();
  virtual ~CertificateInstallationReq();

  void dumpMsg(void) override;

  bool operator==(CertificateInstallationReq &object_compare)
  {
    return true;
  }
};

#endif // __CERTIFICATEINSTALLATIONREQ_H__