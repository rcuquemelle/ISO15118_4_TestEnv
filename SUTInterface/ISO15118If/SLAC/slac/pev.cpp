#include "slac.h"
#include "pev.h"
#include "TestSystemLogging.h"
using namespace DataStructure_HAL_61851;

#define START_REINIT_SLAC 1
#define NO_REINIT_SLAC 0

// store previous BC state, to verify if state change occur
IEC_61851_States Plc::preState = IEC_61851_States::none_;
std::atomic<uint8_t> Plc::reInitCounter = NO_REINIT_SLAC;
std::atomic<pevStateType> Plc::state = pevStateType_DISCONNECTED;
SeccBasicSignaling *Plc::slacInstance = nullptr;
uint8_t Plc::C_conn_max_match = 3;
uint8_t Plc::C_EV_vald_nb_toggles = 3; // 1-3
uint8_t Plc::C_EVSE_match_parallel = 5;
uint8_t Plc::C_sequ_retry = 2;
uint8_t Plc::C_EV_match_MNBC = 10;
uint8_t Plc::C_EV_match_retry = 2;
uint8_t Plc::C_EV_match_signalattn_direct = 40;
uint8_t Plc::C_EV_match_signalattn_indirect = 80;
uint8_t Plc::C_EV_start_atten_char_inds = 3;
float Plc::T_conn_init_HLC = 0.2;
float Plc::T_conn_resume = 6;
float Plc::T_conn_max_comm = 8;
float Plc::T_conn_resetup = 15;
float Plc::T_vald_detect_time = 0.2;
float Plc::TP_EV_vald_state_duration = 0.3; // 0.2-0.4
float Plc::TP_EV_vald_toggle = 2.4;         // 0.6-3.5
float Plc::TT_EVSE_vald_toggle = 3.5;
float Plc::TP_match_leave = 1;
float Plc::T_step_EF = 4;
float Plc::TP_amp_map_exchange = 0.1;
float Plc::TP_EV_batch_msg_interval = 0.02; // 0.02-0.05
float Plc::TP_EV_match_session = 0.5;
float Plc::TP_EV_SLAC_init = 15; // 10
float Plc::TP_EVSE_avg_atten_calc = 0.1;
float Plc::TP_link_ready_notification = 0.2; // 0.2 - 1
float Plc::TP_match_response = 0.1;
float Plc::TP_match_sequence = 0.1;
float Plc::TT_amp_map_exchange = 0.2;
float Plc::TT_EV_atten_results = 1.2;
float Plc::TT_EVSE_match_MNBC = 0.6;
float Plc::TT_EVSE_match_session = 10;
float Plc::TT_EVSE_SLAC_init = 20; // 20-50
float Plc::TT_match_join = 12;
float Plc::TT_match_response = 0.2;
float Plc::TT_match_sequence = 0.4;
float Plc::TT_matching_repetition = 10;
float Plc::TT_matching_rate = 0.4;
float RANDOM_DELAY = 0;
Plc::Plc(const std::string &config_file, const std::string &interface_name, const std::shared_ptr<SeccBasicSignaling> &_BC, const std::shared_ptr<CppCommon::Asio::Service> &_service, float delay_value)
{
  RANDOM_DELAY = delay_value;
  // pev.ini file
  this->cfgFile = config_file;
  // qca interface name
  this->ifName = interface_name;
  // reference to BC instance (for BCB toggle and state change notification)
  this->BC = _BC;
  // asio service
  this->service = _service;
  this->runTheadFlag = false;
  this->threadCompleted = false;
  this->_onEventHandler = nullptr;
  this->BC->setNotifyStateChange(&Plc::updateControlPilotState);
  this->mTimer = std::make_shared<PATimer>("TP_EV_SLAC_Init", Plc::TP_EV_SLAC_init , service);
  this->mTimer->setNotifyFunc(&Plc::timeout_pev_init);
  this->mTimerGeneral = std::make_shared<PATimer>("general", 3, service);
}
Plc::~Plc()
{
  Logging::info(LogSLAC_ENABLE, "[SLAC]: disposed");
}

const std::vector<IEC_61851_States> TRG_INIT_STATE = {IEC_61851_States::B, IEC_61851_States::C, IEC_61851_States::D};
const std::vector<IEC_61851_States> ORG_INIT_STATE = {IEC_61851_States::A, IEC_61851_States::E, IEC_61851_States::F, IEC_61851_States::none_};
static bool isInStateArr(IEC_61851_States a, const std::vector<IEC_61851_States> &arr)
{
  for (auto &&i : arr)
  {
    if (i == a)
    {
      return true;
    }
  }
  return false;
}
void Plc::timeout_pev_init(bool timeout)
{
  Logging::info(LogSLAC_ENABLE, "[SLAC]: Timeout pev init");
  Plc::state = pevStateType_DISCONNECTED;
}

