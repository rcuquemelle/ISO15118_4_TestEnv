#include "SeccBasicSignaling.h"
#include "asiowrapper/timer.h"
#include <functional>
#include "TestSystemLogging.h"
#include "PAInterface.h"
#if (PI_ENABLE == 1)
#include "serial0.h"
#include "sys_tick.h"
#include "ticker.h"

const char *CMD_NAME[] = {[FRAME_CMD_HEART_BEAT] = "HEART_BEAT",
                          [FRAME_CMD_SET_ICU_RESET] = "RESET_ICU",
                          [FRAME_CMD_SET_SWITCH2] = "SET_SW2",
                          [FRAME_CMD_SET_CABLE] = "SET_CABLE",
                          [FRAME_CMD_SET_EV_LOAD] = "SET_EV_LOAD",
                          [FRAME_CMD_SET_RES] = "SET_RESISTOR",
                          [FRAME_CMD_SET_POTENT] = "SET_POTENT",
                          [FRAME_CMD_SET_VOLT_FB] = "SET_VA",
                          [FRAME_CMD_SET_EVSE_STATE] = "SET_EVSE_STATE",
                          [FRAME_CMD_SET_TRIGGER] = "SET_TRIGGER_SRC",
                          [FRAME_CMD_SET_BULK] = "SET_BULK",
                          [FRAME_CMD_GET_PWM_STS] = "GET_PWM_STS",
                          [FRAME_CMD_GET_PWM_DUTY] = "GET_PWM_DUTY",
                          [FRAME_CMD_GET_AC_SUPP_STS] = "AC_SUPP_STS",
                          [FRAME_CMD_GET_AC_CURR_STS] = "AC_CURR_STS",
                          [FRAME_CMD_GET_CP_VOLT] = "GET_CP_VOLT",
                          [FRAME_CMD_GET_EVSE_STATE] = "GET_EVSE_STATE",
                          [FRAME_CMD_GET_AC_SUPP_TM] = "GET_AC_SUPP_TIME",
                          [FRAME_CMD_GET_AC_CURR_TM] = "AC_CURR_TIME",
                          [FRAME_CMD_GET_BULK] = "GET_BULK"};
static const char *HAL_CMD[] = {
    [DataStructure_HAL_61851::IEC_61851_States::A] = "A",
    [DataStructure_HAL_61851::IEC_61851_States::B] = "B",
    [DataStructure_HAL_61851::IEC_61851_States::C] = "C",
    [DataStructure_HAL_61851::IEC_61851_States::D] = "D",
    [DataStructure_HAL_61851::IEC_61851_States::E] = "E",
    [DataStructure_HAL_61851::IEC_61851_States::F] = "F",
    [DataStructure_HAL_61851::IEC_61851_States::NA] = "NA",
    [DataStructure_HAL_61851::IEC_61851_States::none_] = "NONE"};
#endif

// BASIC CHARGING
// set state A, B, C, D (Rasp GPIO set)
// control CP/PE/Prox relay for ChargingGun connection
// Resistor B, C, D, short-circuit for A, B, C, D, E state

// get pwm status, duty, frequency, voltage level
// (uart/serial communication from stm32 board)

