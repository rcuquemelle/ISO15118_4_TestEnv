#include "V2GAppSECCChargeParameterDiscovery.h"
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

TestCases_SECC_ChargeParameterDiscovery::TestCases_SECC_ChargeParameterDiscovery(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_ChargeParameterDiscovery>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_001"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_002"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_003"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_004"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_005"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_006"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_007"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_008"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_009"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_010"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_011"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_012"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_013"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_014"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_015"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_015));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_016"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_016));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_017"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_017));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_018"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_018));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_019"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_019));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_020"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_020));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_021"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_021));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_022"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_022));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_023"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_023));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_024"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_024));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_025"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_025));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_026"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_026));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_027"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_027));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_028"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_028));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_029"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_029));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_030"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_030));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_031"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_031));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_032"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_032));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_033"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_033));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_034"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_034));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_035"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_035));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_ChargeParameterDiscovery_036"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_036));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_001"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_002"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_003"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_004"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_005"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_006"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_007"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_007));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_008"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_008));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_009"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_009));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_010"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_010));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_011"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_011));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_012"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_012));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_013"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_013));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_014"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_014));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_015"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_015));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_016"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_016));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_017"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_017));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_018"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_018));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_019"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_019));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_020"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_020));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_021"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_021));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_022"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_022));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_023"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_023));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_024"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_024));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_025"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_025));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_026"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_026));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_027"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_027));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_028"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_028));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_029"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_029));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_030"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_030));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_031"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_031));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_032"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_032));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_033"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_033));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_034"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_034));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_035"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_035));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_ChargeParameterDiscovery_036"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_036));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_ChargeParameterDiscovery_001"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_CMN_VTB_ChargeParameterDiscovery_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_ChargeParameterDiscovery_002"), &TestCases_SECC_ChargeParameterDiscovery::TC_SECC_CMN_VTB_ChargeParameterDiscovery_002));
}

TestCases_SECC_ChargeParameterDiscovery::~TestCases_SECC_ChargeParameterDiscovery(){
}