bool Plc::reinitValid() {
  return isInStateArr(this->BC->getState(), TRG_INIT_STATE);
}
// map to IEC61851 to notify when state change
void Plc::updateControlPilotState(IEC_61851_States cur_state)
{
  // handling state change to B (plugin or reinit)
  if (Plc::preState != cur_state)
  {
    // trigger condition (AEF to BCD)
    if (isInStateArr(Plc::preState, ORG_INIT_STATE) && isInStateArr(cur_state, TRG_INIT_STATE))
    {
      Logging::info(LogSLAC_ENABLE, "[SLAC]: trigger init matching");
      // start timer 10s - after timeout no matched session then push event to upper layer TP_EV_SLAC_init
      PAsleep(RANDOM_DELAY);
      Plc::state = pevStateType_MATCHING;
    }
    else if (isInStateArr(Plc::preState, TRG_INIT_STATE) && isInStateArr(cur_state, ORG_INIT_STATE))
    {
      // transition from BCD to AEF
      Plc::state = pevStateType_DISCONNECTED;
      Plc::reInitCounter = START_REINIT_SLAC;
      Logging::info(LogSLAC_ENABLE, "[SLAC]: end matching");
    }
    Plc::preState = cur_state;
  }
}
static void pevSleep(float val)
{
  uint64_t micros_val = val * 1000000;
  std::this_thread::sleep_for(std::chrono::microseconds(micros_val));
}
void callBCBToggle(float period, uint8_t number)
{
  if (Plc::slacInstance != nullptr)
    ((SeccBasicSignaling *)Plc::slacInstance)->toggleBCB(period, number);
}

bool Plc::init(bool runThread)
{
  Plc::slacInstance = this->BC.get();
  // open eth channel and set session config data
  if (1 == api_initialize(this->cfgFile.c_str(), this->ifName.c_str()))
  {
    // error return
    Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed to open eth channel or incorrect config data");
    return false;
  }
  // set qca interface attribute NMK, NID,
  if (1 == api_set_key())
  {
    // error return
    Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed to set param for QCA interface");
    return false;
  }
  pevSleep(2);
  if (runThread == true)
  {
    // execute run thread to monitor slac matching
    this->runTheadFlag = true;
    this->threadCompleted = false;
    // no need to reinit
    Plc::reInitCounter = NO_REINIT_SLAC;
    this->service->Dispatch([this]()
                            { this->run(); });
  }
  Logging::debug(LogSLAC_ENABLE, "[SLAC]: Init qca interface completed");
  return true;
}

bool Plc::reinit(void)
{
  // try close previous fd
  if (0 != api_close())
  {
    Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed to close eth channel");
  }
  // open eth channel and set session config data
  if (1 == api_initialize(this->cfgFile.c_str(), this->ifName.c_str()))
  {
    // error return
    Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed to open eth channel or incorrect config data");
    return false;
  }
  // set qca interface attribute NMK, NID,
  pevSleep(1);
  if (1 == api_set_key())
  {
    // error return
    Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed to set param for QCA interface");
    return false;
  }
  pevSleep(1);
  return true;
}
#define FUNC_SIZE 4
matchingType funcArr[FUNC_SIZE] = {api_param_exchange, api_start_atten_char, api_mnbc_sound, api_atten_char};
typedef enum
{
  PARAM_EXCHANGE = 0,
  START_ATTEN_CHAR,
  MNBC_SOUND,
  ATTEN_CHAR,
  VALIDATE,
  SLAC_MATCH,
  AMP_MAP,
  BCB_TOGGLE,
  RESET
} funcCodeType;

const char *FUNC_NAME[] = {
    [PARAM_EXCHANGE] = "CM_SLAC_PARAM",
    [START_ATTEN_CHAR] = "CM_START_ATTEN_CHAR",
    [MNBC_SOUND] = "CM_MNBC_SOUND",
    [ATTEN_CHAR] = "CM_ATTEN_CHAR",
    [VALIDATE] = "CM_VALIDATE",
    [SLAC_MATCH] = "CM_SLAC_MATCH",
    [AMP_MAP] = "CM_AMP_MAP"};
typedef struct matchingTransitionType_St
{
  funcCodeType preFunc;
  bool retCode;
  funcCodeType nextFunc;
} matchingTransitionType;
#define TRANSITION_SIZE 10
const matchingTransitionType transitionTable[TRANSITION_SIZE]{
    {PARAM_EXCHANGE, false, PARAM_EXCHANGE},
    {PARAM_EXCHANGE, true, START_ATTEN_CHAR},
    {START_ATTEN_CHAR, false, RESET},
    {START_ATTEN_CHAR, true, MNBC_SOUND},
    {MNBC_SOUND, false, RESET},
    {MNBC_SOUND, true, ATTEN_CHAR},
    {ATTEN_CHAR, false, RESET},
    {ATTEN_CHAR, true, VALIDATE}};
