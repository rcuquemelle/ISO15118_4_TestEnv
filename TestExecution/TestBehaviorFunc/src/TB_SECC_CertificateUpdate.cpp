#include "TB_SECC_CertificateUpdate.h"
#include "Common_Cfg.h"
#include "PreConditions_SECC.h"
#include "PostConditions_SECC.h"
#include "TimerCfg.h"
#include "PIXITCfg.h"
#include "PICSCfg.h"
#include "V2gALMsg.h"
#include "TB_SECC_Msg.h"
#include "TestSystemLogging.h"

using namespace Timer_15118_2::Timer_par_15118_2;
using namespace Timer_15118::Timer_par_15118;
using namespace Pixit_15118_2::PIXIT_15118_2::PIXIT_SECC_Tester;
using namespace Pixit_15118::PIXIT_15118::PIXIT_CMN;
using namespace Pixit_15118::PIXIT_15118::PIXIT_EVCC_Tester;
using namespace Pics_15118::PICS_CMN;
using namespace Pics_15118::PICS_SECC_Tester;
using namespace Pics_15118_2::PICS_15118_2::PICS_CMN;
using namespace Pics_15118_2::PICS_15118_2::PICS_SECC_Tester;
using namespace DataStructure_PIXIT_15118_2;
using namespace urn_iso_15118_2_2013_MsgDataTypes;
using namespace DataStructure_PICS_15118;

// Plug and charge message

