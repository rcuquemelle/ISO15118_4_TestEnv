

#ifndef EVCC_SERVICEPAYMENTSELECTIONREQ_H
#define EVCC_SERVICEPAYMENTSELECTIONREQ_H

#include "../V2gExiMessage.h"

class ServicePaymentSelectionReq : public V2gExiMessage
{
public:
  ServicePaymentSelectionReq();
  virtual ~ServicePaymentSelectionReq();
  void dumpMsg(void) override;
  paymentOptionType getSelectedPaymentOption();
  void setSelectedPaymentOption(paymentOptionType payment);
  SelectedServiceListType *getSelectedServiceList();
  void setSelectedServiceList(SelectedServiceListType *list);

  comparision_indicate_flag pSelectedServiceList_flag = has_value;
  comparision_indicate_flag mSelectedPaymentOption_flag = has_value;

  bool operator==(ServicePaymentSelectionReq &object_compare)
  {
    bool arr_result[2] = {true, true};
    bool final_result = true;
    SelectedServiceListType *pSelectedServiceListCmp = object_compare.getSelectedServiceList();
    switch (this->pSelectedServiceList_flag)
    {
    case specific:
      if ((pSelectedServiceListCmp != nullptr) && (this->pSelectedServiceList != nullptr))
      {
        arr_result[0] = (0 == memcmp(pSelectedServiceListCmp, this->pSelectedServiceList, sizeof(SelectedServiceListType)));
      }
      else
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if (pSelectedServiceListCmp == nullptr)
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->mSelectedPaymentOption_flag)
    {
    case specific:
      if (this->mSelectedPaymentOption != object_compare.getSelectedPaymentOption())
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (object_compare.getSelectedPaymentOption() > 1)
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
  SelectedServiceListType *pSelectedServiceList = nullptr;
  paymentOptionType mSelectedPaymentOption = (paymentOptionType)2;
};

#endif //EVCC_SERVICEPAYMENTSELECTIONREQ_H
