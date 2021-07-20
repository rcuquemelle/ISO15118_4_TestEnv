#include "serial0.h"
#include "ticker.h"
#include "frame.h"
#include "frame_com.h"
#include "frame_com_service.h"

#if (defined FRAME_SERVICE_DEBUG_ENABLE) && (FRAME_SERVICE_DEBUG_ENABLE == 1)
#define FRAME_SERVICE_DBG(f_, ...) fprintf(stdout, f_, ##__VA_ARGS__)
#define FRAME_SERVICE_TAG_DBG(f_, ...)      \
  do                                        \
  {                                         \
    FRAME_SERVICE_DBG("\r\nFRAME. ");       \
    FRAME_SERVICE_DBG((f_), ##__VA_ARGS__); \
  } while (0)
#else
#define FRAME_SERVICE_DBG(f_, ...)
#define FRAME_SERVICE_TAG_DBG(f_, ...)
#endif

#define FRAME_CMD_ACK 0
#define FRAME_CMD_NACK 1

#define FRAME_INPUT_OK UART_OK

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define COMMAND_RX_BUFF_SIZE FRAME_SIZE_MAX
#define COMMAND_TX_BUFF_SIZE FRAME_SIZE_MAX

/* Private variables ---------------------------------------------------------*/
/**@brief String literals for the serial command. */
#if (defined FRAME_SERVICE_DEBUG_ENABLE) && (FRAME_SERVICE_DEBUG_ENABLE == 1)
static char const *lit_frame_cmd_id[] = {
    /* 0 */ "FRAME_CMD_HEART_BEAT",
    /* 1 */ "FRAME_CMD_RELAY"};
#endif

/* Variables uart ttl interface */
static uint8_t uart_ttl_rx_buff[COMMAND_RX_BUFF_SIZE];
static uint8_t uart_ttl_tx_buff[COMMAND_TX_BUFF_SIZE];

static frame_com_cxt_t frame_com_uart_ttl_cxt;

static serial_frame_cxt_t *frame_handle;

/* Private function prototypes -----------------------------------------------*/
static void command_parse_callback(frame_com_cxt_t *frame_instance, uint8_t result, uint8_t cmd, uint8_t *data, uint16_t length);
static void command_send_callback(frame_com_cxt_t *frame_instance, uint8_t *buff, uint16_t length);
static void command_parse_process(void);

void stm_handle_loop(void)
{
  /* Get command event process */
  command_parse_process();
}

void stm_handle_init(serial_frame_cxt_t *fp_callback)
{
  frame_handle = fp_callback;

  /* Init object handle communicate frame */
  frame_com_begin(&frame_com_uart_ttl_cxt,
                  command_parse_callback,
                  command_send_callback,
                  uart_ttl_tx_buff,
                  uart_ttl_rx_buff,
                  COMMAND_TX_BUFF_SIZE,
                  COMMAND_RX_BUFF_SIZE);
}

/* Brief: API send frame command to RFID
 * [cmd]: command refer from serial_command_t
 * [data]: data buffer shall fill to data's field of frame command
 * [length]: the length of data buffer
 * */
void stm_frame_send(uint8_t cmd, uint8_t *data, uint16_t length)
{
  frame_com_send(&frame_com_uart_ttl_cxt, cmd, data, length);
}

static void command_parse_process(void)
{
  frame_size get_cnt;
  uint8_t data;

  get_cnt = FRAME_SIZE_MAX / 2; /* counter limit once getchar from serial */
  if (frame_handle->input_cb)
  {
    while (FRAME_INPUT_OK == frame_handle->input_cb((uint8_t *)&data))
    {
      // input data into utilities frame
      if (FRAME_COM_FINISH == frame_com_data_in(&frame_com_uart_ttl_cxt, data))
      {
        break;
      }

      // Avoid while loop forever if uart_rx painfully
      --get_cnt;
      if (0 == get_cnt)
      {
        break;
      }
    }
  }
}

/* Brief: the function callback to send frame buff over serial
 *        once call the function frame_com_send()
 * */
static void command_send_callback(frame_com_cxt_t *frame_instance, uint8_t *buff, uint16_t length)
{
  FRAME_SERVICE_DBG("\r\nSend a frame buffer with length = %u", length);
  FRAME_SERVICE_DBG("\r\nBuffer: ");
  for (frame_size i = 0; i < length; ++i)
  {
    FRAME_SERVICE_DBG("%02X ", buff[i]);
  }
  FRAME_SERVICE_DBG("\r\n");

  if (frame_instance == &frame_com_uart_ttl_cxt)
  {
    if (frame_handle->output_cb)
    {
      for (uint16_t i = 0; i < length; ++i)
      {
        frame_handle->output_cb(buff[i]);
      }
    }
  }
}

/* Brief: the function event callback the parse a frame message */
static void command_parse_callback(frame_com_cxt_t *frame_instance, uint8_t result, uint8_t cmd, uint8_t *data, uint16_t length)
{
  if ((uint8_t)FRAME_OK == result)
  {
    if (FRAME_CMD_NUM <= cmd)
    {
      FRAME_SERVICE_DBG("\r\nCMD error\r\n");
      return;
    }

    FRAME_SERVICE_DBG("\r\nGet new frame");
    FRAME_SERVICE_DBG("\r\n- CMD: %s", lit_frame_cmd_id[cmd]);
    FRAME_SERVICE_DBG("\r\n- Data length: %u", length);
    FRAME_SERVICE_DBG("\r\n- Data: ");
    for (uint16_t i = 0; i < length; ++i)
    {
      FRAME_SERVICE_DBG("%02X ", data[i]);
    }
    FRAME_SERVICE_DBG("\r\n");

    switch (cmd)
    {
    /* HEART BEAT command
     * Hercules terminal test string: $7E$02$00$02$7F
     * Hex recieve: {7E}{02}{00}{02}{7F}
     * Hex ACK response: {7E}{03}{00}{00}{03}{7F}
     * */
    case FRAME_CMD_HEART_BEAT:
    {
      // check data length of heart beat command
      if (HEARTBEAT_DF_LENGTH == length && FRAME_CMD_ACK == data[HEARTBEAT_DF_ACK_INDEX])
      {
        /* Call cb function */
        if (frame_handle->heartbeat_cb)
        {
          frame_handle->heartbeat_cb();
        }
        FRAME_SERVICE_DBG("\r\nHEART_BEAT OK");
      }
      else
      {
        FRAME_SERVICE_DBG("\r\nHEART_BEAT ERROR");
      }
      break;
    }
    case FRAME_CMD_SET_ICU_RESET:
    case FRAME_CMD_SET_SWITCH2:
    case FRAME_CMD_SET_CABLE:
    case FRAME_CMD_SET_EV_LOAD:
    case FRAME_CMD_SET_RES:
    case FRAME_CMD_SET_POTENT:
    case FRAME_CMD_SET_VOLT_FB:
    case FRAME_CMD_SET_EVSE_STATE:
    case FRAME_CMD_SET_TRIGGER:
    case FRAME_CMD_SET_BULK:
    {
      if (SET_CMD_RESP_DF_LEN == length){
        frame_handle->set_cmd_cb(cmd, data[0]);
      }
      break;
    }
    case FRAME_CMD_GET_PWM_STS:
    case FRAME_CMD_GET_PWM_DUTY:
    case FRAME_CMD_GET_AC_SUPP_STS:
    case FRAME_CMD_GET_AC_CURR_STS:
    case FRAME_CMD_GET_CP_VOLT:
    case FRAME_CMD_GET_EVSE_STATE:
    case FRAME_CMD_GET_AC_SUPP_TM:
    case FRAME_CMD_GET_AC_CURR_TM:
    case FRAME_CMD_GET_BULK:
    {
      frame_handle->get_cmd_cb(cmd, data, length);
      break;
    }
    default:
      break;
    }
  }
}