static funcCodeType lookup_transition(funcCodeType current_func, bool returnCode)
{
  for (size_t i = 0; i < TRANSITION_SIZE; i++)
  {
    if ((transitionTable[i].preFunc == current_func) && (transitionTable[i].retCode == returnCode))
    {
      if (true == returnCode)
      {
        Logging::info(LogSLAC_ENABLE, fmt::format("[SLAC]: {} successful", FUNC_NAME[current_func]));
      }
      else
      {
        Logging::info(LogSLAC_ENABLE, fmt::format("[SLAC]: {} retry", FUNC_NAME[current_func]));
      }
      return transitionTable[i].nextFunc;
    }
  }
  return RESET;
}

void Plc::notifyEvent(pevStateType event)
{
  static pevStateType state = pevStateType_DISCONNECTED;
  if (event != state)
  {
    if (this->_onEventHandler != nullptr){
      (*this->_onEventHandler)(event);
      state = event;
    }
  }
}

void Plc::run(void)
{
  funcCodeType funcType = PARAM_EXCHANGE;
  bool rstCode = false;
  Logging::debug(LogSLAC_ENABLE, "[SLAC]: Thread dispatch");
  while (this->runTheadFlag)
  {
    switch (Plc::state)
    {
    // execute whenever control pilot state change from B,C,D to A, E, F
    case pevStateType_DISCONNECTED:
    {
      this->notifyEvent(pevStateType_DISCONNECTED);
      funcType = PARAM_EXCHANGE;
      rstCode = false;
      // set reInitCounter = 1 to trigger reinit (set qca channel info)
      if (Plc::reInitCounter > NO_REINIT_SLAC)
      {
        if (false == this->reinit())
        {
          // reinit failed
          Plc::reInitCounter++;
          Logging::error(LogSLAC_ENABLE, "[SLAC]: Reinit operation, failed to set param for QCA interface");
          pevSleep(1);
        }
        else
        {
          Plc::reInitCounter = NO_REINIT_SLAC;
          Logging::info(LogSLAC_ENABLE, "[SLAC]: ReInit qca interface completed");
          if (this->reinitValid()) {
            Plc::state = pevStateType_MATCHING;
          }
        }
      }
      // end after 10 retry
      if (Plc::reInitCounter == 10)
      {
        Plc::reInitCounter = NO_REINIT_SLAC;
      }
      break;
    }
    case pevStateType_MATCHING:
    {
      this->notifyEvent(pevStateType_MATCHING);
      // DISCONNECT
      // loop param exchange: CM_SLAC_PARAM.REQ|CM_SLAC_PARAM.CNF
      // UNMATCHED
      // signal strength measure: (C_EV_start_atten_char_inds 3 times)CM_START_ATTEN_CHAR.IND|CM_START_ATTEN_CHAR.RSP,
      // CM_MNBC_SOUND.IND, CM_ATTEN_CHAR.IND|CM_ATTEN_CHAR.RSP
      // TP_EV_vald_state_duration Duration of each state B or C within the BCB-Toggle 200 400
      // evse potential found -> validate
      // evse found -> skip validate
      // evse not found -> skip session
      // start maching timer -> timeout after 10s
      this->mTimer->start();
      rstCode = (*funcArr[funcType])();
      auto prefunc = funcType;
      funcType = lookup_transition(funcType, rstCode);
      if (funcType == RESET)
      {
        Plc::state = pevStateType_DISCONNECTED;
        Plc::reInitCounter = START_REINIT_SLAC;
        // notify SLAC fail and reinit
        Logging::error(LogSLAC_ENABLE, fmt::format("[SLAC]: Failed message {}", FUNC_NAME[prefunc]));
      }
      // pass all previous func
      else if (funcType == VALIDATE)
      {
        // check evseDetectType
        int val = api_avg_atten_val();
        if (val < Plc::C_EV_match_signalattn_direct)
        {
          // skip move to MATCH
          Plc::state = pevStateType_MATCHED;
          Logging::info(LogSLAC_ENABLE, fmt::format("[SLAC]: Average attenuation {0} less than limit {1} | MATCHED", val, Plc::C_EV_match_signalattn_direct));
        }
        else if (val < Plc::C_EV_match_signalattn_indirect)
        {
          Logging::info(LogSLAC_ENABLE, fmt::format("[SLAC]: Average attenuation {0} between {1} - {2} | VALIDATE", val, Plc::C_EV_match_signalattn_direct, Plc::C_EV_match_signalattn_indirect));
          Logging::info(LogSLAC_ENABLE, "[SLAC]: SLAC Validation 1st phase");
          this->mTimerGeneral->start();
          while ((0 > api_validate(0, 0, 0, nullptr)) && (this->mTimerGeneral->running()))
          {
          }
          if (this->mTimerGeneral->timeout() == true)
          {
            Plc::state = pevStateType_DISCONNECTED;
            Plc::reInitCounter = START_REINIT_SLAC;
            Logging::error(LogSLAC_ENABLE, "[SLAC]: Timeout when retry 1st step validation");
          }
          else
          {
            this->mTimerGeneral->stop();
            Logging::info(LogSLAC_ENABLE, "[SLAC]: SLAC Validation 2nd phase");
            if (0 > api_validate((uint8_t)(Plc::TP_EV_vald_toggle * 10), Plc::TP_EV_vald_state_duration, Plc::C_EV_vald_nb_toggles, callBCBToggle))
            {
              // fail validation
              Plc::state = pevStateType_DISCONNECTED;
              Plc::reInitCounter = START_REINIT_SLAC;
              Logging::error(LogSLAC_ENABLE, "[SLAC]: Failed 2nd step validation");
            }
            else
            {
              Plc::state = pevStateType_MATCHED;
              Logging::info(LogSLAC_ENABLE, "[SLAC]: SLAC Validation successful");
            }
          }
        }
        else
        {
          // skip to reinit, average attenuation value to large
          Plc::state = pevStateType_DISCONNECTED;
          Plc::reInitCounter = START_REINIT_SLAC;
          Logging::info(LogSLAC_ENABLE, fmt::format("[SLAC]: Average attenuation {0} more than {1} | UNMATCHED", val, this->C_EV_match_signalattn_indirect));
        }
      }
      break;
    }
    case pevStateType_MATCHED:
    {
      this->mTimer->stop();
      if (true == api_match())
      {
        Logging::info(LogSLAC_ENABLE, "[SLAC]: SLAC MATCH successful");
        bool set_key_flag = false;
        for (size_t i = 0; i < 5; i++)
        {
          if (0 == api_set_key()) {
            pevSleep(1);
            set_key_flag = true;
            break;
          }
        }
        if (set_key_flag)
        {
          this->notifyEvent(pevStateType_MATCHED);
          Plc::state = pevStateType_LOOP;
          Logging::info(LogSLAC_ENABLE, "[SLAC]: Join logical network successful");
        }
        else
        {
          Plc::state = pevStateType_DISCONNECTED;
          Plc::reInitCounter = START_REINIT_SLAC;
          Logging::info(LogSLAC_ENABLE, "[SLAC]: Failed to set key of evse logical network");
        }
      }
      else
      {
        Plc::state = pevStateType_DISCONNECTED;
        Plc::reInitCounter = START_REINIT_SLAC;
        Logging::info(LogSLAC_ENABLE, "[SLAC]: No CM_SLAC_MATCH.CNF received. Failed match");
      }
      break;
    }
    case pevStateType_LOOP:
    {
      this->notifyEvent(pevStateType_LOOP);
      break;
    }
    case pevStateType_SLEEP:
    {
      /* code */
      break;
    }
    default:
      break;
    }
  }
  this->threadCompleted = true;
}

