

#ifndef EVCC_PAYMENTDETAILSREQ_H
#define EVCC_PAYMENTDETAILSREQ_H

#include "../V2gExiMessage.h"

class PaymentDetailsReq : public V2gExiMessage
{
public:
  PaymentDetailsReq();
  virtual ~PaymentDetailsReq();
  void dumpMsg(void) override;
  std::string &getEMAID();
  void setEMAID(const std::string &emaid);

  CertificateChainType *getContractCertChain();
  void setContractCertChain(CertificateChainType *chain);

  comparision_indicate_flag mEMAID_flag = has_value;
  comparision_indicate_flag pContractSignatureCertChain_flag = has_value;

  bool operator==(PaymentDetailsReq &object_compare)
  {
    bool arr_result[2] = {true, true};
    bool final_result = true;

    CertificateChainType *receive_chain = object_compare.getContractCertChain();
    CertificateChainType *expect_chain = this->getContractCertChain();

    std::string expected_emaid = object_compare.getEMAID();
    std::string received_emaid = this->getEMAID();
    switch (this->mEMAID_flag)
    {
    case specific:
      arr_result[0] = (0 == expected_emaid.compare(received_emaid));
      break;
    case has_value:
      if (received_emaid.empty())
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }
    switch (this->pContractSignatureCertChain_flag)
    {
    case specific:
      if ((receive_chain != nullptr) && (expect_chain != nullptr))
      {
        arr_result[1] = (0 == memcmp(receive_chain, expect_chain, sizeof(CertificateChainType)));
      }
      else
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if (nullptr == receive_chain)
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
  std::string mEMAID = "";
  CertificateChainType *pContractSignatureCertChain = nullptr;
};

#endif //EVCC_PAYMENTDETAILSREQ_H
