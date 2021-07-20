#include "V2GAppSECCCertificateUpdate.h"
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

TestCases_SECC_CertificateUpdate::TestCases_SECC_CertificateUpdate(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_CertificateUpdate>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_001"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_002"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_003"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_004"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_005"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_006"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_007"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_008"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_009"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_010"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_011"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_012"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_013"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_014"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_015"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_015));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_016"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_016));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_CertificateUpdate_017"), &TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_017));
}

TestCases_SECC_CertificateUpdate::~TestCases_SECC_CertificateUpdate()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, contract certificate chain, EMAID and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with a
valid signature, current SessionID, ResponseCode 'OK', SAProvisioning
certificate chain, contract certificate chain,
ContractSignatureEncryptedPrivateKey, DHpublickey, EMAID and all additional
mandatory parameters.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_001()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_001(fail);
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
message instead of a CertificateUpdateReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_002()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, invalid SessionID, contract certificate chain, valid
EMAID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_003()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_003();
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
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_004()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_004();
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with an invalid signature (wrong private key used), current SessionID, valid
EMAID contract certificate chain, valid EMAID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_SignatureError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1360
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_005()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_005();
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with an invalid signature (signed body changed after signature calculation),
current SessionID, contract certificate chain, valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_SignatureError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_006()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_006();
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Order of Sub CAs is inverted), valid EMAID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertChainError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,361PICS_CertificateHandling = certUpdate, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_007()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_007("WrongSubCertOrder");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Leaf Certificate from wrong PKI is selected), valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertChainError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_008()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_007("WrongPKILeafCert");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Sub2 Certificate from wrong PKI is selected), valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertChainError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_009()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_007("WrongPKISub2Cert");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Sub1 Certificate from wrong PKI is selected), valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertChainError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_010()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_007("WrongPKISub1Cert");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Certificate chain from wrong PKI is selected), valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertChainError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_011()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_007("WrongPKICertChain");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, contract certificate chain, wrong
EMAID (BodyType CertificateUpdateReq) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED', 'FAILED_NoCertificateAvailable' or
'FAILED_ContractCanceled' and all additional mandatory parameters and terminates
the V2G communication session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_012()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_008("DE1ABCD2EF357B");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, contract certificate chain, invalid
EMAID (BodyType CertificateUpdateReq) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED', 'FAILED_NoCertificateAvailable' or
'FAILED_ContractCanceled' and all additional mandatory parameters and terminates
the V2G communication session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_013()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_008("Invalid_EMAID_");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, contract certificate chain, wrong
EMAID (contract certificate) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED', 'FAILED_NoCertificateAvailable' or
'FAILED_ContractCanceled' and all additional mandatory parameters and terminates
the V2G communication session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_014()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_009("CRT_CONTRACT_LEAF_WRONG_EMAID");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, contract certificate chain, invalid
EMAID 365 (contract certificate) and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED', 'FAILED_NoCertificateAvailable' or
'FAILED_ContractCanceled' and all additional mandatory parameters and terminates
the V2G communication session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_015()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_009("CRT_CONTRACT_LEAF_INVALID_EMAID");
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Expired), valid EMAID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED_CertificateExpired' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_016()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_010("CRT_CONTRACT_LEAF_EXPIRED", {(responseCodeType)iso1Part4_ResponseCodeType::fAILED_CertificateExpired});
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
1. CONDITION: Test System executes GoodCase procedure and sends a CertificateUpdateReq message
with a valid signature, current SessionID, invalid contract certificate chain
(Invalid content ‐> Country name was set), valid EMAID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a CertificateUpdateRes message with
the current SessionID, ResponseCode 'FAILED' or 'FAILED_NoCertificateAvailable'
and all additional mandatory parameters and terminates the V2G communication
session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC,PICS_CertificateHandling = certUpdate,
PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_CertificateUpdate::TC_SECC_CMN_VTB_CertificateUpdate_017()
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
    this->tb->f_SECC_CMN_TB_VTB_CertificateUpdate_010("CRT_CONTRACT_LEAF_INVALID_CONTENT",
      { (responseCodeType)iso1Part4_ResponseCodeType::oK,
        (responseCodeType)iso1Part4_ResponseCodeType::fAILED_NoCertificateAvailable});
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