TestBehavior_SECC_CertificateUpdate::TestBehavior_SECC_CertificateUpdate(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_CertificateUpdate::~TestBehavior_SECC_CertificateUpdate()
{
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isSignatureOk = true;
  // bool isCertChainOk = false;
  // if (f_checkCertificateService(vc_serviceList))
  // {
  //   X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  //   X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  //   X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  //   vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  //   if (this->mtc->getverdict() == pass)
  //   {
  //     std::string v_EMAID = fx_getEMAID(v_leafCert);
  //     vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //     vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //     BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //         md_SECC_CMN_CertificateUpdateReq_001(
  //             "certificateUpdateReq",
  //             md_CertificateChainType_002(v_leafCert,
  //                                         v_subCert2, v_subCert1),
  //             v_EMAID, vc_x509IssuerName,
  //             vc_x509SerialNumber));
  //     std::string v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_EXPIRES");
  //     Signature aSignature = md_CMN_Signature_001(
  //         md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                   f_generateDigestFromBodyType(
  //                                       myCertificateUpdateBodyType)),
  //         v_privateKey);
  //     this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //     this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(md_CMN_MessageHeaderType_003(
  //                                                                              vc_SessionID, aSignature),
  //                                                                          myCertificateUpdateBodyType));
  //     while(true)
  //     {
  //       if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //                                                               md_CMN_MessageHeaderType_002(vc_SessionID),
  //                                                               md_CMN_BodyType_001(
  //                                                                   mdw_SECC_CMN_CertificateUpdateRes_001(
  //                                                                       m_CMN_sAProvisioningCertificateChain_001(),
  //                                                                       m_CMN_contractSignatureCertChain_001(),
  //                                                                       v_EMAID))))
  //           ->value v_responseMessage
  //) {
  //         this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //         vc_sAProvisioningCertCha = v_responseMessage.body.bodyElement.certificateUpdateRes.sAProvisioningCertificateChain;
  //         vc_contractSignatureCertCha = v_responseMessage.body.bodyElement.certificateUpdateRes.contractSignatureCertChain;
  //         vc_contractSignatureEncryptedPrivateKey = v_responseMessage.body.bodyElement.certificateUpdateRes.contractSignatureEncryptedPrivateKey;
  //         vc_dHpublickey = v_responseMessage.body.bodyElement.certificateUpdateRes.dHpublickey;
  //         vc_eMAID = v_responseMessage.body.bodyElement.certificateUpdateRes.eMAID;
  //         if (this->mtc->getverdict() == pass)
  //         {
  //           Signature authSignature = v_responseMessage.header.signature_;
  //           BodyType certificateUpdateResBodyType = v_responseMessage.body;
  //           isSignatureOk = f_verifySignature(
  //               certificateUpdateResBodyType,
  //               authSignature,
  //               vc_sAProvisioningCertChain.x509Certificate, v_vct);
  //           if (isSignatureOk)
  //           {
  //             vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  //             isCertChainOk = fx_verifyCertChain(vc_sAProvisioningCertChain,
  //                                                vc_v2gRootCert, "CPS");
  //           }
  //           if (isCertChainOk)
  //           {
  //             bool result = fx_checkCertificateValidity(
  //                 vc_contractSignatureCertChain.x509Certificate.tBSCertificate.validity.not_Before,
  //                 vc_contractSignatureCertChain.x509Certificate.tBSCertificate.validity.not_After);
  //             if (not result)
  //             {
  //               this->mtc->setverdict(v_vct, "Invalid Certificate validity was detected.");
  //             }
  //             if (this->mtc->getverdict() == pass)
  //             {
  //               Logging::info(LogTbFnc_ENABLE, "EMAID: " & toString<std::string>(vc_eMAID.base));
  //               result = fx_validateEMAID(vc_eMAID.base);
  //               if (not result)
  //               {
  //                 this->mtc->setverdict(v_vct, "Invalid EMAID syntax was detected.");
  //               }
  //               else
  //               {
  //                 this->mtc->setverdict(pass, "CertificateUpdateRes message was correct.");
  //               }
  //               vc_sharedSecret = fx_calculateSharedSecret("CRT_CONTRACT_LEAF_EXPIRES",
  //                                                          vc_dHpublickey);
  //               vc_contractPrivateKey = fx_decryptContractPrivateKey(vc_sharedSecret,
  //                                                                    vc_contractSignatureEncryptedPrivateKey);
  //               //check contract cert private key with given NEW contract cert (public key)
  //               bool isValidContractPrivateKey = fx_isPrivateKeyValidForCertificate(
  //                   vc_contractPrivateKey,
  //                   vc_contractSignatureCertChain.x509Certificate);
  //               if (not isValidContractPrivateKey)
  //               {
  //                 this->mtc->setverdict(v_vct, "Contract private key does not match the contract certificate");
  //               }
  //               else
  //               {
  //                 Logging::info(LogTbFnc_ENABLE, "VALID contract private key to contract certificate: ",
  //                               isValidContractPrivateKey);
  //               }
  //             }
  //           }
  //           else
  //           {
  //             this->mtc->setverdict(v_vct, "CertChaof the oEMProvisioningCert is not valid.");
  //           }
  //         }
  //       }
  //       if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
  //       {
  //         break;
  //       }
  //       if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
  //       {
  //         break;
  //       }
  //       if (this->cmn->isError())
  //       {
  //         if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //         {
  //           break;
  //         }
  //       }
  //       if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received CertificateUpdateRes  message, but with invalid data content."))
  //       {
  //         break;
  //       }
  //       if (this->cmn->a_SECC_Timeout(v_vct))
  //       {
  //         break;
  //       }
  //     }
  //   }
  // }
  // else
  // {
  //   this->mtc->setverdict(inconc, "Wrong PIXIT selection. No certificate service has been offered.");
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  // this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //     md_CMN_MessageHeaderType_001(vc_SessionID),
  //     md_CMN_BodyType_001(
  //         md_CMN_CMN_ServiceDiscoveryReq_002(omit))));
  // while(true)
  // {
  //   if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //   {
  //     isShutdownOSC = true;
  //     repeat;
  //   }
  //   if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_001(vc_SessionID),
  //       md_CMN_BodyType_001(
  //           mdw_SECC_CMN_ServiceDiscoveryRes_001(
  //               fAILED_SequenceError))))) {
  //     this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //     this->mtc->setverdict(pass, "ServiceDiscoveryRes with responseCode 'fAILED_SequenceError' is successful.");
  //     this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //         e_getPortStatus));
  //     this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //     while(true)
  //     {
  //       if (isShutdownOSC == false)
  //       {
  //         if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //         {
  //           isShutdownOSC = true;
  //           repeat;
  //         }
  //       }
  //       if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //         }
  //         this->mtc->pt_HAL_61851_Internal_Port->clear();
  //         break;
  //       }
  //       if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //       {
  //         break;
  //       }
  //       if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //       {
  //         break;
  //       }
  //     }
  //     break;
  //   }
  //   if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //   {
  //     break;
  //   }
  //   if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //   {
  //     break;
  //   }
  //   if (this->cmn->isError())
  //   {
  //     if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //     {
  //       break;
  //     }
  //   }
  //   if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //   {
  //     break;
  //   }
  //   if (this->cmn->a_SECC_Timeout(fail))
  //   {
  //     break;
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string v_EMAID = fx_getEMAID(v_leafCert);
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_EXPIRES");
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           f_rnd_SessionID(1, 429496), aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(md_CMN_MessageHeaderType_002(?),
  //     md_CMN_BodyType_001(
  //     mdw_SECC_CMN_CertificateUpdateRes_002(
  //     fAILED_UnknownSession))))) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode 'fAILED_UnknownSession' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // timer t_wait;
  // bool isShutdownOSC = false;
  // // Wait until sequence timeout SUT should expire
  // t_wait.start(par_V2G_SECC_Sequence_Timeout -
  //              par_CMN_Transmission_Delay);
  // this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //     e_getPortStatus));
  // while(true)
  // {
  //   if (t_wait.timeout)
  //   {
  //     break;
  //   }
  // }
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  // while(true)
  // {
  //   if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //   {
  //     isShutdownOSC = true;
  //     repeat;
  //   }
  //   if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //   {
  //     if (isShutdownOSC == false)
  //     {
  //       Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //     }
  //     this->mtc->pt_HAL_61851_Internal_Port->clear();
  //     break;
  //   }
  //   if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //   {
  //     break;
  //   }
  //   if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //   {
  //     break;
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string v_EMAID = fx_getEMAID(v_leafCert);
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   // load wrong private key
  //   std::string v_privateKey = fx_loadPrivateKey("CRT_V2G_ROOT_VALID");
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //         md_CMN_MessageHeaderType_002(vc_SessionID),
  //         md_CMN_BodyType_001(
  //             mdw_SECC_CMN_CertificateUpdateRes_002(
  //                 fAILED_SignatureError))))) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode 'fAILED_SignatureError' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string v_EMAID = fx_getEMAID(v_leafCert);
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_EXPIRES");
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   // change id after signature generation
  //   myCertificateUpdateBodyType.bodyElement.certificateUpdateReq.id = "contentChanged";
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //         md_CMN_MessageHeaderType_002(vc_SessionID),
  //         md_CMN_BodyType_001(
  //             mdw_SECC_CMN_CertificateUpdateRes_002(
  //                 fAILED_SignatureError))))) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode 'fAILED_SignatureError' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_007(const std::string &v_config)
{
  // Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // PkiType v_wrongPki = PKI_2;
  // bool isShutdownOSC = false;
  // X509CertificateType v_leafCert;
  // X509CertificateType v_subCert1;
  // X509CertificateType v_subCert2;
  // std::string v_config1 = "WrongSubCertOrder";
  // std::string v_config2 = "WrongPKILeafCert";
  // std::string v_config3 = "WrongPKISub2Cert";
  // std::string v_config4 = "WrongPKISub1Cert";
  // std::string v_config5 = "WrongPKICertChain";
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // if (v_config == v_config1)
  // {
  //   v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  //   v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  //   v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // }
  // else if (v_config == v_config2)
  // {
  //   v_leafCert = fx_loadCertificate(v_wrongPki, "CRT_CONTRACT_LEAF_EXPIRES");
  //   v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  //   v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // }
  // else if (v_config == v_config3)
  // {
  //   v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  //   v_subCert2 = fx_loadCertificate(v_wrongPki, "CRT_MO_SUB2_VALID");
  //   v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // }
  // else if (v_config == v_config4)
  // {
  //   v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  //   v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  //   v_subCert1 = fx_loadCertificate(v_wrongPki, "CRT_MO_SUB1_VALID");
  // }
  // else if (v_config == v_config5)
  // {
  //   v_leafCert = fx_loadCertificate(v_wrongPki, "CRT_CONTRACT_LEAF_EXPIRES");
  //   v_subCert2 = fx_loadCertificate(v_wrongPki, "CRT_MO_SUB2_VALID");
  //   v_subCert1 = fx_loadCertificate(v_wrongPki, "CRT_MO_SUB1_VALID");
  // }
  // else
  // {
  //   this->mtc->setverdict(inconc, "Unknown configuration was detected.");
  // }
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string v_EMAID = fx_getEMAID(v_leafCert);
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_EXPIRES");
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //         md_CMN_MessageHeaderType_002(vc_SessionID),
  //         md_CMN_BodyType_001(
  //             mdw_SECC_CMN_CertificateUpdateRes_002(
  //                 fAILED_CertChainError))))) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode 'fAILED_CertChainError' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_008(const std::string &v_EMAID_Unknown)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // ResponseCodeType v_responseCodeReceived;

  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // std::string v_EMAID = fx_getEMAID(v_leafCert);
  // if (v_EMAID != v_EMAID_Unknown)
  // {
  //   v_EMAID = v_EMAID_Unknown;
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey("CRT_CONTRACT_LEAF_EXPIRES");
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //                                                             md_CMN_MessageHeaderType_002(vc_SessionID),
  //                                                             md_CMN_BodyType_001(
  //                                                                 mdw_SECC_CMN_CertificateUpdateRes_002(
  //                                                                     m_CMN_failedResponseCodeList_002()))))
  //         ->value v_responseMessage) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       v_responseCodeReceived = v_responseMessage.body.bodyElement.certificateUpdateRes.responseCode;
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode '" &
  //                            toString<ResponseCodeType>(v_responseCodeReceived) &
  //                            "' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  // else
  // {
  //   this->mtc->setverdict(inconc, "Unknown EMAID was valid for the Contract Leaf Certificate.");
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_009(const std::string &v_certName)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // ResponseCodeType v_responseCodeReceived;

  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCertUnused = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_EXPIRES");
  // std::string v_EMAID = fx_getEMAID(v_leafCertUnused);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, v_certName);
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // std::string v_EMAID_Unknown = fx_getEMAID(v_leafCert);
  // if (v_EMAID != v_EMAID_Unknown)
  // {
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey(v_certName);
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //                                                             md_CMN_MessageHeaderType_002(vc_SessionID),
  //                                                             md_CMN_BodyType_001(
  //                                                                 mdw_SECC_CMN_CertificateUpdateRes_002(
  //                                                                     m_CMN_failedResponseCodeList_002()))))
  //         ->value v_responseMessage) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       v_responseCodeReceived = v_responseMessage.body.bodyElement.certificateUpdateRes.responseCode;
  //       this->mtc->setverdict(pass, "CertificateUpdateRes with responseCode '" &
  //                            toString<ResponseCodeType>(v_responseCodeReceived) &
  //                            "' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  // else
  // {
  //   this->mtc->setverdict(inconc, "Unknown EMAID was valid for the Contract Leaf Certificate.");
  // }
  return this->mtc->getverdict();
}

verdict_val TestBehavior_SECC_CertificateUpdate::f_SECC_CMN_TB_VTB_CertificateUpdate_010(const std::string &v_certName, const std::vector<responseCodeType> &v_responseCodeList)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]", __FUNCTION__));
  // bool isShutdownOSC = false;
  // ResponseCodeType v_responseCodeReceived;

  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(0, 0);
  // f_SECC_changeValidDutyCycleRange(100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, v_certName);
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  // vc_v2gRootCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_V2G_ROOT_VALID");
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string v_EMAID = fx_getEMAID(v_leafCert);
  //   vc_x509IssuerName = vc_v2gRootCert.tBSCertificate.issuer;
  //   vc_x509SerialNumber = hex2int(str2hex(vc_v2gRootCert.tBSCertificate.serial_Number));
  //   BodyType myCertificateUpdateBodyType = md_CMN_BodyType_001(
  //       md_SECC_CMN_CertificateUpdateReq_001(
  //           "certificateUpdateReq",
  //           md_CertificateChainType_002(v_leafCert,
  //                                       v_subCert2, v_subCert1),
  //           v_EMAID, vc_x509IssuerName,
  //           vc_x509SerialNumber));
  //   std::string v_privateKey = fx_loadPrivateKey(v_certName);
  //   Signature aSignature = md_CMN_Signature_001(
  //       md_CMN_SignedInfoType_001("certificateUpdateReq",
  //                                 f_generateDigestFromBodyType(
  //                                     myCertificateUpdateBodyType)),
  //       v_privateKey);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_CertificateUpdateReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_003(
  //           vc_SessionID, aSignature),
  //       myCertificateUpdateBodyType));
  //   while(true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //       repeat;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //                                                             md_CMN_MessageHeaderType_002(vc_SessionID),
  //                                                             md_CMN_BodyType_001(
  //                                                                 mdw_SECC_CMN_CertificateUpdateRes_002(
  //                                                                     v_responseCode))))
  //         ->value v_responseMessage) {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       v_responseCodeReceived = v_responseMessage.body.bodyElement.certificateUpdateRes.responseCode;
  //       this->mtc->setverdict(pass, fmt::format("CertificateUpdateRes with responseCode ' {}' is successful.", toString<ResponseCodeType>(v_responseCodeReceived)));
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001(
  //           e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while(true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
  //             repeat;
  //           }
  //         }
  //         if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
  //         {
  //           if (isShutdownOSC == false)
  //           {
  //             Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
  //           }
  //           this->mtc->pt_HAL_61851_Internal_Port->clear();
  //           break;
  //         }
  //         if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
  //         {
  //           break;
  //         }
  //         if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
  //         {
  //           break;
  //         }
  //       }
  //       break;
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(fail, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(fail, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(fail, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received CertificateUpdateRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(fail))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}