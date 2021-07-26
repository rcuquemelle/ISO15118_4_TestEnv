//
// Created by james on 27/09/2020.
//

#include "V2gExiMessage.h"
#include <string.h>
#include <vector>

static const char *V2G_MSG_NAME[] = {
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SESSION_SETUP_REQ] = "--->SessionSetupRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SESSION_SETUP_RES] = "<---SessionSetupResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SERVICE_DISCOVERY_REQ] = "--->ServiceDiscoveryRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SERVICE_DISCOVERY_RES] = "<---ServiceDiscoveryResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SERVICE_DETAILS_REQ] = "--->ServiceDetailRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SERVICE_DETAILS_RES] = "<---ServiceDetailResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PAYMENT_SERVICE_SELECTION_REQ] = "--->PaymentServiceSelectionRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PAYMENT_SERVICE_SELECTION_RES] = "<---PaymentServiceSelectionResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PAYMENT_DETAILS_REQ] = "--->PaymentDetailsRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PAYMENT_DETAILS_RES] = "<---PaymentDetailsResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_AUTHORIZATION_REQ] = "--->AuthorizationRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_AUTHORIZATION_RES] = "<---AuthorizationResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CHARGE_PARAMETER_DISCOVERY_REQ] = "--->ChargeParameterDiscoveryRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CHARGE_PARAMETER_DISCOVERY_RES] = "<---ChargeParameterDiscoveryResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_METERING_RECEIPT_REQ] = "--->MeteringReceiptRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_METERING_RECEIPT_RES] = "<---MeteringReceiptResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_POWER_DELIVERY_REQ] = "--->PowerDeliveryRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_POWER_DELIVERY_RES] = "<---PowerDeliveryResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SESSION_STOP_REQ] = "--->SessionStopRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_SESSION_STOP_RES] = "<---SessionStopResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CERTIFICATE_UPDATE_REQ] = "--->CertificateUpdateRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CERTIFICATE_UPDATE_RES] = "<---CertificateUpdateResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CERTIFICATE_INSTALLATION_REQ] = "--->CertificateInstallationRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CERTIFICATE_INSTALLATION_RES] = "<---CertificateInstallationResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CHARGING_STATUS_REQ] = "--->ChargingStatusRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CHARGING_STATUS_RES] = "<---ChargingStatusResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CABLE_CHECK_REQ] = "--->CableCheckRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CABLE_CHECK_RES] = "<---CableCheckResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PRE_CHARGE_REQ] = "--->PreChargeRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_PRE_CHARGE_RES] = "<---PreChargeResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CURRENT_DEMAND_REQ] = "--->CurrentDemandRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_CURRENT_DEMAND_RES] = "<---CurrentDemandResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_WELDING_DETECTION_REQ] = "--->WeldingDetectionRequest",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_WELDING_DETECTION_RES] = "<---WeldingDetectionResponse",
    [V2gExiMessage::V2gExiMessageType::V2G_MSG_MAX] = "InvalidMsgName"};

V2gExiMessage::V2gExiMessage() : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_EXI)
{
    // set type ALM EXI message
    ALMsgType = ALM_EXI;
    // init iso1 EXI Documents
    init_iso1EXIDocument(&mExiData);
    mExiData.V2G_Message_isUsed = 1u;
    init_iso1BodyType(&mExiData.V2G_Message.Body);
    init_iso1MessageHeaderType(&mExiData.V2G_Message.Header);
    mType = V2G_MSG_UNKNOWN_TYPE;
}

V2gExiMessage::V2gExiMessage(V2gExiMessageType type) : V2gTpMessage(V2gTpMessage::V2G_TP_PAYLOAD_EXI), mType(type)
{
    ALMsgType = ALM_EXI;
    init_iso1EXIDocument(&mExiData);
    mExiData.V2G_Message_isUsed = 1u;
}

V2gExiMessage::~V2gExiMessage()
{
}

