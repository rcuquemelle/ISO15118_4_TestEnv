#include "CommonLib.h"
#include "PAInterface.h"
#include "fmt/core.h"
#include <memory>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <array>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <regex>

static const char* HAL_CMD[] = {
  [IEC_61851_States::A] = "A",
  [IEC_61851_States::B] = "B",
  [IEC_61851_States::C] = "C",
  [IEC_61851_States::D] = "D",
  [IEC_61851_States::E] = "E",
  [IEC_61851_States::F] = "F",
  [IEC_61851_States::NA] = "NA",
  [IEC_61851_States::none_] = "NONE"
};

using namespace urn_iso_15118_2_2013_MsgDataTypes;

void f_SECC_changeValidStateCondition(DataStructure_HAL_61851::IEC_61851_States state)
{
  // check if valid state change
  Logging::debug(LogCmnLib_ENABLE, fmt::format("[CMN_LIB]: f_SECC_changeValidStateCondition {}", HAL_CMD[state]));
}
verdict_val f_SECC_setProximity(int val) {
  /* function set proximity parameter for proximity line connection */
  Logging::debug(LogCmnLib_ENABLE, "[CMN_LIB]: f_SECC_setProximity");
  return pass;
}
verdict_val f_SECC_setState(std::shared_ptr<System_SECC> &_systemSECC, DataStructure_HAL_61851::IEC_61851_States state, std::shared_ptr<HAL_61851_Listener> &v_HAL_61851_Listener)
{
  _systemSECC->_pBCIf->setState(state);
  Logging::debug(LogCmnLib_ENABLE, fmt::format("[CMN_LIB]: f_SECC_setState {}", HAL_CMD[state]));
  return pass;
}
void f_SECC_changeValidFrequencyRange(std::shared_ptr<System_SECC> &_systemSECC, float lower, float upper) {
  float feq = _systemSECC->_pBCIf->getPWMFreq();
  if (!((lower <= feq) && (feq <= upper))){
    Logging::error(LogCmnLib_ENABLE, fmt::format("[CMN_LIB]: Frequency of CP PWM {0} is out of range {1}-{2}", feq, lower, upper));
  }
}
void f_SECC_changeValidDutyCycleRange(std::shared_ptr<System_SECC> &_systemSECC, float lower, float upper) {
  float duty = _systemSECC->_pBCIf->getPWMDuty();
  if (!((lower <= duty) && (duty <= upper))){
    Logging::error(LogCmnLib_ENABLE, fmt::format("[CMN_LIB]: Duty of CP PWM {0} is out of range {1}-{2}", duty, lower, upper));
  }
}
// check plc link status
verdict_val f_SECC_CMN_PR_PLCLinkStatus_002(std::shared_ptr<System_SECC> &systemSECC, std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<HAL_61851_Listener>& v_HAL_61851_Listener)
{
  f_SECC_setState(systemSECC, A, v_HAL_61851_Listener);
  PAsleep(0.5);
  f_SECC_setState(systemSECC, B, v_HAL_61851_Listener);
  PAsleep(0.5);
  return f_SECC_CMN_PR_PLCLinkStatus_001(systemSECC, _mtc);
}
// check plc link status
verdict_val f_SECC_CMN_PR_PLCLinkStatus_001(std::shared_ptr<System_SECC> &systemSECC, std::shared_ptr<SECC_Tester> &_mtc)
{
  Logging::debug(LogCmnLib_ENABLE, "[CMN_LIB]: f_SECC_CMN_PR_PLCLinkStatus_001");
  map(_mtc->pt_SLAC_Port, systemSECC->pt_SLAC_Port);
  std::shared_ptr<BaseOperation> cmd = std::make_shared<BaseOperation>(OpType_SLAC);
  std::shared_ptr<PATimer> t_sleep = _mtc->pt_TimerManager->createTimer("local_slac", 30);
  cmd->SLACReq = std::make_shared<DLINKCmd>();
  cmd->SLACReq->cmd = en_DLINKCmdType::GET_DLINK_STATUS;
  cmd->SLACRes = std::make_shared<DLINKEvent>();
  cmd->SLACRes->event = en_DLINKEventType::DISCONNECT;

  auto handler = [](std::shared_ptr<BaseOperation>& expected, std::shared_ptr<BaseOperation>& received) -> bool {
    if (received->SLACRes->event == en_DLINKEventType::MATCHED) {
      expected->SLACRes->event = en_DLINKEventType::MATCHED;
      Logging::debug(LogCfgFnc_ENABLE, "[CMN_LIB]: MATCHED Event receive");
      return true;
    }
    else {
      Logging::debug(LogCfgFnc_ENABLE, fmt::format("[CMN_LIB]: SLAC Event {} receive", received->SLACRes->event));
      return false;
    }
  };
  _mtc->pt_SLAC_Port->send(cmd);
  t_sleep->start();
  while(1)
  {
    if (_mtc->pt_SLAC_Port->receive(cmd, handler))
    {
      _mtc->pt_TimerManager->popTimer("local_slac");
      break;
    }
    if (t_sleep->timeout()){
      Logging::info(LogCfgFnc_ENABLE, "[CMN_LIB]: SLAC timeout");
      _mtc->pt_TimerManager->popTimer("local_slac");
      cmd->SLACRes->event = en_DLINKEventType::DISCONNECT;
      break;
    }
  }
  if (cmd->SLACRes->event == en_DLINKEventType::MATCHED)
  {
    PAsleep(5);
    cmd->SLACReq->cmd = en_DLINKCmdType::SET_DLINK_CLOSE_FD;
    _mtc->pt_SLAC_Port->send(cmd);
    PAsleep(5);
    if (systemSECC->_pUDPIf->start()) {
      Logging::info(LogCmnLib_ENABLE, "[CMN_LIB]: SLAC - CONNECTED");
      return pass;
    }
    else {
      Logging::info(LogCmnLib_ENABLE, "[CMN_LIB]: UDP connect - FAIL");
      return fail;
    }
  }
  else
  {
    Logging::info(LogCmnLib_ENABLE, "[CMN_LIB]: SLAC - FAIL");
    return fail;
  }
}

