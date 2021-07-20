#include "frame_com.h"
#include "ticker.h"

#if (defined FRAME_COM_DEBUG_ENABLE) && (FRAME_COM_DEBUG_ENABLE == 1)
#include "serial0.h"
#define FRAME_COM_PRINTF(f_, ...) fprintf(stdout, (f_), ##__VA_ARGS__)
#define FRAME_COM_TAG_PRINTF(f_, ...)      \
  do                                       \
  {                                        \
    FRAME_COM_PRINTF("\r\nFRAME_COM. ");   \
    FRAME_COM_PRINTF((f_), ##__VA_ARGS__); \
  } while (0)
#else
#define FRAME_COM_PRINTF(f_, ...)
#define FRAME_COM_TAG_PRINTF(f_, ...)
#endif

#if (defined FRAME_COM_DEBUG_ENABLE) && (FRAME_COM_DEBUG_ENABLE == 1)
/**@brief String literals for the frame parse. */
static char const *lit_frameid[] =
    {
        "FRAME_OK",
        "FRAME_ERR",
        "FRAME_SIZE_MIN_ERR",
        "FRAME_SOF_EOF_ERR",
        "FRAME_LENGTH_PACK_ERR",
        "FRAME_CRC_ERR"};
#endif

sm_frame_com_typedef sm_frame_com = FRAME_COM_WAIT_START;
static uint8_t frame_com_id;
static uint8_t frame_com_wait_stop_byte_num;

#define FRAME_COM_TIMEOUT 1000 /* ms */
static ticker_t frame_com_timeout = TICKER_STOP_INIT;

static frame_com_cxt_t *frame_com;

/* make an event callback function */
static void frame_com_parse_event(uint8_t *buff, frame_size length)
{
  frame_data_t Rx_Frame_t;
  frame_parse_result_t result;

  result = frame_data_parse(&Rx_Frame_t, buff, length);
  FRAME_COM_TAG_PRINTF("result %s\r\n", lit_frameid[result]);

  // call event callback function (frame_com_cxt_t*, result, cmd, data, length)
  frame_com->event_cb(frame_com, result, Rx_Frame_t.cmd, Rx_Frame_t.p_data, DATA_FIELD_SIZE(Rx_Frame_t.length));
}

void frame_com_begin(
    frame_com_cxt_t *p_frame_com,
    frame_com_event_callback_t event_cb,
    frame_com_send_callback_t send_cb,
    uint8_t *tx_buff,     /*!< pointer to tx buffer store data of frame*/
    uint8_t *rx_buff,     /*!< pointer to rx buffer store data of frame*/
    frame_size tx_length, /*!< maximum length is FRAME_SIZE_MAX(258)*/
    frame_size rx_length  /*!< maximum length is FRAME_SIZE_MAX(258)*/
)
{
  frame_com = p_frame_com;

  /* Init object handle communicate frame */
  frame_com->rx_buff = rx_buff;
  frame_com->rx_length = rx_length;
  frame_com->tx_buff = tx_buff;
  frame_com->tx_length = tx_length;

  /* register event callback function parse command from serial */
  frame_com->event_cb = event_cb;

  /* register callback function to send frame buffer over serial */
  frame_com->send_cb = send_cb;
}

/* Brief: API make and send a frame
 * Callback should be an asynchronous handle to high performance
 * */
void frame_com_send(frame_com_cxt_t *p_frame_com, uint8_t cmd, uint8_t *data, uint16_t length)
{
  frame_data_t frame_create;
  frame_size tx_length;
  frame_com = p_frame_com;

  /* assert pointer frame_com */
  if (!frame_com->send_cb)
  {
    return;
  }

  /* create a frame */
  frame_data_create(&frame_create, cmd, data, length);
  tx_length = frame_com->tx_length;
  /* fill fields of frame into buff */
  if (FRAME_OK == frame_data_fill_buff(&frame_create, frame_com->tx_buff, &tx_length))
  {
    /* call send callback function */
    frame_com->send_cb(frame_com, frame_com->tx_buff, tx_length);
  }
}

/* Brief: capture frame and parse element
 * When the capture a frame is success, will executing process parse data
 * There are event callback has call to provide command and data
 * */
uint8_t frame_com_data_in(frame_com_cxt_t *p_frame_com, uint8_t c)
{
  frame_com = p_frame_com;

  /* assert pointer frame_com */
  if (!frame_com->event_cb)
  {
    return FRAME_COM_NONE;
  }

  // check timeout to restart capture a new frame
  if (ticker_expired(&frame_com_timeout))
  {
    /* reset state machine equal FRAME_COM_WAIT_START */
    sm_frame_com = FRAME_COM_WAIT_START;
    FRAME_COM_TAG_PRINTF("Timeout command\r\n");
  }

  switch (sm_frame_com)
  {
  case FRAME_COM_FINISH:
    sm_frame_com = FRAME_COM_WAIT_START;
  case FRAME_COM_WAIT_START:
    if (c == FRAME_START_BYTE)
    {
      sm_frame_com = FRAME_COM_GET_LENGTH;
      frame_com_id = FRAME_START_INDEX;
      frame_com->rx_buff[frame_com_id++] = c;

      FRAME_COM_TAG_PRINTF("START");
      // active timeout start get a frame data
      ticker_begin(&frame_com_timeout, FRAME_COM_TIMEOUT);
    }
    break;

  case FRAME_COM_GET_LENGTH:
    if (LENGTH_FIELD_SIZE_MIN > c || LENGTH_FIELD_SIZE(frame_com->rx_length) < c)
    {
      sm_frame_com = FRAME_COM_WAIT_START;
      break;
    }
    sm_frame_com = FRAME_COM_WAIT_STOP;
    frame_com->rx_buff[frame_com_id++] = c;
    frame_com_wait_stop_byte_num = c + STOP_BYTE_NUM;
    FRAME_COM_TAG_PRINTF("length byte 0x%02X\r\n", c);
    break;

  case FRAME_COM_WAIT_STOP:
    frame_com->rx_buff[frame_com_id++] = c;
    // FRAME_COM_PRINTF("%02X ", c);
    --frame_com_wait_stop_byte_num;
    if (0 == frame_com_wait_stop_byte_num)
    {
      FRAME_COM_TAG_PRINTF("STOP");
      sm_frame_com = FRAME_COM_FINISH;
      /* parse frame buffer */
      frame_com_parse_event(frame_com->rx_buff, FRAME_SIZE(frame_com->rx_buff[FRAME_LENGTH_INDEX]));
      /* Stop ticker frame_com_timeout */
      ticker_stop(&frame_com_timeout);
    }
    break;

  default:
    sm_frame_com = FRAME_COM_WAIT_START;
    break;
  }

  return sm_frame_com;
}