bool V2gExiMessage::serialize()
{
    if (serialized_flag == false) {
        uint8_t buffer[4096];
        bitstream_t byteStream;
        size_t pos1 = V2GTP_HEADER_LENGTH;
        memset(buffer, 0x00, sizeof(buffer));

        byteStream.data = buffer;
        byteStream.pos = &pos1;
        byteStream.size = 4096;
        // deserialize data to bytestream
        int result = this->toByteStream(&byteStream);
        if (0 == result)
        {
            this->setMessage((const char *)byteStream.data, pos1);
            this->dumpTpHeader();
            this->dumpMsg();
            serialized_flag = true;
            return true;
        }
        else
        {
            Logging::error(LogMsgDump_ENABLE, fmt::format("{0} - Failed to serialized {1} message", result, this->getTypeName()));
            return false;
        }
    }
}

bool V2gExiMessage::deserialize()
{
    uint8_t buffer[4096];
    bitstream_t byteStream;
    size_t pos;
    memset(buffer, 0x00, sizeof(buffer));

    byteStream.data = buffer;
    byteStream.pos = &pos;
    byteStream.size = 4096;

    if (-1 != this->getMessage((char *)buffer, sizeof(buffer)))
    {
        int result = this->fromByteStream(&byteStream);
        this->dumpTpHeader();
        this->dumpMsg();
        if (result == 0)
        {
            return true;
        }
        else
        {
            Logging::error(LogMsgDump_ENABLE, fmt::format("{0} - Failed to deserialized {1} message", result, this->getTypeName()));
            return false;
        }
    }
    else
    {
        Logging::error(LogMsgDump_ENABLE, fmt::format("Failed to get {0} message data", this->getTypeName()));
        return false;
        ;
    }
}

int V2gExiMessage::toByteStream(bitstream_t *out)
{
    int errn = -1;
    if (nullptr != out)
    {
        // call encode function of openv2g push data to bitstream
        errn = encode_iso1ExiDocument(out, &mExiData);
        if (0 == errn)
        {
            // write v2g tp layer header
            (void)write_v2gtpHeader(out->data, (*out->pos) - V2GTP_HEADER_LENGTH, V2GTP_EXI_TYPE);
        }
    }
    return errn;
}

