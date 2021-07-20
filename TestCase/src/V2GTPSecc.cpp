#include "V2GTPSecc.h"
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

TestCases_SECC_V2GTPSDP::TestCases_SECC_V2GTPSDP(std::shared_ptr<SECC_Tester> &_mtc, std::shared_ptr<System_SECC> _stc,
                                  std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,
                                  std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
                                    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_V2GTPSDP>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSDP_001"), &TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSDP_002"), &TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSDP_003"), &TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSDP_004"), &TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSDP_005"), &TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_005));
}
TestCases_SECC_V2GTPSDP::~TestCases_SECC_V2GTPSDP()
{
}

TestCases_SECC_V2GTPSessionSetup::TestCases_SECC_V2GTPSessionSetup(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
      : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_V2GTPSessionSetup>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSessionSetup_001"), &TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSessionSetup_002"), &TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSessionSetup_003"), &TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_003));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSessionSetup_004"), &TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_004));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_V2GTPSessionSetup_005"), &TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_005));
}
TestCases_SECC_V2GTPSessionSetup::~TestCases_SECC_V2GTPSessionSetup()
{
}

iso1Part4_V2GTP_header_TYPE md_CMN_V2GTP_header_TYPE_001(iso1Part4_ProtocolVersion_TYPE ver,
  iso1Part4_InvProtocolVersion_TYPE invVer, iso1Part4_PayloadType_TYPE type, iso1Part4_PayloadLength_TYPE len){
  iso1Part4_V2GTP_header_TYPE tpHeader;
  tpHeader.protocolVersion = ver;
  tpHeader.invProtocolVersion = invVer;
  tpHeader.payloadType = type;
  tpHeader.payloadLength = len;
  return tpHeader;
}


/**
1. CONDITION: Test System executes GoodCase procedure and sends a SessionSetupReq message with 
the V2GTP header information 'protocolVersion' equals to '0x01'H, 
'invProtocolVersion' equals to 'FE'H and 'payloadType' equals to '0x8001'H. (V2GTP 
Header is matched for V2G message content). 
2. EXPECTED: Test System then checks that the SUT sends a SessionSetupRes message with the 
V2GTP header information 'protocolVersion' equals to '0x01'H, 'invProtocolVersion' 
equals to 'FE'H and 'payloadType' equals to '0x8001'H. 
3. PICS selection: PICS_CMN_CMN_V2gtpV2g := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_001()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSessionSetup_001();
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'payloadLength' equals 
to '00000000'H in the V2GTP header of the SessionSetupReq message. 
2. EXPECTED: Test System then checks that the SUT ignores the SessionSetupReq message by 
detecting a 'V2G_Msg_Timeout'. 
3. PICS selection: PICS_CMN_CMN_V2gtpV2g := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_002()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFE, 0x8001, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'payloadType' equals 
to '7001'H in the V2GTP header of the SessionSetupReq message. 
2. EXPECTED: Test System then checks that the SUT ignores the SessionSetupReq message by 
detecting a 'V2G_Msg_Timeout'. 
3. PICS selection: PICS_CMN_CMN_V2gtpV2g := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_003()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFE, 0x7001, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'protocolVersion' 
equals to 'FF'H in the V2GTP header of the SessionSetupReq message. 
2. EXPECTED: Test System then checks that the SUT ignores the SessionSetupReq message by 
detecting a 'V2G_Msg_Timeout'. 
3. PICS selection: PICS_CMN_CMN_V2gtpV2g := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_004()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(md_CMN_V2GTP_header_TYPE_001(0xFF, 0xFE, 0x8001, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'invProtocolVersion' 
equals to 'FF'H in the V2GTP header of the SessionSetupReq message. 
2. EXPECTED: Test System then checks that the SUT ignores the SessionSetupReq message by 
detecting a 'V2G_Msg_Timeout'. 
3. PICS selection: PICS_CMN_CMN_V2gtpV2g := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSessionSetup::TC_SECC_CMN_VTB_V2GTPSessionSetup_005()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSessionSetup_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFF, 0x8001, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends a valid SDP request message with 
the V2GTP header information 'protocolVersion' equals to '0x01'H, 
'invProtocolVersion' equals to 'FE'H and 'payloadType' equals to '0x9000'H. (V2GTP 
Header is matched for SDP message content). 
2. EXPECTED: Test System then checks that the SUT sends a SDP response message with the V2GTP 
header information 'protocolVersion' equals to '0x01'H, 'invProtocolVersion' equals to 
'FE'H, payloadType' equals to '0x9001'H and 'payloadLength' equals to '00000014'H. 
3. PICS selection: PICS_CMN_CMN_V2gtpSdp := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_001()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSDP_001();
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'payloadLength' equals 
to '00000000'H in the V2GTP header of the SDP request message. 
2. EXPECTED: Test System then checks that the SUT ignores the SDP response message by detecting 
an SDP message timeout. 
3. PICS selection: PICS_CMN_CMN_V2gtpSdp := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_002()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSDP_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFE, 0x9000, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'payloadType' equals 
to '7000'H in the V2GTP header of the SDP request message. 
2. EXPECTED: Test System then checks that the SUT ignores the SDP response message by detecting 
an SDP message timeout. 
3. PICS selection: PICS_CMN_CMN_V2gtpSdp := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_003()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSDP_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFE, 0x7000, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'protocolVersion' 
equals to 'FF'H in the V2GTP header of the SDP request message.
2. EXPECTED: Test System then checks that the SUT ignores the SDP response message by detecting 
an SDP message timeout. 
3. PICS selection: PICS_CMN_CMN_V2gtpSdp := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_004()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSDP_002(md_CMN_V2GTP_header_TYPE_001(0xFF, 0xFE, 0x9000, 0));
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
1. CONDITION: Test System executes GoodCase procedure and sends an invalid 'invProtocolVersion' 
equals to 'FF'H in the V2GTP header of the SDP request message.
2. EXPECTED: Test System then checks that the SUT ignores the SDP response message by detecting 
an SDP message timeout. 
3. PICS selection: PICS_CMN_CMN_V2gtpSdp := true
4. PIXIT selection:
*/
verdict_val TestCases_SECC_V2GTPSDP::TC_SECC_CMN_VTB_V2GTPSDP_005()
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
    this->tb->f_SECC_CMN_TB_VTB_V2GTPSDP_002(md_CMN_V2GTP_header_TYPE_001(0x01, 0xFF, 0x9000, 0));
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