

#ifndef EVCC_SESSIONSETUPRES_H
#define EVCC_SESSIONSETUPRES_H

#include "../V2gExiMessage.h"

class SessionSetupRes : public V2gExiMessage
{
public:
  SessionSetupRes();
  SessionSetupRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~SessionSetupRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);

  std::string &getEVSEID();
  void setEVSEID(const std::string &id);

  uint64_t getEVSETimeStamp();
  void setEVSETimeStamp(uint64_t timestamp);
  void dumpMsg(void) override;
  comparision_indicate_flag mEVSEID_flag = has_value;
  comparision_indicate_flag mTimeStamp_flag = omit;
  comparision_indicate_flag mResponseCode_flag = has_value;

  bool operator==(SessionSetupRes &object_compare)
  {
    bool arr_result[3] = {true, true, true};
    bool final_result = true;
    std::string mEVSEIDCmpStr = object_compare.getEVSEID();
    switch (this->mEVSEID_flag)
    {
    case specific:
      arr_result[0] = (0 == this->mEVSEID.compare(mEVSEIDCmpStr));
      break;
    case has_value:
      arr_result[0] = (mEVSEIDCmpStr != "");
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
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->mTimeStamp_flag)
    {
    case specific:
      if (this->mTimeStamp != object_compare.getEVSETimeStamp())
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (object_compare.getEVSETimeStamp() == 0)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 3; i++)
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
  std::string mEVSEID = "";
  uint64_t mTimeStamp = 0;
  responseCodeType mResponseCode = (responseCodeType)26;
};

#endif //EVCC_SESSIONSETUPRES_H