int V2gExiMessage::fromByteStream(bitstream_t *in)
{
    uint32_t payloadLength;
    int errn = -1;
    if (nullptr != in)
    {
        *in->pos = 0;
        errn = read_v2gtpHeader(in->data, &payloadLength);
        if (0 == errn)
        {
            *in->pos = V2GTP_HEADER_LENGTH;
            errn = decode_iso1ExiDocument(in, &mExiData);
        }
    }
    return errn;
}
const char *V2gExiMessage::getTypeName()
{
    return V2G_MSG_NAME[(uint8_t)getType()];
}
V2gExiMessage::V2gExiMessageType V2gExiMessage::getType()
{
    if (mExiData.V2G_Message.Body.SessionSetupReq_isUsed == 1)
    {
        mType = V2G_MSG_SESSION_SETUP_REQ;
    }
    else if (mExiData.V2G_Message.Body.SessionSetupRes_isUsed == 1)
    {
        mType = V2G_MSG_SESSION_SETUP_RES;
    }
    else if (mExiData.V2G_Message.Body.ServiceDiscoveryReq_isUsed == 1)
    {
        mType = V2G_MSG_SERVICE_DISCOVERY_REQ;
    }
    else if (mExiData.V2G_Message.Body.ServiceDiscoveryRes_isUsed == 1)
    {
        mType = V2G_MSG_SERVICE_DISCOVERY_RES;
    }
    else if (mExiData.V2G_Message.Body.ServiceDetailReq_isUsed == 1)
    {
        mType = V2G_MSG_SERVICE_DETAILS_REQ;
    }
    else if (mExiData.V2G_Message.Body.ServiceDetailRes_isUsed == 1)
    {
        mType = V2G_MSG_SERVICE_DETAILS_RES;
    }
    else if (mExiData.V2G_Message.Body.PaymentServiceSelectionReq_isUsed == 1)
    {
        mType = V2G_MSG_PAYMENT_SERVICE_SELECTION_REQ;
    }
    else if (mExiData.V2G_Message.Body.PaymentServiceSelectionRes_isUsed == 1)
    {
        mType = V2G_MSG_PAYMENT_SERVICE_SELECTION_RES;
    }
    else if (mExiData.V2G_Message.Body.AuthorizationReq_isUsed == 1)
    {
        mType = V2G_MSG_AUTHORIZATION_REQ;
    }
    else if (mExiData.V2G_Message.Body.AuthorizationRes_isUsed == 1)
    {
        mType = V2G_MSG_AUTHORIZATION_RES;
    }
    else if (mExiData.V2G_Message.Body.PowerDeliveryReq_isUsed == 1)
    {
        mType = V2G_MSG_POWER_DELIVERY_REQ;
    }
    else if (mExiData.V2G_Message.Body.PowerDeliveryRes_isUsed == 1)
    {
        mType = V2G_MSG_POWER_DELIVERY_RES;
    }
    else if (mExiData.V2G_Message.Body.ChargingStatusReq_isUsed == 1)
    {
        mType = V2G_MSG_CHARGING_STATUS_REQ;
    }
    else if (mExiData.V2G_Message.Body.ChargingStatusRes_isUsed == 1)
    {
        mType = V2G_MSG_CHARGING_STATUS_RES;
    }
    else if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed == 1)
    {
        mType = V2G_MSG_CHARGE_PARAMETER_DISCOVERY_REQ;
    }
    else if (mExiData.V2G_Message.Body.ChargeParameterDiscoveryRes_isUsed == 1)
    {
        mType = V2G_MSG_CHARGE_PARAMETER_DISCOVERY_RES;
    }
    else if (mExiData.V2G_Message.Body.PaymentDetailsReq_isUsed == 1)
    {
        mType = V2G_MSG_PAYMENT_DETAILS_REQ;
    }
    else if (mExiData.V2G_Message.Body.PaymentDetailsRes_isUsed == 1)
    {
        mType = V2G_MSG_PAYMENT_DETAILS_RES;
    }
    else if (mExiData.V2G_Message.Body.MeteringReceiptReq_isUsed == 1)
    {
        mType = V2G_MSG_METERING_RECEIPT_REQ;
    }
    else if (mExiData.V2G_Message.Body.MeteringReceiptRes_isUsed == 1)
    {
        mType = V2G_MSG_METERING_RECEIPT_RES;
    }
    else if (mExiData.V2G_Message.Body.SessionStopReq_isUsed == 1)
    {
        mType = V2G_MSG_SESSION_STOP_REQ;
    }
    else if (mExiData.V2G_Message.Body.SessionStopRes_isUsed == 1)
    {
        mType = V2G_MSG_SESSION_STOP_RES;
    }
    else if (mExiData.V2G_Message.Body.CableCheckReq_isUsed == 1)
    {
        mType = V2G_MSG_CABLE_CHECK_REQ;
    }
    else if (mExiData.V2G_Message.Body.CableCheckRes_isUsed == 1)
    {
        mType = V2G_MSG_CABLE_CHECK_RES;
    }
    else if (mExiData.V2G_Message.Body.PreChargeReq_isUsed == 1)
    {
        mType = V2G_MSG_PRE_CHARGE_REQ;
    }
    else if (mExiData.V2G_Message.Body.PreChargeRes_isUsed == 1)
    {
        mType = V2G_MSG_PRE_CHARGE_RES;
    }
    else if (mExiData.V2G_Message.Body.WeldingDetectionReq_isUsed == 1)
    {
        mType = V2G_MSG_WELDING_DETECTION_REQ;
    }
    else if (mExiData.V2G_Message.Body.WeldingDetectionRes_isUsed == 1)
    {
        mType = V2G_MSG_WELDING_DETECTION_RES;
    }
    else if (mExiData.V2G_Message.Body.CertificateInstallationReq_isUsed == 1)
    {
        mType = V2G_MSG_CERTIFICATE_INSTALLATION_REQ;
    }
    else if (mExiData.V2G_Message.Body.CertificateInstallationRes_isUsed == 1)
    {
        mType = V2G_MSG_CERTIFICATE_INSTALLATION_RES;
    }
    else if (mExiData.V2G_Message.Body.CertificateUpdateReq_isUsed == 1)
    {
        mType = V2G_MSG_CERTIFICATE_UPDATE_REQ;
    }
    else if (mExiData.V2G_Message.Body.CertificateUpdateRes_isUsed == 1)
    {
        mType = V2G_MSG_CERTIFICATE_UPDATE_RES;
    }
    else if (mExiData.V2G_Message.Body.CurrentDemandReq_isUsed == 1)
    {
        mType = V2G_MSG_CURRENT_DEMAND_REQ;
    }
    else if (mExiData.V2G_Message.Body.CurrentDemandRes_isUsed == 1)
    {
        mType = V2G_MSG_CURRENT_DEMAND_RES;
    }
    else
    {
        mType = V2G_MSG_MAX;
    }
    return mType;
}

