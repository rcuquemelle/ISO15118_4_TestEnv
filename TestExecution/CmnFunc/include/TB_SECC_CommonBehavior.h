#ifndef __TB_SECC_COMMONBEHAVIOR_H__
#define __TB_SECC_COMMONBEHAVIOR_H__

#include "Components.h"


class TestBehavior_SECC_CommonBehavior {
public:
  TestBehavior_SECC_CommonBehavior(const std::shared_ptr<SECC_Tester> &_mtc);
  ~TestBehavior_SECC_CommonBehavior();

  // check flag unexpected message conent of port receive queue
  bool a_SECC_Unexpected_Message_Content(verdict_val v_verdict,const std::string & v_message);
  bool a_SECC_Unexpected_Message_Content_002(verdict_val v_verdict,const std::string & v_message);
  // check unexpected message of port receive queue
  bool a_SECC_Unexpected_Message(verdict_val v_verdict,const std::string & v_message);

  bool a_SECC_Unexpected_V2G_Message(verdict_val v_verdict,const std::string & v_message);
  // check SDP port queue = flag = not receive any message
  bool a_No_SDP_Message(std::string v_message, verdict_val v_verdict);

  bool a_SDP_Message();
  bool a_SECC_TCPConnection_Status_Listener(verdict_val v_verdict,const std::string & v_message);
  bool isError();
  bool f_SECC_startSleepingPhase(float v_time);
  // SDP message request response timeout
  bool a_SECC_SDP_Timeout(verdict_val v_verdict);
  // V2G message pair timeout
  bool a_SECC_Timeout(verdict_val v_verdict);
  // HLC communication setup timeout
  bool a_SECC_CommunicationSetup_Timeout(verdict_val v_verdict);
  // Termination TCP did not occur due to SUT not disconnect
  bool a_SECC_TCP_Connection_Termination_Timeout();

  std::shared_ptr<SECC_Tester> mtc;
};

#endif // __TB_SECC_COMMONBEHAVIOR_H__