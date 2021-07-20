//
// Created by james on 30/09/2020.
//

#include "V2gSdpMessage.h"

using namespace DataStructure_SDP;

V2gSdpMessage::V2gSdpMessage() : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_SDP_REQ),
                                 mSecurityType(V2G_SDP_NON_SECURED),
                                 mTransportType(V2G_SDP_TRANSPORT_TCP)
{

  ALMsgType = ALM_SDP_REQ;
  char payload[V2gSdpMessage::V2G_SDP_PAYLOAD_LEN + 1];
  payload[0] = mSecurityType;
  payload[1] = mTransportType;
  setPayload(payload, V2G_SDP_PAYLOAD_LEN);
}

V2gSdpMessage::V2gSdpMessage(uint8_t security, uint8_t transport)
    : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_SDP_REQ), mSecurityType(security), mTransportType(transport)
{

  ALMsgType = ALM_SDP_REQ;
  char payload[V2gSdpMessage::V2G_SDP_PAYLOAD_LEN];
  payload[0] = mSecurityType;
  payload[1] = mTransportType;
  setPayload(payload, V2G_SDP_PAYLOAD_LEN);
}

void V2gSdpMessage::setSecurityType(uint8_t type)
{
  mSecurityType = type;
}

uint8_t V2gSdpMessage::getSecurityType()
{

  return mSecurityType;
}

void V2gSdpMessage::setTransportType(uint8_t type)
{
  mTransportType = type;
}

uint8_t V2gSdpMessage::getTransportType()
{
  return mTransportType;
}

void V2gSdpMessage::serialize()
{
  // set payload type
  setPayloadType(V2gTpMessage::V2G_TP_PAYLOAD_SDP_REQ);
  // set payload data
  uint8_t buffer[ISO1PART2_SDP_REQ_LENGTH] = {this->mSecurityType, this->mTransportType};
  setPayload((char *)buffer, ISO1PART2_SDP_REQ_LENGTH);
  this->dumpTpHeader();
  this->dumpMsg();
}

bool V2gSdpMessage::deserialize()
{
  if (V2gTpMessage::V2G_TP_PAYLOAD_SDP_REQ == getPayloadType())
  {
    char buffer[ISO1PART2_SDP_REQ_LENGTH] = {0, 0};
    if (0 != getPayload(buffer, ISO1PART2_SDP_REQ_LENGTH))
    {
      this->mSecurityType = buffer[0];
      this->mTransportType = buffer[1];
      this->dumpTpHeader();
      this->dumpMsg();
      return true;
    }
    else
    {
      Logging::error(LogMsgDump_ENABLE, "SDP Request msg has incorrect payload length");
      return false;
    }
  }
  else
  {
    Logging::error(LogMsgDump_ENABLE, "SDP Request msg has incorrect payload type");
    return false;
  }
}

void V2gSdpMessage::dumpMsg(void)
{
  Logging::info(LogMsgDump_ENABLE, fmt::format("--->SDP Request: SecType:{0:02X}, TpType:{1:02X}",
                                               this->mSecurityType, this->mTransportType));
}