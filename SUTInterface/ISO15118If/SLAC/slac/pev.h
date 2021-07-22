#ifndef __PEV_H__
#define __PEV_H__
#include "TsDataType.h"
#include "PAInterface.h"
#include <string>
#include <atomic>
#include <memory>
#include "SeccBasicSignaling.h"
typedef enum en_pevStateType {
  pevStateType_DISCONNECTED = 0,
  pevStateType_UNMATCHED,
  pevStateType_MATCHING,
  pevStateType_MATCHED,
  pevStateType_SLEEP,
  pevStateType_LOOP
} pevStateType;

typedef enum en_evseDetectType {
  evseDetectType_FOUND = 0,
  evseDetectType_POTENTIALLY_FOUND,
  evseDetectType_NOT_FOUND,
  evseDetectType_CONNECTED
} evseDetectType;

// get 61851 state -> A
// start in disconnected state -> DISCONNECT
// detect B change move to start pev -> UNMATCHED
// matching -> MATCHED -> notify upper
// dected A-> UNMATCH -> ,DISCONNECT
class onSLACEventType {
public:
  onSLACEventType(){
  }
  virtual void operator() (pevStateType pev_state) {}
};

// SLAC FLOW
// transition to B detect (plugin or reinit)
// TP_EV_SLAC_init timer - send CM_SLAC_PARAM.REQ, with for CNF until timeout
//
// static class operation push to thread, report slac Plc status
class Plc : public std::enable_shared_from_this<Plc>
{
private:
  std::string cfgFile;
  std::string ifName;
  std::atomic<bool> runTheadFlag;
  std::atomic<bool> threadCompleted;
  std::shared_ptr<SeccBasicSignaling> BC;
  std::shared_ptr<CppCommon::Asio::Service> service;
  std::shared_ptr<PATimer> mTimer;
  std::shared_ptr<PATimer> mTimerGeneral;
  std::shared_ptr<onSLACEventType> _onEventHandler;

public:
  /* SYSTEM */
  /* Number of retries of matching process */
  static uint8_t C_conn_max_match;
  /* Number of BCB-Toggles */
  static uint8_t C_EV_vald_nb_toggles;
  static uint8_t C_EVSE_match_parallel;
  /* Number of matching retries by Control Pilot state E transitions */
  static uint8_t C_sequ_retry;
  /* Minimum B state duration after a state F, D, or C */
  static float T_conn_init_HLC;
  /* Time after the wake up trigger (e.g. BCB-Toggle) until the lowlayer communication module is ready for communciation */
  static float T_conn_resume;
  /* Time after plug-in until the lowlayer communication module is ready for communciation */
  static float T_conn_max_comm;
  /* Time to resetup the matching process after a loss of communication */
  static float T_conn_resetup;
  /* Time to detect a variation of the state on EVSE side */
  static float T_vald_detect_time;
  /* Duration of each state B or C within the BCB-Toggle */
  static float TP_EV_vald_state_duration;
  /* Duration of BCB-Toggle sequence */
  static float TP_EV_vald_toggle;
  static float TT_EVSE_vald_toggle;
  /* Time to stay at E/F state */
  static float TP_match_leave;
  /* Time to stay at E/F state */
  static float T_step_EF;
  /* SLAC */
  /* Timeout value for EV SLAC init */
  static uint8_t C_EV_match_MNBC;
  static uint8_t C_EV_match_retry;
  static uint8_t C_EV_match_signalattn_direct;
  static uint8_t C_EV_match_signalattn_indirect;
  static uint8_t C_EV_start_atten_char_inds;
  static float TP_amp_map_exchange;
  static float TP_EV_batch_msg_interval;
  static float TP_EV_match_session;
  static float TP_EV_SLAC_init;
  static float TP_EVSE_avg_atten_calc;
  static float TP_link_ready_notification;
  static float TP_match_response;
  static float TP_match_sequence;
  static float TT_amp_map_exchange;
  static float TT_EV_atten_results;
  static float TT_EVSE_match_MNBC;
  static float TT_EVSE_match_session;
  static float TT_EVSE_SLAC_init;
  static float TT_match_join;
  static float TT_match_response;
  static float TT_match_sequence;
  static float TT_matching_repetition;
  static float TT_matching_rate;
  static DataStructure_HAL_61851::IEC_61851_States preState;
  static std::atomic<uint8_t> reInitCounter;
  static std::atomic<pevStateType> state;
  static SeccBasicSignaling *slacInstance;
public:
  Plc(const std::string &config_file, const std::string &interface_name, const std::shared_ptr<SeccBasicSignaling> &_BC, const std::shared_ptr<CppCommon::Asio::Service>& _service);
  ~Plc();
  bool init(bool runThread);
  bool reinit(void);
  void run(void);
  pevStateType getState(void) {return Plc::state;}
  void close_interface(void);
  void pause(void);
  void stop(void);
  void setEventCallBack(const std::shared_ptr<onSLACEventType>& eventHandler) { _onEventHandler = eventHandler; }
  static void updateControlPilotState(DataStructure_HAL_61851::IEC_61851_States cur_state);
  static void timeout_pev_init(bool timeout);
  bool reinitValid(void);
private:
  void notifyEvent(pevStateType event);
};

#endif // __PEV_H__
