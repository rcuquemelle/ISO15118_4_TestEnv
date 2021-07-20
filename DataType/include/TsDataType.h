#ifndef _TSDATATYPE_H_
#define _TSDATATYPE_H_
// Annex O(normative)Data typedef definitions
// define TestSystem Data Type here (V2G data typedef and general test environment typedef)

#include <string>
#include <cstring>
#include <vector>
#include <memory>

typedef enum comparision_flag {
  omit = 0,
  has_value = 1,
  specific = 2
} comparision_indicate_flag;

typedef enum verdict_val {
  none = 0,
  pass = 1,
  inconc = 2,
  fail = 3,
  error = 4
} verdict_val;
class verdicttype {
public:
  verdict_val value;
  std::vector<std::string> msg_list;
  verdicttype() {
    value = none;
  }
  verdicttype(verdict_val val) {
    value = val;
  }
  verdicttype(verdict_val val, const std::string& _msg) {
    value = val;
    msg_list.emplace_back(_msg);
  }
  ~verdicttype() {};
  verdicttype &operator= (const verdicttype &obj){
    if (this != &obj) {
      if (obj.value > this->value){
        this->value = obj.value;
      }
      this->msg_list.insert(this->msg_list.end(), obj.msg_list.begin(), obj.msg_list.end());
    }
    return *this;
  }
  verdicttype &operator= (verdict_val val) {
    if (val > this->value){
      this->value = val;
    }
    return *this;
  }
  bool operator == (const verdicttype &obj) {
    return (this->value == obj.value);
  }
  bool operator == (const verdict_val val) {
    return (this->value == val);
  }
};


typedef enum {
  GET_DLINK_STATUS = 0,
  SET_DLINK_TERMINATE,
  SET_DLINK_PAUSE,
  SET_DLINK_CLOSE_FD
} en_DLINKCmdType;

typedef enum {
  DISCONNECT=0,
  UNMATCH,
  MATCHING,
  MATCHED,
  PAUSE
} en_DLINKEventType;

typedef struct SLAC_Event_St {
  en_DLINKEventType event;
} DLINKEvent;
typedef struct SLAC_Cmd_St {
  en_DLINKCmdType cmd;
} DLINKCmd;

typedef enum {
  en_BCEventType_PWM_STATUS,
  en_BCEventType_PWM_DUTY,
  en_BCEventType_PWM_FREQ,
  en_BCEventType_PWM_VOLT
} en_BCEventType;

namespace DataStructure_HAL_61851 {
  typedef enum IEC_61851_States {
    A=0,
    B,
    C,
    D,
    E,
    F,
    NA,
    none_
  } IEC_61851_States;
  typedef enum IEC_61851_ErrStates {
    LOST_CP = 0,
    LOST_PE,
    LOST_DIODE,
    SHORT_CP_PE
  } IEC_61851_ErrStates;
  typedef struct HAL_61851_Event_St {
    en_BCEventType type;
    bool PWMStatus;
    float PWMDuty;
    float PWMFreq;
    float VoltLevel;
    IEC_61851_States state;
  } HAL_61851_Event;

  typedef struct HAL_61851_Cmd_St {
    IEC_61851_States cmd;
  } HAL_61851_Cmd;
}

namespace DataStructure_PICS_15118 {
  enum class iso1Part4_ChargingMode {
    aC,
    dC
  };
  enum class iso1Part4_IdentificationMode {
    pnC,
    eIM
  };
  enum class iso1Part4_PlugType {
    type1,
    type2
  };
  enum class iso1Part4_CableCapabilityACType {
    capability13A,
    capability20A,
    capability32A,
    capability63A,
    capability70A
  };
  enum class iso1Part4_EIMDone {
    beforePlugin,
    afterPlugin,
    duringSlac,
    v2gAuthorization
  };
  enum class iso1Part4_ZeroPow {
    sleepWithoutCharge,
    sleepAfterCharge,
    none_
  };
}

namespace DataStructure_PIXIT_15118_2 {
  enum class iso1Part4_CertificateHandlingEVCC{
    none_,
    certInstall,
    certUpdate,
    unknown
  };
  enum class iso1Part4_CertificateHandlingSECC{
    none_,
    certInstall,
    certUpdate
  };
  enum class iso1Part4_VASEVCC{
    none_,
    serviceDetail,
    unknown
  };
  enum class iso1Part4_VASSECC{
    none_,
    serviceDetail
  } ;
  enum class iso1Part4_WeldingDetection{
    none_,
    weldingDetection,
    unknown
  } ;
  enum class iso1Part4_TLS{
    none_,
    tls,
    unknown
  } ;
  enum class iso1Part4_PkiType{
    PKI_1,
    PKI_2,
    PKI_3,
    PKI_4,
    PKI_5,
    PKI_6,
    PKI_7,
    PKI_Ext,
    PKI_1_Testival,
    PKI_2_Testival
  };
  enum class iso1Part4_SalesTariff{
    salesTariff,
    unknown
  };
  enum class iso1Part4_InternetAccess{
    internetAccess,
    unknown
  };
  enum class iso1Part4_Ongoing{
    ongoing,
    unknown
  };
  enum class iso1Part4_Renegotiation{
    renegotiation,
    unknown
  };
  enum class iso1Part4_DepartureTime{
    departureTime,
    unknown,
    none_
  };
  enum class iso1Part4_MeterInfo{
    meterInfo,
    unknown
  };
  enum class iso1Part4_MeterReading{
    meterReading,
    unknown
  };
  enum class iso1Part4_MaxNumberOfPhasesInUse{
    maxNumberOfPhasesInUse,
    unknown
  };
  enum class iso1Part4_ChargingProfileOpt{
    optimization,
    unknown,
    none_
  };
  enum class iso1Part4_NewSAScheduleTupleID{
    newSAScheduleTupleID,
    unknown
  };
  enum class iso1Part4_SAScheduleTupleIDMR{
    sAScheduleTupleID,
    unknown
  };
  enum class iso1Part4_PaymentOption{
    externalPayment,
    contract
  };
}

namespace DataStructure_PIXIT_15118 {
  enum class iso1Part4_Pause {
    pause,
    unknown,
    none_
  };
}

namespace XSDAUX {
  typedef uint8_t unsignedByte;
  typedef bool Boolean;
  typedef std::string string;
  typedef uint32_t unsignedInt;
  typedef std::string anyURI;
  typedef std::vector<uint8_t> base64Binary;
  typedef std::vector<int32_t> AnyType;
  typedef uint32_t ID;
  typedef std::string AnyAttributes;
  typedef int integerXSD;
  typedef uint16_t unsignedShort;
  typedef std::vector<uint8_t> hexBinary;
  typedef int8_t byte;
  typedef uint64_t unsignedLong;
}

namespace urn_iso_15118_2_2013_X509Def {
  using namespace XSDAUX;
  typedef struct {
    XSDAUX::Boolean cA;
    int pathLen;
  } iso1Part4_BasicConstraintsType;
  typedef struct {
    XSDAUX::string publicKey;
    XSDAUX::string eCParam;
  } iso1Part4_ECPublicKeyType;
  typedef struct {
    XSDAUX::Boolean digitalSignature;
    XSDAUX::Boolean nonRepudiation;
    XSDAUX::Boolean keyEncipherment;
    XSDAUX::Boolean dataEncipherment;
    XSDAUX::Boolean keyAgreement;
    XSDAUX::Boolean keyCertSign;
    XSDAUX::Boolean cRLSign;
    XSDAUX::Boolean encipherOnly;
    XSDAUX::Boolean decipherOnly;
  } iso1Part4_KeyUsageType;
  typedef XSDAUX::base64Binary iso1Part4_RawCertificateType;
  typedef struct {
    XSDAUX::string public_Key_Algorithm;
    iso1Part4_ECPublicKeyType eC_Public_Key;
  } iso1Part4_SubjectPublicKeyType;
  typedef struct {
    XSDAUX::string not_Before;
    XSDAUX::string not_After;
  } iso1Part4_ValidityType;
  typedef struct {
    iso1Part4_BasicConstraintsType basic_Constraints;
    XSDAUX::string name_Constraints;
    XSDAUX::string policy_Constraints;
    iso1Part4_KeyUsageType key_Usage;
    XSDAUX::string extended_Key_Usage;
    XSDAUX::string subject_Key_Identifier;
    XSDAUX::string authority_Key_Identifier;
    XSDAUX::string subject_Alternative_Name;
    XSDAUX::string issuer_Alternative_Name;
    XSDAUX::string subject_Directory_Attributes;
    XSDAUX::string cRL_Distribution_Points;
    int inhibit_Any_Policy;
    iso1Part4_ValidityType private_Key_Usage_Period;
    XSDAUX::string certificate_Policies;
    XSDAUX::string policy_Mappings;
  } iso1Part4_X509V3ExtensionsType;
  typedef struct {
    XSDAUX::string netscape_Comment;
    XSDAUX::string netscape_Certificate_Type;
    XSDAUX::string old_Authority_Key_Identifier;
    XSDAUX::string old_Primary_Key_Attributes;
  } iso1Part4_X509NonStandardExtensionsType;
  typedef struct {
    int version;
    XSDAUX::string serial_Number;
    XSDAUX::string signature_Algorithm;
    XSDAUX::string issuer;
    iso1Part4_ValidityType validity;
    XSDAUX::string subject;
    iso1Part4_SubjectPublicKeyType subject_Public_Key;
    iso1Part4_X509V3ExtensionsType standard_Extensions;
    iso1Part4_X509NonStandardExtensionsType non_Standard_Extensions;
  } iso1Part4_X509CertificateContentsType;
  typedef struct {
    XSDAUX::string signature_Algorithm;
    XSDAUX::string signature_;
  } iso1Part4_X509CertificateSignatureType;
  typedef struct {
    iso1Part4_X509CertificateContentsType tBSCertificate;
    iso1Part4_RawCertificateType raw_Certificate;
    iso1Part4_X509CertificateSignatureType certificate_Signature;
  } iso1Part4_X509CertificateType;
}

