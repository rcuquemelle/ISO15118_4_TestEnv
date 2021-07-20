#ifndef _FRAME_COM_
#define _FRAME_COM_

/* Macro enable debug frame communication */
#define FRAME_COM_DEBUG_ENABLE  0

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

#include "frame.h"

typedef enum {
  FRAME_COM_NONE,
  FRAME_COM_WAIT_START,
  FRAME_COM_GET_LENGTH,
  FRAME_COM_WAIT_STOP,
  FRAME_COM_FINISH
} sm_frame_com_typedef;

struct frame_com_cxt;

typedef void (*frame_com_event_callback_t)(struct frame_com_cxt*, uint8_t result, uint8_t cmd, uint8_t* data, uint16_t length);
typedef void (*frame_com_send_callback_t)(struct frame_com_cxt*, uint8_t* buff, uint16_t length);
typedef struct frame_com_cxt
{
  frame_com_event_callback_t event_cb;
  frame_com_send_callback_t  send_cb;
  uint8_t *tx_buff;   /*!< pointer to tx buffer store data of frame*/
  uint8_t *rx_buff;   /*!< pointer to rx buffer store data of frame*/
  uint16_t tx_length;  /*!< maximum length is FRAME_SIZE_MAX(258)*/
  uint16_t rx_length;  /*!< maximum length is FRAME_SIZE_MAX(258)*/
} frame_com_cxt_t;

void frame_com_begin (
  frame_com_cxt_t* p_frame_com,
  frame_com_event_callback_t event_cb,
  frame_com_send_callback_t  send_cb,
  uint8_t *tx_buff,   /*!< pointer to tx buffer store data of frame*/
  uint8_t *rx_buff,   /*!< pointer to rx buffer store data of frame*/
  frame_size tx_length,  /*!< maximum length is FRAME_SIZE_MAX(258)*/
  frame_size rx_length  /*!< maximum length is FRAME_SIZE_MAX(258)*/
  );
uint8_t frame_com_data_in(frame_com_cxt_t* p_frame_com, uint8_t c);
void frame_com_send(frame_com_cxt_t* p_frame_com, uint8_t cmd, uint8_t* data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* _FRAME_COM_ */
