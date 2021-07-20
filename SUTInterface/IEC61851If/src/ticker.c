#include "sys_tick.h"
#include "ticker.h"

static ticker_function_handle_t* ticker_function_handle[TICKER_FUNCTION_HANDLE_MAX];
static void ticker_function_loop(ticker_function_handle_t *fp_ticker);

void ticker_begin(ticker_t *ticker, uint32_t interval) {
  ticker->start = millis();
  ticker->interval = interval;
  ticker->status = TICKER_RUNNING;
}

/* brief: check ticker expired
 * return 1: ticker running to stop
 * return 0: ticker stop
 * */
uint8_t ticker_expired(ticker_t *ticker) {
  if((TICKER_RUNNING == ticker->status) && ((millis() - ticker->start) >= ticker->interval)) {
    ticker->status = TICKER_STOP;
    return 1;
  }
  return 0;
}

void ticker_stop(ticker_t *ticker) {
  ticker->status = TICKER_STOP;
}

ticker_status_t ticker_status(ticker_t *ticker) {
  return ticker->status;
}

uint32_t ticker_remain(ticker_t *ticker) {
  if(TICKER_STOP == ticker->status) return 0;
  if((millis() - ticker->start) >= ticker->interval) return 0;
  return (ticker->start + ticker->interval - millis());
}

void ticker_refresh(ticker_t *ticker) {
  ticker->start = millis();
}

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
                        uint16_t repeat)
{
    ticker_begin(&fp_ticker->ticker, interval);
    fp_ticker->cb = fp_register;
    fp_ticker->interval = interval;
    fp_ticker->repeat = repeat;

  for(uint8_t i = 0; i < TICKER_FUNCTION_HANDLE_MAX; ++i)
  {
    if(0 == ticker_function_handle[i])
    {
      ticker_function_handle[i] = fp_ticker;
      return (i + 1);
    }
  }

  return 0;
}

void ticker_loop(void)
{
  for(uint8_t i = 0; i < TICKER_FUNCTION_HANDLE_MAX; ++i)
  {
    if(0 != ticker_function_handle[i])
    {
      ticker_function_loop(ticker_function_handle[i]);
    }
    else
    {
      break;  // end loop
    }

  }
}

static void ticker_function_loop(ticker_function_handle_t *fp_ticker)
{
  if (!ticker_expired(&fp_ticker->ticker)) return;
  if(TICKER_FOREVER == fp_ticker->repeat)
  {
    fp_ticker->ticker.status = TICKER_RUNNING;
  }
  else
  {
    --fp_ticker->repeat;
  if(0 != fp_ticker->repeat)
    {
      fp_ticker->ticker.status = TICKER_RUNNING;
    }
  }
  // update offset timer start
  fp_ticker->ticker.start += fp_ticker->interval;

  // call cb function
  fp_ticker->cb(fp_ticker->repeat);
}
