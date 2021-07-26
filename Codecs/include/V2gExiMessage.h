//
// Created by james on 27/09/2020.
//

#ifndef EVCC_V2GEXIMESSAGE_H
#define EVCC_V2GEXIMESSAGE_H

#include <vector>
#include <string.h>
#include "V2gCodecs.h"
#include "V2gTpMessage.h"
#include "V2gDataPrint.h"

#define MAX_BUFFER_SIZE 1024
class V2gExiMessage : public V2gTpMessage
{
public:
    typedef enum
    {
        V2G_MSG_UNKNOWN_TYPE = -1,
        V2G_MSG_SESSION_SETUP_REQ = 0,
        V2G_MSG_SESSION_SETUP_RES,
        V2G_MSG_SERVICE_DISCOVERY_REQ,
        V2G_MSG_SERVICE_DISCOVERY_RES,
        V2G_MSG_SERVICE_DETAILS_REQ,
        V2G_MSG_SERVICE_DETAILS_RES,
        V2G_MSG_PAYMENT_SERVICE_SELECTION_REQ,
        V2G_MSG_PAYMENT_SERVICE_SELECTION_RES,
        V2G_MSG_PAYMENT_DETAILS_REQ,
        V2G_MSG_PAYMENT_DETAILS_RES,
        V2G_MSG_AUTHORIZATION_REQ,
        V2G_MSG_AUTHORIZATION_RES,
        V2G_MSG_CHARGE_PARAMETER_DISCOVERY_REQ,
        V2G_MSG_CHARGE_PARAMETER_DISCOVERY_RES,
        V2G_MSG_METERING_RECEIPT_REQ,
        V2G_MSG_METERING_RECEIPT_RES,
        V2G_MSG_POWER_DELIVERY_REQ,
        V2G_MSG_POWER_DELIVERY_RES,
        V2G_MSG_SESSION_STOP_REQ,
        V2G_MSG_SESSION_STOP_RES,
        V2G_MSG_CERTIFICATE_UPDATE_REQ,
        V2G_MSG_CERTIFICATE_UPDATE_RES,
        V2G_MSG_CERTIFICATE_INSTALLATION_REQ,
        V2G_MSG_CERTIFICATE_INSTALLATION_RES,
        V2G_MSG_CHARGING_STATUS_REQ,
        V2G_MSG_CHARGING_STATUS_RES,
        V2G_MSG_CABLE_CHECK_REQ,
        V2G_MSG_CABLE_CHECK_RES,
        V2G_MSG_PRE_CHARGE_REQ,
        V2G_MSG_PRE_CHARGE_RES,
        V2G_MSG_CURRENT_DEMAND_REQ,
        V2G_MSG_CURRENT_DEMAND_RES,
        V2G_MSG_WELDING_DETECTION_REQ,
        V2G_MSG_WELDING_DETECTION_RES,
        V2G_MSG_MAX
    } V2gExiMessageType;

public:
    V2gExiMessage();
    V2gExiMessage(V2gExiMessageType type);
    virtual ~V2gExiMessage();
    V2gExiMessageType getType();
    bool serialize();
    bool deserialize();
    virtual void dumpMsg(void) = 0;
    std::string getHeaderStr(void);
    struct iso1EXIDocument *getExiData()
    {
        return &mExiData;
    }

    void setSessionId(std::vector<uint8_t> &id);
    std::vector<uint8_t> getSessionId();

    void setNotification(NotificationType *noti);
    NotificationType *getNotification(void);

    void setSignature(SignatureType *sig);
    SignatureType *getSignature(void);

    const char *getTypeName();

    void resetSerializeFlag(void) { serialized_flag = false;}
protected:
    virtual int toByteStream(bitstream_t *out);
    virtual int fromByteStream(bitstream_t *in);

private:
    std::vector<uint8_t> mSessionId;
    bool serialized_flag;

protected:
    V2gExiMessageType mType;
    struct iso1EXIDocument mExiData;
};

#endif //EVCC_V2GEXIMESSAGE_H
