#ifndef __COMMONLIB_H__
#define __COMMONLIB_H__
#include "Components.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "Common_Cfg.h"

#define int2float(VAL) ((float)(VAL))
#define float2int(VAL) ((int)(VAL))

extern bool a_CMN_shutdownOscillator(std::shared_ptr<HAL_61851_Internal_Port>& port);
extern verdict_val f_SECC_CMN_PR_PLCLinkStatus_002(std::shared_ptr<System_SECC> &systemSECC, std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<HAL_61851_Listener>& v_HAL_61851_Listener);
extern verdict_val f_SECC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<System_SECC> &systemSECC, std::shared_ptr<SECC_Tester> &_mtc);
extern void f_SECC_changeValidStateCondition(DataStructure_HAL_61851::IEC_61851_States state);
extern verdict_val f_SECC_setState(std::shared_ptr<System_SECC> &_systemSECC, DataStructure_HAL_61851::IEC_61851_States state,\
  std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener);
extern void f_SECC_changeValidFrequencyRange(std::shared_ptr<System_SECC> &_systemSECC, float lower, float upper);
extern void f_SECC_changeValidDutyCycleRange(std::shared_ptr<System_SECC> &_systemSECC, float lower, float upper);
extern void md_CMN_CMN_tcpTlsStatusReq_001(std::shared_ptr<BaseOperation> &cmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE val);
extern bool f_checkInvalidServiceID(std::shared_ptr<SECC_Tester> &_mtc, uint16_t v_invalidServiceID, ServiceListType &service_list);
extern void f_check_PhysicalValue_valueRange(std::shared_ptr<SECC_Tester> &_mtc, PhysicalValueType &v_physicalValue,\
  urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_UnitSymbolType v_unit, float v_maxValue, verdict_val v_vct, const std::string &msg_value);

extern void f_SECC_setIsConfirmationFlagDC(void);
extern verdict_val f_SECC_setProximity(int val);
extern std::shared_ptr<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType> fx_loadCertificate(DataStructure_PIXIT_15118_2::iso1Part4_PkiType type, const std::string &name);
extern bool fx_validateEVSEID(const std::string& v_evseID,const std::string& v_protocol);
extern std::vector<uint8_t> f_rnd_SessionID(uint32_t lower_val, uint32_t upper_val);
extern std::string f_toString(char *arr, int size);
extern std::string f_toString(char arr[]);
extern bool ispresent(ServiceListType &service_list);
extern float f_CMN_PhysicalValue_GetValue(const urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType &v);
extern float f_CMN_PhysicalValue_GetValue(const PhysicalValueType &v);
extern float f_CMN_Pow(int v_multiplier);
extern void f_hexStringToArr(const std::string &hexString, std::vector<uint8_t> &arr);
extern std::string f_outHexString(const std::string &val);
extern std::string f_outHexString(std::vector<uint8_t> &val);
extern bool f_verifySignature(BodyType *p_bodyType, SignatureType *p_signatureType, urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType *p_certificate, verdict_val v_vct);
extern std::string fx_loadPrivateKey(const std::string &cert_name);
extern bool isbound(const std::string &par);
extern std::vector<uint8_t> f_generateDigestFromBodyType(BodyType *p_BodyType);
extern void md_CMN_Signature_001(SignatureType &sign, SignedInfoType *signInfo, const std::string &privateKey);
extern SignedInfoType *md_CMN_SignedInfoType_001(const std::string &msgName, const std::vector<uint8_t> &digestKey);
extern std::vector<uint8_t> fx_generateGenChallenge(void);
extern std::shared_ptr<DataStructure_Security::iso1Part4_idDigestValueMap>& f_calculateIdDigestMapFromBodyType(BodyType &body);
#endif // __COMMONLIB_H__