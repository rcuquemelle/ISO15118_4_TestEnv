#ifndef _SECCBASICSIGNALING_H_
#define _SECCBASICSIGNALING_H_

#define PI_ENABLE 1
#define NEW_BOARD 1
#include "TsDataType.h"
#include "asiowrapper/service.h"
#include "asiowrapper/timer.h"
#include <vector>
#if (PI_ENABLE == 1)
#include <pigpio.h>
#include "frame_com_service.h"
#endif

typedef void (*NotifyFunc)(DataStructure_HAL_61851::IEC_61851_States);

class onBCEventType
{
public:
  onBCEventType()
  {
  }
  virtual void operator()(en_BCEventType event) {}
};
#if (PI_ENABLE == 1)
typedef struct stm32_if_data_t_St
{
  bool cmd_flags[FRAME_CMD_NUM];
  uint8_t receive_data[256];
  uint8_t len;
} stm32_if_data_t;
#endif
// handle control HAL 61851 and notify event on changes
class SeccBasicSignaling : public std::enable_shared_from_this<SeccBasicSignaling>
{
private:
#if (NEW_BOARD == 1)
#define SIZE_RELAY 6
#define NUM_RELAY_CONTROL 6
#else
#define SIZE_RELAY 10
#define NUM_RELAY_CONTROL 7
#endif
#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0
#define RASP_GPIO_OK 0
#define RASP_GPIO_NG 0xFF
#define STM32_POLL_RATE 10
#define BUTTON_SAMPLING_RATE 2
#define NUM_STATE_CONTROL 5

#define INPUT_ISR_PIN 21
public:
#if (NEW_BOARD == 1)
  typedef enum relay_pin_t_En{
      RELAY_PE_LINE = 26,      // PE line, ON = connect/ OFF = disconnect
      RELAY_SHORT_CIRCUIT = 0, // short circuit, ON = no short/ OFF short
      RELAY_DIODE = 5,         // diode line, ON = has diode/ OFF no diode
      RELAY_RES_B = 6,         // resistor value to state B
      RELAY_RES_C = 13,        // resistor value to state C (need RES_B connect)
      RELAY_RES_D = 19         // resistor  value to state D (need RES_B and RES_C)
  } relay_pin_t;
#else
  typedef enum relay_pin_t_En
  {
    RELAY_CP_LINE = 5,        // CP line, ON = connect/ OFF = disconnect           | relay1
    RELAY_PE_LINE = 21,       // PE line, ON = connect/ OFF = disconnect           | relay6
    RELAY_SHORT_CIRCUIT = 26, // short circuit, ON = no short/ OFF short           | relay5
    RELAY_DIODE = 20,         // diode line, ON = has diode/ OFF no diode          | relay7
    RELAY_PROX = 12,          // proximity line, ON = proximity avail/ OFF no prox | relay9
    RELAY_RES_B = 6,          // resistor value to state B                         | relay2
    RELAY_RES_C = 13,         // resistor value to state C (need RES_B connect)    | relay3
    RELAY_RES_D = 19,         // resistor  value to state D (need RES_B and RES_C) | relay4
    RELAY_ICU_RESET = 16,     // reset ICU, ON = ICU ON/ OFF = ICU OFF             | relay8
    RELAY_TBD = 1             // TBD                                               | relay10
  } relay_pin_t;
#endif
  typedef enum relay_val_En
  {
    RELAY_VAL_OFF = 0, // not available connection
    RELAY_VAL_ON = 1   // available     connection
  } relay_val_t;
  typedef enum relay_type_En
  {
    DEFAULT = 0,
    REVERSE = 1
  } relay_type;
  typedef struct relay_St
  {
    relay_pin_t gpio;
    uint8_t default_val;
    relay_type type;
    uint8_t pull_type;
  } relay_t;

private:
  // SET_RELAY[available_gpio[idx].type][RELAY_VAL_OFF] | trigger operation
  // SET_RELAY[available_gpio[idx].type][RELAY_VAL_ON] | default normal state
  const uint8_t SET_RELAY[2][2] = {
      // default:  RELAY_VAL_OFF, RELAY_VAL_ON
      [DEFAULT] = {GPIO_PIN_RESET, GPIO_PIN_SET},
      // reverse:  RELAY_VAL_OFF, RELAY_VAL_ON
      [REVERSE] = {GPIO_PIN_SET, GPIO_PIN_RESET}};
#if (PI_ENABLE == 1)
#if (NEW_BOARD == 1)
  const relay_t relay_list[SIZE_RELAY] = {
      {RELAY_PE_LINE, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},
      {RELAY_SHORT_CIRCUIT, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},
      {RELAY_DIODE, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},
      {RELAY_RES_B, GPIO_PIN_SET, DEFAULT, PI_PUD_DOWN},
      {RELAY_RES_C, GPIO_PIN_SET, DEFAULT, PI_PUD_DOWN},
      { RELAY_RES_D, GPIO_PIN_SET, DEFAULT, PI_PUD_DOWN}
    };
#else
  const relay_t relay_list[SIZE_RELAY] = {
      {RELAY_CP_LINE, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},     // relay1 default low = disconnect    | relay off
      {RELAY_PE_LINE, GPIO_PIN_SET, DEFAULT, PI_PUD_DOWN},       // relay6    default low = disconnect    | relay off
      {RELAY_SHORT_CIRCUIT, GPIO_PIN_SET, REVERSE, PI_PUD_DOWN}, // relay5   default high = no short     | relay off
      {RELAY_DIODE, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},       // relay7    default low = has diode     | relay on
      {RELAY_PROX, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},        // relay9    default low = has prox      | relay on
      {RELAY_RES_B, GPIO_PIN_SET, REVERSE, PI_PUD_DOWN},         // relay2     default high = no res B     | relay off
      {RELAY_RES_C, GPIO_PIN_SET, REVERSE, PI_PUD_DOWN},         // relay3     default high = no res C     | relay off
      {RELAY_RES_D, GPIO_PIN_SET, REVERSE, PI_PUD_DOWN},         // relay4     default high = no res D     | relay off
      {RELAY_ICU_RESET, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN},   // relay8      default low = no off ICU    | relay on
      {RELAY_TBD, GPIO_PIN_RESET, DEFAULT, PI_PUD_DOWN} // relay10     default low
  };
#endif
#endif
#if (NEW_BOARD == 1)
  const relay_val_t CP_STATE_RES_MAP[NUM_STATE_CONTROL][NUM_RELAY_CONTROL] = {
      // B                C              D            PE               DIODE        SH
      [DataStructure_HAL_61851::IEC_61851_States::A] = {RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::B] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::C] = {RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::D] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::E] = { RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_ON}};