namespace http_www_w3_org_2000_09_xmldsig {
  using namespace XSDAUX;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    std::vector<XSDAUX::AnyType> elem_list;
  } iso1Part4_CanonicalizationMethodType;
  typedef iso1Part4_CanonicalizationMethodType iso1Part4_CanonicalizationMethod;
  typedef XSDAUX::base64Binary iso1Part4_CryptoBinary;
  typedef struct {
    struct {
      iso1Part4_CryptoBinary p;
      iso1Part4_CryptoBinary q;
    } sequence;
    iso1Part4_CryptoBinary g;
    iso1Part4_CryptoBinary y;
    iso1Part4_CryptoBinary j;
    struct {
      iso1Part4_CryptoBinary seed;
      iso1Part4_CryptoBinary pgenCounter;
    } sequence_1;
  } iso1Part4_DSAKeyValueType;
  typedef iso1Part4_DSAKeyValueType iso1Part4_DSAKeyValue;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    std::vector<XSDAUX::AnyType> elem_list;
  } iso1Part4_DigestMethodType;
  typedef iso1Part4_DigestMethodType iso1Part4_DigestMethod;
  typedef XSDAUX::base64Binary iso1Part4_DigestValueType;
  typedef iso1Part4_DigestValueType iso1Part4_DigestValue;
  typedef XSDAUX::integerXSD iso1Part4_HMACOutputLengthType;
  typedef struct {
    iso1Part4_CryptoBinary modulus;
    iso1Part4_CryptoBinary exponent;
  } iso1Part4_RSAKeyValueType;
  typedef iso1Part4_RSAKeyValueType iso1Part4_RSAKeyValue;
  typedef struct {
    XSDAUX::string embed_values;
    union {
      iso1Part4_DSAKeyValueType dSAKeyValue;
      iso1Part4_RSAKeyValueType rSAKeyValue;
      XSDAUX::AnyType elem;
    } choice;
  } iso1Part4_KeyValueType;
  typedef iso1Part4_KeyValueType iso1Part4_KeyValue;
  typedef XSDAUX::string iso1Part4_KeyName;
  typedef XSDAUX::string iso1Part4_MgmtData;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI encoding;
    XSDAUX::ID id;
    XSDAUX::string mimeType;
    typedef struct {
      XSDAUX::AnyType elem;
    } dummyObjectType;
    std::vector<dummyObjectType> sequence_list;
  } iso1Part4_ObjectType;
  typedef iso1Part4_ObjectType iso1Part4_Object;
  typedef struct {
    union {
      struct {
        XSDAUX::base64Binary pGPKeyID;
        XSDAUX::base64Binary pGPKeyPacket;
        std::vector<XSDAUX::AnyType> elem_list;
      } sequence;
      struct {
        XSDAUX::base64Binary pGPKeyPacket;
        std::vector<XSDAUX::AnyType> elem_list;
      } sequence_1;
    } choice;
  } iso1Part4_PGPDataType;
  typedef iso1Part4_PGPDataType iso1Part4_PGPData;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    typedef union {
      XSDAUX::AnyType elem;
      XSDAUX::string xPath;
    } dummyTransformType;
    std::vector<dummyTransformType> choice_list;
  } iso1Part4_TransformType;
  typedef iso1Part4_TransformType iso1Part4_Transform;
  typedef struct {
    std::vector<iso1Part4_TransformType> transform_list;
  } iso1Part4_TransformsType;
  typedef iso1Part4_TransformsType iso1Part4_Transforms;
  typedef struct {
    XSDAUX::ID id;
    XSDAUX::anyURI type_;
    XSDAUX::anyURI uRI;
    iso1Part4_TransformsType transforms;
    iso1Part4_DigestMethodType digestMethod;
    iso1Part4_DigestValueType digestValue;
  } iso1Part4_ReferenceType;
  typedef iso1Part4_ReferenceType iso1Part4_Reference;
  typedef struct {
    XSDAUX::ID id;
    std::vector<iso1Part4_ReferenceType> reference_list;
  } iso1Part4_ManifestType;
  typedef iso1Part4_ManifestType iso1Part4_Manifest;
  typedef struct {
    XSDAUX::anyURI type_;
    XSDAUX::anyURI uRI;
    iso1Part4_TransformsType transforms;
  } iso1Part4_RetrievalMethodType;
  typedef iso1Part4_RetrievalMethodType iso1Part4_RetrievalMethod;
  typedef struct {
    typedef struct {
      XSDAUX::base64Binary sPKISexp;
      XSDAUX::AnyType elem;
    } dummySPKIDataType;
    std::vector<dummySPKIDataType> sequence_list;
  } iso1Part4_SPKIDataType;
  typedef iso1Part4_SPKIDataType iso1Part4_SPKIData;
  typedef struct {
    XSDAUX::string x509IssuerName;
    XSDAUX::integerXSD x509SerialNumber;
  } iso1Part4_X509IssuerSerialType;
  typedef struct {
    typedef union {
      iso1Part4_X509IssuerSerialType x509IssuerSerial;
      XSDAUX::base64Binary x509SKI;
      XSDAUX::string x509SubjectName;
      XSDAUX::base64Binary x509Certificate;
      XSDAUX::base64Binary x509CRL;
      XSDAUX::AnyType elem;
    } choiceX509DataType;
    std::vector<choiceX509DataType> sequence_list;
  } iso1Part4_X509DataType;
  typedef iso1Part4_X509DataType iso1Part4_X509Data;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::ID id;
    typedef union {
      XSDAUX::string keyName;
      iso1Part4_KeyValueType keyValue;
      iso1Part4_RetrievalMethodType retrievalMethod;
      iso1Part4_X509DataType x509Data;
      iso1Part4_PGPDataType pGPData;
      iso1Part4_SPKIDataType sPKIData;
      XSDAUX::string mgmtData;
      XSDAUX::AnyType elem;
    } dummyKeyInfoType;
    std::vector<dummyKeyInfoType> choice_list;
  } iso1Part4_KeyInfoType;
  typedef iso1Part4_KeyInfoType iso1Part4_KeyInfo;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    iso1Part4_HMACOutputLengthType hMACOutputLength;
    std::vector<XSDAUX::AnyType> elem_list;
  } iso1Part4_SignatureMethodType;
  typedef iso1Part4_SignatureMethodType iso1Part4_SignatureMethod;
  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::ID id;
    XSDAUX::anyURI target;
    typedef union {
      XSDAUX::AnyType elem;
    } dummySignaturePropertyType;
    std::vector<dummySignaturePropertyType> choice_list;
  } iso1Part4_SignaturePropertyType;
  typedef iso1Part4_SignaturePropertyType iso1Part4_SignatureProperty;
  typedef struct {
    XSDAUX::ID id;
    std::vector<iso1Part4_SignaturePropertyType> signatureProperty_list;
  } iso1Part4_SignaturePropertiesType;
  typedef iso1Part4_SignaturePropertiesType iso1Part4_SignatureProperties;
  typedef struct {
    XSDAUX::ID id;
    XSDAUX::base64Binary base;
  } iso1Part4_SignatureValueType;
  typedef iso1Part4_SignatureValueType iso1Part4_SignatureValue;
  typedef struct {
    XSDAUX::ID id;
    iso1Part4_CanonicalizationMethodType canonicalizationMethod;
    iso1Part4_SignatureMethodType signatureMethod;
    std::vector<iso1Part4_ReferenceType> reference_list;
  } iso1Part4_SignedInfoType;
  typedef iso1Part4_SignedInfoType iso1Part4_SignedInfo;
  typedef struct {
    XSDAUX::ID id;
    iso1Part4_SignedInfoType signedInfo;
    iso1Part4_SignatureValueType signatureValue;
    iso1Part4_KeyInfoType keyInfo;
    std::vector<iso1Part4_ObjectType> object_list;
  } iso1Part4_SignatureType;
  typedef iso1Part4_SignatureType iso1Part4_Signature;
}

