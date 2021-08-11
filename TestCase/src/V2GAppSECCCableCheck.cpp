#include "V2GAppSECCCableCheck.h"
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

TestCases_SECC_CableCheck::TestCases_SECC_CableCheck(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_CableCheck>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_001"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_002"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_003"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_004"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_005"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_006"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_007"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_CableCheck_008"), &TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_008));
}

TestCases_SECC_CableCheck::~TestCases_SECC_CableCheck()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure, signals CP State C and sends a
CableCheckReq message with the current SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a CableCheckRes message with EVSEProcessing
'Ongoing' was received before, the Test System sends another CableCheckReq
message. This message sequence will be repeated until the cable check of the SUT
has finished or 'V2G_EVCC_CableCheck_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_CMN_EvStateInChargeProgress = C
4. PIXIT selection: PIXIT_SECC_DC_CableCheckOngoing == unknown
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, signals CP State D and sends a
CableCheckReq message with the current SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. If a CableCheckRes message with EVSEProcessing
'Ongoing' was received before, the Test System sends another CableCheckReq
message. This message sequence will be repeated until the cable check of the SUT
has finished or 'V2G_EVCC_CableCheck_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_CMN_EvStateInChargeProgress = D
4. PIXIT selection: PIXIT_SECC_DC_CableCheckOngoing == unknown
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, signals CP State C or D and sends a
valid ServiceDiscoveryReq message instead of a CableCheckReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_002(v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure, signals CP State C or D and sends a
CableCheckReq message with an invalid SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with a valid
SessionID, ResponseCode 'FAILED_UnknownSession' and all additional mandatory
parameters and terminates the V2G communication session by closing the TCP
connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_003(v_HAL_61851_Listener);
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
ChargeParameterDiscoveryRes message with the current SessionID, ResponseCode
'OK', EVSEProcessing 'Finished', a valid scheduleList and all additional
mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_004();
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
1. CONDITION: Test System executes GoodCase procedure, signals CP State D and sends a
CableCheckReq message with the current SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the CableCheck
message sequence will be checked until the cable check of the SUT has finished
or 'V2G_EVCC_CableCheck_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_CMN_EvStateInChargeProgress = C
4. PIXIT selection: PIXIT_SECC_DC_CableCheckOngoing == ongoing
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, signals CP State D and sends a
CableCheckReq message with the current SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with the
current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished' and all
additional mandatory parameters. Furthermore the repetition of the CableCheck
message sequence will be checked until the cable check of the SUT has finished
or 'V2G_EVCC_CableCheck_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,PICS_SECC_CMN_EvStateInChargeProgress = D
4. PIXIT selection: PIXIT_SECC_DC_CableCheckOngoing == ongoing
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_001(v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, signals no CP State C or D and sends a
CableCheckReq message with the current SessionID and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a CableCheckRes message with the
current SessionID, ResponseCode 'FAILED' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_CableCheck::TC_SECC_DC_VTB_CableCheck_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_CableCheck_005();
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