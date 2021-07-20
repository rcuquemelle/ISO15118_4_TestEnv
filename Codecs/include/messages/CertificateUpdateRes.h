#ifndef __CERTIFICATEUPDATERES_H__
#define __CERTIFICATEUPDATERES_H__

#include "../V2gExiMessage.h"

class CertificateUpdateRes: public V2gExiMessage
{
public:
  CertificateUpdateRes();
  CertificateUpdateRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~CertificateUpdateRes();

  void dumpMsg(void) override;

  bool operator==(CertificateUpdateRes &object_compare)
  {
    return true;
  }
};

#endif // __CERTIFICATEUPDATERES_H__