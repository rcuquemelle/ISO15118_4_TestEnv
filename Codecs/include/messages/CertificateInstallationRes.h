#ifndef __CERTIFICATEINSTALLATIONRES_H__
#define __CERTIFICATEINSTALLATIONRES_H__

#include "../V2gExiMessage.h"

class CertificateInstallationRes: public V2gExiMessage
{
public:
  CertificateInstallationRes();
  CertificateInstallationRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~CertificateInstallationRes();

  void dumpMsg(void) override;

  bool operator==(CertificateInstallationRes &object_compare)
  {
    return true;
  }
};

#endif // __CERTIFICATEINSTALLATIONRES_H__