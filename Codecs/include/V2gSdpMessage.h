//
// Created by james on 30/09/2020.
//

#ifndef EVCC_V2GSDPMESSAGE_H
#define EVCC_V2GSDPMESSAGE_H

#include "V2gTpMessage.h"

using namespace DataStructure_SDP;

#define ISO1PART2_SDP_REQ_LENGTH 2
#define ISO1PART2_SDP_REQ_SEC_TLS 0x00
#define ISO1PART2_SDP_REQ_NO_SEC 0x10
#define ISO1PART2_SDP_REQ_TRAN_TCP 0x00
#define ISO1PART2_SDP_REQ_TRAN_UDP 0x10

class V2gSdpMessage : public V2gTpMessage
{

public:
  V2gSdpMessage();
  V2gSdpMessage(uint8_t security, uint8_t transport);
  virtual ~V2gSdpMessage() {}

  void setSecurityType(uint8_t type);
  void setTransportType(uint8_t type);
  uint8_t getSecurityType();
  uint8_t getTransportType();
  void serialize(void);
  bool deserialize(void);
  void dumpMsg(void);
  static const uint8_t V2G_SDP_SEC_TLS = 0x00;
  static const uint8_t V2G_SDP_NON_SECURED = 0x10;
  static const uint8_t V2G_SDP_TRANSPORT_TCP = 0x00;
  static const uint8_t V2G_SDP_TRANSPORT_UDP = 0x10;

  static const uint32_t V2G_SDP_PAYLOAD_LEN = 2U;

  /* The flag of mSecurity type */
  comparision_indicate_flag mSecurity_flag = has_value;

  /* The flag of mTransport type */
  comparision_indicate_flag mTransport_flag = has_value;

  bool operator==(V2gSdpMessage &object_compare)
  {
    bool final_result = true;
    bool arr_result[2] = {true, true};
    switch (this->mSecurity_flag)
    {
    case specific:
      if (this->mSecurityType != object_compare.getSecurityType())
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if ((object_compare.getSecurityType() != ISO1PART2_SDP_REQ_SEC_TLS) && (object_compare.getSecurityType() != ISO1PART2_SDP_REQ_NO_SEC))
      {
        arr_result[0] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->mTransport_flag)
    {
    case specific:
      if (this->mTransportType != object_compare.getTransportType())
      {
        arr_result[1] = false;
      }
      break;
    case has_value:
      if ((object_compare.getTransportType() != ISO1PART2_SDP_REQ_TRAN_UDP) && (object_compare.getTransportType() != ISO1PART2_SDP_REQ_TRAN_TCP))
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    for (int i = 0; i < 2; i++)
    {
      if (arr_result[i] != true)
      {
        final_result = false;
        break;
      }
    }
    return final_result;
  }

private:
  uint8_t mSecurityType = 0xFF;
  // 0x00= TCP
  // 0x01-0x0F = reserved
  // 0x10 = reserved for UDP
  // 0x11-0xFF = reserved
  uint8_t mTransportType = 0xFF;
};

#endif //EVCC_V2GSDPMESSAGE_H