namespace urn_iso_15118_2_2013_MsgDataTypes {
  using namespace urn_iso_15118_2_2013_X509Def;
  using namespace http_www_w3_org_2000_09_xmldsig;
  using namespace XSDAUX;

  enum class iso1Part4_ChargeProgressType {
    start_,
    stop_,
    renegotiate
  };
  enum class iso1Part4_ChargingSessionType {
    terminate,
    pause
  };
  enum class iso1Part4_CostKindType {
    relativePricePercentage,
    renewableGenerationPercentage,
    carbonDioxideEmission
  };
  enum class iso1Part4_DC_EVErrorCodeType {
    nO_ERROR,
    fAILED_RESSTemperatureInhibit,
    fAILED_EVShiftPosition,
    fAILED_ChargerConnectorLockFault,
    fAILED_EVRESSMalfunction,
    fAILED_ChargingCurrentdifferential,
    fAILED_ChargingVoltageOutOfRange,
    reserved_A,
    reserved_B,
    reserved_C,
    fAILED_ChargingSystemIncompatibility,
    noData
  };
  enum class iso1Part4_DC_EVSEStatusCodeType {
    eVSE_NotReady,
    eVSE_Ready,
    eVSE_Shutdown,
    eVSE_UtilityInterruptEvent,
    eVSE_IsolationMonitoringActive,
    eVSE_EmergencyShutdown,
    eVSE_Malfunction,
    reserved_8,
    reserved_9,
    reserved_A,
    reserved_B,
    reserved_C
  };
  enum class iso1Part4_EVSENotificationType {
    none_,
    stopCharging,
    reNegotiation
  };
  enum class iso1Part4_EVSEProcessingType {
    finished,
    ongoing,
    ongoing_WaitingForCustomerInteraction
  };
  enum class iso1Part4_EnergyTransferModeType {
    aC_single_phase_core,
    aC_three_phase_core,
    dC_core,
    dC_extended,
    dC_combo_core,
    dC_unique
  };
  enum class iso1Part4_IsolationLevelType {
    invalid,
    valid,
    warning,
    fault,
    no_IMD
  };
  enum class iso1Part4_PaymentOptionType {
    contract,
    externalPayment
  };
  enum class iso1Part4_ResponseCodeType {
    oK,
    oK_NewSessionEstablished,
    oK_OldSessionJoined,
    oK_CertificateExpiresSoon,
    fAILED,
    fAILED_SequenceError,
    fAILED_ServiceIDInvalid,
    fAILED_UnknownSession,
    fAILED_ServiceSelectionInvalid,
    fAILED_PaymentSelectionInvalid,
    fAILED_CertificateExpired,
    fAILED_SignatureError,
    fAILED_NoCertificateAvailable,
    fAILED_CertChainError,
    fAILED_ChallengeInvalid,
    fAILED_ContractCanceled,
    fAILED_WrongChargeParameter,
    fAILED_PowerDeliveryNotApplied,
    fAILED_TariffSelectionInvalid,
    fAILED_ChargingProfileInvalid,
    fAILED_MeteringSignatureNotValid,
    fAILED_NoChargeServiceSelected,
    fAILED_WrongEnergyTransferMode,
    fAILED_ContactorError,
    fAILED_CertificateNotAllowedAtThisEVSE,
    fAILED_CertificateRevoked
  };
  enum class iso1Part4_ServiceCategoryType {
    eVCharging,
    internet,
    contractCertificate,
    otherCustom
  };
  typedef XSDAUX::byte iso1Part4_UnitMultiplierType;
  enum class iso1Part4_UnitSymbolType {
    h,
    m,
    s,
    a,
    v,
    w,
    wh
  };
  enum class iso1Part4_ValueType {
    _bool,
    _byte,
    _short,
    _int,
    _physicalValue,
    _string
  };
  enum class iso1Part4_FaultCodeType {
    parsingError,
    noTLSRootCertificatAvailable,
    unknownError
  };


  typedef XSDAUX::byte iso1Part4_PercentValueType;

  typedef struct {
    XSDAUX::Boolean eVReady;
    iso1Part4_DC_EVErrorCodeType eVErrorCode;
    iso1Part4_PercentValueType eVRESSSOC;
  } iso1Part4_DC_EVStatusType;

  typedef iso1Part4_DC_EVStatusType iso1Part4_DC_EVStatus;
  typedef XSDAUX::base64Binary iso1Part4_DHpublickeyType;
  typedef XSDAUX::string iso1Part4_EMAIDType_1;
  typedef XSDAUX::hexBinary iso1Part4_EvccIDType;
  typedef XSDAUX::string iso1Part4_EvseIDType;
  typedef XSDAUX::string iso1Part4_FaultMsgType;
  typedef XSDAUX::base64Binary iso1Part4_GenChallengeType;
  typedef XSDAUX::byte iso1Part4_MaxNumPhasesType;
  typedef XSDAUX::string iso1Part4_MeterIDType;
  typedef short iso1Part4_MeterStatusType;
  typedef XSDAUX::unsignedByte iso1Part4_SAIDType;
  typedef XSDAUX::unsignedShort iso1Part4_ServiceIDType;
  typedef XSDAUX::string iso1Part4_ServiceNameType;
  typedef XSDAUX::string iso1Part4_ServiceScopeType;
  typedef XSDAUX::hexBinary iso1Part4_SessionIDType;
  typedef XSDAUX::base64Binary iso1Part4_SigMeterReadingType;
  typedef XSDAUX::string iso1Part4_TariffDescriptionType;
  typedef XSDAUX::base64Binary iso1Part4_PrivateKeyType;

  typedef struct {
    XSDAUX::unsignedInt start_;
    XSDAUX::unsignedInt duration;
  } iso1Part4_RelativeTimeIntervalType;
  typedef iso1Part4_RelativeTimeIntervalType iso1Part4_RelativeTimeInterval;

  typedef struct {
  } iso1Part4_SASchedulesType;
  typedef struct {
    iso1Part4_ServiceIDType serviceID;
    short parameterSetID;
  } iso1Part4_SelectedServiceType;

  typedef struct {
    iso1Part4_UnitMultiplierType multiplier;
    iso1Part4_UnitSymbolType unit;
    short value_;
  } iso1Part4_PhysicalValueType;

  typedef struct {
    XSDAUX::unsignedInt departureTime;
    iso1Part4_PhysicalValueType eAmount;
    iso1Part4_PhysicalValueType eVMaxVoltage;
    iso1Part4_PhysicalValueType eVMaxCurrent;
    iso1Part4_PhysicalValueType eVMinCurrent;
  } iso1Part4_AC_EVChargeParameterType;
  typedef iso1Part4_AC_EVChargeParameterType iso1Part4_AC_EVChargeParameter;

  typedef struct {
    XSDAUX::unsignedShort notificationMaxDelay;
    iso1Part4_EVSENotificationType eVSENotification;
    XSDAUX::Boolean rCD;
  } iso1Part4_AC_EVSEStatusType;
  typedef iso1Part4_AC_EVSEStatusType iso1Part4_AC_EVSEStatus;

  typedef struct {
	iso1Part4_AC_EVSEStatusType aC_EVSEStatus;
    iso1Part4_PhysicalValueType eVSENominalVoltage;
    iso1Part4_PhysicalValueType eVSEMaxCurrent;
  } iso1Part4_AC_EVSEChargeParameterType;
  typedef iso1Part4_AC_EVSEChargeParameterType iso1Part4_AC_EVSEChargeParameter;

  typedef struct {
    std::vector<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType> x509Certificate_list;
  } iso1Part4_SubCertificatesType;

