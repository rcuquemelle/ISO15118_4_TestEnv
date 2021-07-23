#include "V2GAppSECCSessionSetup.h"
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

TestCases_SECC_SessionSetup::TestCases_SECC_SessionSetup(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_SessionSetup>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SessionSetup_001"), &TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SessionSetup_002"), &TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SessionSetup_003"), &TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SessionSetup_004"), &TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_001"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_002"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_003"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_004"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_005"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionSetup_006"), &TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_001"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_002"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_003"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_004"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_005"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionSetup_006"), &TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_006));
}

TestCases_SECC_SessionSetup::~TestCases_SECC_SessionSetup()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a SessionSetupReq message with
SessionID '0', valid EvccID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with a new
SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocol_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_001(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a valid ServiceDiscoveryReq
message instead of a SessionSetupReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocol_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_002();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and waits until the
'V2G_Sequence_Timeout' timer has expired after receiving a
SupportedAppProtocolResmessage with ResponseCode 'OK_SuccessfulNegotiation', a
valid schema and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocol_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_003();
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and waits until the
'V2G_SECC_CommunicationSetup_Timeout' timer has expired after receiving a
SupportedAppProtocolRes message with ResponseCode 'OK_SuccessfulNegotiation', a
valid schema and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_CMN_VTB_SessionSetup_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocol_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_004();
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
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with the previous sessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
previous SessionID, ResponseCode 'OK_OldSessionJoined', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_005(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message the with a new SessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(false);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with a SessionID '0', valid EvccID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(true);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with the previous sessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
previous SessionID, ResponseCode 'OK_OldSessionJoined', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_005(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message the with a new SessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(false);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with a SessionID '0', valid EvccID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := aC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_AC_VTB_SessionSetup_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(true);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with the previous sessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
previous SessionID, ResponseCode 'OK_OldSessionJoined', valid EvseId and all 245
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_005(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message the with a new SessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(false);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp' Test
System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with a SessionID '0', valid EvccID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PICS_CMN_CMN_WakeUp);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(true);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with the previous sessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
previous SessionID, ResponseCode 'OK_OldSessionJoined', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_005(fail);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message the with a new SessionID, valid EvccID and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(false);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: Test System executes GoodCase procedure and initiates a paused V2G communication
session by sending a SessionStopReq message with the current SessionID,
ChargingSession 'Pause' and all additional mandatory parameters. After receipt
of a valid SessionStopRes message, Test System waits for termination of the
logical network by the SUT. Furthermore Test System checks that the SUT turns
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
SessionSetupReq message with a SessionID '0', valid EvccID and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the
current SessionID, ResponseCode 'OK_NewSessionEstablished', valid EvseId and all
additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode := dC, PICS_SECC_CMN_Pause := true,
PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionSetup::TC_SECC_DC_VTB_SessionSetup_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_SessionStop_001(v_HAL_61851_Listener);
  if (preConVerdict == pass)
  {
    map(this->mtc->pt_SLAC_Port, this->stc->pt_SLAC_Port);
    this->cmn->f_SECC_startSleepingPhase(PIXIT_CMN_CMN_WakeUp - 5.0);
  }
  if (preConVerdict == pass)
  {
    unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
    preConVerdict = this->pre->f_SECC_CMN_PR_SupportedAppProtocolPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionSetup_006(true);
  }
  else
  {
    Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
  }
  //------------- Post Conditions--------------------------------------------------------
  this->mtc->tc_V2G_EVCC_CommunicationSetup_Timer->stop();
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}
