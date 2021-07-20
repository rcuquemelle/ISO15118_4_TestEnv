#ifndef __CERTIFICATEUPDATEREQ_H__
#define __CERTIFICATEUPDATEREQ_H__

#include "../V2gExiMessage.h"

class CertificateUpdateReq: public V2gExiMessage
{
public:
  CertificateUpdateReq();
  virtual ~CertificateUpdateReq();

  void dumpMsg(void) override;

  bool operator==(CertificateUpdateReq &object_compare)
  {
    return true;
  }
};

#endif // __CERTIFICATEUPDATEREQ_H__