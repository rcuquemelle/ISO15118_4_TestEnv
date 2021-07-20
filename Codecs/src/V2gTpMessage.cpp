/*
 * V2gTpMessage.cpp
 *
 *  Created on: Feb 5, 2021
 *      Author: nhannh3
 */

#include "V2gTpMessage.h"
#include <string.h>

#define PAYLOAD_LEN_MAX 16384
#define MESSAGE_LEN_MAX (PAYLOAD_LEN_MAX + V2GTP_HEADER_LENGTH)
// 0x0000 - 0x8000      Reserved
// 0x8001               EXI encoded V2G Message
// 0x8002 - 0x8FFF      Reserved
// 0x9000               SDP request message
// 0x9001               SDP response message
// 0x9002 - 0x9FFF      Reserved
// 0xA000 - 0xFFFF      Manufacturer specific use
V2gTpMessage::V2gTpMessage()
{
  // ptr to output byte stream of message
  this->mMessage = new char[MESSAGE_LEN_MAX];
  // ptr to header of msg
  this->mHeader = this->mMessage;
  // ptr to payload part
  this->mPayload = this->mMessage + V2GTP_HEADER_LENGTH;
  this->mHeader[0] = V2GTP_VERSION;
  this->mHeader[1] = V2GTP_VERSION_INV;

  /* initial mMessage */
  this->mPayloadLength = PAYLOAD_LEN_MAX;
  this->mPayloadType = V2G_TP_PAYLOAD_EXI;
  this->ALMsgType = ALM_EXI;
}

V2gTpMessage::V2gTpMessage(uint8_t v2gtp_version, uint8_t v2gtp_version_inv)
    : V2gTpMessage()
{
  mHeader[0] = v2gtp_version;
  mHeader[1] = v2gtp_version_inv;
}

V2gTpMessage::V2gTpMessage(uint16_t payloadType)
    : V2gTpMessage()
{

  // 0x8001: V2G msg(TCP)
  // 0x9000: SDP request (UDP)
  // 0x9001: SDP response (UDP)
  this->mPayloadType = payloadType;
  // The most significant byte is sent first, the least significant byte is sent last.
  this->mHeader[2] = (this->mPayloadType >> 8);
  this->mHeader[3] = this->mPayloadType;
}

V2gTpMessage::V2gTpMessage(uint16_t payloadType, char *buffer, size_t size)
    : V2gTpMessage()
{
  this->mPayloadType = payloadType;
  this->mPayloadLength = size;
  if (buffer)
  {
    memcpy(this->mPayload, buffer, size);
  }
}

V2gTpMessage::~V2gTpMessage()
{
  if (this->mMessage)
  {
    delete this->mMessage;
  }
}

void V2gTpMessage::setTPVersion(uint8_t ver, uint8_t inverse)
{
  this->mHeader[0] = ver;
  this->mHeader[1] = inverse;
}
void V2gTpMessage::setPayloadType(uint16_t type)
{
  this->mPayloadType = type;
  this->mHeader[2] = (this->mPayloadType >> 8);
  this->mHeader[3] = this->mPayloadType;
}
void V2gTpMessage::setPayloadLength(uint32_t size)
{
  this->mHeader[4] = (uint8_t)(size >> 24);
  this->mHeader[5] = (uint8_t)(size >> 16);
  this->mHeader[6] = (uint8_t)(size >> 8);
  this->mHeader[7] = (uint8_t)size;
}
void V2gTpMessage::setPayload(const char *buffer, size_t len)
{
  if (buffer != nullptr)
  {
    memcpy(this->mPayload, buffer, len);
    mPayloadLength = len;
    this->mHeader[4] = (uint8_t)(mPayloadLength >> 24);
    this->mHeader[5] = (uint8_t)(mPayloadLength >> 16);
    this->mHeader[6] = (uint8_t)(mPayloadLength >> 8);
    this->mHeader[7] = (uint8_t)mPayloadLength;
  }
}
void V2gTpMessage::setHeader(const char *buffer)
{
  if ((buffer != nullptr) && ((buffer + V2GTP_HEADER_LENGTH) != nullptr))
  {
    memcpy(mHeader, buffer, V2GTP_HEADER_LENGTH);
  }
}
void V2gTpMessage::setMessage(const char *buffer, size_t len)
{
  // copy all data from buffer to mMessage data stream > to be sent
  if ((buffer != nullptr) && (len > V2GTP_HEADER_LENGTH))
    memcpy(this->mMessage, buffer, len);
  // update payload type attribute
  (void)this->getPayloadType();
  // update payload length value
  (void)this->getPayloadLength();
}

uint16_t V2gTpMessage::getPayloadType()
{
  this->mPayloadType = ((uint16_t)this->mHeader[2] << 8) | (uint16_t)this->mHeader[3];
  return this->mPayloadType;
}
uint32_t V2gTpMessage::getPayloadLength()
{
  mPayloadLength = ((uint32_t)this->mHeader[4] << 24) | ((uint32_t)this->mHeader[5] << 16) |
                   ((uint32_t)this->mHeader[6] << 8) | (uint32_t)this->mHeader[7];
  return mPayloadLength;
}
void V2gTpMessage::getHeader(char *buffer)
{
  if ((buffer != nullptr) && ((buffer + V2GTP_HEADER_LENGTH) != nullptr))
  {
    memcpy(buffer, mHeader, V2GTP_HEADER_LENGTH);
  }
}
size_t V2gTpMessage::getPayload(char *buffer, size_t len)
{
  size_t size = 0;

  if (buffer)
  {
    size = (len > mPayloadLength) ? mPayloadLength : len;
    memcpy(buffer, this->mPayload, size);
  }
  return size;
}
ssize_t V2gTpMessage::getMessage(char *buffer, size_t len)
{
  size_t messageLength = 0;
  if ((len <= V2GTP_HEADER_LENGTH) || (buffer == nullptr))
    return -1;
  // update payload length value from receive byte stream
  (void)this->getPayloadLength();
  // message byte stream length value
  messageLength = (mPayloadLength + V2GTP_HEADER_LENGTH);
  // if msg name more than max len of buffer then take length of buffer
  messageLength = (messageLength < len) ? messageLength : len;
  // copy all message byte stream to buffer
  memcpy(buffer, this->mMessage, messageLength);
  return messageLength;
}

ssize_t V2gTpMessage::getBufferPtr(char **buffer_ptr)
{
  *buffer_ptr = this->mMessage;
  return (mPayloadLength + V2GTP_HEADER_LENGTH);
}

void V2gTpMessage::dumpTpHeader(void)
{
  if (Logging::LogCfg.LogMsgTPDump == 1)
  {
    Logging::info(LogMsgTPDump_ENABLE,
                  fmt::format("V2GTp Header: ver:{0:02X}, inv={1:02X}, payloadType:{2:04X}, len:{3:d}",
                              (uint8_t)this->mHeader[0], (uint8_t)this->mHeader[1], this->getPayloadType(), this->getPayloadLength()));
  }
}