

#ifndef EVCC_CABLECHECKRES_H
#define EVCC_CABLECHECKRES_H

#include "../V2gExiMessage.h"

class CableCheckRes : public V2gExiMessage
{
public:
  CableCheckRes();
  CableCheckRes(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~CableCheckRes();

  responseCodeType getResponseCode();
  void setResponseCode(responseCodeType code);
  DC_EVSEStatusType *getDCEVSEStatus();
  void setDCEVSEStatus(DC_EVSEStatusType *status);
  EVSEProcessingType getEVSEProcessing();
  void setEVSEProcessing(EVSEProcessingType proc);

  void dumpMsg(void) override;
  comparision_indicate_flag mResponseCode_flag = has_value;
  comparision_indicate_flag pDC_EVSEStatus_flag = has_value;
  comparision_indicate_flag mEVSEProcessing_flag = has_value;

  bool operator==(CableCheckRes &object_compare)
  {
    bool arr_result[3] = {true, true, true};
    bool final_result = true;
    switch (this->pDC_EVSEStatus_flag)
    {
    case specific:
      arr_result[0] = (0 == memcmp(object_compare.getDCEVSEStatus(), this->getDCEVSEStatus(), sizeof(DC_EVSEStatusType)));
      break;
    case has_value:
    case omit:
    default:
      break;
    }
    switch (this->mResponseCode_flag)
    {
    case specific:
      if (this->getResponseCode() != object_compare.getResponseCode())
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
    switch (this->mEVSEProcessing_flag)
    {
    case specific:
      if (this->getEVSEProcessing() != object_compare.getEVSEProcessing())
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (object_compare.getEVSEProcessing() > 2)
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
};

#endif //EVCC_CABLECHECKRES_H
