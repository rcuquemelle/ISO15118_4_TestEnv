#include "frame.h"

#if (defined FRAME_DEBUG_ENABLE) && (FRAME_DEBUG_ENABLE == 1)
#include "serial0.h"
#define FRAME_PRINTF(f_, ...)               fprintf(stdout, (f_), ##__VA_ARGS__)
#define FRAME_TAG_PRINTF(f_, ...)           do {\
                                               FRAME_PRINTF("\r\nFRAME. ");\
                                               FRAME_PRINTF((f_), ##__VA_ARGS__);\
                                               } while(0)
#else
#define FRAME_PRINTF(f_, ...)
#define FRAME_TAG_PRINTF(f_, ...)
#endif

/* Brief: Make output buffer from frame field
 * [frame] pointer of frame data input
 * [buff] pointer of data buff output
 * [length] length data buff to fill
 * Return: frame_parse_result_t
 * */
frame_parse_result_t frame_data_fill_buff(frame_data_t *frame, uint8_t *buff, uint16_t* length)
{
    uint16_t len;
    len = *length;

  // assert length of buff
    if(frame->length > LENGTH_FIELD_SIZE(len))
    {
      FRAME_TAG_PRINTF("fill length(%u) field failure", LENGTH_FIELD_SIZE(len));
      FRAME_TAG_PRINTF("fill length field expected >= %u", frame->length);
      // The buffer is not enough to fill frame data
        return FRAME_LENGTH_PACK_ERR;
    }

    buff[FRAME_START_INDEX]   = frame->start;
    buff[FRAME_LENGTH_INDEX]  = frame->length;
    buff[FRAME_COMMAND_INDEX] = frame->cmd;
    // fill data field
    for(int i = 0; i < DATA_FIELD_SIZE(frame->length); i++)
    {
        buff[FRAME_DATA_INDEX + i] = frame->p_data[i];
    }
    buff[FRAME_CRC_INDEX(frame->length)] = frame->crc;
    buff[FRAME_STOP_INDEX(frame->length)] = frame->stop;

    // size of buffer after fill
    *length = FRAME_SIZE(frame->length);
    FRAME_TAG_PRINTF("fill buffer length %u\r\n", *length);

    // all thing is OK
    return FRAME_OK;
}

/* Brief: Create frame data within command, data and length
 * [frame] pointer of frame data output
 * [cmd] command of frame
 * [p_data] pointer to data of frame
 * [length] length data buff of frame
 * */
void frame_data_create(frame_data_t *frame, uint8_t cmd, uint8_t *p_data, uint16_t length)
{
    // byte start
    frame->start  = FRAME_START_BYTE;
    frame->length = length + LENGTH_FIELD_SIZE_MIN;
    frame->cmd    = cmd;
    frame->p_data = p_data;

    // make crc of frame
    frame->crc = 0;
    frame->crc ^= frame->length;
    frame->crc ^= frame->cmd;
    // xor crc with data field
    for(int i = 0; i < DATA_FIELD_SIZE(frame->length); i++)
    {
        frame->crc ^= frame->p_data[i];
    }

    // byte stop
    frame->stop = FRAME_STOP_BYTE;

    FRAME_TAG_PRINTF("====== create fields ======");
    FRAME_PRINTF("\r\n- start : 0x%02X", frame->start);
    FRAME_PRINTF("\r\n- length: 0x%02X", frame->length);
    FRAME_PRINTF("\r\n- cmd   : 0x%02X", frame->cmd);
    FRAME_PRINTF("\r\n- crc   : 0x%02X", frame->crc);
    FRAME_PRINTF("\r\n- stop  : 0x%02X\r\n", frame->stop);
}

/* Brief: Parse frame data within buffer and length
 * [frame] pointer of frame data output
 * [p_buff] pointer to frame buff
 * [length] length of frame buff
 * Return: frame_parse_result_t
 * */
frame_parse_result_t frame_data_parse(frame_data_t *frame, uint8_t *p_buff, uint16_t length)
{
  uint8_t crc;
    // assert length of buff
  if( FRAME_SIZE_MIN > length)
    {
    FRAME_TAG_PRINTF("parse length(%u) of buffer failure", length);
    FRAME_TAG_PRINTF("length of buffer expected >= %u", FRAME_SIZE_MIN);
    // the buffer length is not enough to parse into frame data
        return FRAME_SIZE_MIN_ERR;
    }
    frame->start  = p_buff[FRAME_START_INDEX];
    frame->length = p_buff[FRAME_LENGTH_INDEX];
    frame->cmd    = p_buff[FRAME_COMMAND_INDEX];
    frame->p_data = &p_buff[FRAME_DATA_INDEX];

    // don't using FRAME_CRC_INDEX() to get crc field
    frame->crc    = p_buff[length - 2]; // crc field is a byte near last byte of buff
    // don't using FRAME_STOP_INDEX() to get stop field
    frame->stop   = p_buff[length - 1]; // stop field is the end byte of buff

    // assert start and stop field
    if(FRAME_START_BYTE != frame->start
        || FRAME_STOP_BYTE != frame->stop
        )
    {
      FRAME_TAG_PRINTF("parse start(0x%02X)/stop(0x%02X) fields failure", frame->start, frame->stop);
      return FRAME_SOF_EOF_ERR;
    }

    // assert length field
    if(frame->length != LENGTH_FIELD_SIZE(length))
    {
      FRAME_TAG_PRINTF("parse length(0x%02X) fields failure", frame->length);
      FRAME_TAG_PRINTF("length field expected 0x%02X", LENGTH_FIELD_SIZE(length));
      // the length field is not fit with length of buff
        return FRAME_LENGTH_PACK_ERR;
    }

    // check crc of frame
    crc = 0;
    crc ^= frame->length;
    crc ^= frame->cmd;
    // xor crc with data field
    for(int i = 0; i < DATA_FIELD_SIZE(frame->length); i++)
    {
        crc ^= frame->p_data[i];
    }

    // assert crc field
    if(crc != frame->crc)
    {
      FRAME_TAG_PRINTF("parse crc(0x%02X) fields failure", frame->crc);
      FRAME_TAG_PRINTF("crc field expected 0x%02X", crc);
      // Add crc expect of frame
        frame->crc = crc;
        return FRAME_CRC_ERR;
    }

    FRAME_TAG_PRINTF("====== parse fields =======");
  FRAME_PRINTF("\r\n- start : 0x%02X", frame->start);
  FRAME_PRINTF("\r\n- length: 0x%02X", frame->length);
  FRAME_PRINTF("\r\n- cmd   : 0x%02X", frame->cmd);
  FRAME_PRINTF("\r\n- crc   : 0x%02X", frame->crc);
  FRAME_PRINTF("\r\n- stop  : 0x%02X\r\n", frame->stop);

    // all thing is OK
    return FRAME_OK;
}