void f_SECC_setIsConfirmationFlagDC(void){

}

void f_hexStringToArr(const std::string &hexString, std::vector<uint8_t> &arr) {
  std::string temp;
  for (auto c=hexString.begin(); c!=hexString.end(); c++) {
    if ((*c) != ':')
      temp.push_back(*c);
  }
  for (unsigned int i = 0; i < temp.length(); i += 2) {
    std::string byteString = temp.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    arr.push_back(byte);
  }
}

// check if pwm output is turnoff by SECC before TCP connection is shutdown
bool a_CMN_shutdownOscillator(std::shared_ptr<HAL_61851_Internal_Port>& port){

  return false;
}

bool fx_validateEVSEID(const std::string& v_evseID,const std::string& v_protocol) {
  std::regex regex_msg("\\w{2}\\*[a-zA-Z0-9]{3}\\*E[a-zA-Z0-9\\*]{1,30}", std::regex_constants::ECMAScript);
  std::smatch matches;
  if (v_protocol == "ISO") {
    if (std::regex_search(v_evseID, matches, regex_msg)) {
      return true;
    }
    else {
      return false;
    }
  }
  else {
    return (v_evseID.compare(v_protocol) != 0);
  }
}

// output random sessionID value
std::vector<uint8_t> f_rnd_SessionID(uint32_t lower_val, uint32_t upper_val){
  std::vector<uint8_t> result;
  result.assign(8, 0);
  srand(time(NULL));
  for (auto &&i : result)
  {
    i = rand()%((255 - 1) + 1);
  }
  return result;
}

void md_CMN_CMN_tcpTlsStatusReq_001(std::shared_ptr<BaseOperation> &cmd, iso1Part4_V2G_TCP_TLS_Port_Control_Command_TYPE val){
  cmd->TcpControlReq = std::make_shared<iso1Part4_V2G_TCP_TLS_Port_Control_Internal_MessageReq>();
  cmd->TcpControlReq->command = val;
}

std::string f_toString(char *arr, int size)
{
  return std::string(arr, size);
}

std::string f_toString(char arr[])
{
  return std::string(arr);
}

bool ispresent(ServiceListType &service_list) {
  return (service_list.Service.arrayLen != 0);
}

