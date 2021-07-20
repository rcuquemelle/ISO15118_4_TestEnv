//
// Created by james on 17/10/2020.
//

#include "V2gAppHandMessage.h"
#include <string.h>
#include <vector>
static const char *MSG_NAME[] = {
    [V2gAppHandMessage::AppHandMessageType::V2G_SUPPORT_APP_PROTO_REQ] = "--->SupportedAppProtocolRequest",
    [V2gAppHandMessage::AppHandMessageType::V2G_SUPPORT_APP_PROTO_RES] = "<---SupportedAppProtocolResponse"};

V2gAppHandMessage::V2gAppHandMessage() : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_EXI)
{
    init_appHandEXIDocument(&mAppHandshakeData);
    ALMsgType = ALM_HAND_SHAKE;
}

V2gAppHandMessage::V2gAppHandMessage(AppHandMessageType type)
    : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_EXI), mMessageType(type)
{
    ALMsgType = ALM_HAND_SHAKE;
}

V2gAppHandMessage::~V2gAppHandMessage()
{
}

/* Serialize structure data to byte stream */
bool V2gAppHandMessage::serialize()
{
    // allocate 4kb buffer for msg byte stream
    uint8_t buffer[4096];
    bitstream_t byteStream;
    size_t pos1 = V2GTP_HEADER_LENGTH;
    memset(buffer, 0x00, sizeof(buffer));

    byteStream.data = buffer;
    // buffer position counter
    byteStream.pos = &pos1;
    byteStream.size = 4096;
    // encode msg to bytestream
    int result = this->toByteStream(&byteStream);
    if (0 == result)
    {
        // copy data of byte stream to base class TP data for current object
        this->setMessage((const char *)byteStream.data, pos1);
        this->dumpTpHeader();
        this->dumpMsg();
        return true;
    }
    else
    {
        Logging::error(LogMsgDump_ENABLE, fmt::format("{0} - Failed to serialized {1} message", result, MSG_NAME[this->getMessageType()]));
        return false;
    }
}

bool V2gAppHandMessage::deserialize()
{
    uint8_t buffer[4096];
    bitstream_t byteStream;
    size_t pos;
    memset(buffer, 0x00, sizeof(buffer));

    byteStream.data = buffer;
    byteStream.pos = &pos;
    byteStream.size = 4096;

    // copy receive msg data stream to buffer
    if (-1 != this->getMessage((char *)buffer, sizeof(buffer)))
    {
        // deserialized bytestream to data  structure
        int result = this->fromByteStream(&byteStream);
        this->dumpTpHeader();
        this->dumpMsg();
        if (result == 0)
        {
            return true;
        }
        else
        {
            Logging::error(LogMsgDump_ENABLE, fmt::format("{0} - Failed to deserialized {1} message", result, MSG_NAME[this->getMessageType()]));
            return false;
        }
    }
    else
    {
        Logging::error(LogMsgDump_ENABLE, fmt::format("Failed to get {0} message data", MSG_NAME[this->getMessageType()]));
        return false;
        ;
    }
}

/* encode msg and add v2gtp header to byte stream */
int V2gAppHandMessage::toByteStream(bitstream_t *out)
{
    int errn;
    if (out)
    {
        errn = encode_appHandExiDocument(out, &mAppHandshakeData);
        if (errn == 0)
        {
            (void)write_v2gtpHeader(out->data, *(out->pos) - V2GTP_HEADER_LENGTH, V2GTP_EXI_TYPE);
        }
    }
    return errn;
}

/* decode data stream to data structure */
int V2gAppHandMessage::fromByteStream(bitstream_t *in)
{
    uint32_t payloadLength;
    int errn = -1;
    if (nullptr != in)
    {
        errn = read_v2gtpHeader(in->data, &payloadLength);
        if (0 == errn)
        {
            *in->pos = V2GTP_HEADER_LENGTH;
            errn = decode_appHandExiDocument(in, &mAppHandshakeData);
        }
    }
    return errn;
}

V2gAppHandMessage::AppHandMessageType V2gAppHandMessage::getMessageType()
{
    return mMessageType;
}

std::string V2gAppHandMessage::getMessageName()
{
    return MSG_NAME[this->getMessageType()];
}