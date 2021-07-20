

#ifndef EVCC_AUTHORIZATIONRES_H
#define EVCC_AUTHORIZATIONRES_H

#include "../V2gExiMessage.h"

class AuthorizationRes : public V2gExiMessage
{
public:
  AuthorizationRes();
  AuthorizationRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~AuthorizationRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);

  EVSEProcessingType getEVSEProcessing();
  void setEVSEProcessing(EVSEProcessingType proc);

  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = has_value;
  comparision_indicate_flag mEVSEProcessing_flag = has_value;

  bool operator==(AuthorizationRes &object_compare)
  {
    bool arr_result[2] = {true, true};
    bool final_result = true;
    switch (this->mResponseCode_flag)
    {
    case specific:
      if (this->getResponseCode() != object_compare.getResponseCode())
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (object_compare.getResponseCode() > 25)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mEVSEProcessing_flag)
    {
    case specific:
      if (this->getEVSEProcessing() != object_compare.getEVSEProcessing())
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (object_compare.getEVSEProcessing() > 2)
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
};

#endif //EVCC_AUTHORIZATIONRES_H
