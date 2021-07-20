//
// Created by james on 23/10/2020.
//

#include <string.h>
#include "V2gSdpResMessage.h"
#include "asio/ip/address_v6.hpp"
V2gSdpResMessage::V2gSdpResMessage()
    : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_SDP_RES)
{
    ALMsgType = ALM_SDP_RES;
    this->mPort = 0;
    this->mSecurityType = 0;
    this->mTransportType = 0;
    this->mIpV6Addr.fill(0);
}
V2gSdpResMessage::V2gSdpResMessage(const std::string &ipv6, uint16_t port, uint8_t secType, uint8_t tpType)
    : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_SDP_RES)
{
    this->mPort = port;
    this->mSecurityType = secType;
    this->mTransportType = tpType;
    this->mIpV6Addr = asio::ip::make_address_v6(ipv6).to_bytes();
}
void V2gSdpResMessage::setSecurityType(uint8_t secType)
{
    this->mSecurityType = secType;
}

void V2gSdpResMessage::setTransportType(uint8_t tpType)
{
    this->mTransportType = tpType;
}

size_t V2gSdpResMessage::setIpV6Addr(const char *buffer, size_t len)
{
    if (nullptr != buffer)
    {
        memcpy(this->mIpV6Addr.data(), buffer, len);
        return len;
    }
    else
    {
        return -1;
    }
}
size_t V2gSdpResMessage::setIpV6Addr(const std::string &ipv6_str_val)
{
    this->mIpV6Addr = asio::ip::make_address_v6(ipv6_str_val).to_bytes();
    return this->mIpV6Addr.max_size();
}
size_t V2gSdpResMessage::setIpV6Addr(const std::array<uint8_t, 16> &ipv6_val)
{
    this->mIpV6Addr = ipv6_val;
    return this->mIpV6Addr.max_size();
}
void V2gSdpResMessage::setPort(uint16_t port)
{
    this->mPort = port;
}

uint8_t V2gSdpResMessage::getSecurityType()
{
    return this->mSecurityType;
}

uint8_t V2gSdpResMessage::getTransportType()
{
    return this->mTransportType;
}

size_t V2gSdpResMessage::getSeccIpAddr(char *buffer, size_t len)
{

    size_t size = 0;
    if (nullptr != buffer)
    {
        size = ((len > V2G_SDP_RES_SECC_IP_LENGTH) ? V2G_SDP_RES_SECC_IP_LENGTH : len);
        memcpy(buffer, this->mIpV6Addr.data(), size);
    }
    return size;
}

uint16_t V2gSdpResMessage::getSeccPort(void)
{
    return this->mPort;
}

void V2gSdpResMessage::serialize(void)
{
    uint8_t payload_buffer[ISO1PART2_SDP_RES_LENGTH];
    payload_buffer[V2G_SDP_RES_SECC_SEC_INDEX] = this->mSecurityType;
    payload_buffer[V2G_SDP_RES_SECC_TRANSPORT_INDEX] = this->mTransportType;
    memcpy(payload_buffer, this->mIpV6Addr.data(), V2G_SDP_RES_SECC_IP_LENGTH);
    payload_buffer[V2G_SDP_RES_SECC_PORT_INDEX] = (uint8_t)(((0xFF00) & (this->mPort)) >> 8);
    payload_buffer[V2G_SDP_RES_SECC_PORT_INDEX + 1] = (uint8_t)(((0x00FF) & (this->mPort)));
    this->setPayload((const char *)payload_buffer, ISO1PART2_SDP_RES_LENGTH);
    this->dumpTpHeader();
    this->dumpMsg();
}

bool V2gSdpResMessage::deserialize(void)
{
    bool result = true;
    this->mSecurityType = this->mPayload[V2G_SDP_RES_SECC_SEC_INDEX];
    this->mTransportType = this->mPayload[V2G_SDP_RES_SECC_TRANSPORT_INDEX];
    memcpy((void *)this->mIpV6Addr.data(), this->mPayload, V2G_SDP_RES_SECC_IP_LENGTH);
    this->mPort = ((uint16_t)this->mPayload[V2G_SDP_RES_SECC_PORT_INDEX] << 8 |
                   this->mPayload[V2G_SDP_RES_SECC_PORT_INDEX + 1]);
    if ((this->mSecurityType != V2G_SDP_SEC_TLS) && (this->mSecurityType != V2G_SDP_NON_SECURED))
    {
        result = false;
    }
    if ((this->mTransportType != V2G_SDP_TRANSPORT_TCP) && (this->mTransportType != V2G_SDP_TRANSPORT_UDP))
    {
        result = false;
    }
    this->dumpTpHeader();
    this->dumpMsg();
    return result;
}

void V2gSdpResMessage::dumpMsg(void)
{
    Logging::info(LogMsgDump_ENABLE, fmt::format("<---SDP Response: SecType:{0:02X}, TpType:{1:02X}, IP:{2}, Port:{3:d}",
                                                 this->mSecurityType, this->mTransportType, asio::ip::make_address_v6(this->mIpV6Addr).to_string(), this->mPort));
}