  typedef struct {
    XSDAUX::ID id;
    urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType x509Certificate;
    iso1Part4_SubCertificatesType subCertificates;
  } iso1Part4_CertificateChainType;

  typedef struct {
    std::vector<iso1Part4_EnergyTransferModeType> energyTransferMode_list;
  } iso1Part4_SupportedEnergyTransferModeType;

  typedef struct {
    iso1Part4_ServiceIDType serviceID;
    iso1Part4_ServiceNameType serviceName;
    iso1Part4_ServiceCategoryType serviceCategory;
    iso1Part4_ServiceScopeType serviceScope;
    XSDAUX::Boolean freeService;
    iso1Part4_SupportedEnergyTransferModeType supportedEnergyTransferMode;
  } iso1Part4_ChargeServiceType;

  typedef struct {
    iso1Part4_CostKindType costKind;
    XSDAUX::unsignedInt amount;
    iso1Part4_UnitMultiplierType amountMultiplier;
  } iso1Part4_CostType;

  typedef struct {
    iso1Part4_PhysicalValueType startValue;
    std::vector<iso1Part4_CostType> cost_list;
  } iso1Part4_ConsumptionCostType;

  typedef struct {
    XSDAUX::ID id;
    iso1Part4_PrivateKeyType base;
  } iso1Part4_ContractSignatureEncryptedPrivateKeyType;

  typedef struct {
    XSDAUX::unsignedInt departureTime;
    iso1Part4_DC_EVStatusType dC_EVStatus;
    iso1Part4_PhysicalValueType eVMaximumCurrentLimit;
    iso1Part4_PhysicalValueType eVMaximumPowerLimit;
    iso1Part4_PhysicalValueType eVMaximumVoltageLimit;
    iso1Part4_PhysicalValueType eVEnergyCapacity;
    iso1Part4_PhysicalValueType eVEnergyRequest;
    iso1Part4_PercentValueType fullSOC;
    iso1Part4_PercentValueType bulkSOC;
  } iso1Part4_DC_EVChargeParameterType;
  typedef iso1Part4_DC_EVChargeParameterType iso1Part4_DC_EVChargeParameter;

  typedef struct {
	iso1Part4_DC_EVStatusType dC_EVStatus;
    XSDAUX::Boolean bulkChargingComplete;
    XSDAUX::Boolean chargingComplete;
  } iso1Part4_DC_EVPowerDeliveryParameterType;
  typedef iso1Part4_DC_EVPowerDeliveryParameterType iso1Part4_DC_EVPowerDeliveryParameter;

  typedef struct {
    XSDAUX::unsignedShort notificationMaxDelay;
    iso1Part4_EVSENotificationType eVSENotification;
    iso1Part4_IsolationLevelType eVSEIsolationStatus;
    iso1Part4_DC_EVSEStatusCodeType eVSEStatusCode;
  } iso1Part4_DC_EVSEStatusType;
  typedef iso1Part4_DC_EVSEStatusType iso1Part4_DC_EVSEStatus;

  typedef struct {
    iso1Part4_DC_EVSEStatusType dC_EVSEStatus;
    iso1Part4_PhysicalValueType eVSEMaximumCurrentLimit;
    iso1Part4_PhysicalValueType eVSEMaximumPowerLimit;
    iso1Part4_PhysicalValueType eVSEMaximumVoltageLimit;
    iso1Part4_PhysicalValueType eVSEMinimumCurrentLimit;
    iso1Part4_PhysicalValueType eVSEMinimumVoltageLimit;
    iso1Part4_PhysicalValueType eVSECurrentRegulationTolerance;
    iso1Part4_PhysicalValueType eVSEPeakCurrentRipple;
    iso1Part4_PhysicalValueType eVSEEnergyToBeDelivered;
  } iso1Part4_DC_EVSEChargeParameterType;
  typedef iso1Part4_DC_EVSEChargeParameterType iso1Part4_DC_EVSEChargeParameter;

  typedef struct {
    XSDAUX::ID id;
    iso1Part4_DHpublickeyType base;
  } iso1Part4_DiffieHellmanPublickeyType;

  typedef struct {
    XSDAUX::ID id;
    iso1Part4_EMAIDType_1 base;
  } iso1Part4_EMAIDType;

  typedef struct {
    XSDAUX::unsignedInt departureTime;
  } iso1Part4_EVChargeParameterType;

  typedef union {
    iso1Part4_EVChargeParameterType eVChargeParameterType;
    iso1Part4_AC_EVChargeParameterType aC_EVChargeParameterType;
    iso1Part4_DC_EVChargeParameterType dC_EVChargeParameterType;
  } iso1Part4_EVChargeParameterType_derivations;
  typedef iso1Part4_EVChargeParameterType_derivations iso1Part4_EVChargeParameter;

  typedef union {
    iso1Part4_EVChargeParameter eVChargeParameter;
    iso1Part4_AC_EVChargeParameter aC_EVChargeParameter;
    iso1Part4_DC_EVChargeParameter dC_EVChargeParameter;
  } iso1Part4_EVChargeParameter_group;

  typedef struct {
  } iso1Part4_EVPowerDeliveryParameterType;

  typedef union {
    iso1Part4_EVPowerDeliveryParameterType eVPowerDeliveryParameterType;
    iso1Part4_DC_EVPowerDeliveryParameterType dC_EVPowerDeliveryParameterType;
  } iso1Part4_EVPowerDeliveryParameterType_derivations;
  typedef iso1Part4_EVPowerDeliveryParameterType_derivations iso1Part4_EVPowerDeliveryParameter;

  typedef union {
    iso1Part4_EVPowerDeliveryParameter eVPowerDeliveryParameter;
    iso1Part4_DC_EVPowerDeliveryParameter dC_EVPowerDeliveryParameter;
  } iso1Part4_EVPowerDeliveryParameter_group;

  typedef struct {
  } iso1Part4_EVSEChargeParameterType;

  typedef union {
    iso1Part4_EVSEChargeParameterType eVSEChargeParameterType;
    iso1Part4_AC_EVSEChargeParameterType aC_EVSEChargeParameterType;
    iso1Part4_DC_EVSEChargeParameterType dC_EVSEChargeParameterType;
  } iso1Part4_EVSEChargeParameterType_derivations;
  typedef iso1Part4_EVSEChargeParameterType_derivations iso1Part4_EVSEChargeParameter;

  typedef union {
    iso1Part4_EVSEChargeParameter eVSEChargeParameter;
    iso1Part4_AC_EVSEChargeParameter aC_EVSEChargeParameter;
    iso1Part4_DC_EVSEChargeParameter dC_EVSEChargeParameter;
  } iso1Part4_EVSEChargeParameter_group;

  typedef struct {
    XSDAUX::unsignedShort notificationMaxDelay;
    iso1Part4_EVSENotificationType eVSENotification;
  } iso1Part4_EVSEStatusType;

  typedef union {
    iso1Part4_EVSEStatusType eVSEStatusType;
    iso1Part4_AC_EVSEStatusType aC_EVSEStatusType;
    iso1Part4_DC_EVSEStatusType dC_EVSEStatusType;
  } iso1Part4_EVSEStatusType_derivations;
  typedef iso1Part4_EVSEStatusType_derivations iso1Part4_EVSEStatus;

  typedef union {
    iso1Part4_EVSEStatus eVSEStatus;
    iso1Part4_AC_EVSEStatus aC_EVSEStatus;
    iso1Part4_DC_EVSEStatus dC_EVSEStatus;
  } iso1Part4_EVSEStatus_group;

  typedef struct {
  } iso1Part4_EVStatusType;

  typedef union {
    iso1Part4_EVStatusType eVStatusType;
    iso1Part4_DC_EVStatusType dC_EVStatusType;
  } iso1Part4_EVStatusType_derivations;
  typedef iso1Part4_EVStatusType_derivations iso1Part4_EVStatus;

  typedef union {
    iso1Part4_EVStatus eVStatus;
    iso1Part4_DC_EVStatus dC_EVStatus;
  } iso1Part4_EVStatus_group;

  typedef struct {
  } iso1Part4_IntervalType;

  typedef union {
    iso1Part4_IntervalType intervalType;
    iso1Part4_RelativeTimeIntervalType relativeTimeIntervalType;
  } iso1Part4_IntervalType_derivations;
  typedef iso1Part4_IntervalType_derivations iso1Part4_TimeInterval;

  typedef union {
    iso1Part4_TimeInterval timeInterval;
    iso1Part4_RelativeTimeInterval relativeTimeInterval;
  } iso1Part4_TimeInterval_group;

  typedef struct {
    iso1Part4_TimeInterval_group timeInterval;
  } iso1Part4_EntryType;

  typedef struct {
    iso1Part4_TimeInterval_group timeInterval;
    iso1Part4_PhysicalValueType pMax;
  } iso1Part4_PMaxScheduleEntryType;
  typedef iso1Part4_PMaxScheduleEntryType iso1Part4_PMaxScheduleEntry;

  typedef struct {
    iso1Part4_TimeInterval_group timeInterval;
    XSDAUX::unsignedByte ePriceLevel;
    std::vector<iso1Part4_ConsumptionCostType> consumptionCost_list;
  } iso1Part4_SalesTariffEntryType;
  typedef iso1Part4_SalesTariffEntryType iso1Part4_SalesTariffEntry;

  typedef union {
    iso1Part4_EntryType entryType;
    iso1Part4_PMaxScheduleEntryType pMaxScheduleEntryType;
    iso1Part4_SalesTariffEntryType salesTariffEntryType;
  } iso1Part4_EntryType_derivations;
  typedef iso1Part4_EntryType_derivations iso1Part4_Entry;

  typedef union {
    iso1Part4_Entry entry;
    iso1Part4_PMaxScheduleEntry pMaxScheduleEntry;
    iso1Part4_SalesTariffEntry salesTariffEntry;
  } iso1Part4_Entry_group;

  typedef struct {
    std::vector<http_www_w3_org_2000_09_xmldsig::iso1Part4_X509IssuerSerialType> rootCertificateID_list;
  } iso1Part4_ListOfRootCertificateIDsType;

  typedef struct {
    iso1Part4_MeterIDType meterID;
    uint64_t meterReading;
    iso1Part4_SigMeterReadingType sigMeterReading;
    iso1Part4_MeterStatusType meterStatus;
    long tMeter;
  } iso1Part4_MeterInfoType;
  typedef struct {
    iso1Part4_FaultCodeType faultCode;
    iso1Part4_FaultMsgType faultMsg;
  } iso1Part4_NotificationType;
  typedef struct {
    std::vector<iso1Part4_PMaxScheduleEntryType> pMaxScheduleEntry_list;
  } iso1Part4_PMaxScheduleType;

  typedef struct {
    XSDAUX::string name;
    union {
      XSDAUX::Boolean boolValue;
      XSDAUX::byte byteValue;
      short shortValue;
      int intValue;
      iso1Part4_PhysicalValueType physicalValue;
      XSDAUX::string stringValue;
    } choice;
  } iso1Part4_ParameterType;

  typedef struct {
    short parameterSetID;
    std::vector<iso1Part4_ParameterType> parameter_list;
  } iso1Part4_ParameterSetType;

  typedef struct {
    std::vector<iso1Part4_PaymentOptionType> paymentOption_list;
  } iso1Part4_PaymentOptionListType;

  typedef struct {
    XSDAUX::unsignedInt chargingProfileEntryStart;
    iso1Part4_PhysicalValueType chargingProfileEntryMaxPower;
    iso1Part4_MaxNumPhasesType chargingProfileEntryMaxNumberOfPhasesInUse;
  } iso1Part4_ProfileEntryType;

  typedef struct {
    std::vector<iso1Part4_ProfileEntryType> profileEntry_list;
  } iso1Part4_ChargingProfileType;

  typedef struct {
    XSDAUX::ID id;
    iso1Part4_SAIDType salesTariffID;
    iso1Part4_TariffDescriptionType salesTariffDescription;
    XSDAUX::unsignedByte numEPriceLevels;
    std::vector<iso1Part4_SalesTariffEntryType> salesTariffEntry_list;
  } iso1Part4_SalesTariffType;

  typedef struct {
    iso1Part4_SAIDType sAScheduleTupleID;
    iso1Part4_PMaxScheduleType pMaxSchedule;
    iso1Part4_SalesTariffType salesTariff;
  } iso1Part4_SAScheduleTupleType;

  typedef struct {
   std::vector<iso1Part4_SAScheduleTupleType> sAScheduleTuple_list;
  } iso1Part4_SAScheduleListType;
  typedef iso1Part4_SAScheduleListType iso1Part4_SAScheduleList;

  typedef union {
    iso1Part4_SASchedulesType sASchedulesType;
    iso1Part4_SAScheduleListType sAScheduleListType;
  } iso1Part4_SASchedulesType_derivations;
  typedef iso1Part4_SASchedulesType_derivations iso1Part4_SASchedules;

  typedef union {
    iso1Part4_SASchedules sASchedules;
    iso1Part4_SAScheduleList sAScheduleList;
  } iso1Part4_SASchedules_group;

  typedef struct {
    std::vector<iso1Part4_SelectedServiceType> selectedService_list;
  } iso1Part4_SelectedServiceListType;

  typedef struct {
    iso1Part4_ServiceIDType serviceID;
    iso1Part4_ServiceNameType serviceName;
    iso1Part4_ServiceCategoryType serviceCategory;
    iso1Part4_ServiceScopeType serviceScope;
    XSDAUX::Boolean freeService;
  } iso1Part4_ServiceType;

  typedef union {
    iso1Part4_ServiceType serviceType;
    iso1Part4_ChargeServiceType chargeServiceType;
  } iso1Part4_ServiceType_derivations;

  typedef struct {
    std::vector<iso1Part4_ServiceType_derivations> service_list;
  } iso1Part4_ServiceListType;

  typedef struct {
    std::vector<iso1Part4_ParameterSetType> parameterSet_list;
  } iso1Part4_ServiceParameterListType;

}

namespace DataStructure_Security {
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  using namespace http_www_w3_org_2000_09_xmldsig;
  typedef struct {
    std::string id;
    std::string digestValue;
  } iso1Part4_IdDigestElement;
  typedef iso1Part4_IdDigestElement iso1Part4_idDigestValueMap;
  typedef std::string iso1Part4_CertificatesList;
  typedef iso1Part4_ReferenceType iso1Part4_LocalReferenceList;
}

namespace DataStructure_V2G_TCP_TLS_Port_Control {
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  using namespace  urn_iso_15118_2_2013_X509Def;

  enum class iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE {
    e_getPort,
    e_disconnectPort,
    e_getPortStatus,
    e_connectPort
  };

  enum class iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE {
    e_failed,
    e_success,
    e_unkownCommand
  };

  typedef struct {
    int intValue;
  } iso1Part4_V2G_TCP_TLS_Port_Number_TYPE;

  typedef struct {
    bool closed;
  } iso1Part4_V2G_TCP_TLS_Port_Status_TYPE;

  typedef struct {
    iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE command;
    iso1Part4_V2G_TCP_TLS_Port_Control_Ack_TYPE ack;
    struct {
      iso1Part4_V2G_TCP_TLS_Port_Number_TYPE portNumber;
      iso1Part4_V2G_TCP_TLS_Port_Status_TYPE portStatus;
    } result;
  } iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageRes;

  typedef struct {
    iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE command;
  } iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq;

  typedef struct V2G_TCP_TLS_Parameter_ST{
    V2G_TCP_TLS_Parameter_ST(){
      seccIpaddress = "";
      seccPort = 0;
      security = 0;
    };
    std::string seccIpaddress;
    uint32_t seccPort;
    int security;
    // V2G_TLS_Parameter_TYPE tlsParameter;
  } iso1Part4_V2G_TCP_TLS_Parameter;
  typedef struct {
    std::string cipherSuite;
    std::string enabledProtocol;
    union{
      urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType certificateChain;
      iso1Part4_X509CertificateType certificate;
    } result;
  } iso1Part4_V2G_TLS_Parameter_TYPE;
}

namespace DataStructure_SDP {
  typedef int iso1Part4_Security_TYPE;
  typedef int iso1Part4_TransportProtocol_TYPE;
  typedef std::string iso1Part4_SECC_IPaddress_TYPE;
  typedef struct {
    iso1Part4_SECC_IPaddress_TYPE ipAddress;
  } iso1Part4_Sender_IPaddress_TYPE;
  typedef uint16_t iso1Part4_SECC_Port_TYPE;

  typedef struct {
    iso1Part4_Security_TYPE security;
    iso1Part4_TransportProtocol_TYPE transportProtocol;
  } iso1Part4_SDP_Request_TYPE;

  typedef struct {
    iso1Part4_SECC_IPaddress_TYPE secc_IPaddress;
    iso1Part4_SECC_Port_TYPE secc_Port;
    iso1Part4_Security_TYPE security;
    iso1Part4_TransportProtocol_TYPE transportProtocol;
  } iso1Part4_SDP_Response_TYPE;
  // Define SDP data structure
  typedef struct {
    union {
      iso1Part4_SDP_Request_TYPE *sdp_Request;
      iso1Part4_SDP_Response_TYPE *sdp_Response;
    } content;
  } iso1Part4_SDP_Message;

  typedef enum {
    ISO1PART4_SDP_REQ_MESSAGE = 0,
    ISO1PART4_SDP_RES_MESSAGE
  }iso1Part4_SDP_Message_Flag;
}

// open V2G C code iso1MessageHeaderType iso1EXIDatatypes.h
namespace urn_iso_15118_2_2013_MsgHeader {
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  using namespace http_www_w3_org_2000_09_xmldsig;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SessionIDType sessionID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_NotificationType notification;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_SignatureType signature_;
  } iso1Part4_MessageHeaderType;
}

// open V2G C code
namespace urn_iso_15118_2_2013_MsgBody {
  using namespace urn_iso_15118_2_2013_X509Def;
  using namespace urn_iso_15118_2_2013_MsgDataTypes;
  using namespace XSDAUX;
  typedef struct {
    XSDAUX::ID id;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_GenChallengeType genChallenge;
  } iso1Part4_AuthorizationReqType;
  typedef iso1Part4_AuthorizationReqType iso1Part4_AuthorizationReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEProcessingType eVSEProcessing;
  } iso1Part4_AuthorizationResType;
  typedef iso1Part4_AuthorizationResType iso1Part4_AuthorizationRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVStatusType dC_EVStatus;
  } iso1Part4_CableCheckReqType;
  typedef iso1Part4_CableCheckReqType iso1Part4_CableCheckReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVSEStatusType dC_EVSEStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEProcessingType eVSEProcessing;
  } iso1Part4_CableCheckResType;
  typedef iso1Part4_CableCheckResType iso1Part4_CableCheckRes;
  typedef struct {
    XSDAUX::ID id;
    urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType oEMProvisioningCert;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ListOfRootCertificateIDsType listOfRootCertificateIDs;
  } iso1Part4_CertificateInstallationReqType;
  typedef iso1Part4_CertificateInstallationReqType iso1Part4_CertificateInstallationReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType sAProvisioningCertificateChain;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType contractSignatureCertChain;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ContractSignatureEncryptedPrivateKeyType contractSignatureEncryptedPrivateKey;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DiffieHellmanPublickeyType dHpublickey;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EMAIDType eMAID;
  } iso1Part4_CertificateInstallationResType;
  typedef iso1Part4_CertificateInstallationResType iso1Part4_CertificateInstallationRes;
  typedef struct {
    XSDAUX::ID id;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType contractSignatureCertChain;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EMAIDType_1 eMAID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ListOfRootCertificateIDsType listOfRootCertificateIDs;
  } iso1Part4_CertificateUpdateReqType;
  typedef iso1Part4_CertificateUpdateReqType iso1Part4_CertificateUpdateReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType sAProvisioningCertificateChain;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType contractSignatureCertChain;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ContractSignatureEncryptedPrivateKeyType contractSignatureEncryptedPrivateKey;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DiffieHellmanPublickeyType dHpublickey;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EMAIDType eMAID;
    short retryCounter;
  } iso1Part4_CertificateUpdateResType;
  typedef iso1Part4_CertificateUpdateResType iso1Part4_CertificateUpdateRes;
  typedef struct {
    XSDAUX::unsignedShort maxEntriesSAScheduleTuple;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EnergyTransferModeType requestedEnergyTransferMode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVChargeParameter_group eVChargeParameter;
  } iso1Part4_ChargeParameterDiscoveryReqType;
  typedef iso1Part4_ChargeParameterDiscoveryReqType iso1Part4_ChargeParameterDiscoveryReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEProcessingType eVSEProcessing;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SASchedules_group sASchedules;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEChargeParameter_group eVSEChargeParameter;
  } iso1Part4_ChargeParameterDiscoveryResType;
  typedef iso1Part4_ChargeParameterDiscoveryResType iso1Part4_ChargeParameterDiscoveryRes;
  typedef struct {
  } iso1Part4_ChargingStatusReqType;
  typedef iso1Part4_ChargingStatusReqType iso1Part4_ChargingStatusReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EvseIDType eVSEID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SAIDType sAScheduleTupleID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEMaxCurrent;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_MeterInfoType meterInfo;
    XSDAUX::Boolean receiptRequired;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_AC_EVSEStatusType aC_EVSEStatus;
  } iso1Part4_ChargingStatusResType;
  typedef iso1Part4_ChargingStatusResType iso1Part4_ChargingStatusRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVStatusType dC_EVStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVTargetCurrent;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVMaximumVoltageLimit;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVMaximumCurrentLimit;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVMaximumPowerLimit;
    XSDAUX::Boolean bulkChargingComplete;
    XSDAUX::Boolean chargingComplete;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType remainingTimeToFullSoC;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType remainingTimeToBulkSoC;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVTargetVoltage;
  } iso1Part4_CurrentDemandReqType;
  typedef iso1Part4_CurrentDemandReqType iso1Part4_CurrentDemandReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVSEStatusType dC_EVSEStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEPresentVoltage;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEPresentCurrent;
    XSDAUX::Boolean eVSECurrentLimitAchieved;
    XSDAUX::Boolean eVSEVoltageLimitAchieved;
    XSDAUX::Boolean eVSEPowerLimitAchieved;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEMaximumVoltageLimit;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEMaximumCurrentLimit;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEMaximumPowerLimit;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EvseIDType eVSEID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SAIDType sAScheduleTupleID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_MeterInfoType meterInfo;
    XSDAUX::Boolean receiptRequired;
  } iso1Part4_CurrentDemandResType;
  typedef iso1Part4_CurrentDemandResType iso1Part4_CurrentDemandRes;
  typedef struct {
    XSDAUX::ID id;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SessionIDType sessionID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SAIDType sAScheduleTupleID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_MeterInfoType meterInfo;
  } iso1Part4_MeteringReceiptReqType;
  typedef iso1Part4_MeteringReceiptReqType iso1Part4_MeteringReceiptReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEStatus_group eVSEStatus;
  } iso1Part4_MeteringReceiptResType;
  typedef iso1Part4_MeteringReceiptResType iso1Part4_MeteringReceiptRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EMAIDType_1 eMAID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_CertificateChainType contractSignatureCertChain;
  } iso1Part4_PaymentDetailsReqType;
  typedef iso1Part4_PaymentDetailsReqType iso1Part4_PaymentDetailsReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_GenChallengeType genChallenge;
    long eVSETimeStamp;
  } iso1Part4_PaymentDetailsResType;
  typedef iso1Part4_PaymentDetailsResType iso1Part4_PaymentDetailsRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PaymentOptionType selectedPaymentOption;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SelectedServiceListType selectedServiceList;
  } iso1Part4_PaymentServiceSelectionReqType;
  typedef iso1Part4_PaymentServiceSelectionReqType iso1Part4_PaymentServiceSelectionReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
  } iso1Part4_PaymentServiceSelectionResType;
  typedef iso1Part4_PaymentServiceSelectionResType iso1Part4_PaymentServiceSelectionRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ChargeProgressType chargeProgress;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_SAIDType sAScheduleTupleID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ChargingProfileType chargingProfile;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVPowerDeliveryParameter_group eVPowerDeliveryParameter;
  } iso1Part4_PowerDeliveryReqType;
  typedef iso1Part4_PowerDeliveryReqType iso1Part4_PowerDeliveryReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EVSEStatus_group eVSEStatus;
  } iso1Part4_PowerDeliveryResType;
  typedef iso1Part4_PowerDeliveryResType iso1Part4_PowerDeliveryRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVStatusType dC_EVStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVTargetVoltage;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVTargetCurrent;
  } iso1Part4_PreChargeReqType;
  typedef iso1Part4_PreChargeReqType iso1Part4_PreChargeReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVSEStatusType dC_EVSEStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEPresentVoltage;
  } iso1Part4_PreChargeResType;
  typedef iso1Part4_PreChargeResType iso1Part4_PreChargeRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceIDType serviceID;
  } iso1Part4_ServiceDetailReqType;
  typedef iso1Part4_ServiceDetailReqType iso1Part4_ServiceDetailReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceIDType serviceID;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceParameterListType serviceParameterList;
  } iso1Part4_ServiceDetailResType;
  typedef iso1Part4_ServiceDetailResType iso1Part4_ServiceDetailRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceScopeType serviceScope;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceCategoryType serviceCategory;
  } iso1Part4_ServiceDiscoveryReqType;
  typedef iso1Part4_ServiceDiscoveryReqType iso1Part4_ServiceDiscoveryReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PaymentOptionListType paymentOptionList;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ChargeServiceType chargeService;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ServiceListType serviceList;
  } iso1Part4_ServiceDiscoveryResType;
  typedef iso1Part4_ServiceDiscoveryResType iso1Part4_ServiceDiscoveryRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EvccIDType eVCCID;
  } iso1Part4_SessionSetupReqType;
  typedef iso1Part4_SessionSetupReqType iso1Part4_SessionSetupReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_EvseIDType eVSEID;
    long eVSETimeStamp;
  } iso1Part4_SessionSetupResType;
  typedef iso1Part4_SessionSetupResType iso1Part4_SessionSetupRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ChargingSessionType chargingSession;
  } iso1Part4_SessionStopReqType;
  typedef iso1Part4_SessionStopReqType iso1Part4_SessionStopReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
  } iso1Part4_SessionStopResType;
  typedef iso1Part4_SessionStopResType iso1Part4_SessionStopRes;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVStatusType dC_EVStatus;
  } iso1Part4_WeldingDetectionReqType;
  typedef iso1Part4_WeldingDetectionReqType iso1Part4_WeldingDetectionReq;
  typedef struct {
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_ResponseCodeType responseCode;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_DC_EVSEStatusType dC_EVSEStatus;
    urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType eVSEPresentVoltage;
  } iso1Part4_WeldingDetectionResType;
  typedef iso1Part4_WeldingDetectionResType iso1Part4_WeldingDetectionRes;
  typedef struct {
  } iso1Part4_BodyBaseType;
  typedef union {
    iso1Part4_BodyBaseType bodyBaseType;
    iso1Part4_AuthorizationReqType authorizationReqType;
    iso1Part4_AuthorizationResType authorizationResType;
    iso1Part4_CableCheckReqType cableCheckReqType;
    iso1Part4_CableCheckResType cableCheckResType;
    iso1Part4_CertificateInstallationReqType certificateInstallationReqType;
    iso1Part4_CertificateInstallationResType certificateInstallationResType;
    iso1Part4_CertificateUpdateReqType certificateUpdateReqType;
    iso1Part4_CertificateUpdateResType certificateUpdateResType;
    iso1Part4_ChargeParameterDiscoveryReqType chargeParameterDiscoveryReqType;
    iso1Part4_ChargeParameterDiscoveryResType chargeParameterDiscoveryResType;
    iso1Part4_ChargingStatusReqType chargingStatusReqType;
    iso1Part4_ChargingStatusResType chargingStatusResType;
    iso1Part4_CurrentDemandReqType currentDemandReqType;
    iso1Part4_CurrentDemandResType currentDemandResType;
    iso1Part4_MeteringReceiptReqType meteringReceiptReqType;
    iso1Part4_MeteringReceiptResType meteringReceiptResType;
    iso1Part4_PaymentDetailsReqType paymentDetailsReqType;
    iso1Part4_PaymentDetailsResType paymentDetailsResType;
    iso1Part4_PaymentServiceSelectionReqType paymentServiceSelectionReqType;
    iso1Part4_PaymentServiceSelectionResType paymentServiceSelectionResType;
    iso1Part4_PowerDeliveryReqType powerDeliveryReqType;
    iso1Part4_PowerDeliveryResType powerDeliveryResType;
    iso1Part4_PreChargeReqType preChargeReqType;
    iso1Part4_PreChargeResType preChargeResType;
    iso1Part4_ServiceDetailReqType serviceDetailReqType;
    iso1Part4_ServiceDetailResType serviceDetailResType;
    iso1Part4_ServiceDiscoveryReqType serviceDiscoveryReqType;
    iso1Part4_ServiceDiscoveryResType serviceDiscoveryResType;
    iso1Part4_SessionSetupReqType sessionSetupReqType;
    iso1Part4_SessionSetupResType sessionSetupResType;
    iso1Part4_SessionStopReqType sessionStopReqType;
    iso1Part4_SessionStopResType sessionStopResType;
    iso1Part4_WeldingDetectionReqType weldingDetectionReqType;
    iso1Part4_WeldingDetectionResType weldingDetectionResType;
  } iso1Part4_BodyBaseType_derivations;
  typedef iso1Part4_BodyBaseType_derivations iso1Part4_BodyElement;
  typedef union {
    iso1Part4_BodyElement bodyElement;
    iso1Part4_AuthorizationReq authorizationReq;
    iso1Part4_AuthorizationRes authorizationRes;
    iso1Part4_CableCheckReq cableCheckReq;
    iso1Part4_CableCheckRes cableCheckRes;
    iso1Part4_CertificateInstallationReq certificateInstallationReq;
    iso1Part4_CertificateInstallationRes certificateInstallationRes;
    iso1Part4_CertificateUpdateReq certificateUpdateReq;
    iso1Part4_CertificateUpdateRes certificateUpdateRes;
    iso1Part4_ChargeParameterDiscoveryReq chargeParameterDiscoveryReq;
    iso1Part4_ChargeParameterDiscoveryRes chargeParameterDiscoveryRes;
    iso1Part4_ChargingStatusReq chargingStatusReq;
    iso1Part4_ChargingStatusRes chargingStatusRes;
    iso1Part4_CurrentDemandReq currentDemandReq;
    iso1Part4_CurrentDemandRes currentDemandRes;
    iso1Part4_MeteringReceiptReq meteringReceiptReq;
    iso1Part4_MeteringReceiptRes meteringReceiptRes;
    iso1Part4_PaymentDetailsReq paymentDetailsReq;
    iso1Part4_PaymentDetailsRes paymentDetailsRes;
    iso1Part4_PaymentServiceSelectionReq paymentServiceSelectionReq;
    iso1Part4_PaymentServiceSelectionRes paymentServiceSelectionRes;
    iso1Part4_PowerDeliveryReq powerDeliveryReq;
    iso1Part4_PowerDeliveryRes powerDeliveryRes;
    iso1Part4_PreChargeReq preChargeReq;
    iso1Part4_PreChargeRes preChargeRes;
    iso1Part4_ServiceDetailReq serviceDetailReq;
    iso1Part4_ServiceDetailRes serviceDetailRes;
    iso1Part4_ServiceDiscoveryReq serviceDiscoveryReq;
    iso1Part4_ServiceDiscoveryRes serviceDiscoveryRes;
    iso1Part4_SessionSetupReq sessionSetupReq;
    iso1Part4_SessionSetupRes sessionSetupRes;
    iso1Part4_SessionStopReq sessionStopReq;
    iso1Part4_SessionStopRes sessionStopRes;
    iso1Part4_WeldingDetectionReq weldingDetectionReq;
    iso1Part4_WeldingDetectionRes weldingDetectionReS;
  } iso1Part4_BodyElement_group;
  typedef struct {
    iso1Part4_BodyElement_group bodyElement;
  } iso1Part4_BodyType;
}

// open V2G C code iso1AnonType_V2G_Message iso1EXIDatatypes.h
namespace urn_iso_15118_2_2013_MsgDef {
  using namespace urn_iso_15118_2_2013_MsgHeader;
  using namespace urn_iso_15118_2_2013_MsgBody;
  typedef union
  {
    /* This type follow the ISO15118-4-2019 */
    typedef struct {
      urn_iso_15118_2_2013_MsgHeader::iso1Part4_MessageHeaderType header;
      urn_iso_15118_2_2013_MsgBody::iso1Part4_BodyType body;
    } iso1Part4_V2G_Message;
  } iso1Part4_V2GMessageDataType;
}

// open V2G C code appHandEXIDocument appHandEXIDatatypes.h
namespace urn_iso_15118_2_2010_AppProtocol {
  using namespace XSDAUX;
  typedef XSDAUX::unsignedByte iso1Part4_IdType;
  typedef XSDAUX::unsignedByte iso1Part4_PriorityType;
  typedef XSDAUX::string iso1Part4_ProtocolNameType;
  typedef XSDAUX::anyURI iso1Part4_ProtocolNamespaceType;
  /* appHandAppProtocolType */
  typedef struct {
    iso1Part4_ProtocolNamespaceType protocolNamespace;
    XSDAUX::unsignedInt versionNumberMajor;
    XSDAUX::unsignedInt versionNumberMinor;
    iso1Part4_IdType schemaID;
    iso1Part4_PriorityType priority;
  } iso1Part4_AppProtocolType;
  /* appHandresponseCodeType */
  enum class iso1Part4_appHandresponseCodeType {
    oK_SuccessfulNegotiation,
    oK_SuccessfulNegotiationWithMinorDeviation,
    failed_NoNegotiation
  };

  typedef struct {
    std::vector<iso1Part4_AppProtocolType> appProtocol_list;
  } iso1Part4_appHandAnonType_supportedAppProtocolReqType;

  /* appHandAnonType_supportedAppProtocolReq */
  typedef union {
    iso1Part4_appHandAnonType_supportedAppProtocolReqType \
      iso1_part4_appHandAnonType_supportedAppProtocolReq;
  } iso1Part4_appHandAnonType_supportedAppProtocolReq;

  typedef struct {
    iso1Part4_appHandresponseCodeType responseCode;
    iso1Part4_IdType schemaID;
  } iso1Part4_appHandAnonType_supportedAppProtocolResType;

  /* appHandAnonType_supportedAppProtocolRes */
  typedef union {
    iso1Part4_appHandAnonType_supportedAppProtocolResType \
      iso1_Part4_appHandAnonType_supportedAppProtocolRes;
  }iso1Part4_appHandAnonType_supportedAppProtocolRes;

}

namespace DataStructure_V2GTP {
  using namespace DataStructure_SDP;
  using namespace urn_iso_15118_2_2013_MsgDef;
  using namespace urn_iso_15118_2_2010_AppProtocol;
  typedef iso1Part4_appHandAnonType_supportedAppProtocolReq iso1Part4_SupportedAppProtocolReq;
  typedef iso1Part4_appHandAnonType_supportedAppProtocolRes iso1Part4_SupportedAppProtocolRes;
  typedef uint8_t iso1Part4_ProtocolVersion_TYPE;
  typedef uint8_t iso1Part4_InvProtocolVersion_TYPE;
  typedef uint16_t iso1Part4_PayloadType_TYPE;
  typedef uint32_t iso1Part4_PayloadLength_TYPE;

  typedef struct {
    union {
      iso1Part4_SDP_Message sdp_message;
      iso1Part4_V2GMessageDataType v2g_message;
      iso1Part4_SupportedAppProtocolReq supportedAppProtocolReq_message;
      iso1Part4_SupportedAppProtocolRes supportedAppProtocolRes_message;
    } content;
  } iso1Part4_V2GTP_payload_TYPE;
  typedef struct {
    iso1Part4_PayloadLength_TYPE payloadLength;
    iso1Part4_PayloadType_TYPE payloadType;
    iso1Part4_ProtocolVersion_TYPE protocolVersion;
    iso1Part4_InvProtocolVersion_TYPE invProtocolVersion;
  } iso1Part4_V2GTP_header_TYPE;
  // Define V2GTP data structure
  typedef struct {
    iso1Part4_V2GTP_header_TYPE v2gtp_header;
    iso1Part4_V2GTP_payload_TYPE v2gtp_payload;
  } iso1Part4_V2GTP_Message;
}

namespace http_www_w3_org_2001_04_xmlenc {
  using namespace http_www_w3_org_2000_09_xmldsig;
  using namespace XSDAUX;

  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    XSDAUX::base64Binary kA_Nonce;
    std::vector<XSDAUX::AnyType> elem_list;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_KeyInfoType originatorKeyInfo;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_KeyInfoType recipientKeyInfo;
  } iso1Part4_AgreementMethodType;
  typedef iso1Part4_AgreementMethodType iso1Part4_AgreementMethod;

  typedef XSDAUX::integerXSD iso1Part4_KeySizeType;

  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::anyURI algorithm;
    iso1Part4_KeySizeType keySize;
    XSDAUX::base64Binary oAEPparams;
    std::vector<XSDAUX::AnyType> elem_list;
  } iso1Part4_EncryptionMethodType;

  typedef struct {
    XSDAUX::string embed_values;
    XSDAUX::ID id;
    XSDAUX::anyURI target;
    XSDAUX::AnyAttributes attr;
    typedef union {
      XSDAUX::AnyType elem;
    } iso1Part4_dummyEncryptionPropertyType;
    std::vector<iso1Part4_dummyEncryptionPropertyType> choice_list;
  } iso1Part4_EncryptionPropertyType;
  typedef iso1Part4_EncryptionPropertyType iso1Part4_EncryptionProperty;

  typedef struct {
    XSDAUX::ID id;
    std::vector<iso1Part4_EncryptionPropertyType> encryptionProperty_list;
  } iso1Part4_EncryptionPropertiesType;
  typedef iso1Part4_EncryptionPropertiesType iso1Part4_EncryptionProperties;

  typedef struct {
    typedef union {
      iso1Part4_ReferenceType dataReference;
      iso1Part4_ReferenceType keyReference;
    } dummyReferenceList;
    std::vector<dummyReferenceList> choice_list;
  } iso1Part4_ReferenceList;
  typedef struct {
    XSDAUX::anyURI uRI;
    std::vector<XSDAUX::AnyType> elem_list;
  } iso1Part4_ReferenceType;
  typedef struct {
    std::vector<http_www_w3_org_2000_09_xmldsig::iso1Part4_TransformType> transform_list;
  } iso1Part4_TransformsType;

  typedef struct {
    XSDAUX::anyURI uRI;
    union {
      iso1Part4_TransformsType transforms_list[2];
    } choice;
  } iso1Part4_CipherReferenceType;
  typedef iso1Part4_CipherReferenceType iso1Part4_CipherReference;

  typedef struct {
    union {
      XSDAUX::base64Binary cipherValue;
      iso1Part4_CipherReferenceType cipherReference;
    } choice;
  } iso1Part4_CipherDataType;
  typedef iso1Part4_CipherDataType iso1Part4_CipherData;

  typedef struct {
    XSDAUX::anyURI encoding;
    XSDAUX::ID id;
    XSDAUX::string mimeType;
    XSDAUX::anyURI type_;
    iso1Part4_EncryptionMethodType encryptionMethod;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_KeyInfoType keyInfo;
    iso1Part4_CipherDataType cipherData;
    iso1Part4_EncryptionPropertiesType encryptionProperties;
  } iso1Part4_EncryptedDataType;
  typedef iso1Part4_EncryptedDataType iso1Part4_EncryptedData;
  typedef struct {
    XSDAUX::anyURI encoding;
    XSDAUX::ID id;
    XSDAUX::string mimeType;
    XSDAUX::string recipient;
    XSDAUX::anyURI type_;
    iso1Part4_EncryptionMethodType encryptionMethod;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_KeyInfoType keyInfo;
    iso1Part4_CipherDataType cipherData;
    iso1Part4_EncryptionPropertiesType encryptionProperties;
    iso1Part4_ReferenceList referenceList;
    XSDAUX::string carriedKeyName;
  } iso1Part4_EncryptedKeyType;
  typedef iso1Part4_EncryptedKeyType EncryptedKey;
    typedef struct {
    XSDAUX::anyURI encoding;
    XSDAUX::ID id;
    XSDAUX::string mimeType;
    XSDAUX::anyURI type_;
    iso1Part4_EncryptionMethodType encryptionMethod;
    http_www_w3_org_2000_09_xmldsig::iso1Part4_KeyInfoType keyInfo;
    iso1Part4_CipherDataType cipherData;
    iso1Part4_EncryptionPropertiesType encryptionProperties;
  } iso1Part4_EncryptedType;

  typedef union {
    iso1Part4_EncryptedType encryptedType;
    iso1Part4_EncryptedDataType encryptedDataType;
    iso1Part4_EncryptedKeyType encryptedKeyType;
  } iso1Part4_EncryptedType_derivations;
}


extern DataStructure_SDP::iso1Part4_Security_TYPE cc_hexTls;
extern DataStructure_SDP::iso1Part4_Security_TYPE cc_hexTcp;
extern int cc_proximity_type1;
extern int cc_proximity_type2_AC_13A;
extern int cc_proximity_type2_AC_20A;
extern int cc_proximity_type2_AC_32A;
extern int cc_proximity_type2_AC_63A;
extern int cc_proximity_type2_DC;
extern std::string cc_EvseId_NotSup;
extern float cc_maximum_value_physicalValue_case1;
extern float cc_maximum_value_physicalValue_case2;
extern float cc_maximum_value_physicalValue_case4;
extern uint64_t cc_maximum_value_meterReading;

#endif
