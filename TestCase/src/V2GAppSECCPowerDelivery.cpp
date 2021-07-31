#include "V2GAppSECCPowerDelivery.h"
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
using namespace urn_iso_15118_2_2013_MsgDataTypes;

TestCases_SECC_PowerDelivery::TestCases_SECC_PowerDelivery(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_PowerDelivery>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_001"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_002"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_003"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_004"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_005"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_006"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_007"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_008"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_009"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_010"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_011"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_012"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_013"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_PowerDelivery_014"), &TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_001"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_002"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_003"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_004"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_005"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_006"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_007"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_008"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_009"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_010"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_011"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_012"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_013"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_014"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_015"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_015));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_016"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_016));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_017"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_017));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_018"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_018));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_019"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_019));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_020"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_020));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_PowerDelivery_021"), &TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_021));
}

TestCases_SECC_PowerDelivery::~TestCases_SECC_PowerDelivery()
{
}


/**
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
the current SessionID, ChargeProgress 'Start_', valid charging profile and
TupleID and all additional mandatory parameters and signals CP State C.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC,PICS_SECC_CMN_EvStateInChargeProgress = C
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
the current SessionID, ChargeProgress 'Start_' and all additional mandatory
parameters and signals CP State D.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC,PICS_SECC_CMN_EvStateInChargeProgress = D
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure and initiates a renegotiation by sending
a PowerDeliveryReq message with the current SessionID, ChargeProgress
'Renegotiate' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication <PICS_CMN_CMN_LoopCounter
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargingStatusOrMeteringReceiptRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, initiates a renegotiation and sends a
PowerDeliveryReq message with the current SessionID, ChargeProgress 'Start_' and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication <PICS_CMN_CMN_LoopCounter
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscoveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, fail);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
the current SessionID, ChargeProgress 'Stop_' and all additional mandatory
parameters and signals CP State B.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, fail);
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
message instead of a PowerDeliveryReq message with chargeProgressType 'Start_'.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_002(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener);
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
message instead of a PowerDeliveryReq message with chargeProgressType 'Stop_'.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_002(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
an invalid SessionID, ChargeProgress 'Start_', valid charging profile and
TupleID and all additional mandatory parameters and signals CP State C or D.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_002(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
an invalid SessionID, ChargeProgress 'Stop_' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
the current SessionID, ChargeProgress 'Start_', invalid charging profile
(>EVSEMaximumPowerLimit), valid TupleID and all additional mandatory parameters
and signals CP State C or D.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED_ChargingProfileInvalid' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_004(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure, sends a PowerDeliveryReq message with
the current SessionID, ChargeProgress 'Start_', valid charging profile, invalid
TupleID and all additional mandatory parameters and signals CP State C or D.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED_TariffSelectionInvalid' and all
additional mandatory parameters and terminates the V2G communication session
by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_011()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_005(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener);
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
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_012()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PowerDelivery_001();
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
'V2G_Sequence_Timeout' timer has expired after receiving a valid
ChargingStatusRes or MeteringReceipt message.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_013()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargingStatusOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PowerDelivery_001();
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Renegotiate' and all additional
mandatory parameters but no PowerDeliveryReq with ChargeProgress 'Start' was
sent before.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_AC_VTB_PowerDelivery_014()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_ChargeParameterDiscovery_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_PowerDelivery_006(v_HAL_61851_Listener);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Start_', valid charging profile and
TupleID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, false, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Stop_' and all additional mandatory
parameters. Furthermore Test System signals CP State B after received valid
PowerDeliveryRes message.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
message instead of a PowerDeliveryReq message with ChargeProgressType 'Start_'.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_002();
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
message instead of a PowerDeliveryReq message with ChargeProgressType 'Stop_'.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with an invalid SessionID, ChargeProgress 'Start_', valid charging profile and
TupleID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType::start_);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with an invalid SessionID, ChargeProgress 'Stop_' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with a
valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_003(iso1Part4_ChargeProgressType::stop_);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Start_', invalid charging profile
(>EVSEMaximumPowerLimit), valid TupleID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED_ChargingProfileInvalid' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_004(iso1Part4_ChargeProgressType::start_);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Start_', valid charging profile,
invalid TupleID and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED_TariffSelectionInvalid' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = true;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_005(iso1Part4_ChargeProgressType::start_);
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
'V2G_Sequence_Timeout' timer has expired after receiving a PreChargeRes message
with the current SessionID, ResponseCode 'OK' and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection: f_SECC_DC_PR_PreCharge_001
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PowerDelivery_001();
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
'V2G_Sequence_Timeout' timer has expired after receiving a valid
CurrentDemandRes or MeteringReceipt message.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_PowerDelivery_001();
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
1. CONDITION: Test System executes GoodCase procedure and initiates a renegotiation by sending
a PowerDeliveryReq message with the current SessionID, ChargeProgress
'Renegotiate' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication <PICS_CMN_CMN_LoopCounter
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_011()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::renegotiate, v_HAL_61851_Listener, false, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure, initiates a renegotiation and sends a
PowerDeliveryReq message with the current SessionID, ChargeProgress 'Start_' and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication <PICS_CMN_CMN_LoopCounter
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_012()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_ChargeParameterDiscoveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::start_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, ChargeProgress 'Renegotiate' and all additional
mandatory parameters but no PowerDeliveryReq with ChargeProgress 'Start' was
sent before.
2. EXPECTED: Test System then checks that the SUT sends a PowerDeliveryRes message with the
current SessionID, ResponseCode 'FAILED' and all additional mandatory parameters
and terminates the V2G communication session by closing the TCP connection
within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_013()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PreCharge_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_006();
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_RESSTemperatureInhibit',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_014()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_RESSTemperatureInhibit;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_EVShiftPosition',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_015()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_EVShiftPosition;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_ChargerConnectorLockFault',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_016()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_ChargerConnectorLockFault;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_EVRESSMalfunction',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_017()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_EVRESSMalfunction;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_ChargingCurrentdifferential',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_018()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_ChargingCurrentdifferential;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_ChargingVoltageOutOfRange',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_019()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_ChargingVoltageOutOfRange;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'FAILED_ChargingSystemIncompatibility',
ChargeProgressType 'Stop_' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_020()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::fAILED_ChargingSystemIncompatibility;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a PowerDeliveryReq message
with the current SessionID, EVErrorCode 'NoData', ChargeProgressType 'Stop_' and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the EVErrorCode not influences the EVSE charging
process by receiving a PowerDeliveryRes message with the current SessionID,
ResponseCode 'OK' and all additional mandatory parameters.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_PowerDelivery::TC_SECC_DC_VTB_PowerDelivery_021()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_CurrentDemandOrMeteringReceiptStop_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_DC_EVStatus.EVReady = false;
    this->mtc->vc_DC_EVStatus.EVErrorCode = (DC_EVErrorCodeType)iso1Part4_DC_EVErrorCodeType::noData;
    this->tb->f_SECC_DC_TB_VTB_PowerDelivery_001(iso1Part4_ChargeProgressType::stop_, v_HAL_61851_Listener, true, true, fail);
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