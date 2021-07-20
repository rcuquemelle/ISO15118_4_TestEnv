/*====================================================================*
 *
 *   Copyright (c) 2013 Qualcomm Atheros, Inc.
 *
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted (subject to the limitations
 *   in the disclaimer below) provided that the following conditions
 *   are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials
 *     provided with the distribution.
 *
 *   * Neither the name of Qualcomm Atheros nor the names of
 *     its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written
 *     permission.
 *
 *   NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 *   GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE
 *   COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 *   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 *   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *   NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 *   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *--------------------------------------------------------------------*/
/*====================================================================*
 *
 *   slac.h -
 *
 *   this file contains defintions for the HomePlug Green PHY SLAC
 *   protocol;
 *
 *--------------------------------------------------------------------*/
#ifndef SLAC_HEADER
#define SLAC_HEADER
#ifdef __cplusplus
 extern "C" {
#endif
/*====================================================================*
 *   system header files;
 *--------------------------------------------------------------------*/
#include <stdint.h>
/*====================================================================*
 *   custom header files;
 *--------------------------------------------------------------------*/
#include "../tools/types.h"
#include "../tools/slac_endian.h"
#include "../ether/ether.h"
#include "../mme/mme.h"
#include "../ether/channel.h"
/*====================================================================*
 *   constants;
 *--------------------------------------------------------------------*/
#define SLAC_DEBUG 1
/*
 * The following two constants control whether or not the PEV or EVSE
 * change AVLN on SLAC protocol cycle; The recommended setting is PEV
 * changes with each pass and the EVSE does not;
 */
#define SLAC_AVLN_PEV 1
#define SLAC_AVLN_EVSE 0
#define SLAC_APPLICATION_PEV_EVSE 0x00
#define SLAC_SECURITY_NONE 0x00
#define SLAC_SECURITY_PUBLIC_KEY 0x01
#define SLAC_RUNID_LEN 8
#define SLAC_UNIQUE_ID_LEN 17
#define SLAC_RND_LEN 16
#define SLAC_NID_LEN 7
#define SLAC_NMK_LEN 16
#define SLAC_MSOUNDS 10
#define SLAC_TIMETOSOUND 6
#define SLAC_TIMEOUT 1000
#define SLAC_APPLICATION_TYPE 0
#define SLAC_SECURITY_TYPE 0
#define SLAC_RESPONSE_TYPE 0
#define SLAC_MSOUND_TARGET "FF:FF:FF:FF:FF:FF"
#define SLAC_FORWARD_STATION "00:00:00:00:00:00"
#define SLAC_GROUPS 58
#define SLAC_LIMIT 80
#define SLAC_PAUSE 20
#define SLAC_SETTLETIME 10
#define SLAC_CHARGETIME 2
#define SLAC_FLAGS 0
#define SLAC_SILENCE   (1 << 0)
#define SLAC_VERBOSE   (1 << 1)
#define SLAC_SESSION   (1 << 2)
#define SLAC_COMPARE   (1 << 3)
#define SLAC_SOUNDONLY (1 << 4)
#define SLAC_CM_SETKEY_KEYTYPE 0x01
#define SLAC_CM_SETKEY_PID 0x04
#define SLAC_CM_SETKEY_PRN 0x00
#define SLAC_CM_SETKEY_PMN 0x00
#define SLAC_CM_SETKEY_CCO 0x00
#define SLAC_CM_SETKEY_EKS 0x01
#define RESULT_CODE_NOT_READY 0x00
#define RESULT_CODE_READY 0x01
#define RESULT_CODE_SUCCESS 0x02
#define RESULT_CODE_FAILURE 0x03
#define RESULT_CODE_NOT_REQUIRED 0x04
/*===================================================================*
 *   messages;
 *--------------------------------------------------------------------*/
#ifndef __GNUC__
#pragma pack (push,1)
#endif
typedef struct __packed session_t
{
  struct session_t * next;
  struct session_t * prev;
  byte_t RunID [SLAC_RUNID_LEN];
  byte_t APPLICATION_TYPE;
  byte_t SECURITY_TYPE;
  byte_t RESP_TYPE;
  byte_t NUM_SOUNDS;
  byte_t TIME_OUT;
  byte_t AAG [SLAC_GROUPS];
  byte_t NumGroups;
  byte_t MSOUND_TARGET [ETHER_ADDR_LEN];
  byte_t FORWARDING_STA [ETHER_ADDR_LEN];
  byte_t PEV_ID [SLAC_UNIQUE_ID_LEN];
  byte_t PEV_MAC [ETHER_ADDR_LEN];
  byte_t EVSE_ID [SLAC_UNIQUE_ID_LEN];
  byte_t EVSE_MAC [ETHER_ADDR_LEN];
  byte_t RND [SLAC_UNIQUE_ID_LEN];
  byte_t NMK [SLAC_NMK_LEN];
  byte_t NID [SLAC_NID_LEN];
  byte_t original_nmk [SLAC_NMK_LEN];
  byte_t original_nid [SLAC_NID_LEN];
  unsigned state;
  unsigned sounds;
  unsigned limit;
  unsigned pause;
  unsigned chargetime;
  unsigned settletime;
  unsigned counter;
  unsigned flags;
  signed exit;
} session_t;
typedef struct __packed cm_sta_identity_request
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
} cm_sta_identity_request;
typedef struct __packed cm_sta_identity_confirm
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t GREEN_PHY_CAPABILITY;
  uint8_t POWER_SAVE_CAPABILITY;
  uint8_t GREEN_PHY_PREFERRED_ALLOCATION_CAPABILITY;
  uint8_t REPEATING_AND_ROUTING_CAPABILITY;
  uint8_t HOMEPLUG_AV_VERSION;
  uint8_t EFL;
  uint8_t EF [1];
}
cm_sta_identity_confirm;
typedef struct __packed cm_slac_param_request
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  uint8_t RunID [SLAC_RUNID_LEN];
  uint8_t CipherSuiteSetSize;
  uint16_t CipherSuite [1];
}
cm_slac_param_request;
typedef struct __packed cm_slac_param_confirm
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t MSOUND_TARGET [ETHER_ADDR_LEN];
  uint8_t NUM_SOUNDS;
  uint8_t TIME_OUT;
  uint8_t RESP_TYPE;
  uint8_t FORWARDING_STA [ETHER_ADDR_LEN];
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  uint8_t RunID [SLAC_RUNID_LEN];
  uint16_t CipherSuite;
}
cm_slac_param_confirm;
typedef struct __packed cm_start_atten_char_indicate
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  struct __packed
  {
    uint8_t NUM_SOUNDS;
    uint8_t TIME_OUT;
    uint8_t RESP_TYPE;
    uint8_t FORWARDING_STA [ETHER_ADDR_LEN];
    uint8_t RunID [SLAC_RUNID_LEN];
  }
  ACVarField;
}
cm_start_atten_char_indicate;
typedef struct __packed cm_start_atten_char_response
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
}
cm_start_atten_char_response;
typedef struct __packed cm_atten_char_indicate
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  struct __packed
  {
    uint8_t SOURCE_ADDRESS [ETHER_ADDR_LEN];
    uint8_t RunID [SLAC_RUNID_LEN];
    uint8_t SOURCE_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t RESP_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t NUM_SOUNDS;
    struct __packed
    {
      uint8_t NumGroups;
      uint8_t AAG [255];
    }
    ATTEN_PROFILE;
  }
  ACVarField;
}
cm_atten_char_indicate;
typedef struct __packed cm_atten_char_response
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  struct __packed
  {
    uint8_t SOURCE_ADDRESS [ETHER_ADDR_LEN];
    uint8_t RunID [SLAC_RUNID_LEN];
    uint8_t SOURCE_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t RESP_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t Result;
  }
  ACVarField;
}
cm_atten_char_response;
typedef struct __packed cm_mnbc_sound_indicate
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  struct __packed
  {
    uint8_t SenderID [SLAC_UNIQUE_ID_LEN];
    uint8_t CNT;
    uint8_t RunID [SLAC_RUNID_LEN];
    uint8_t RND [SLAC_UNIQUE_ID_LEN];
  }
  MSVarField;
}
cm_mnbc_sound_indcate;
typedef struct __packed cm_validate_request
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t SignalType;
  struct __packed
  {
    uint8_t Timer;
    uint8_t Result;
  }
  VRVarField;
}
cm_validate_request;
typedef struct __packed cm_validate_confirm
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t SignalType;
  struct __packed
  {
    uint8_t ToggleNum;
    uint8_t Result;
  }
  VCVarField;
}
cm_validate_confirm;
typedef struct __packed cm_slac_match_request
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  uint16_t MVFLength;
  struct __packed
  {
    uint8_t PEV_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t PEV_MAC [ETHER_ADDR_LEN];
    uint8_t EVSE_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t EVSE_MAC [ETHER_ADDR_LEN];
    uint8_t RunID [SLAC_RUNID_LEN];
    uint8_t RSVD [8];
  }
  MatchVarField;
}
cm_slac_match_request;
typedef struct __packed cm_slac_match_confirm
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t APPLICATION_TYPE;
  uint8_t SECURITY_TYPE;
  uint16_t MVFLength;
  struct __packed
  {
    uint8_t PEV_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t PEV_MAC [ETHER_ADDR_LEN];
    uint8_t EVSE_ID [SLAC_UNIQUE_ID_LEN];
    uint8_t EVSE_MAC [ETHER_ADDR_LEN];
    uint8_t RunID [SLAC_RUNID_LEN];
    uint8_t RSVD1 [8];
    uint8_t NID [SLAC_NID_LEN];
    uint8_t RSVD2;
    uint8_t NMK [SLAC_NMK_LEN];
  }
  MatchVarField;
}
cm_slac_match_confirm;
typedef struct __packed cm_atten_profile_indicate
{
  struct ethernet_hdr ethernet;
  struct homeplug_fmi homeplug;
  uint8_t PEV_MAC [ETHER_ADDR_LEN];
  uint8_t NumGroups;
  uint8_t RSVD;
  uint8_t AAG [255];
}
cm_atten_profile_indicate;
#ifndef __GNUC__
#pragma pack (pop)
#endif
typedef bool (*matchingType)(void);
typedef void (*callBCB)(float period, uint8_t number);
/*====================================================================*
 *   functions;
 *--------------------------------------------------------------------*/
