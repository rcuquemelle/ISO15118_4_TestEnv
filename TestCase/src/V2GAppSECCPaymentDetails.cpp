#include "V2GAppSECCPaymentDetails.h"
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

TestCases_SECC_PaymentDetails::TestCases_SECC_PaymentDetails(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_PaymentDetails>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_001"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_002"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_003"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_004"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_005"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_006"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_007"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_008"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_009"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_PaymentDetails_010"), &TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_010));
}

TestCases_SECC_PaymentDetails::~TestCases_SECC_PaymentDetails()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, contract certificate chain and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'OK', valid GenChallenge and all additional
mandatory parameters.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_001(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, contract certificate chain and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'OK', valid GenChallenge and all additional
mandatory parameters.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certInstall,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_CertificateInstallation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_001(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, contract certificate chain and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'OK', valid GenChallenge and all additional
mandatory parameters.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certUpdate,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_CertificateUpdate_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_001(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a valid ServiceDiscoveryReq
message instead of a PaymentDetailsReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_002();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with an invalid SessionID, valid EMAID, contract certificate chain and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_003();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and waits until the
'V2G_Sequence_Timeout' timer has expired after receiving a
PaymentServiceSelectionRes message with the current SessionID, ResponseCode 'OK'
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_004();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, invalid contract certificate chain
(Expired) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'FAILED_CertificateExpired' and all additional
mandatory parameters and terminates the V2G communication session by closing the
269 TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_005("CRT_CONTRACT_LEAF_EXPIRED",
      "CRT_MO_SUB2_VALID", "CRT_MO_SUB1_VALID", (responseCodeType)iso1Part4_ResponseCodeType::fAILED_CertificateExpired);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, invalid contract certificate chain
(Invalid content ‐>Country name was set) and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'FAILED', 'fAILED_NoCertificateAvailable' or
'fAILED_CertificateNotAllowedAtThisEVSE' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    // fAILED, fAILED_NoCertificateAvailable, fAILED_CertificateNotAllowedAtThisEVSE
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_005("CRT_CONTRACT_LEAF_INVALID_CONTENT",
      "CRT_MO_SUB2_VALID", "CRT_MO_SUB1_VALID",
        (responseCodeType)iso1Part4_ResponseCodeType::fAILED_NoCertificateAvailable);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, invalid contract certificate chain
(Expired 270 issuer Sub CA 1) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'FAILED', 'fAILED_NoCertificateAvailable' or
'fAILED_CertificateNotAllowedAtThisEVSE' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_005( "CRT_CONTRACT_LEAF_EXPIRED_ISSUER_SUB1",
      "CRT_MO_SUB2_EXPIRED", "CRT_MO_SUB1_VALID",
        (responseCodeType)iso1Part4_ResponseCodeType::fAILED_CertificateNotAllowedAtThisEVSE);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a PaymentDetailsReq message
with the current SessionID, valid EMAID, invalid contract certificate chain
(Expired issuer Sub CA 2) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PaymentDetailsRes message with the
current SessionID, ResponseCode 'FAILED', 'fAILED_NoCertificateAvailable' or
'fAILED_CertificateNotAllowedAtThisEVSE' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = _none, PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_PaymentDetails::TC_SECC_CMN_VTB_PaymentDetails_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentServiceSelection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PaymentDetails_005(
      "CRT_CONTRACT_LEAF_EXPIRED_ISSUER_SUB2",
        "CRT_MO_SUB2_VALID", "CRT_MO_SUB1_EXPIRED",
          (responseCodeType)iso1Part4_ResponseCodeType::fAILED_CertificateNotAllowedAtThisEVSE);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}