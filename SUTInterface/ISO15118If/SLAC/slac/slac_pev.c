#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include "../tools/getoptv.h"
#include "../tools/putoptv.h"
#include "../tools/memory.h"
#include "../tools/number.h"
#include "../tools/types.h"
#include "../tools/flags.h"
#include "../tools/files.h"
#include "../tools/error.h"
#include "../tools/config.h"
#include "../tools/permissions.h"
#include "../tools/timer.h"
#include "../ether/channel.h"
#include "../slac/slac.h"
/*====================================================================*
 *   program constants;
 *--------------------------------------------------------------------*/
// file descriptor to ethernet socket
struct channel_t glb_channel =
{
  (file_t)(-1),
  0,
  CHANNEL_ETHNUMBER,
  CHANNEL_ETHDEVICE,
  {
    0x00,
    0xB0,
    0x52,
    0x00,
    0x00,
    0x01
  },
  {
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00
  },
  0x88E1,
#if defined (__linux__)
#elif defined (__APPLE__) || defined (__OpenBSD__) || defined (__NetBSD__) || defined (__FreeBSD__)
  (struct bpf *) (0),
#elif defined (WINPCAP) || defined (LIBPCAP)
  (pcap_t *)(0),
  {
    0
  },
#else
#error "Unknown Environment"
#endif
  CHANNEL_TIMEOUT,
  CHANNEL_TIMEOUT,
  CHANNEL_FLAGS
};

#define PLCDEVICE "PLC"
#define PROFILE "pev.ini"
#define SECTION "default"
#define PEV_STATE_NONE 0
#define PEV_STATE_DISCONNECTED 1
#define PEV_STATE_UNMATCHED 2
#define PEV_STATE_MATCHED 3
#define PEV_VID "0000000000000000000000000000000000" // VehicleIdentifier
#define PEV_NMK "50D3E4933F855B7040784DF815AA8DB7"   // HomePlugAV
#define PEV_NID "B0F2E695666B03"                     // HomePlugAV
unsigned state = 0;

// datalink connection session
static struct session_t glb_session;
// send message = ethernet header + payload
static struct message_t glb_message;
static char const * profile = PROFILE;
static char const * section = SECTION;

/*====================================================================*
 *
 *   static void configure ();
 *
 *   print template PEV-HLE configuration file on stdout so that
 *   profile, section and element names match;
 *
 *--------------------------------------------------------------------*/
// static void configure ()
// {
//   printf ("# file: %s\n", PROFILE);
//   printf ("# ====================================================================\n");
//   printf ("# PEV-HLE initialization;\n");
//   printf ("# --------------------------------------------------------------------\n");
//   printf ("[%s]\n", SECTION);
//   printf ("vehicle identifier = %s\n", PEV_VID);
//   printf ("network membership key = %s\n", PEV_NMK);
//   printf ("network identifier = %s\n", PEV_NID);
//   printf ("attenuation threshold = %d\n", SLAC_LIMIT);
//   printf ("msound pause = %d\n", SLAC_PAUSE);
//   printf ("charge time = %d\n", SLAC_CHARGETIME);
//   printf ("settle time = %d\n", SLAC_SETTLETIME);
//   return;
// }
static void initialize_session (struct session_t * session, char const * profile, char const * section)
{
  session->next = session->prev = session;
  // get string value and convert to hex value store to PEV_ID_field
  hexencode (session->PEV_ID, sizeof (session->PEV_ID), configstring (profile, section, "VehicleIdentifier", PEV_VID));
  // NMK from input file
  hexencode (session->NMK, sizeof (session->NMK), configstring (profile, section, "NetworkMembershipKey", PEV_NMK));
  // NID from input file
  hexencode (session->NID, sizeof (session->NID), configstring (profile, section, "NetworkIdentifier", PEV_NID));
  session->limit = confignumber_range (profile, section, "AttenuationThreshold", SLAC_LIMIT, 0, UINT_MAX);
	// sleep millisecond between SoundMessage
  session->pause = confignumber_range (profile, section, "MSoundPause", SLAC_PAUSE, 0, UINT_MAX);
	// sleep second between state (after set key value)
  session->settletime = confignumber_range (profile, section, "SettleTime", SLAC_SETTLETIME, 0, UINT_MAX);
	// sleep second after join network (charging)
  session->chargetime = confignumber_range (profile, section, "ChargeTime", SLAC_CHARGETIME, 0, UINT_MAX);
  session->state = PEV_STATE_DISCONNECTED;
  session->flags = 0;
	// store the original NMK, to rewrite back after leaving network
	// device shall get NMK, NID, VehicleID from input file
	// NMK,NID change during slac operation, joining other network
  memcpy (session->original_nmk, session->NMK, sizeof (session->original_nmk));
  memcpy (session->original_nid, session->NID, sizeof (session->original_nid));
  // print out debug info
  slac_session (session);
  return;
}

static signed identifier (struct session_t * session, struct channel_t * channel)
{
  time_t now;
  time (& now);
  memset (session->RunID, 0, sizeof (session->RunID));
  // set RunID for session = mac address of channel interface
	memcpy (session->RunID, channel->host, ETHER_ADDR_LEN);
  // set session pev mac
	memcpy (session->PEV_MAC, channel->host, sizeof (session->PEV_MAC));
  return (0);
}

