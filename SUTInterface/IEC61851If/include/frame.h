/* Frame format
 *  ______________________________________________________
 * | Start(0x7E) | Length | CMD | Data | CRC | Stop(0x7F) |
 * |_____________|________|_____|______|_____|____________|
 *
 * Length field (1 byte): total bytes from cmd field to CRC field.
 * CMD (1 byte): is a command of frame.
 * Data (n bytes): is data of frame with the length dependent once command.
 * CRC (1 byte): is XOR formula of bytes from Length field to the end byte of data field
 * */

#ifndef _FRAME_FORMAT_H
#define _FRAME_FORMAT_H

/* Macro enable debug frame format */
#define FRAME_DEBUG_ENABLE  0

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"
/* size fields of frame */
#define START_BYTE_NUM             1  /*!< 1 byte */
#define LENGTH_BYTE_NUM            1  /*!< 1 byte */
#define CMD_BYTE_NUM               1  /*!< 1 byte */
#define CRC_BYTE_NUM               1  /*!< 1 byte */
#define STOP_BYTE_NUM              1  /*!< 1 byte */
#define START_LENGTH_STOP_NUM      (START_BYTE_NUM + LENGTH_BYTE_NUM + STOP_BYTE_NUM)    /*!< 3 bytes */

#define LENGTH_FIELD_SIZE_MAX      255  /*!< 8 bit value max */
#define LENGTH_FIELD_SIZE_MIN      (CMD_BYTE_NUM + CRC_BYTE_NUM)   /*!< 2 bytes */
#define FRAME_SIZE_MAX             (LENGTH_FIELD_SIZE_MAX + START_LENGTH_STOP_NUM)   /*!< 258 bytes */
#define FRAME_SIZE_MIN             (START_BYTE_NUM + LENGTH_BYTE_NUM + CMD_BYTE_NUM + CRC_BYTE_NUM + STOP_BYTE_NUM)  /*!< 5 bytes */

/* x: lenght of frame buffer */
#define LENGTH_FIELD_SIZE(x)  (x - START_LENGTH_STOP_NUM) /*!< - (1byte start + 1byte stop + 1byte length) */
/* x: lenght field size */
#define DATA_FIELD_SIZE(x)    (x - LENGTH_FIELD_SIZE_MIN) /*!< length of data field */
/* x: lenght field size */
#define FRAME_SIZE(x)         (START_LENGTH_STOP_NUM + x) /*!< + (1byte start + 1byte stop + 1byte length) */

#define FRAME_START_BYTE      0x7E
#define  FRAME_STOP_BYTE       0x7F

// the index fields of frame
#define FRAME_START_INDEX     0
#define FRAME_LENGTH_INDEX    1
#define FRAME_COMMAND_INDEX   2
#define FRAME_DATA_INDEX      3
/* x: length field value of frame */
#define FRAME_CRC_INDEX(x)    (1 + x)
#define FRAME_STOP_INDEX(x)   (2 + x)

typedef enum
{
    FRAME_OK = 0,            /*!< FRAME parse true */
    FRAME_ERR,               /*!< FRAME parse false common */
    FRAME_SIZE_MIN_ERR,    /*!< FRAME parse result with length of buff < FRAME_SIZE_MIN */
    FRAME_SOF_EOF_ERR,       /*!< FRAME parse error FRAME_START_BYTE or FRAME_STOP_BYTE */
    FRAME_LENGTH_PACK_ERR,   /*!< FRAME create/parse error with Length field is not fit length of buff */
    FRAME_CRC_ERR            /*!< FRAME parse error CRC */
} frame_parse_result_t;

typedef struct
{
  uint8_t *p_data;         /*!< FRAME pointer to data buff */
  uint8_t start;         /*!< FRAME start byte */
  uint8_t length;          /*!< FRAME length byte */
  uint8_t cmd;             /*!< FRAME command byte */
  uint8_t crc;             /*!< FRAME crc byte */
  uint8_t stop;            /*!< FRAME stop byte */
} frame_data_t;

typedef uint16_t frame_size;

/* Brief: Make output buffer from frame field
 * [frame] pointer of frame data input
 * [buff] pointer of data buff output
 * [length] length data buff to fill
 * Return: frame_parse_result_t
 * */
frame_parse_result_t frame_data_fill_buff(frame_data_t *frame, uint8_t *buff, uint16_t* length);

/* Brief: Create frame data within command, data and length
 * [frame] pointer of frame data output
 * [cmd] command of frame
 * [p_data] pointer to data of frame
 * [length] length data buff of frame
 * */
void frame_data_create(frame_data_t *frame, uint8_t cmd, uint8_t *p_data, uint16_t length);

/* Brief: Parse frame data within buffer and length
 * [frame] pointer of frame data output
 * [p_buff] pointer to frame buff
 * [length] length of frame buff
 * Return: frame_parse_result_t
 * */
frame_parse_result_t frame_data_parse(frame_data_t *frame, uint8_t *p_buff, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /* _FRAME_FORMAT_H */
