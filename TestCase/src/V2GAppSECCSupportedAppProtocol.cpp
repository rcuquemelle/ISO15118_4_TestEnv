#include "V2GAppSECCSupportedAppProtocol.h"
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

TestCases_SECC_SupportedAppProtocol::TestCases_SECC_SupportedAppProtocol(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_SupportedAppProtocol>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_001"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_002"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_003"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_004"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_005"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SupportedAppProtocol_006"), &TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_006));
}

TestCases_SECC_SupportedAppProtocol::~TestCases_SECC_SupportedAppProtocol()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a SupportedAppProtocolReq
message with a list of valid AppProtocols including ISO namespace and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SupportedAppProtocolRes message
with ResponseCode 'OK_SuccessfulNegotiation' or
'OK_SuccessfulNegotiationWithMinorDeviation' and all additional mandatory
parameters.
3. PICS selection: 
4. PIXIT selection: PIXIT_SECC_CMN_TLS = true
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, pass, fail);
    this->tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_001(fail);
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SupportedAppProtocolReq
message with an invalid ISO namespace and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SupportedAppProtocolRes message
with ResponseCode 'FAILED_NoNegotiation' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: 
4. PIXIT selection: 
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, pass, fail);
    this->tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_002(fail);
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
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
'V2G_Sequence_Timeout' timer has expired after receiving a SDP response message
with valid security option, 'transportProtocol' equals to '0x00'H and a valid
port and IP address.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: 
4. PIXIT selection: 
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, pass, fail);
    this->tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_003();
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SupportedAppProtocolReq
message with a list of valid AppProtocols including ISO namespace and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SupportedAppProtocolRes message
with ResponseCode 'OK_SuccessfulNegotiation' or
'OK_SuccessfulNegotiationWithMinorDeviation' and all additional mandatory
parameters.
3. PICS selection: PICS_CMN_CMN_IdentificationMode = eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS = false
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, pass, fail);
    this->tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_001(fail);
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
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
'V2G_SECC_CommunicationSetup_Timeout' timer has expired on SUT side
2. EXPECTED: Test System then checks that the SUT stops waiting for establishing the TCP/TLS
connection and does not respond to a TCP/TLS handshake request.
3. PICS selection: 
4. PIXIT selection: 
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  while(true)
  {
    if (this->mtc->tc_V2G_SECC_CommunicationSetup_Timer->timeout()){
      break;
    }
    if (this->mtc->pt_V2G_UDP_SDP_Port->receive())
    {
      this->mtc->setverdict(fail, "No SDP message was expected.");
    }
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, fail, pass);
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
1. CONDITION: Test System executes GoodCase procedure and sends a SupportedAppProtocolReq
message with a list of valid AppProtocols (VersionNumberMinor does not match
VersionNumberMinor of the SUT) including ISO namespace and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SupportedAppProtocolRes message
with ResponseCode 'OK_SuccessfulNegotiationWithMinorDeviation' and all
additional mandatory parameters.
3. PICS selection: 
4. PIXIT selection: PIXIT_SECC_CMN_VersionNumberMinor
*/
verdict_val TestCases_SECC_SupportedAppProtocol::TC_SECC_CMN_VTB_SupportedAppProtocol_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Binding_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->cfg->f_SECC_CMN_PR_InitConfiguration_002(this->stc, pass, fail);
    this->tb->f_SECC_CMN_TB_VTB_SupportedAppProtocol_004();
    this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
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