void V2gExiMessage::setSessionId(std::vector<uint8_t> &id)
{
    for (size_t i = 0; i < id.size(); i++)
    {
        mExiData.V2G_Message.Header.SessionID.bytes[i] = id[i];
    }
    mExiData.V2G_Message.Header.SessionID.bytesLen = id.size();
}

std::vector<uint8_t> V2gExiMessage::getSessionId()
{
    mSessionId.clear();
    for (int i = 0; i < mExiData.V2G_Message.Header.SessionID.bytesLen; i++)
    {
        mSessionId.push_back(mExiData.V2G_Message.Header.SessionID.bytes[i]);
    }
    // HEADER: return a vector of sessionID value
    return mSessionId;
}

void V2gExiMessage::setNotification(NotificationType *noti)
{
    init_iso1NotificationType(&mExiData.V2G_Message.Header.Notification);
    mExiData.V2G_Message.Header.Notification_isUsed = 0;
    if (nullptr != noti)
    {
        mExiData.V2G_Message.Header.Notification_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Header.Notification, noti, sizeof(NotificationType));
    }
}
NotificationType *V2gExiMessage::getNotification(void)
{
    // HEADER: return Notification structure data if it is used
    if (mExiData.V2G_Message.Header.Notification_isUsed == 1)
    {
        return &mExiData.V2G_Message.Header.Notification;
    }
    else
    {
        return nullptr;
    }
}

void V2gExiMessage::setSignature(SignatureType *sig)
{
    init_iso1SignatureType(&mExiData.V2G_Message.Header.Signature);
    mExiData.V2G_Message.Header.Signature_isUsed = 0;
    if (nullptr != sig)
    {
        mExiData.V2G_Message.Header.Signature_isUsed = 1;
        memcpy(&mExiData.V2G_Message.Header.Signature, sig, sizeof(SignatureType));
    }
}
SignatureType *V2gExiMessage::getSignature(void)
{
    // HEADER: return Signature structure data if it is used
    if (mExiData.V2G_Message.Header.Signature_isUsed == 1)
    {
        return &mExiData.V2G_Message.Header.Signature;
    }
    else
    {
        return nullptr;
    }
}

std::string V2gExiMessage::getHeaderStr(void)
{
    NotificationType *notif = this->getNotification();
    SignatureType *sig = this->getSignature();
    std::string notif_str = "";
    std::string sign_str = "";
    if (nullptr != notif)
    {
        notif_str.append(fmt::format("{0}:{1}", notif->FaultCode, std::string(notif->FaultMsg.characters)));
    }
    if (nullptr != sig)
    {
        if (sig->Id_isUsed == 1)
        {
            sign_str.append(std::string(sig->Id.characters));
            sign_str.append("-");
        }
        sign_str.append(outHexString(sig->SignatureValue.CONTENT.bytes, sig->SignatureValue.CONTENT.bytesLen));
    }
    std::string temp = fmt::format("{0}: SessionID={1}, Notification={2}, Signature={3}\n",
                                   this->getTypeName(), outHexString(this->getSessionId()), notif_str, sign_str);
    return temp;
}