signed pev_cm_set_key (struct session_t *, struct channel_t *, struct message_t *);
signed pev_cm_slac_param (struct session_t *, struct channel_t *, struct message_t *);
signed pev_cm_start_atten_char (struct session_t *, struct channel_t *, struct message_t *);
signed pev_cm_mnbc_sound (struct session_t *, struct channel_t *, struct message_t *);
signed pev_cm_atten_char (struct session_t *, struct channel_t *, struct message_t *);
signed pev_cm_validate (struct session_t * session, struct channel_t * channel, struct message_t * message, uint8_t timer_val, float period, uint8_t toggle_num, callBCB func);
signed pev_cm_slac_match (struct session_t *, struct channel_t *, struct message_t *);
signed pev_amp_map(struct session_t * session, struct channel_t * channel, struct message_t * message);

signed slac_connect (struct session_t *);
void slac_session (struct session_t *);
void slac_structs ();
signed slac_debug (struct session_t * session, signed status, char const * string, char const * format, ...);

int api_initialize(const char *config_file, const char *interface_name);
int api_set_key(void);
bool api_param_exchange(void);
bool api_start_atten_char(void);
bool api_mnbc_sound(void);
bool api_atten_char(void);
int api_avg_atten_val(void);
int api_validate(uint8_t timer_val, float period, uint8_t toggle_num, callBCB func);
bool api_match(void);
int api_amp_map(void);
int api_reset_config(void);
int api_store_config(void);
int api_close(void);
int api_open(void);
/*====================================================================*
 *
 *--------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif
