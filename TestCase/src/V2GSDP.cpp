#include "V2GSDP.h"
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

TestCases_SECC_SDP::TestCases_SECC_SDP(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> _stc,
                                       std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,
                                       std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
  : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_SDP>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_001"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_002"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_003"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_004"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_005"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_005));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_006"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_006));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_SDP_007"), &TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_007));
}

TestCases_SECC_SDP::~TestCases_SECC_SDP()
{
}

/**
1. CONDITION: Test System executes GoodCase procedure and sends an SDP request message with 
'Security' equals to '0x10'H and 'TransportProtocol' equals to '0x00'H. 
2. EXPECTED: Test System then checks that the SUT sends an SDP response message with 'Security' 
equals to '0x10'H, 'TransportProtocol' equals to '0x00'H and a valid port and IP 
address. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS := false
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_001()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    // no transport TLS
    this->tb->f_SECC_CMN_TB_VTB_SDP_001(0x10, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends an SDP request message with 
'Security' equals to '0x00'H and 'TransportProtocol' equals to '0x00'H. 
2. EXPECTED: Test System then checks that the SUT sends an SDP response message with 'Security' 
equals to '0x00'H, 'TransportProtocol' equals to '0x00'H and a valid port and IP 
address. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS := true
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_002()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    // TLS
    this->tb->f_SECC_CMN_TB_VTB_SDP_001(0x00, fail);
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
1. CONDITION: Test System executes GoodCase procedure and sends an SDP request message with 
'Security' equals to '0x00'H and 'TransportProtocol' equals to '0x00'H. 
2. EXPECTED: Test System then checks that the SUT sends an SDP response message with 'Security' 
equals to '0x00'H, 'TransportProtocol' equals to '0x00'H and a valid port and IP 
address. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := pnC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_003()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SDP_001(0x00, fail);
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
'V2G_SECC_CommunicationSetup_Timeout' timer has expired on SUT side.
2. EXPECTED: Test System then checks that the SUT stops the SDP server and does not respond to a 
valid SDP request message with 'Security' equals to '0x10'H and 'TransportProtocol' 
equals to '0x00'H. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS := false
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_004()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SDP_002(0x10);
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
'V2G_SECC_CommunicationSetup_Timeout' timer has expired on SUT side. 
2. EXPECTED: Test System then checks that the SUT stops the SDP server and does not respond to a 
valid SDP request message with 'Security' equals to '0x00'H and 'TransportProtocol' 
equals to '0x00'H. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS := true
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_005()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SDP_002(0x00);
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
'V2G_SECC_CommunicationSetup_Timeout' timer has expired on SUT side.
2. EXPECTED: Test System then checks that the SUT stops the SDP server and does not respond to a 
valid SDP request message with 'Security' equals to '0x00'H and 'TransportProtocol' 
equals to '0x00'H. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := pnC
4. PIXIT selection:
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_006()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SDP_002(0x00);
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
1. CONDITION: Test System executes GoodCase procedure and sends an SDP request message with 
'Security' equals to '0x00'H and 'TransportProtocol' equals to '0x00'H. 
2. EXPECTED: Test System then checks that the SUT sends an SDP response message with 'Security' 
equals to '0x10'H, 'TransportProtocol' equals to '0x00'H and a valid port and IP 
address. 
3. PICS selection: PICS_CMN_CMN_IdentificationMode := eIM
4. PIXIT selection: PIXIT_SECC_CMN_TLS := false
*/
verdict_val TestCases_SECC_SDP::TC_SECC_CMN_VTB_SDP_007()
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict;
  //-------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_StateB_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    this->tb->f_SECC_CMN_TB_VTB_SDP_003();
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
