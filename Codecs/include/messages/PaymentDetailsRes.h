

#ifndef EVCC_PAYMENTDETAILSRES_H
#define EVCC_PAYMENTDETAILSRES_H

#include <vector>
#include "../V2gExiMessage.h"

class PaymentDetailsRes : public V2gExiMessage  {
public:
    PaymentDetailsRes();
    PaymentDetailsRes(std::shared_ptr<V2gExiMessage>& msg);
    virtual ~PaymentDetailsRes();

    responseCodeType getResponseCode();
    void setResponseCode(responseCodeType code);

    std::vector<uint8_t>& getGenChallenge(void);
    void setGenChallenge(const std::vector<uint8_t> &challenge);

    int64_t getEVSETimeStamp();
    void setEVSETimeStamp(int64_t timestamp);
    void dumpMsg(void) override;
    comparision_indicate_flag mResponseCode_flag = specific;
    comparision_indicate_flag GenChallenge_flag = has_value;
    comparision_indicate_flag mEVSETimeStamp_flag =  has_value;

    bool operator==(PaymentDetailsRes &object_compare)
    {
      bool arr_result[3] = {true, true, true};
      bool final_result = true;

      std::vector<uint8_t> receive_cha = object_compare.getGenChallenge();
      std::vector<uint8_t> expected_cha = this->getGenChallenge();
      switch (this->GenChallenge_flag) {
        case specific:
          arr_result[0] = (expected_cha == receive_cha);
          break;
        case has_value:
          if (receive_cha.size() == 0){
              arr_result[0] = false;
          }
          break;
        case omit:
        default:
          break;
      }
      switch (this->mResponseCode_flag)
      {
        case specific:
          if(this->mResponseCode != object_compare.getResponseCode())
          {
            arr_result[1] = false;
          }
          break;
        case has_value:
          if(object_compare.getResponseCode() > 25)
          {
            arr_result[1] = false;
          }
          break;
        case omit:
        default:
          break;
      }
      switch (this->mEVSETimeStamp_flag)
      {
        case specific:
          if(this->mEVSETimeStamp != object_compare.getEVSETimeStamp())
          {
            arr_result[2] = false;
          }
          break;
        case has_value:
          if(object_compare.getEVSETimeStamp() == 0)
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
    std::vector<uint8_t> pGenChallenge;
    responseCodeType mResponseCode = (responseCodeType)26;
    int64_t mEVSETimeStamp = 0;

};

#endif //EVCC_PAYMENTDETAILSRES_H
