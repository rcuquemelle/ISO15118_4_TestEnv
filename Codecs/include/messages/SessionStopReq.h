//
// Created by james on 30/10/2020.
//

#ifndef EVCC_SESSIONSTOPREQ_H
#define EVCC_SESSIONSTOPREQ_H

#include "../V2gExiMessage.h"

class SessionStopReq : public V2gExiMessage
{
public:
  SessionStopReq();
  virtual ~SessionStopReq() {}
  void dumpMsg(void) override;
  void setChargingSession(chargingSessionType type);
  chargingSessionType getChargingSession();

  comparision_indicate_flag mChargingSession_flag = has_value;

  bool operator==(SessionStopReq &object_compare)
  {
    bool final_result = true;
    switch (this->mChargingSession_flag)
    {
    case specific:
      if (this->mChargingSession != object_compare.getChargingSession())
      {
        final_result = false;
      }
      break;
    case has_value:
      if (object_compare.getChargingSession() > 1)
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
  chargingSessionType mChargingSession = (chargingSessionType)2;
};

#endif //EVCC_SESSIONSTOPREQ_H