void Plc::stop(void)
{
  // reset qca configuration, close slac socket fd and stop running thread
  if (this->runTheadFlag == true)
  {
    this->runTheadFlag = false;
    while (false == this->threadCompleted);
    this->threadCompleted = false;
    Logging::info(LogSLAC_ENABLE, "[SLAC]: thread stop");
  }
  else
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: thread already stop");
  }
  Logging::info(LogSLAC_ENABLE, "[SLAC]: stop and close slac fd");
  this->reinit();
  if (0 != api_close())
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: Fail to close Channel fd");
  }
}
void Plc::close_interface(void)
{
  // close slac socket fd and stop running thread
  if (0 == api_close())
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: close Channel fd");
  }
  else
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: Fail to close Channel fd");
  }
  if (this->runTheadFlag == true)
  {
    this->runTheadFlag = false;
    while (false == this->threadCompleted);
    this->threadCompleted = false;
    Logging::info(LogSLAC_ENABLE, "[SLAC]: thread stop");
  }
  else
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: thread already stop");
  }
}
void Plc::pause(void)
{
  // start running thread and move to pause operation, wait for wakeup operation
  this->runTheadFlag = true;
  this->threadCompleted = false;
  // no need to reinit
  Plc::reInitCounter = NO_REINIT_SLAC;
  Plc::state = pevStateType_SLEEP;
  if (0 == api_open())
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: open Channel fd");
  }
  else
  {
    Logging::info(LogSLAC_ENABLE, "[SLAC]: Fail to open Channel fd");
  }
  this->service->Dispatch([this]()
                          { this->run(); });
}