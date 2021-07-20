#ifndef __FRAME_COM_SERV_H
#define __FRAME_COM_SERV_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

#define FRAME_SERVICE_DEBUG_ENABLE  0

typedef enum
{
  /* 0 */ FRAME_CMD_HEART_BEAT = 0,
  /* SET INPUT CONTROL */
  /* 1 */ FRAME_CMD_SET_ICU_RESET, // IO set/clear trigger reset on ICU board                               [RASP]
  /* 2 */ FRAME_CMD_SET_SWITCH2,   // IO open/close relay corresponding switch 2                            [RASP]
  /* 3 */ FRAME_CMD_SET_CABLE,     // IO open/close relay = unplug/plug connect (CP line in current design) [RASP]
  /* 4 */ FRAME_CMD_SET_EV_LOAD,   // IO open/close relay of EV load (open/close L1/N line of load circuit) = ON/OFF current draw on EV side [RASP?]
  /* 5 */ FRAME_CMD_SET_RES,       // IO open/close relay of specific resistor for state B, C, D            [RASP]
  /* 6 */ FRAME_CMD_SET_POTENT,    // Control potentiometer value and open relay for potent line            [RASP - STM]
  /* 7 */ FRAME_CMD_SET_VOLT_FB,   // Voltage value -> calculate to corresponding resistor value            [RASP - STM]
  /* 8 */ FRAME_CMD_SET_EVSE_STATE,// request set EVSE state                                                [RASP - STM]
  /* 9 */ FRAME_CMD_SET_TRIGGER,   // SET TIMMING TRIGGER SOURCE                                            [STM]
  /* 10 */ FRAME_CMD_SET_BULK,     // request set EVSE state                                                [RASP - STM]

  /* GET EXPECTED RESULT */
  /* 11 */ FRAME_CMD_GET_PWM_STS,      // request send back PWM Status (either 0%, 100% = OFF, other = ON)  [STM]
  /* 12 */ FRAME_CMD_GET_PWM_DUTY,     // request send back duty cycle value                                [STM]
  /* 13 */ FRAME_CMD_GET_AC_SUPP_STS,  // request AC Supply status on L1/N line                             [STM]
  /* 14 */ FRAME_CMD_GET_AC_CURR_STS,  // get status of AC current draw                                     [STM]
  /* 15 */ FRAME_CMD_GET_CP_VOLT,      // request voltage level on CP line to confirm resistor set          [STM]
  /* 16 */ FRAME_CMD_GET_EVSE_STATE,   // request get EVSE state                                            [STM]
  /* 17 */ FRAME_CMD_GET_AC_SUPP_TM,   // request get EVSE state                                            [STM]
  /* 18 */ FRAME_CMD_GET_AC_CURR_TM,   // request get EVSE state                                            [STM]
  /* 19 */ FRAME_CMD_GET_BULK,         // request set EVSE state                                            [STM] // PWMStatus, Duty, EVSEState, ACSupplyStatus, CurrentDrawStatus, ACSupTime, EVCurTime
  /* 20 */ FRAME_CMD_NUM
} serial_command_t;

/* Heart beat data frame element*/
#define HEARTBEAT_DF_LENGTH         1 /* number of data field */
#define HEARTBEAT_DF_ACK_INDEX      0  /* length is 1 byte */
#define SET_CMD_RESP_DF_LEN         1

#define FRAME_ACK 0
#define FRAME_NACK 1

typedef struct {
  int (*input_cb)(uint8_t *c);
  int (*output_cb)(uint8_t c);
  void (*heartbeat_cb)(void);           // callback to handle heartbeat response from stm32
  void (*set_cmd_cb)(serial_command_t, uint8_t); // call back for set cmd reponse
  void (*get_cmd_cb)(serial_command_t, uint8_t* ,uint8_t); // reponse data from get cmd
} serial_frame_cxt_t;

void stm_handle_init(serial_frame_cxt_t *fp_callback);
void stm_handle_loop(void);

/* Brief: API send frame command to RFID
 * [cmd]: command refer from rfid_command_t
 * [data]: data buffer shall fill to data's field of frame command
 * [length]: the length of data buffer
 * */
void stm_frame_send(uint8_t cmd, uint8_t* data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif
