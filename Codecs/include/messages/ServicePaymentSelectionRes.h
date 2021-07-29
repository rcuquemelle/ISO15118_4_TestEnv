

#ifndef EVCC_SERVICEPAYMENTSELECTIONRES_H
#define EVCC_SERVICEPAYMENTSELECTIONRES_H

#include "../V2gExiMessage.h"

class ServicePaymentSelectionRes : public V2gExiMessage  {
  public:
    ServicePaymentSelectionRes();
    ServicePaymentSelectionRes(std::shared_ptr<V2gExiMessage>& msg);
    virtual ~ServicePaymentSelectionRes();

    responseCodeType getResponseCode();
    void setResponseCode(responseCodeType code);
    void dumpMsg(void) override;
    comparision_indicate_flag mResponseCode_flag = specific;

    bool operator==(ServicePaymentSelectionRes &object_compare)
    {
      bool final_result = true;
      switch(this->mResponseCode_flag)
      {
        case specific:
          if (this->mResponseCode != object_compare.getResponseCode())
          {
            final_result = false;
          }
          break;
        case has_value:
          if (object_compare.getResponseCode() > 25)
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
    responseCodeType mResponseCode = (responseCodeType)26;
};


#endif //EVCC_SERVICEPAYMENTSELECTIONRES_H