/**
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple and DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with an invalid SessionID, a valid RequestedEnergyTransferType and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with a valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, an invalid RequestedEnergyTransferType
'dC_extended' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'FAILED_WrongEnergyTransferMode' and
all additional mandatory parameters and terminates the V2G communication session
by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_003();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, valid RequestedEnergyTransferType,
EVMaxCurrent '‐100' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'FAILED_WrongChargeParameter' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_004();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp> PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_007()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple and DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp> PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_011()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, without DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_012()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, without DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_013()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. Furthermore the
repetition of the ChargeParameterDiscovery message sequence will be checked
(EVSEProcessing = 'Ongoing') until the 'V2G_SECC_Ongoing_Timer' has expired on
SUT side. Test system then checks that the SUT terminates the V2G communication
session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC
4. PIXIT selection: PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing = ongoing
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_014()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_008();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_015()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_016()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
logical network by the SUT. Furthermore Test System checks that the SUT
turns off the oscillator for the entire sleep mode. After 'PICS_CMN_CMN_WakeUp'
Test System resumes the previously paused session by initiating a BCB toggle and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp >PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_017()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
  PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_018()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp> PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_019()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false, PICS_SECC_CMN_Pause = true,
  PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
  PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_020()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
  PICS_CMN_CMN_CombinedTesting = true, PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_021()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp,
  PICS_CMN_CMN_CombinedTesting = true, PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_022()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_023()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_024()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_CMN_CMN_Renegotiation = true, PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_025()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC,
PICS_SECC_CMN_DepartureTime = false, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_026()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_027()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_028()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaxCurrent = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 32};
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp< PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_029()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp< PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_030()
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
    if (preConVerdict == pass)
    {
      unmap(this->mtc->pt_V2G_TCP_TLS_ALM_SECC_Port, this->stc->pt_V2G_TCP_TLS_ALM_SECC_Port);
      preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
    }
    //-------------- Test behavior---------------------------------------------------------
    if (preConVerdict == pass)
    {
      this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
    }
    else
    {
      Logging::info(LogTc_ENABLE, "PreCondition was unsuccessful.");
    }
    //------------- Post Conditions--------------------------------------------------------
    this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
    this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  }
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp <PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_031()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory
parameters and the SAScheduleTuple which was selected by the EVCC in the
previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_032()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp< PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_033()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = false,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_034()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
  PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_035()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = aC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp <PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_AC_VTB_ChargeParameterDiscovery_036()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_AC_TB_VTB_ChargeParameterDiscovery_005();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple and DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with an invalid SessionID, a valid RequestedEnergyTransferType and all
additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with a valid SessionID, ResponseCode 'FAILED_UnknownSession' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_002();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, an invalid RequestedEnergyTransferType
'dC_extended' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'FAILED_WrongEnergyTransferMode' and
all additional mandatory parameters and terminates the V2G communication session
by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_003();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, valid RequestedEnergyTransferType,
EVMaxCurrent '‐100' and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'FAILED_WrongChargeParameter' and all
additional mandatory parameters and terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_004();
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_007()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple and DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_008()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC,
PICS_SECC_CMN_DepartureTime = false, PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_009()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_010()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp> PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_011()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, without DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_012()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, without DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered)
and all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_013()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, without
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. Furthermore the
repetition of the ChargeParameterDiscovery message sequence will be checked
(EVSEProcessing = 'Ongoing') until the 'V2G_SECC_Ongoing_Timer' has expired on
SUT side. Test system then checks that the SUT terminates the V2G communication
session by closing the TCP connection within
'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection: PIXIT_SECC_CMN_ChargeParameterDiscoveryOngoing = ongoing
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_014()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_008();
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_015()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends a ChargeParameterDiscoveryReq
message with the current SessionID, a valid RequestedEnergyTransferType, a
MaxEntriesSAScheduleTuple, a DepartureTime and all additional mandatory
parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_016()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_017()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp >PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_018()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_019()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp> PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_020()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp >PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_021()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp > PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_022()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and all additional mandatory parameters. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter, PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_023()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff and all additional mandatory parameters. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_024()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_025()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false, PICS_CMN_CMN_Renegotiation = true,
PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_026()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) and
all additional mandatory parameters. If a valid ChargeParameterDiscoveryRes
message with EVSEProcessing 'Ongoing' was received before, the Test System sends
another ChargeParameterDiscoveryReq message. This message sequence will be
repeated until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_027()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_006(fail);
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
new ChargeParameterDiscoveryReq message with the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered) and all additional
mandatory parameters. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_CMN_CMN_Renegotiation = true,PICS_CMN_CMN_RenegotiationLoopIndication < PICS_CMN_CMN_LoopCounter,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_CMN_CMN_Renegotiation = unknown,PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_028()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryRenegotiation_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->mtc->vc_EVMaximumCurrentLimit = {.Multiplier = 0, .Unit = (unitSymbolType)iso1Part4_UnitSymbolType::a, .Value = 22};
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_001(fail);
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_029()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple and DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp< PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_030()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList, all additional mandatory parameters and the SAScheduleTuple
which was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_031()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter)
triggered by the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, without MaxEntriesSAScheduleTuple, a DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff all additional mandatory parameters and the
SAScheduleTuple which was selected by the EVCC in the previous session. If a
valid ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was
received before, the Test System sends another ChargeParameterDiscoveryReq
message. This message sequence will be repeated until the processing of the
charging information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp <PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = false
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_032()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple,
without DepartureTime and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_033()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, without DepartureTime
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which was selected by
the EVCC in the previous session. If a valid ChargeParameterDiscoveryRes message
with EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = false,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp< PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_034()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList and salesTariff (MaxEntriesSAScheduleTuple is considered) all
additional mandatory parameters and the SAScheduleTuple which
was selected by the EVCC in the previous session. If a valid
ChargeParameterDiscoveryRes message with EVSEProcessing 'Ongoing' was received
before, the Test System sends another ChargeParameterDiscoveryReq message. This
message sequence will be repeated until the processing of the charging
information has finished or 'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true,
PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp <PICS_CMN_CMN_WakeUp,
PICS_CMN_CMN_CombinedTesting = true,PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = salesTariff
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_035()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_007();
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
off the oscillator for the entire sleep mode. After 'PIXIT_CMN_CMN_WakeUp' the
SUT resumes the previously paused session by initiating a B1/B2 transition and
waits for successful link detection (old logical network parameter) triggered by
the SUT. Test System then executes Goodcase procedure and sends a
ChargeParameterDiscoveryReq message the current SessionID, a valid
RequestedEnergyTransferType, a MaxEntriesSAScheduleTuple, a DepartureTime and
all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT sends a ChargeParameterDiscoveryRes message
with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished', a
valid scheduleList (MaxEntriesSAScheduleTuple is considered), all additional
mandatory parameters and the SAScheduleTuple which was selected by the EVCC in
the previous session. If a valid ChargeParameterDiscoveryRes message with
EVSEProcessing 'Ongoing' was received before, the Test System sends another
ChargeParameterDiscoveryReq message. This message sequence will be repeated
until the processing of the charging information has finished or
'V2G_EVCC_Ongoing_Timer' has expired.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC, PICS_SECC_CMN_DepartureTime = true, PICS_SECC_CMN_Pause = true, PIXIT_CMN_CMN_WakeUp < PICS_CMN_CMN_WakeUp, PICS_CMN_CMN_CombinedTesting = true,
PICS_SECC_CMN_MaxEntriesSAScheduleTuple = true
4. PIXIT selection: PIXIT_SECC_CMN_SalesTariff = unknown
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_DC_VTB_ChargeParameterDiscovery_036()
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
    preConVerdict = this->pre->f_SECC_CMN_PR_AuthorizationPausedSession_001(v_HAL_61851_Listener);
  }
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_DC_TB_VTB_ChargeParameterDiscovery_005();
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
message instead of a ChargeParameterDiscoveryReq message.
2. EXPECTED: Test System then checks that the SUT sends a ServiceDiscoveryRes message with
the current SessionID, ResponseCode 'FAILED_SequenceError' and all additional
mandatory parameters and terminates the V2G communication session by closing the
TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_CMN_VTB_ChargeParameterDiscovery_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_001();
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
'V2G_Sequence_Timeout' timer has expired after receiving a AuthorizationRes
message with the current SessionID, ResponseCode 'OK', EVSEProcessing 'Finished'
and all additional mandatory parameters.
2. EXPECTED: Test System then checks that the SUT terminates the V2G communication session by
closing the TCP connection within 'par_CMN_TCP_Connection_Termination_Timeout'.
3. PICS selection: PICS_CMN_CMN_ChargingMode = dC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_ChargeParameterDiscovery::TC_SECC_CMN_VTB_ChargeParameterDiscovery_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_Authorization_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_ChargeParameterDiscovery_002();
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