bool f_checkInvalidServiceID(std::shared_ptr<SECC_Tester> &_mtc, uint16_t v_invalidServiceID, ServiceListType &service_list)
{
  for (int i = 0; i < service_list.Service.arrayLen; i = i + 1)
  {
    if (v_invalidServiceID == service_list.Service.array[0].ServiceID)
    {
      _mtc->setverdict(inconc, fmt::format("Service list has ID {}. Selected serviceID is not invalid.", v_invalidServiceID));
      return false;
    }
  }
  return true;
}
float f_CMN_PhysicalValue_GetValue(const urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_PhysicalValueType &v) {
  PhysicalValueType temp;
  memcpy(&temp, &v, sizeof(PhysicalValueType));
  return f_CMN_PhysicalValue_GetValue(temp);
}
float f_CMN_PhysicalValue_GetValue(const PhysicalValueType &v){
  float ret;
  if (v.Multiplier < 0) {
    ret = (int2float(v.Value) * (1.0/(f_CMN_Pow(v.Multiplier*-1))));
  }
  else if (v.Multiplier > 0) {
    ret = (int2float(v.Value) * (f_CMN_Pow(v.Multiplier)));
  }
  else {
    ret = int2float(v.Value);
  }
  return ret;
}
float f_CMN_Pow(int v_multiplier) {
  float ret = 10.0;
  for (int i=0; i<v_multiplier-1; i=i + 1) {
    ret = ret * 10.0;
  }
  return ret;
}

void f_CMN_PhysicalValue_SetValue(PhysicalValueType &v, int8_t multi, unitSymbolType unit, int16_t value) {
  v.Multiplier = multi;
  v.Unit = unit;
  v.Value = value;
}

void f_check_PhysicalValue_valueRange(std::shared_ptr<SECC_Tester> &_mtc, PhysicalValueType &v_physicalValue,\
  urn_iso_15118_2_2013_MsgDataTypes::iso1Part4_UnitSymbolType v_unit, float v_maxValue, verdict_val v_vct, const std::string &msg_value) {
  if(f_CMN_PhysicalValue_GetValue(v_physicalValue) > v_maxValue) {
    _mtc->setverdict(v_vct, fmt::format("The corresponding physical value has an invalid maximum value. {0} - val:{1} - max_val:{2}", msg_value, f_CMN_PhysicalValue_GetValue(v_physicalValue), v_maxValue));
  }
  if(v_physicalValue.Unit != (unitSymbolType)v_unit) {
    _mtc->setverdict(v_vct, fmt::format("The corresponding physical value has an invalid unit. {0} - type:{1} - expected:{2}", msg_value, v_physicalValue.Unit, v_unit));
  }
}

std::string f_outHexString(const std::string &val){
  std::string temp;
  for (auto c = val.begin(); c != val.end(); c++)
  {
    temp.append(fmt::format("{:02X} ", (uint8_t)(*c)));
  }
  return temp;
}

std::string f_outHexString(std::vector<uint8_t> &val){
  std::string temp;
  for (auto c = val.begin(); c != val.end(); c++)
  {
    temp.append(fmt::format("{:02X} ", (uint8_t)(*c)));
  }
  return temp;
}

// urn_iso_15118_2_2013_X509Def::X509CertificateType
std::shared_ptr<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType> fx_loadCertificate(DataStructure_PIXIT_15118_2::iso1Part4_PkiType type, const std::string &name){
  std::shared_ptr<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType> cert = std::make_shared<urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType>();
  // TODO:
  Logging::debug(LogCmnLib_ENABLE, fmt::format("[CMN_LIB]: fx_loadCertificate {0}-{1}", type, name));
  return cert;
}


bool f_verifySignature(BodyType *p_bodyType, SignatureType *p_signatureType,
  urn_iso_15118_2_2013_X509Def::iso1Part4_X509CertificateType *p_certificate, verdict_val v_vct) {

  return true;
}

std::string fx_loadPrivateKey(const std::string &cert_name) {
  return "";
}

