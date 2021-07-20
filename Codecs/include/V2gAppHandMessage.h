//
// Created by james on 17/10/2020.
//

#ifndef EVCC_V2GAPPHANDMESSAGE_H
#define EVCC_V2GAPPHANDMESSAGE_H

#include "V2gCodecs.h"
#include "V2gTpMessage.h"
#include "V2gDataPrint.h"

class V2gAppHandMessage : public V2gTpMessage
{
public:
    typedef enum
    {
        V2G_SUPPORT_APP_PROTO_REQ = 0,
        V2G_SUPPORT_APP_PROTO_RES
    } AppHandMessageType;

public:
    V2gAppHandMessage();
    V2gAppHandMessage(AppHandMessageType type);
    ~V2gAppHandMessage();

    bool serialize();
    bool deserialize();
    virtual void dumpMsg(void) = 0;
    AppHandMessageType getMessageType();
    std::string getMessageName();
    struct appHandEXIDocument *getAppHandEXI()
    {
        return &mAppHandshakeData;
    }

protected:
    int toByteStream(bitstream_t *out);
    int fromByteStream(bitstream_t *in);

protected:
    AppHandMessageType mMessageType;

public:
    // supportedAppProtocolReq_isUsed
    // appHandAnonType_supportedAppProtocolReq
    // supportedAppProtocolRes_isUsed
    // appHandAnonType_supportedAppProtocolRes
    struct appHandEXIDocument mAppHandshakeData;
};

#endif //EVCC_V2GAPPHANDMESSAGE_H
