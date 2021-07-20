

#ifndef EVCC_METERRECEIPTREQ_H
#define EVCC_METERRECEIPTREQ_H

#include <vector>
#include "../V2gExiMessage.h"

class MeterReceiptReq : public V2gExiMessage
{
public:
  MeterReceiptReq();
  virtual ~MeterReceiptReq();
  void dumpMsg(void) override;
  std::string getId(void);
  void setId(const std::string& strId);

  std::vector<uint8_t> &getFieldSessionID(void);
  void setFieldSessionID(const std::vector<uint8_t> &value);

  uint16_t getSAScheduleTupleID();
  void setSAScheduleTupleID(uint16_t id);

  MeterInfoType *getMeterInfo();
  void setMeterInfo(MeterInfoType *meter);

  comparision_indicate_flag mSessionID_flag = has_value;
  comparision_indicate_flag mId_flag = omit;
  comparision_indicate_flag mSAScheduleTupleID_flag = omit;
  comparision_indicate_flag pMeterInfo_flag = has_value;

  bool operator==(MeterReceiptReq &object_compare)
  {
    bool arr_result[4] = {true, true, true, true};
    bool final_result = true;
    std::string mIDCmpStr = object_compare.getId();
    std::vector<uint8_t> mSessionIDCmp = object_compare.getFieldSessionID();
    MeterInfoType *pMeterInfoCmp = object_compare.getMeterInfo();

    switch (this->mSessionID_flag)
    {
    case specific:
      arr_result[0] = (mSessionIDCmp == pSessionId);
      break;
    case has_value:
      arr_result[0] = (0 != mSessionIDCmp.size());
    case omit:
    default:
      break;
    }
    switch (this->mId_flag)
    {
    case specific:
      arr_result[1] = (0 == this->mId.compare(mIDCmpStr));
      break;
    case has_value:
      arr_result[1] = (0 != mIDCmpStr.size());
      break;
    case omit:
    default:
      break;
    }
    switch (this->pMeterInfo_flag)
    {
    case specific:
      if ((pMeterInfoCmp != nullptr) && (this->pMeterInfo != nullptr))
      {
        arr_result[2] = (0 == memcmp(pMeterInfoCmp, this->pMeterInfo, sizeof(MeterInfoType)));
      }
      else
      {
        arr_result[2] = false;
      }
      break;
    case has_value:
      if (pMeterInfoCmp == nullptr)
      {
        arr_result[2] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mSAScheduleTupleID_flag)
    {
    case specific:
      if (this->mSAScheduleTupleID != object_compare.getSAScheduleTupleID())
      {
        arr_result[3] = false;
      }
      break;
    case has_value:
      if (object_compare.getSAScheduleTupleID() == 0)
      {
        arr_result[3] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    for (int i = 0; i < 4; i++)
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
  std::string mId = "";
  std::vector<uint8_t> pSessionId;
  uint8_t mSAScheduleTupleID = 0;
  MeterInfoType *pMeterInfo = nullptr;
};

#endif //EVCC_METERRECEIPTREQ_H
