/*
 * V2gTpMessage.h
 *
 *  Created on: Feb 5, 2021
 *      Author: nhannh3
 */

#ifndef V2GTPMESSAGE_H_
#define V2GTPMESSAGE_H_

#if !defined(_V2G_TP_MESSAGE_H_)
#define _V2G_TP_MESSAGE_H_

#include <iostream>
#include <sstream>
#include <memory>
#include <string>
// transport layer function
#include <v2gtp.h>
#include "TsDataType.h"
#include "TestSystemLogging.h"
typedef enum
{
  ALM_HAND_SHAKE = 0,
  ALM_EXI,
  ALM_SDP_REQ,
  ALM_SDP_RES
} ALMType;

using namespace DataStructure_V2GTP;

#define V2GTP_VERSION (unsigned char)0x01
#define V2GTP_VERSION_INV (unsigned char)0xFE
#define V2GTP_HEADER_LENGTH 8

class V2gTpMessage : public std::enable_shared_from_this<V2gTpMessage>
{
public:
  V2gTpMessage();
  // init internal data (allocate mMessage data) with payload type
  V2gTpMessage(uint16_t payloadType);
  // init internal data (allocate mMessage data) with payload type and data
  V2gTpMessage(uint16_t payloadType, char *buffer, size_t size);
  V2gTpMessage(uint8_t v2gtp_version, uint8_t v2gtp_version_inv);
  virtual ~V2gTpMessage();
  // set message data
  void setMessage(const char *buffer, size_t len);

  // get message data
  ssize_t getMessage(char *buffer, size_t len);
  ssize_t getBufferPtr(char **buffer_ptr);

  void setHeader(const char *buffer);
  void getHeader(char *buffer);

  void setPayload(const char *buffer, size_t len);
  size_t getPayload(char *buffer, size_t len);
  // set payload type
  void setPayloadType(uint16_t type);

  // return payload type
  uint16_t getPayloadType();
  // return payload length
  uint32_t getPayloadLength();
  void setPayloadLength(uint32_t size);
  void setTPVersion(uint8_t ver, uint8_t inverse);
  void dumpTpHeader(void);

  static const uint16_t V2G_TP_PAYLOAD_EXI = 0x8001;
  static const uint16_t V2G_TP_PAYLOAD_SDP_REQ = 0x9000;
  static const uint16_t V2G_TP_PAYLOAD_SDP_RES = 0x9001;

  ALMType ALMsgType;

protected:
  const uint8_t mProtocolVersion = V2GTP_VERSION;
  const uint8_t mInverseProtocolVersion = V2GTP_VERSION_INV;
  uint16_t mPayloadType;
  uint32_t mPayloadLength;
  char *mHeader;
  char *mPayload;
  char *mMessage;
};

#endif //!defined(_V2G_TP_MESSAGE_H_)

#endif /* V2GTPMESSAGE_H_ */
