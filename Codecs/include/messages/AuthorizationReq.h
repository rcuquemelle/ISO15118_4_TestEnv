

#ifndef EVCC_AUTHORIZATIONREQ_H
#define EVCC_AUTHORIZATIONREQ_H

#include <vector>
#include "../V2gExiMessage.h"

class AuthorizationReq : public V2gExiMessage
{
public:
  AuthorizationReq();
  virtual ~AuthorizationReq();
  void dumpMsg(void) override;
  std::vector<uint8_t> *getGenChallenge(void);
  void setGenChallenge(const std::vector<uint8_t> &challenge);

  std::string &getId();
  void setId(const std::string &id);

  comparision_indicate_flag mGenchallenge_flag = omit;
  comparision_indicate_flag mId_flag = omit;

  bool operator==(AuthorizationReq &object_compare)
  {
    bool arr_result[2] = {true, true};
    bool final_result = true;
    std::vector<uint8_t> *pGenChallengeValueCmp = object_compare.getGenChallenge();

    switch (this->mGenchallenge_flag)
    {
    case specific:
      arr_result[0] = (this->pGenChallenge == (*pGenChallengeValueCmp));
      break;
    case has_value:
      arr_result[0] = (nullptr != pGenChallengeValueCmp);
    case omit:
    default:
      break;
    }
    switch (this->mId_flag)
    {
    case specific:
      arr_result[1] = (0 == this->mId.compare(object_compare.getId()));
      break;
    case has_value:
      arr_result[1] = ("" != object_compare.getId());
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
  std::vector<uint8_t> pGenChallenge;
  std::string mId;
};

#endif //EVCC_AUTHORIZATIONREQ_H
