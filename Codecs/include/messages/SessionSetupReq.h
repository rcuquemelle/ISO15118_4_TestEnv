

#ifndef EVCC_SESSIONSETUPREQ_H
#define EVCC_SESSIONSETUPREQ_H

#include "../V2gExiMessage.h"

class SessionSetupReq : public V2gExiMessage
{
public:
  SessionSetupReq();
  SessionSetupReq(std::shared_ptr<V2gExiMessage> &msg);
  virtual ~SessionSetupReq() {}
  void dumpMsg(void) override;
  std::vector<uint8_t>& getEVCCID(void);
  void setEVCCID(const std::vector<uint8_t> &evccid);

  comparision_indicate_flag mEVCCID_flag = has_value;

  bool operator==(SessionSetupReq &object_compare)
  {
    bool final_result = true;
    std::vector<uint8_t> receive_val = object_compare.getEVCCID();
    std::vector<uint8_t> expected_val = this->getEVCCID();
    switch (this->mEVCCID_flag)
    {
    case specific:
      final_result = (expected_val == receive_val);
      break;
    case has_value:
      if (receive_val.size() == 0)
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
  std::vector<uint8_t> mEVCCID;
};

#endif //EVCC_SESSIONSETUPREQ_H
