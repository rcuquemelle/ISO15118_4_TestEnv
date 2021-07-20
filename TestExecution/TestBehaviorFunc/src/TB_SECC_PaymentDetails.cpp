#include "TB_SECC_PaymentDetails.h"
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

TestBehavior_SECC_PaymentDetails::TestBehavior_SECC_PaymentDetails(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> &_system)
    : mtc(_mtc), systemSECC(_system)
{
  this->cmn = std::make_shared<TestBehavior_SECC_CommonBehavior>(this->mtc);
}

TestBehavior_SECC_PaymentDetails::~TestBehavior_SECC_PaymentDetails()
{
}

verdict_val TestBehavior_SECC_PaymentDetails::f_SECC_CMN_TB_VTB_PaymentDetails_001(verdict_val v_vct)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  // if (!(isbound(vc_contractSignatureCertChain)))
  // {
  //   X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_VALID");
  //   X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  //   X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  //   vc_contractSignatureCertChain = md_CertificateChainType_002(v_leafCert,
  //                                                               v_subCert2, v_subCert1)
  // }
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string vc_EMAID = fx_getEMAID(vc_contractSignatureCertChain.x509Certificate);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_001(vc_SessionID),
  //       md_CMN_BodyType_001( md_SECC_CMN_PaymentDetailsReq_001(vc_EMAID, vc_contractSignatureCertChain))));
  //   while (true)
  //   {
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //     md_CMN_MessageHeaderType_001(vc_SessionID),
  //     md_CMN_BodyType_001(
  //     md_SECC_CMN_PaymentDetailsRes_001(?,?)))))
  //     {
  //       vc_GenChallenge = v_responseMessage.body.bodyElement.paymentDetailsRes.genChallenge;
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "PaymentDetailsRes message was correct.");
  //     }
  //     if (this->cmn->a_SECC_TCPConnection_Status_Listener(v_vct, "TCP connection was misleadingly terminated by the SUT."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Unexpected_V2G_Message(v_vct, "Unexpected V2G message was received."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->isError())
  //     {
  //       if (this->cmn->a_SECC_Unexpected_Message(v_vct, "SupportedAppProtocolRes received, but V2G_Message was expected."))
  //       {
  //         break;
  //       }
  //     }
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(v_vct, "Received PaymentDetailsRes message, but with invalid data content."))
  //     {
  //       break;
  //     }
  //     if (this->cmn->a_SECC_Timeout(v_vct))
  //     {
  //       break;
  //     }
  //   }
  // }
  return this->mtc->getverdict();
}
verdict_val TestBehavior_SECC_PaymentDetails::f_SECC_CMN_TB_VTB_PaymentDetails_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  // f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq);
  // this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //     md_CMN_MessageHeaderType_001(vc_SessionID),
  //     md_CMN_BodyType_001( md_CMN_CMN_ServiceDiscoveryReq_002(omit))));
  // while (true)
  // {
  //   if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //   {
  //     isShutdownOSC = true;
  //   }
  //   if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //           md_CMN_MessageHeaderType_001(vc_SessionID),
  //           md_CMN_BodyType_001( mdw_SECC_CMN_ServiceDiscoveryRes_001( fAILED_SequenceError)))))
  //   {
  //     this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //     this->mtc->setverdict(pass, "ServiceDiscoveryRes with responseCode 'fAILED_SequenceError' is successful.");
  //     this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001( e_getPortStatus));
  //     this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //     while (true)
  //     {
  //       if (isShutdownOSC == false)
  //       {
  //         if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //         {
  //           isShutdownOSC = true;
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
  //   if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentDetailsRes message, but with invalid data content."))
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
verdict_val TestBehavior_SECC_PaymentDetails::f_SECC_CMN_TB_VTB_PaymentDetails_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  // bool isShutdownOSC = false;
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  // f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // if (not(isbound(vc_contractSignatureCertChain)))
  // {
  //   X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_CONTRACT_LEAF_VALID");
  //   X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB2_VALID");
  //   X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, "CRT_MO_SUB1_VALID");
  //   vc_contractSignatureCertChain = md_CertificateChainType_002(v_leafCert, v_subCert2, v_subCert1)
  // }
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string vc_EMAID = fx_getEMAID(vc_contractSignatureCertChain.x509Certificate);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_001( f_rnd_SessionID(1, 429496)),
  //       md_CMN_BodyType_001( md_SECC_CMN_PaymentDetailsReq_001(vc_EMAID, vc_contractSignatureCertChain))));
  //   while (true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //     md_CMN_MessageHeaderType_001(?),
  //     md_CMN_BodyType_001( mdw_SECC_CMN_PaymentDetailsRes_002( fAILED_UnknownSession)))))
  //     {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       this->mtc->setverdict(pass, "PaymentDetailsRes with responseCode 'fAILED_UnknownSession' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001( e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while (true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
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
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentDetailsRes message, but with invalid data content."))
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
verdict_val TestBehavior_SECC_PaymentDetails::f_SECC_CMN_TB_VTB_PaymentDetails_004()
{
  std::shared_ptr<PATimer> t_wait = this->mtc->pt_TimerManager->createTimer("local", 5);
  // bool isShutdownOSC = false;
  // // Wait until sequence timeout SUT should expire
  // t_wait->start(par_V2G_SECC_Sequence_Timeout - par_CMN_Transmission_Delay);
  // this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001( e_getPortStatus));
  // while (true)
  // {
  //   if (t_wait->timeout())
  //   {
  //     break;
  //   }
  // }
  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  // f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  // while (true)
  // {
  //   if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //   {
  //     isShutdownOSC = true;
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
verdict_val TestBehavior_SECC_PaymentDetails::f_SECC_CMN_TB_VTB_PaymentDetails_005(
  const std::string &v_certName, const std::string &v_sub2CertName, const std::string &v_sub1CertName, responseCodeType v_responseCode)
{
  Logging::info(LogTc_ENABLE, fmt::format("[TB][{}]",__FUNCTION__));
  // bool isShutdownOSC = false;
  // responseCodeType v_responseCodeReceived;

  // f_SECC_setIsConfirmationFlagDC();
  // f_SECC_changeValidFrequencyRange(this->systemSECC, 0, 0);
  // f_SECC_changeValidDutyCycleRange(this->systemSECC, 100, 100);
  // deactivate(vc_Default_IEC_61851_ListenerBehavior);
  // X509CertificateType v_leafCert = fx_loadCertificate(PICS_CMN_CMN_PkiName, v_certName);
  // X509CertificateType v_subCert2 = fx_loadCertificate(PICS_CMN_CMN_PkiName, v_sub2CertName);
  // X509CertificateType v_subCert1 = fx_loadCertificate(PICS_CMN_CMN_PkiName, v_sub1CertName);
  // if (this->mtc->getverdict() == pass)
  // {
  //   std::string vc_EMAID = fx_getEMAID(v_leafCert);
  //   this->mtc->tc_V2G_EVCC_Msg_Timer->start(par_V2G_EVCC_Msg_Timeout_PaymentDetailsReq);
  //   this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_001(vc_SessionID),
  //       md_CMN_BodyType_001( md_SECC_CMN_PaymentDetailsReq_001(vc_EMAID,
  //         md_CertificateChainType_002(v_leafCert, v_subCert2, v_subCert1)))));
  //   while (true)
  //   {
  //     if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //     {
  //       isShutdownOSC = true;
  //     }
  //     if (this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->receive(md_CMN_V2G_Message_001(
  //       md_CMN_MessageHeaderType_001( vc_SessionID),
  //       md_CMN_BodyType_001( mdw_SECC_CMN_PaymentDetailsRes_002( v_responseCode)))))
  //     {
  //       this->mtc->tc_V2G_EVCC_Msg_Timer->stop();
  //       v_responseCodeReceived = v_responseMessage.body.bodyElement.paymentDetailsRes.responseCode;
  //       this->mtc->setverdict(pass, "PaymentDetailsRes with responseCode '" &
  //                                       toString<responseCodeType>(v_responseCodeReceived) &
  //                                       "' is successful.");
  //       this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port->send(md_CMN_CMN_tcpTlsStatusReq_001( e_getPortStatus));
  //       this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
  //       while (true)
  //       {
  //         if (isShutdownOSC == false)
  //         {
  //           if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
  //           {
  //             isShutdownOSC = true;
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
  //     if (this->cmn->a_SECC_Unexpected_Message_Content(fail, "Received PaymentDetailsRes message, but with invalid data content."))
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