// callback on: pwm status change
//           duty change
//           frequency change
//           voltage level change
// init with io_context
typedef union
{
  uint32_t u32;
  int32_t i32;
  float f;
  uint16_t u16[2];
  int16_t i16[2];
  uint8_t u8[4];
  int8_t i8[4];
  char c[4];
} data32b_t;
#if (PI_ENABLE == 1)
static stm32_if_data_t STM32IF_DATA;
#endif
uint32_t byte_to_u32(uint8_t data[4])
{
  data32b_t temp;
  for (int i = 0; i < 4; i++)
  {
    temp.u8[i] = data[i];
  }
  return temp.u32;
}
SeccBasicSignaling::SeccBasicSignaling(const std::shared_ptr<CppCommon::Asio::Service> &service)
    : _service(service)
{
#if (PI_ENABLE == 1)
  bool relay_flag = false;
  bool uart_flag = false;
  const char *state[] = {[0] = "FAILED", [1] = "RELAY OK - UART NG", [2] = "RELAY NG - UART OK", [3] = "DONE"};
  // init data
  this->_onEventHandler = nullptr;
  this->_pwmStatus = false;
  this->_pwmDuty = 0.0;
  this->_pwmFreq = 0.0;
  this->_voltLevel = 0.0;
  this->_state = DataStructure_HAL_61851::IEC_61851_States::none_;
  // init relay
  relay_flag = (RASP_GPIO_OK == this->initRelay());
  // init UART
  uart_flag = (UART_OK == uart_instance0_Init((char *)serial_port_instance.c_str()));
  uint8_t temp = (uint8_t)relay_flag | ((uint8_t)uart_flag << 1);
  Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: Init {}", state[temp]));
  this->stm32_serial_frame.input_cb = getchar_instance0;  /* serial0 input callback */
  this->stm32_serial_frame.output_cb = putchar_instance0; /* serial0 output callback */
  this->stm32_serial_frame.heartbeat_cb = nullptr;
  this->stm32_serial_frame.set_cmd_cb = SeccBasicSignaling::stm32if_set_response_handler;
  this->stm32_serial_frame.get_cmd_cb = SeccBasicSignaling::stm32if_get_response_handler;
  stm_handle_init(&this->stm32_serial_frame);
  // push getSTMDataCyclic to io_context
  //this->_cyclicTimer = std::make_shared<CppCommon::Asio::Timer>(service, std::bind(&SeccBasicSignaling::getSTMDataCyclic, this, std::placeholders::_1), CppCommon::Timespan::milliseconds(STM32_POLL_RATE));
  this->_bcbTimer = std::make_shared<CppCommon::Asio::Timer>(service);
  this->_timer_cancel = false;
  this->btnPressFlag = false;
  this->btnCounter = 0;
  this->_cyclicTimer = std::make_shared<CppCommon::Asio::Timer>(service, std::bind(&SeccBasicSignaling::getButtonPress, this, std::placeholders::_1), CppCommon::Timespan::milliseconds(BUTTON_SAMPLING_RATE));
#endif
}
void SeccBasicSignaling::start(void)
{
#if (PI_ENABLE == 1)
  Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: start polling timer for Control Pilot event"));
  this->_cyclicTimer->WaitAsync();
#endif
}
void SeccBasicSignaling::stop(void)
{
#if (PI_ENABLE == 1)
  // deinit relay
  this->deInitRelay();
  // stop getSTMDataCyclic function
  this->_cyclicTimer->Cancel();
  Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: Deinit GPIO and stop polling timer for Control Pilot event"));
#endif
}
SeccBasicSignaling::~SeccBasicSignaling()
{
  this->stop();
}
bool SeccBasicSignaling::setErrorState(DataStructure_HAL_61851::IEC_61851_ErrStates _state)
{
  bool result = true;
#if (PI_ENABLE == 1)
// change resistor relay
#if (NEW_BOARD == 1)
  const relay_pin_t temp[NUM_RELAY_CONTROL] = {RELAY_RES_B, RELAY_RES_C, RELAY_RES_D, RELAY_PE_LINE, RELAY_DIODE, RELAY_SHORT_CIRCUIT};
  const relay_val_t ERROR_MAP[4][NUM_RELAY_CONTROL] = {
                                                                   // B                C              D            PE               DIODE        SH
      [DataStructure_HAL_61851::IEC_61851_ErrStates::LOST_CP] = {RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_ErrStates::LOST_PE] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_ErrStates::LOST_DIODE] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_ON, RELAY_VAL_OFF},
      [DataStructure_HAL_61851::IEC_61851_ErrStates::SHORT_CP_PE] = {RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_OFF, RELAY_VAL_ON, RELAY_VAL_OFF, RELAY_VAL_ON}};
  Logging::info(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: Error state {}", _state));
  for (int i = 0; i < NUM_RELAY_CONTROL; i++)
  {
    if (0 != this->setRelay(temp[i], ERROR_MAP[_state][i]))
    {
      result = false;
    }
  }
  this->_state = DataStructure_HAL_61851::IEC_61851_States::F;
  for (auto &&func : this->funcList)
  {
    func(this->_state);
  }
#endif
#endif
  return result;
}
bool SeccBasicSignaling::setState(DataStructure_HAL_61851::IEC_61851_States target_state)
{
  bool result = true;
#if (PI_ENABLE == 1)
// change resistor relay
#if (NEW_BOARD == 1)
  const relay_pin_t temp[NUM_RELAY_CONTROL] = {RELAY_RES_B, RELAY_RES_C, RELAY_RES_D, RELAY_PE_LINE, RELAY_DIODE, RELAY_SHORT_CIRCUIT};
#else
  // RELAY_RES_B = 6,  RELAY_RES_C = 13,  RELAY_RES_D = 19 , RELAY_PE_LINE, = 21, RELAY_CP_LINE = 5, RELAY_PROX=12, RELAY_SHORT_CIRCUIT = 26
  const relay_pin_t temp[NUM_RELAY_CONTROL] = {RELAY_RES_B, RELAY_RES_C, RELAY_RES_D, RELAY_CP_LINE, RELAY_PE_LINE, RELAY_PROX, RELAY_SHORT_CIRCUIT};
#endif
  if ((target_state != DataStructure_HAL_61851::IEC_61851_States::none_) &&
      (target_state != DataStructure_HAL_61851::IEC_61851_States::NA) &&
      (target_state != DataStructure_HAL_61851::IEC_61851_States::F))
  {
    // set relay to corresponding state
    if ((this->_state == DataStructure_HAL_61851::IEC_61851_States::none_) ||
        (this->_state == DataStructure_HAL_61851::IEC_61851_States::NA) ||
        (this->_state == DataStructure_HAL_61851::IEC_61851_States::E) ||
        (this->_state == DataStructure_HAL_61851::IEC_61851_States::F))
    {
      Logging::info(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: To CP State {}", HAL_CMD[target_state]));
      for (int i = 0; i < NUM_RELAY_CONTROL; i++)
      {
        if (0 != this->setRelay(temp[i], CP_STATE_RES_MAP[target_state][i]))
        {
          result = false;
        }
      }
      this->_state = (DataStructure_HAL_61851::IEC_61851_States)target_state;
      for (auto &&func : this->funcList)
      {
        func(this->_state);
      }
    }
    else
    {
      /* current state -> target state : transition*/
      int8_t transition = 0;
      if ((int8_t)this->_state > (int8_t)target_state)
      {
        transition = -1;
      }
      else if ((int8_t)this->_state < (int8_t)target_state)
      {
        transition = 1;
      }
      if (transition != 0)
      {
        int8_t current_state = (int8_t)this->_state;
        do
        {
          current_state += transition;
          Logging::info(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: To CP State {}", HAL_CMD[current_state]));
          for (int i = 0; i < NUM_RELAY_CONTROL; i++)
          {
            if (0 != this->setRelay(temp[i], CP_STATE_RES_MAP[current_state][i]))
            {
              result = false;
            }
          }
        } while (current_state != (int8_t)target_state);
        this->_state = (DataStructure_HAL_61851::IEC_61851_States)current_state;
        for (auto &&func : this->funcList)
        {
          func(this->_state);
        }
      }
    }
  }
  else
  {
    result = false;
  }
#endif
  return result;
}

// function to be push into io_context
// function getPWMStatus, Duty, Freq, VoltLevel cyclic 100ms and update internal status
// call _onEventHandler function
void SeccBasicSignaling::getSTMDataCyclic(bool _cancel)
{
#if (PI_ENABLE == 1)
  // cyclic function each 10ms
  static int counter = 0;
  std::vector<en_BCEventType> event_list;
  this->_timer_cancel = _cancel;
  stm_handle_loop();
  // Logging::debug(LogSut61851_ENABLE, "[SUT_IF][61851]: Cyclic function");
  // send uart cmd to stm32 for each 100ms
  if (counter == 0)
  {
    stm_frame_send(FRAME_CMD_SET_BULK, nullptr, 0);
    counter++;
    if (counter == 10)
    {
      counter = 0;
    }
  }
  // receive data, check for receive data
  if (true == STM32IF_DATA.cmd_flags[FRAME_CMD_SET_BULK])
  {
    // PWMStatus, Duty, EVSEState, ACSupplyStatus, CurrentDrawStatus, ACSupTime, EVCurTime, Freq
    if (this->_pwmStatus != (bool)byte_to_u32(&STM32IF_DATA.receive_data[0]))
    {
      event_list.push_back(en_BCEventType_PWM_STATUS);
    }
    this->_pwmStatus = (bool)byte_to_u32(&STM32IF_DATA.receive_data[0]);
    if ((((float)byte_to_u32(&STM32IF_DATA.receive_data[4]) / 100.0) > (this->_pwmStatus + 0.5)) &&
        ((this->_pwmStatus - 0.5) > ((float)byte_to_u32(&STM32IF_DATA.receive_data[4]) / 100.0)))
    {
      event_list.push_back(en_BCEventType_PWM_DUTY);
    }
    this->_pwmDuty = (float)byte_to_u32(&STM32IF_DATA.receive_data[4]) / 100.0;
    if ((((float)byte_to_u32(&STM32IF_DATA.receive_data[28])) > (this->_pwmFreq + 5)) &&
        ((this->_pwmFreq - 5) > ((float)byte_to_u32(&STM32IF_DATA.receive_data[28]))))
    {
      event_list.push_back(en_BCEventType_PWM_DUTY);
    }
    this->_pwmFreq = (float)byte_to_u32(&STM32IF_DATA.receive_data[28]);
    if ((((float)byte_to_u32(&STM32IF_DATA.receive_data[32]) / 1000.0) > (this->_voltLevel + 0.1)) &&
        ((this->_voltLevel - 0.1) > ((float)byte_to_u32(&STM32IF_DATA.receive_data[32]) / 1000.0)))
    {
      event_list.push_back(en_BCEventType_PWM_VOLT);
    }
    this->_voltLevel = (float)byte_to_u32(&STM32IF_DATA.receive_data[32]) / 1000.0;
    SeccBasicSignaling::clear_data(&STM32IF_DATA, FRAME_CMD_SET_BULK);
  }

  // update internal value and call event handler

  // check if internal val change then call event notify
  if (this->_onEventHandler != nullptr)
  {
    for (auto &&i : event_list)
    {
      Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: call event {}", i));
      (*this->_onEventHandler)(i);
    }
  }

  //reload timer
  this->_cyclicTimer->Setup(CppCommon::Timespan::milliseconds(STM32_POLL_RATE));
  this->_cyclicTimer->WaitAsync();
#endif
}

int SeccBasicSignaling::initRelay(void)
{
  int result = RASP_GPIO_OK;
#if (PI_ENABLE == 1)
  this->pid = pigpio_start(NULL, NULL); // Connects to a pigpio daemon
  // if (RASP_GPIO_OK > gpioInitialise())
  if (RASP_GPIO_OK > this->pid)
  {
    result = 0xFF;
  }
  else
  {
    for (int i = 0; i < SIZE_RELAY; i++)
    {
      result += set_mode(this->pid, relay_list[i].gpio, PI_OUTPUT);
      // result += gpioSetMode(relay_list[i].gpio, PI_OUTPUT);
      // pull up default HIGH
      result += set_pull_up_down(this->pid, relay_list[i].gpio, relay_list[i].pull_type);
      // result += gpioSetPullUpDown(relay_list[i].gpio, relay_list[i].pull_type);
      result += gpio_write(this->pid, relay_list[i].gpio, relay_list[i].default_val);
      // result += gpioWrite(relay_list[i].gpio, relay_list[i].default_val);
    }
    result += set_mode(this->pid, INPUT_ISR_PIN, PI_INPUT);
    // result += gpioSetMode(INPUT_ISR_PIN, PI_INPUT);
    result += set_pull_up_down(this->pid, INPUT_ISR_PIN, PI_PUD_UP);
    // result += gpioSetPullUpDown(INPUT_ISR_PIN, PI_PUD_UP);
    result += callback_ex(this->pid, INPUT_ISR_PIN, RISING_EDGE, &SeccBasicSignaling::btnISRFunc, this);
    // result += gpioSetISRFuncEx(INPUT_ISR_PIN, 0, 10, &SeccBasicSignaling::btnISRFunc, this);
  }
  if (RASP_GPIO_OK == result)
  {
    initialized_flag = RASP_GPIO_OK;
    Logging::debug(LogSut61851_ENABLE, "[SUT_IF][61851]: GPIO INITIALIZE COMPLETED");
  }
  else
  {
    initialized_flag = 0xFF;
    Logging::debug(LogSut61851_ENABLE, "[SUT_IF][61851]: GPIO INITIALIZE FAILED");
  }
#endif
  return result;
}
// void SeccBasicSignaling::btnISRFunc(int gpio, int level, uint32_t tick, void *userdata)
void SeccBasicSignaling::btnISRFunc(int pi, uint32_t gpio, uint32_t level, uint32_t tick, void *userdata)
{
  if ((gpio == INPUT_ISR_PIN) && (1 == level))
  {
    SeccBasicSignaling *temp = (SeccBasicSignaling *)userdata;
    temp->pressState = 0x00000001;
    temp->startCheckBtn();
  }
}
uint32_t SeccBasicSignaling::getBtnPressCounter(void)
{
  return this->btnCounter;
}
void SeccBasicSignaling::resetBtnCounter(void)
{
  this->btnCounter = 0;
}
void SeccBasicSignaling::getButtonPress(bool _cancel)
{
  static uint32_t count = 0;
  this->_timer_cancel = _cancel;
  if (false == _cancel)
  {
    // int value = gpioRead(INPUT_ISR_PIN);
    int value = gpio_read(this->pid, INPUT_ISR_PIN);
    if (value >= 0)
    {
      this->pressState = (this->pressState << 1) | value | 0xE0000000;
      count++;
    }
    if (this->pressState == 0xF0000000)
    {
      this->btnPressFlag = true;
      count = 0;
      this->pressState = 0;
      this->_cyclicTimer->Cancel();
      this->btnCounter++;
      Logging::debug(LogCmnFnc_ENABLE, "------- BUTTON PRESS ----------");
    }
    else
    {
      if (count > 32)
      {
        count = 0;
        this->pressState = 0;
        this->_cyclicTimer->Cancel();
      }
      else
      {
        this->_cyclicTimer->Setup(CppCommon::Timespan::milliseconds(BUTTON_SAMPLING_RATE));
        this->_cyclicTimer->WaitAsync();
      }
    }
  }
}

bool SeccBasicSignaling::isButtonPress(void)
{
  bool result = false;
#if (PI_ENABLE == 1)
  result = this->btnPressFlag;
  this->btnPressFlag = false;
#endif
  return result;
}

void SeccBasicSignaling::startCheckBtn(void)
{
  this->_cyclicTimer->Setup(CppCommon::Timespan::milliseconds(BUTTON_SAMPLING_RATE));
  this->btnPressFlag = false;
  this->_cyclicTimer->WaitAsync();
}
void SeccBasicSignaling::deInitRelay(void)
{
#if (PI_ENABLE == 1)
  pigpio_stop(this->pid);
  // gpioTerminate();
#endif
}

uint8_t SeccBasicSignaling::setRelay(relay_pin_t idx, relay_val_t value)
{
  uint8_t result = RASP_GPIO_OK;
#if (PI_ENABLE == 1)
  int relay_idx = 0;
  relay_idx = this->checkValidGpio(idx);
  if ((RASP_GPIO_OK == initialized_flag) && (RASP_GPIO_NG != relay_idx))
  {
    // result = gpioWrite(relay_list[relay_idx].gpio, SET_RELAY[relay_list[relay_idx].type][value]);
    result = gpio_write(this->pid, relay_list[relay_idx].gpio, SET_RELAY[relay_list[relay_idx].type][value]);
    // Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: SET GPIO {0}, VALUE {1} ", relay_list[relay_idx].gpio, SET_RELAY[relay_list[relay_idx].type][value]));
  }
  else
  {
    Logging::debug(LogSut61851_ENABLE, "[SUT_IF][61851]: SET FAILED, GPIO IS UNINITIALIZED");
  }
  if (0 != result)
  {
    Logging::debug(LogSut61851_ENABLE, fmt::format("[SUT_IF][61851]: SET FAILED, ERROR {}", result));
  }
#endif
  return result;
}

uint8_t SeccBasicSignaling::checkValidGpio(relay_pin_t idx)
{
  uint8_t flag = RASP_GPIO_NG;
#if (PI_ENABLE == 1)
  for (int i = 0; i < SIZE_RELAY; i++)
  {
    if (relay_list[i].gpio == idx)
    {
      return i;
    }
  }
#endif
  return flag;
}

#if (PI_ENABLE == 1)
void SeccBasicSignaling::clear_data(stm32_if_data_t *data_st, serial_command_t cmd)
{
  for (int i = 0; i < data_st->len; i++)
  {
    data_st->receive_data[i] = 0;
  }
  data_st->len = 0;
  data_st->cmd_flags[cmd] = false;
}
void SeccBasicSignaling::stm32if_set_response_handler(serial_command_t cmd, uint8_t status)
{
  STM32IF_DATA.len = 1;
  STM32IF_DATA.cmd_flags[cmd] = true;
  STM32IF_DATA.receive_data[0] = status;
  Logging::debug(LogSut61851_ENABLE, fmt::format("Receive response CMD: {0} - {1}", CMD_NAME[cmd], status));
}
void SeccBasicSignaling::stm32if_get_response_handler(serial_command_t cmd, uint8_t *data, uint8_t len)
{
  char out_data[255];
  char *ptr_out;
  STM32IF_DATA.len = len;
  STM32IF_DATA.cmd_flags[cmd] = true;
  for (int i = 0; i < len; i++)
  {
    STM32IF_DATA.receive_data[i] = data[i];
  }

  ptr_out = out_data;
  for (int i = 0; i < len; i++)
  {
    sprintf(ptr_out, "0x%02X", STM32IF_DATA.receive_data[i]);
    ptr_out += 4;
    if (i != len - 1)
    {
      *(ptr_out) = ' ';
      ++ptr_out;
    }
  }
  Logging::debug(LogSut61851_ENABLE, fmt::format("Receive response CMD: {0} - DATA: {1}", CMD_NAME[cmd], out_data));
}

void SeccBasicSignaling::setNotifyStateChange(NotifyFunc func)
{
  this->funcList.push_back(func);
}
void SeccBasicSignaling::toggleBCB(float timeout, uint8_t number)
{
  this->setState(DataStructure_HAL_61851::IEC_61851_States::B);
  this->_bcbTimer->Setup(CppCommon::Timespan::milliseconds(timeout * 1000));
  this->_bcbTimer->WaitSync();
  for (uint8_t i; i < number; i++)
  {
    Logging::info(LogSut61851_ENABLE, fmt::format("Toggle BCB {0}", (i+1)));
    this->setState(DataStructure_HAL_61851::IEC_61851_States::C);
    this->_bcbTimer->Setup(CppCommon::Timespan::milliseconds(timeout * 1000));
    this->_bcbTimer->WaitSync();
    this->setState(DataStructure_HAL_61851::IEC_61851_States::B);
    this->_bcbTimer->Setup(CppCommon::Timespan::milliseconds(timeout * 1000));
    this->_bcbTimer->WaitSync();
  }
}

#endif