//
// Created by james on 23/10/2020.
//

#ifndef EVCC_V2GSDPRESMESSAGE_H
#define EVCC_V2GSDPRESMESSAGE_H

#include "V2gTpMessage.h"

using namespace DataStructure_SDP;

#define ISO1PART2_SDP_RES_LENGTH 20
#define ISO1PART2_SDP_IPV6_LENGTH 16
#define ISO1PART2_SDP_RES_SEC_TLS 0x00
#define ISO1PART2_SDP_RES_NO_SEC 0x10
#define ISO1PART2_SDP_RES_TRAN_TCP 0x00
#define ISO1PART2_SDP_RES_TRAN_UDP 0x10

class V2gSdpResMessage : public V2gTpMessage
{

public:
  // return message data
  // SECC IP Address(16) | SECC Port(2) | Security(1)| Transport Protocol(1)
  V2gSdpResMessage();
  V2gSdpResMessage(const std::string &ipv6, uint16_t port, uint8_t secType, uint8_t tpType);

  virtual ~V2gSdpResMessage() {}

  void setSecurityType(uint8_t secType);
  uint8_t getSecurityType();
  void setTransportType(uint8_t tpType);
  uint8_t getTransportType();
  size_t setIpV6Addr(const char *buffer, size_t len);
  size_t setIpV6Addr(const std::array<uint8_t, 16> &ipv6_val);
  size_t setIpV6Addr(const std::string &ipv6_str_val);
  size_t getSeccIpAddr(char *buffer, size_t len);
  void setPort(uint16_t port);
  uint16_t getSeccPort(void);
  void serialize(void);
  bool deserialize(void);
  void dumpMsg(void);
  void resetSerializeFlag(void) { serialized_flag = false;}

  const uint32_t V2G_SDP_RES_SECC_IP_LENGTH = 16;
  const uint32_t V2G_SDP_RES_SECC_PORT_LENGTH = 2;
  const uint32_t V2G_SDP_RES_SECC_IP_INDEX = 0;
  const uint32_t V2G_SDP_RES_SECC_PORT_INDEX = 16;
  const uint32_t V2G_SDP_RES_SECC_SEC_INDEX = 18;
  const uint32_t V2G_SDP_RES_SECC_TRANSPORT_INDEX = 19;

  static const uint8_t V2G_SDP_SEC_TLS = 0x00;
  static const uint8_t V2G_SDP_NON_SECURED = 0x10;
  static const uint8_t V2G_SDP_TRANSPORT_TCP = 0x00;
  static const uint8_t V2G_SDP_TRANSPORT_UDP = 0x10;
  static const uint32_t V2G_SDP_PAYLOAD_LEN = 2U;

  comparision_indicate_flag mSecurity_flag = has_value;
  comparision_indicate_flag mTransport_flag = has_value;
  comparision_indicate_flag mIpV6Addr_flag = has_value;
  comparision_indicate_flag mPort_flag = has_value;

  bool operator==(V2gSdpResMessage &object_compare)
  {
    bool final_result = true;
    bool arr_result[4] = {true, true, true, true};
    char mIpV6Addr_temp[ISO1PART2_SDP_IPV6_LENGTH] = {0};

    switch (this->mSecurity_flag)
    {
    case specific:
      if (this->mSecurityType != object_compare.getSecurityType())
      {
        arr_result[0] = false;
      }
      break;
    case has_value:
      if ((object_compare.getSecurityType() != ISO1PART2_SDP_RES_SEC_TLS) && (object_compare.getSecurityType() != ISO1PART2_SDP_RES_NO_SEC))
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
      if ((object_compare.getTransportType() != ISO1PART2_SDP_RES_TRAN_UDP) && (object_compare.getTransportType() != ISO1PART2_SDP_RES_TRAN_TCP))
      {
        arr_result[1] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->mIpV6Addr_flag)
    {
    case specific:
      /* Get IPV6 address */
      object_compare.getSeccIpAddr(mIpV6Addr_temp, ISO1PART2_SDP_IPV6_LENGTH);

      char mIpV6Addr_cmp[ISO1PART2_SDP_IPV6_LENGTH];

      memcpy(mIpV6Addr_cmp, this->mIpV6Addr.data(), ISO1PART2_SDP_IPV6_LENGTH);

      arr_result[2] = !memcmp(mIpV6Addr_temp, mIpV6Addr_cmp, ISO1PART2_SDP_IPV6_LENGTH);
      break;
    case has_value:

      arr_result[2] = false;
      object_compare.getSeccIpAddr(mIpV6Addr_temp, ISO1PART2_SDP_IPV6_LENGTH);

      for (int i = 0; i < ISO1PART2_SDP_IPV6_LENGTH; i++)
      {
        if (mIpV6Addr_temp[i] != 0)
        {
          arr_result[2] = true;
          break;
        }
      }
      break;
    case omit:
    default:
      break;
    }

    switch (this->mPort_flag)
    {
    case specific:
      if (this->mPort != object_compare.getSeccPort())
      {
        arr_result[3] = false;
      }

      break;
    case has_value:
      if (object_compare.getTransportType() == 0xFFFF)
      {
        arr_result[3] = false;
      }
      break;
    case omit:
    default:
      break;
    }

    for (int i = 0; i < 4; i++)
    {
      if (arr_result[i] == false)
      {
        final_result = false;
      }
    }

    return final_result;
  }

private:
  bool serialized_flag = false;
  uint8_t mSecurityType = 0xFF;
  uint8_t mTransportType = 0xFF;
  std::array<uint8_t, 16> mIpV6Addr;
  uint16_t mPort = 0xFFFF;
};

#endif //EVCC_V2GSDPRESMESSAGE_H
