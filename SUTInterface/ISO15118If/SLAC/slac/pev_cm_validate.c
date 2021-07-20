
#include <sys/time.h>
#include <memory.h>
#include <errno.h>
#include <string.h>
#include "../tools/types.h"
#include "../tools/error.h"
#include "../ether/channel.h"
#include "../slac/slac.h"
#include "../mme/mme.h"
signed pev_cm_validate (struct session_t * session, struct channel_t * channel, struct message_t * message, uint8_t timer_val, float period, uint8_t toggle_num, callBCB func)
{
  // optional phase to check connect to correct EVSE
  struct cm_validate_request * request = (struct cm_validate_request *) (message);
  struct cm_validate_confirm * confirm = (struct cm_validate_confirm *) (message);
  slac_debug (session, 0, __func__, "--> CM_SLAC_PARAM.REQ");
  // clean message mem
  memset (message, 0, sizeof (* message));
  
  // set header data
  EthernetHeader (& request->ethernet, session->EVSE_MAC, channel->host, channel->type);
  HomePlugHeader1 (& request->homeplug, HOMEPLUG_MMV, (CM_VALIDATE | MMTYPE_REQ));
  
  // set message payload data
  request->SignalType = 0x00;
  request->VRVarField.Timer = timer_val;
  request->VRVarField.Result = RESULT_CODE_READY;
  // send data to FD of socket channel, return number byte send, -1 for error
  // length = ETHERNET PACKET min - crc ??
  if (sendmessage (channel, message, sizeof(*request)) <= 0)
  {
    return (slac_debug (session, 1, __func__, CHANNEL_CANTSEND));
  }
  if (timer_val != 0) {
    // trigger toggle
    (*func)(period, toggle_num);
  }
  while (readmessage (channel, message, HOMEPLUG_MMV, (CM_VALIDATE | MMTYPE_CNF)) > 0)
  {
    // check if return RunID is same and request
    if ((confirm->SignalType == request->SignalType)) {
      if ((RESULT_CODE_NOT_READY <= confirm->VCVarField.Result) && (RESULT_CODE_NOT_REQUIRED >= confirm->VCVarField.Result)) {
        if (timer_val == 0) {
          slac_debug (session, 0, __func__, "<-- CM_SLAC_PARAM.CNF1 %d", confirm->VCVarField.Result);
          return confirm->VCVarField.Result;
        }
        else {
          slac_debug (session, 0, __func__, "<-- CM_SLAC_PARAM.CNF2 %d %d", confirm->VCVarField.Result, confirm->VCVarField.ToggleNum);
          if ((confirm->VCVarField.ToggleNum == toggle_num) && (confirm->VCVarField.Result == RESULT_CODE_SUCCESS)){
            return RESULT_CODE_SUCCESS;
          }
          else {
            return -1;
          }
        }
      }
      else {
        slac_debug (session, 0, __func__, "<-- CM_SLAC_PARAM.CNF ? Fail Result out of range");
        return -1;
      }
    }
    else
    {
      slac_debug (session, 0, __func__, "<-- CM_SLAC_PARAM.CNF ? Fail SignalType");
      return -1;
    }
  }
  slac_debug (session, 0, __func__, "<-- CM_SLAC_PARAM.CNF ?");
  return -1;
}