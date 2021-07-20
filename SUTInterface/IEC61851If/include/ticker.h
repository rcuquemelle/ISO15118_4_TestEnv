#ifndef _TICKER_H_
#define _TICKER_H_

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#define TICKER_FUNCTION_HANDLE_MAX 20 /* maximum number ticker function handler */
#define TICKER_FOREVER 0xFFFF
#define TICKER_START_INIT    \
  {                          \
    .start = 0,              \
    .interval = 0,           \
    .status = TICKER_RUNNING \
  }

#define TICKER_STOP_INIT  \
  {                       \
    .start = 0,           \
    .interval = 0,        \
    .status = TICKER_STOP \
  }

  typedef enum
  {
    TICKER_STOP = 0,
    TICKER_RUNNING
  } ticker_status_t;

  typedef struct
  {
    uint64_t start;    //ticker Start
    uint32_t interval; //tickerout_Value
    ticker_status_t status;
  } ticker_t;

  typedef struct
  {
    ticker_t ticker;
    void (*cb)(uint32_t);
    uint32_t interval;
    uint16_t repeat;
  } ticker_function_handle_t;

  uint8_t ticker_expired(ticker_t *ticker);
  void ticker_begin(ticker_t *ticker, uint32_t interval);
  void ticker_stop(ticker_t *ticker);
  ticker_status_t ticker_status(ticker_t *ticker);
  uint32_t ticker_remain(ticker_t *ticker);
  void ticker_refresh(ticker_t *ticker);

  /* brief: ticker function register init
 * [fp_ticker]: ticker function object
 * [fp_register]: function callback register pointer
 * [interval]: ticker function interval
 * [repeat]: ticker function repeat
 *           TICKER_FOREVER: repeat forever
 * return: 0 (error), otherwise return index function register
*/
  uint8_t ticker_function_init(ticker_function_handle_t *fp_ticker,
                               void (*fp_register)(uint32_t),
                               uint32_t interval,
                               uint16_t repeat);
  void ticker_loop(void);

#ifdef __cplusplus
}
#endif

#endif /* _TICKER_H_ */