int api_initialize(const char *config_file, const char *interface_name) {
  if (0 != initchannel(&glb_channel)) {
    return 1;
  }
  desuid ();
  memset (&glb_session, 0, sizeof(glb_session));
  memset (&glb_message, 0, sizeof(glb_message));
  glb_channel.timeout = SLAC_TIMEOUT;
  // get environment variable "PLC" for name of PLC device
  if (getenv (PLCDEVICE))
  {
    #if defined (WINPCAP) || defined (LIBPCAP)
    channel.ifindex = atoi (getenv (PLCDEVICE));
    #else
    // set plc channel interface name
    glb_channel.ifname = strdup (getenv(PLCDEVICE));
    #endif
  }
  if (NULL != interface_name) {
    glb_channel.ifname = interface_name;
  }
  // open file descriptor of socket
  if (0 != openchannel (&glb_channel)) {
    return 1;
  }
  // update session field with channel data
  if (0 != identifier (&glb_session, &glb_channel)) {
    return 1;
  }
  if (NULL != config_file) {
    profile = config_file;
  }
  printf("PROFILE :%s\r\n", profile);
  // init session data base on input profile
  initialize_session (&glb_session, profile, section);
  return 0;
}

int api_set_key(void) {
  if (pev_cm_set_key(&glb_session, &glb_channel, &glb_message)) {
    slac_debug (&glb_session, 0, __func__, "Can't set key");
    return 1;
  }
  SLEEP(glb_session.settletime);
  return 0;
}

bool api_param_exchange(void) {
  static bool callone = false;
  if (callone == false) {
    slac_session (&glb_session);
    slac_debug (&glb_session, 0, __func__, "Probing ...");
    // increase runID by 1 in the last byte
    memincr (glb_session.RunID, sizeof (glb_session.RunID));
    callone = true;
  }
  // send slac param
  if (0 != pev_cm_slac_param(&glb_session, &glb_channel, &glb_message)){
    return false;
  }
  else {
    callone = false;
    glb_session.state = PEV_STATE_UNMATCHED;
    return true;
  }
}
bool api_start_atten_char(void) {
  static bool callone = false;
  if (callone == false) {
    slac_session(&glb_session);
    slac_debug (&glb_session, 0, __func__, "Start atten char ...");
    callone = true;
  }
  // pev_cm_start_atten_char should be sent 3 time C_EV_start_atten_char_inds
  // only called 1 time here. incase of losing message then session setup fail
  if (0 != pev_cm_start_atten_char(&glb_session, &glb_channel, &glb_message)) {
    return false;
  }
  else {
    callone = false;
    return true;
  }
}
bool api_mnbc_sound(void) {
  static bool callone = false;
  if (callone == false) {
    slac_session(&glb_session);
    slac_debug (&glb_session, 0, __func__, "Sounding ...");
    callone = true;
  }
  if (0 != pev_cm_mnbc_sound(&glb_session, &glb_channel, &glb_message)) {
    return false;
  }
  else {
    callone = false;
    return true;
  }
}
bool api_atten_char(void) {
  static bool callone = false;
  if (callone == false) {
    slac_session(&glb_session);
    slac_debug (&glb_session, 0, __func__, "Atten char ...");
    callone = true;
  }
  if (0 != pev_cm_atten_char(&glb_session, &glb_channel, &glb_message)) {
    return false;
  }
  else {
    callone = false;
    return true;
  }
}
int api_avg_atten_val(void) {
  unsigned group = 0;
  unsigned total = 0;
  if (glb_session.NumGroups > SIZEOF (glb_session.AAG))
  {
    return (slac_debug (&glb_session, glb_session.exit, __func__, "Too much data to analyse!"));
  }
  if (glb_session.NumGroups > 0)
  {
    while (group < glb_session.NumGroups)
    {
      total += glb_session.AAG [group];
      group++;
    }
    total /= group;
    return total;
  }
  return (slac_debug (&glb_session, glb_session.exit, __func__, "Nothing to analyse"));
}
int api_validate(uint8_t timer_val, float period, uint8_t toggle_num, callBCB func) {
  if (timer_val == 0) {
    slac_debug(&glb_session, 0, __func__, "Validate step 1 ...");
  }
  else {
    slac_debug(&glb_session, 0, __func__, "Validate step 2 ...");
  }
  int result = pev_cm_validate(&glb_session, &glb_channel, &glb_message, timer_val, period, toggle_num, func);
  if ((result == -1) || (result == RESULT_CODE_NOT_READY) || (result == RESULT_CODE_FAILURE)){
    slac_debug(&glb_session, 0, __func__, "Validate result fail");
    return -1;
  }
  else {
    return result;
  }
}
bool api_match(void) {
  slac_debug (&glb_session, 0, __func__, "Matching ...");
  if (0 != pev_cm_slac_match(&glb_session, &glb_channel, &glb_message)) {
    return false;
  }
  else {
    return true;
  }
}
int api_amp_map(void) {
  return 0;
}
int api_reset_config(void) {
  memcpy(glb_session.NMK, glb_session.original_nmk, sizeof (glb_session.NMK));
  memcpy(glb_session.NID, glb_session.original_nid, sizeof (glb_session.NID));
  if (0 == api_set_key()) {
    return closechannel(&glb_channel);
  }
  else {
    return 1;
  }
}
int api_store_config(void) {
  return 0;
}
int api_close(void) {
  return closechannel(&glb_channel);
}
int api_open(void) {
  return openchannel(&glb_channel);
}
