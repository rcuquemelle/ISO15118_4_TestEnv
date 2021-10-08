#include "V2GAppSECCSessionStop.h"
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

TestCases_SECC_SessionStop::TestCases_SECC_SessionStop(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_SessionStop>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionStop_001"), &TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionStop_002"), &TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionStop_003"), &TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionStop_004"), &TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_001"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_002"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_003"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_004"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_005"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_006"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_007"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_008"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_009"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_SessionStop_010"), &TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_SessionStop_011"), &TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_011));
}
TestCases_SECC_SessionStop::~TestCases_SECC_SessionStop()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
the current SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
Furthermore Test System checks that the SUT terminates the data link connection
within 'par_TP_match_leave'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, fail);
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
message instead of a SessionStopReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
an invalid SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with a valid
SessionID, ResponseCode 'FAILED_UnknownSession' and all additional mandatory
parameters and terminates the V2G communication session by closing the TCP
connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_003(iso1Part4_ChargingSessionType::terminate);
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
'V2G_Sequence_Timeout' timer has expired after receiving a PowerDeliveryRes
message with the current SessionID, ResponseCode 'OK' and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_004();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
the current SessionID, ChargingSession 'Terminate' and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
Furthermore Test System checks that the SUT terminates the data link connection
within 'par_TP_match_leave'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = false
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
the current SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
Furthermore Test System checks that the SUT terminates the data link connection
within 'par_TP_match_leave'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, fail);
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
message instead of a SessionStopReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = false
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
an invalid SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with a valid
SessionID, ResponseCode 'FAILED_UnknownSession' and all additional mandatory
parameters and terminates the V2G communication session by closing the TCP
connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = false
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_003(iso1Part4_ChargingSessionType::terminate);
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
'V2G_Sequence_Timeout' timer has expired after receiving a PowerDeliveryRes
message with the current SessionID, ResponseCode 'OK' and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = false
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, true);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_004();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
the current SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters without signaling CP State B before.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with the
current SessionID, ResponseCode 'FAILED' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = false
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStop_001(v_HAL_61851_Listener, false);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_005(iso1Part4_ChargingSessionType::terminate);
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
message instead of a SessionStopReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a SessionStopReq message with
an invalid SessionID, ChargingSession 'Terminate' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a SessionStopRes message with a valid
SessionID, ResponseCode 'FAILED_UnknownSession' and all additional mandatory
parameters and terminates the V2G communication session by closing the TCP
connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_003(iso1Part4_ChargingSessionType::terminate);
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
'V2G_Sequence_Timeout' timer has expired after receiving a PowerDeliveryRes
message with the current SessionID, ResponseCode 'OK' and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_WeldingDetection_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_004();
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
1. CONDITION: Test System executes aging
2. EXPECTED: Test System then checks aging
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_DC_WeldingDetection = true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_DC_VTB_SessionStop_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_WeldingDetection_002(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes aging
2. EXPECTED: Test System then checks aging
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SessionStop::TC_SECC_AC_VTB_SessionStop_011()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStop_003(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SessionStop_001(iso1Part4_ChargingSessionType::terminate, v_HAL_61851_Listener, fail);
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