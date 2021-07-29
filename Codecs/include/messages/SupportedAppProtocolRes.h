

#ifndef EVCC_SUPPORTEDAPPPROTOCOLRES_H
#define EVCC_SUPPORTEDAPPPROTOCOLRES_H

#include "../V2gAppHandMessage.h"

class SupportedAppProtocolRes : public V2gAppHandMessage
{
public:
  SupportedAppProtocolRes();
  virtual ~SupportedAppProtocolRes();

  appHandresponseCodeType getResponseCode();
  void setResponseCode(appHandresponseCodeType code);
  uint16_t getSchemeID();
  void setSchemeID(uint16_t id);
  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = specific;
  comparision_indicate_flag mSchemaID_flag = has_value;

  bool operator==(SupportedAppProtocolRes &object_compare)
  {
    bool arr_result[2] = {true, true};
    bool final_result = true;
    switch (this->mSchemaID_flag)
    {
    case specific:
      if (this->mSchemaID != object_compare.getSchemeID())
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      break;
    case omit:
    default:
      break;
    }
    switch (this->mResponseCode_flag)
    {
    case specific:
      if (this->mResponseCode != object_compare.getResponseCode())
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 2)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    for (int i = 0; i < 2; i++)
    {
      if (arr_result[i] == false)
      {
        final_result = false;
        break;
      }
    }
    return final_result;
  }

private:
  uint8_t mSchemaID = 0;
  appHandresponseCodeType mResponseCode = (appHandresponseCodeType)3;
};

#endif //EVCC_SUPPORTEDAPPPROTOCOLRES_H