bool isbound(const std::string &par) {
  if ((0 == par.compare("")) || (0 == par.length())) {
    return false;
  }
  else {
    return true;
  }
}
std::vector<uint8_t> fx_generateGenChallenge(void) {
  std::vector<uint8_t> temp = {0};
  return temp;
}
std::vector<uint8_t> f_generateDigestFromBodyType(BodyType *p_BodyType) {
  // get encode value from encvalue
  // push to digest function with SHA-256 encryption
  // push to byte vector and return
  std::vector<uint8_t> temp = {0};
  return temp;
  // return fx_convertOctetstring2Base64Binary(fx_messageDigest("SHA-256", fx_canonicalExi(encvalue(p_BodyType))));
}
std::shared_ptr<DataStructure_Security::iso1Part4_idDigestValueMap>& f_calculateIdDigestMapFromBodyType(BodyType &body)
{
  std::shared_ptr<DataStructure_Security::iso1Part4_idDigestValueMap> DigestMap = std::make_shared<DataStructure_Security::iso1Part4_idDigestValueMap>();

  return DigestMap;
}
void md_CMN_Signature_001(SignatureType &sign, SignedInfoType *signInfo, const std::string &privateKey) {
  sign.Id_isUsed = 0;
  sign.KeyInfo_isUsed = 0;
  sign.Object.arrayLen = 0;
  memcpy(&sign.SignedInfo, signInfo, sizeof(SignedInfoType));
  sign.SignatureValue.Id_isUsed = 0;
  // sign.CONTENT =
  // base := fx_convertOctetstring2Base64Binary(
  // fx_signSignatureInfo("SHA256withECDSA",
  // fx_canonicalExi(encvalue(p_signedInfo)),p_privateKey))
}

SignedInfoType *md_CMN_SignedInfoType_001(const std::string &msgName, const std::vector<uint8_t> &digestKey) {
  static SignedInfoType signedInfoEle;
  signedInfoEle.Id_isUsed = 0;

  std::string algo = "http://www.w3.org/TR/canonical-exi";
  signedInfoEle.CanonicalizationMethod.ANY_isUsed = 0;
  strcpy(signedInfoEle.CanonicalizationMethod.Algorithm.characters, algo.c_str());
  signedInfoEle.CanonicalizationMethod.Algorithm.charactersLen = algo.length();

  algo = "http://www.w3.org/2001/04/xmldsig-more#ecdsa-sha256";
  signedInfoEle.SignatureMethod.ANY_isUsed = 0;
  signedInfoEle.SignatureMethod.HMACOutputLength_isUsed = 0;
  strcpy(signedInfoEle.SignatureMethod.Algorithm.characters, algo.c_str());
  signedInfoEle.SignatureMethod.Algorithm.charactersLen = algo.length();

  signedInfoEle.Reference.arrayLen = 1;
  signedInfoEle.Reference.array[0].Type_isUsed = 0;

  signedInfoEle.Reference.array[0].Id_isUsed = 1;
  std::string temp = fmt::format("{}ReferenceId", msgName);
  strcpy(signedInfoEle.Reference.array[0].Id.characters, temp.c_str());
  signedInfoEle.Reference.array[0].Id.charactersLen = temp.length();

  signedInfoEle.Reference.array[0].URI_isUsed = 1;
  temp = fmt::format("#{}",msgName);
  strcpy(signedInfoEle.Reference.array[0].URI.characters, temp.c_str());
  signedInfoEle.Reference.array[0].URI.charactersLen = temp.length();

  algo = "http://www.w3.org/TR/canonical-exi";
  signedInfoEle.Reference.array[0].Transforms_isUsed = 1;
  strcpy(signedInfoEle.Reference.array[0].Transforms.Transform.array[0].Algorithm.characters, algo.c_str());
  signedInfoEle.Reference.array[0].Transforms.Transform.array[0].Algorithm.charactersLen = algo.length();
  signedInfoEle.Reference.array[0].Transforms.Transform.arrayLen = 1;

  algo = "http://www.w3.org/2001/04/xmlenc#sha256";

  // for (auto &&i=)
  // signedInfoEle.Reference.array[0].DigestValue.bytes
  // reference_list := {
  //   {
  //     transforms := {
  //       transform_list := {
  //         {
  //         embed_values := omit,
  //         algorithm := ,
  //         choice_list := {}
  //         }
  //       }
  //     },
  //     digestMethod := {
  //       embed_values := omit,
  //       algorithm := "http://www.w3.org/2001/04/xmlenc#sha256",
  //       elem_list := {}
  //     },
  //     digestValue := p_digestValue
  //   }
  // }
  return &signedInfoEle;
}