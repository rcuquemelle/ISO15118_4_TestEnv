#include "V2GAppSECCAuthorization.h"
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

TestCases_SECC_Authorization:: TestCases_SECC_Authorization(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_Authorization>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_001"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_002"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_003"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_004"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_005"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_006"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_007"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_008"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_009"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_010"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_011"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_012"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_013"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_014"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_015"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_015));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_016"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_016));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Authorization_017"), &TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_017));
}

TestCases_SECC_Authorization::~ TestCases_SECC_Authorization()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the current SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a valid AuthorizationRes message with
EVSEProcessing 'Ongoing_WaitingForCustomerInteraction' was received before, the
Test System sends another AuthorizationReq message. This message sequence will
be repeated until the authorization has finished or 'V2G_EVCC_Ongoing_Timer' has
expired.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM
4. PIXIT selection: PIXIT_SECC_CMN_AuthorizationOngoing = unknown
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_001()
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
    this->tb->f_SECC_CMN_TB_VTB_Authorization_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with a valid signature, current SessionID, valid GenChallenge and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a valid AuthorizationRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
AuthorizationReq message. This message sequence will be repeated until the
authorization has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_002(fail);
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
message instead of an AuthorizationReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_003()
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
    this->tb->f_SECC_CMN_TB_VTB_Authorization_003();
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
message instead of an AuthorizationReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_003();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the an invalid SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_005()
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
    this->tb->f_SECC_CMN_TB_VTB_Authorization_004();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with a valid signature, invalid SessionID, valid GenChallenge and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_005();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with a valid signature, current SessionID, invalid GenChallenge and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_ChallengeInvalid' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_006();
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
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_008()
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
    this->tb->f_SECC_CMN_TB_VTB_Authorization_007();
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
'V2G_Sequence_Timeout' timer has expired after receiving a PaymentDetailsRes
message with the current SessionID, ResponseCode 'OK', valid GenChallenge and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_007();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with an invalid signature (wrong private key used), current SessionID, valid
GenChallenge and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SignatureError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_008();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with an invalid signature (signed body changed after signature calculation),
current SessionID, valid GenChallenge and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SignatureError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_011()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_009();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with a valid signature, current SessionID, valid GenChallenge and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a valid AuthorizationRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
AuthorizationReq message. This message sequence will be repeated until the
authorization has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certInstall,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_012()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_002(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with a valid signature, current SessionID, valid GenChallenge and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a valid AuthorizationRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
AuthorizationReq message. This message sequence will be repeated until the
authorization has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certUpdate,PIXIT_CMN_CMN_PkiName = PKI_1
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_013()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_002(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the current SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the Authorization
message sequence will be checked (EVSEProcessing = 'Ongoing_WaitingForCustomerInteraction')
until the 'V2G_SECC_Ongoing_Timer' has expired on SUT side.
Test system then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM, PICS_SECC_CMN_EIMDone = v2gAuthorization
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_014()
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
    this->tb->f_SECC_CMN_TB_VTB_Authorization_010();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the current SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the Authorization
message sequence will be checked (EVSEProcessing = 'Ongoing') until the
'V2G_SECC_Ongoing_Timer' has expired on SUT side. Test system then checks that
the SUT terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_CMN_CMN_PkiName = PKI_1,PIXIT_SECC_CMN_AuthorizationOngoing = ongoing
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_015()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_011();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the current SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the Authorization
message sequence will be checked (EVSEProcessing = 'Ongoing') until the
'V2G_SECC_Ongoing_Timer' has expired on SUT side. Test system then checks that
the SUT terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certInstall,PIXIT_CMN_CMN_PkiName = PKI_1, PIXIT_SECC_CMN_AuthorizationOngoing = ongoing
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_016()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_011();
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
1. CONDITION: Test System executes GoodCase procedure and sends an AuthorizationReq message
with the current SessionID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends an AuthorizationRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the Authorization
message sequence will be checked (EVSEProcessing = 'Ongoing') until the
'V2G_SECC_Ongoing_Timer' has expired on SUT side. Test system then checks that
the SUT terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = pnC, PICS_CMN_CMN_PkiName = PKI_1
4. PIXIT selection: PIXIT_SECC_CMN_CertificateHandling = certUpdate,PIXIT_CMN_CMN_PkiName = PKI_1,PIXIT_SECC_CMN_AuthorizationOngoing = ongoing
*/
verdict_val TestCases_SECC_Authorization::TC_SECC_CMN_VTB_Authorization_017()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_PaymentDetails_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_Authorization_011();
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