

#ifndef EVCC_SUPPORTEDAPPPROTOCOL_H
#define EVCC_SUPPORTEDAPPPROTOCOL_H

#include <vector>
#include "../V2gAppHandMessage.h"

#define NAME_SPACE_ISO0 "urn:iso:15118:2:2010:MsgDef"
#define NAME_SPACE_DIN "urn:din:70121:2012:MsgDef"

class SupportedAppProtocolReq : public V2gAppHandMessage
{
public:
  SupportedAppProtocolReq();
  virtual ~SupportedAppProtocolReq();
  void dumpMsg(void) override;

  void setSupportedAppProtocolsReq(appHand_SupportedAppProtocolReq *pSupportedAppReq);
  appHand_SupportedAppProtocolReq *getSupportedAppProtocolsReq(void);

  void setAppProtocol(appHandAppProtocolType *appProtol);
  appHandAppProtocolType *getAppProtocol(uint8_t idx);

  comparision_indicate_flag pSupportedAppProtocolReq_flag = has_value;

  bool operator==(SupportedAppProtocolReq &object_compare)
  {
    bool final_result = true;
    appHand_SupportedAppProtocolReq *pSupportedAppProtocolReqCmp = object_compare.getSupportedAppProtocolsReq();

    switch (this->pSupportedAppProtocolReq_flag)
    {
    case specific:
      if ((pSupportedAppProtocolReqCmp != nullptr) && (this->pSupportedAppProtocolReq != nullptr))
      {
        final_result = (0 == memcmp(pSupportedAppProtocolReqCmp, this->pSupportedAppProtocolReq, sizeof(appHand_SupportedAppProtocolReq)));
      }
      else
      {
        final_result = false;
      }
    case has_value:
      if (pSupportedAppProtocolReqCmp->AppProtocol.arrayLen == 0)
      {
        final_result = false;
      }
      break;
    case omit:
    default:
      break;
    }
    return final_result;
  }

private:
  appHand_SupportedAppProtocolReq *pSupportedAppProtocolReq = nullptr;
};

#endif //EVCC_SUPPORTEDAPPPROTOCOL_H