#else
  // RELAY_RES_B = 6,  RELAY_RES_C = 13,  RELAY_RES_D = 19 , RELAY_PE_LINE, = 21, RELAY_CP_LINE = 5, RELAY_PROX=12, RELAY_SHORT_CIRCUIT = 26
  const relay_val_t CP_STATE_RES_MAP[NUM_STATE_CONTROL][NUM_RELAY_CONTROL] = {
      [DataStructure_HAL_61851::IEC_61851_States::A] = {RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::B] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::C] = {RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::D] = {RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_States::E] = {RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_ON}};
#endif
  const std::string serial_port_instance = "/dev/ttyS0";
#if (PI_ENABLE == 1)
  serial_frame_cxt_t stm32_serial_frame;
#endif
  std::shared_ptr<onBCEventType> _onEventHandler;
  bool _timer_cancel;
  bool _pwmStatus;
  float _pwmDuty;
  float _pwmFreq;
  float _voltLevel;
  uint32_t btnCounter;
  std::shared_ptr<CppCommon::Asio::Service> _service;
  std::shared_ptr<CppCommon::Asio::Timer> _cyclicTimer;
  std::shared_ptr<CppCommon::Asio::Timer> _bcbTimer;

  DataStructure_HAL_61851::IEC_61851_States _state;
  uint8_t initialized_flag = 0xFF;
  uint8_t checkValidGpio(relay_pin_t idx);
  uint8_t initRelay(void);
  void deInitRelay(void);

  std::vector<NotifyFunc> funcList;

public:
  uint8_t setRelay(relay_pin_t idx, relay_val_t value);

private:
#if (PI_ENABLE == 1)
  static void clear_data(stm32_if_data_t *data_st, serial_command_t cmd);
  static void stm32if_set_response_handler(serial_command_t cmd, uint8_t status);
  static void stm32if_get_response_handler(serial_command_t cmd, uint8_t *data, uint8_t len);
#endif
  /* NA: [V2G4-024], [V2G4-025], [V2G4-026] */
public:
  // init with io_context
  SeccBasicSignaling(const std::shared_ptr<CppCommon::Asio::Service> &service);
  ~SeccBasicSignaling();
  void stop(void);
  void start(void);
  bool setErrorState(DataStructure_HAL_61851::IEC_61851_ErrStates _state);
  /* [V2G4-031] */
  bool setState(DataStructure_HAL_61851::IEC_61851_States _state);
  /* [V2G4-031] */
  DataStructure_HAL_61851::IEC_61851_States getState() { return _state; }
  /* [V2G4-022] */
  bool getPWMStatus() { return _pwmStatus; }
  /* [V2G4-027] */
  float getPWMDuty() { return _pwmDuty; }
  /* [V2G4-029] */
  float getPWMFreq() { return _pwmFreq; }
  /* [V2G4-022] */
  float getVoltLevel() { return _voltLevel; }
  /* [V2G4-023], [V2G4-028], [V2G4-030] */
  void setEventCallBack(const std::shared_ptr<onBCEventType> &eventHandler) { _onEventHandler = eventHandler; }

  void setNotifyStateChange(NotifyFunc func);
  void toggleBCB(float timeout, uint8_t number);
  /* Button ISR */
  uint32_t pressState;
  std::atomic<bool> btnPressFlag;
  bool isButtonPress(void);
  static void btnISRFunc(int gpio, int level, uint32_t tick, void *userdata);
  void startCheckBtn(void);
  uint32_t getBtnPressCounter(void);
  void resetBtnCounter(void);

protected:
  // function to be push into io_context
  // function getPWMStatus, Duty, Freq, VoltLevel cyclic 100ms and update internal status
  // call _onEventHandler function
  /* [V2G4-023], [V2G4-028], [V2G4-030], [V2G4-031] */
  void getSTMDataCyclic(bool _cancel);
  void getButtonPress(bool _cancel);
};

#endif
