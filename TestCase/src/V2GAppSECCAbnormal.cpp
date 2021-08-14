#include "V2GAppSECCAbnormal.h"
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

TestCases_SECC_Abnormal:: TestCases_SECC_Abnormal(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _stc,\
    std::shared_ptr<Configuration_15118_2> _cfg, std::shared_ptr<TestBehavior_SECC_CommonBehavior> _cmn,\
    std::shared_ptr<PreConditions_SECC_15118_2> _pre, std::shared_ptr<PostConditions_SECC_15118_2> _post)
    : V2GTestcaseBase(_mtc, _stc, _cfg, _cmn, _pre, _post)
{
  this->tb = std::make_shared<TestBehavior_SECC_Authorization>(this->mtc, this->stc);
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_CMN_VTB_Abnormal_001"), &TestCases_SECC_Abnormal::TC_SECC_CMN_VTB_Abnormal_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_Abnormal_001"), &TestCases_SECC_Abnormal::TC_SECC_DC_VTB_Abnormal_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_DC_VTB_Abnormal_002"), &TestCases_SECC_Abnormal::TC_SECC_DC_VTB_Abnormal_002));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_Abnormal_001"), &TestCases_SECC_Abnormal::TC_SECC_AC_VTB_Abnormal_001));
  this->testcase_map.emplace(std::make_pair(std::string("TC_SECC_AC_VTB_Abnormal_002"), &TestCases_SECC_Abnormal::TC_SECC_AC_VTB_Abnormal_002));
}

TestCases_SECC_Abnormal::~ TestCases_SECC_Abnormal()
{
}

/**
1. CONDITION: short CP-PE
2. EXPECTED:
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Abnormal::TC_SECC_DC_VTB_Abnormal_001(void)
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict = none;
  bool isShutdownOSC = false;
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->stc);
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    uint32_t loopCounter = 0;
    while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter))
    {
      // CurrentDemand
      if (preConVerdict == pass)
      {
        // increase SOC
        if ((this->mtc->vc_DC_EVStatus.EVRESSSOC+100/PICS_CMN_CMN_LoopCounter)  <= 100)
        {
          this->mtc->vc_DC_EVStatus.EVRESSSOC += 100/PICS_CMN_CMN_LoopCounter;
          Logging::info(LogPreFnc_ENABLE, fmt::format("this->mtc->vc_DC_EVStatus.EVRESSSOC = {0}%", this->mtc->vc_DC_EVStatus.EVRESSSOC));
        }
        preConVerdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
        if (loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication)
        {
          this->stc->_pBCIf->setRelay(SeccBasicSignaling::RELAY_SHORT_CIRCUIT, SeccBasicSignaling::RELAY_VAL_ON);
          PAsleep(par_CMN_waitForNextHAL);
          // error occur TCP should be shutdown after this
          // verify TCP disconnect
          this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
          while (true)
          {
            if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
            {
              isShutdownOSC = true;
            }
            if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
            {
              if (isShutdownOSC == false)
              {
                Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
              }
              this->mtc->pt_HAL_61851_Internal_Port->clear();
              break;
            }
            if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
            {
              break;
            }
            if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
            {
              break;
            }
          }
          // return ControlPilot state to b
          this->stc->_pBCIf->setState(DataStructure_HAL_61851::IEC_61851_States::B);
          PAsleep(par_CMN_waitForNextHAL);
          break;
        }
      }
      else
      {
        return preConVerdict;
      }
      loopCounter = loopCounter + 1;
      if (preConVerdict == pass)
      {
        Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> CurrentDemand: {}", loopCounter));
        PAsleep(par_SECC_chargingLoop_pause);
      }
    }
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
1. CONDITION: lost pe
2. EXPECTED:
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Abnormal::TC_SECC_DC_VTB_Abnormal_002(void)
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict = none;
  bool isShutdownOSC = false;
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->stc);
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_DC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    uint32_t loopCounter = 0;
    while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter))
    {
      // CurrentDemand
      if (preConVerdict == pass)
      {
        // increase SOC
        if ((this->mtc->vc_DC_EVStatus.EVRESSSOC+100/PICS_CMN_CMN_LoopCounter)  <= 100)
        {
          this->mtc->vc_DC_EVStatus.EVRESSSOC += 100/PICS_CMN_CMN_LoopCounter;
          Logging::info(LogPreFnc_ENABLE, fmt::format("this->mtc->vc_DC_EVStatus.EVRESSSOC = {0}%", this->mtc->vc_DC_EVStatus.EVRESSSOC));
        }
        preConVerdict = tb_curDemand->f_SECC_DC_TB_VTB_CurrentDemand_001(inconc);
        if (loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication)
        {
          this->stc->_pBCIf->setRelay(SeccBasicSignaling::RELAY_PE_LINE, SeccBasicSignaling::RELAY_VAL_OFF);
          PAsleep(par_CMN_waitForNextHAL);
          // error occur TCP should be shutdown after this
          // verify TCP disconnect
          this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
          while (true)
          {
            if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
            {
              isShutdownOSC = true;
            }
            if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
            {
              if (isShutdownOSC == false)
              {
                Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
              }
              this->mtc->pt_HAL_61851_Internal_Port->clear();
              break;
            }
            if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
            {
              break;
            }
            if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
            {
              break;
            }
          }
          // return ControlPilot state to b
          this->stc->_pBCIf->setState(DataStructure_HAL_61851::IEC_61851_States::B);
          PAsleep(par_CMN_waitForNextHAL);
          break;
        }
      }
      else
      {
        return preConVerdict;
      }
      loopCounter = loopCounter + 1;
      if (preConVerdict == pass)
      {
        Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> CurrentDemand: {}", loopCounter));
        PAsleep(par_SECC_chargingLoop_pause);
      }
    }
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
1. CONDITION: lost diode
2. EXPECTED:
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Abnormal::TC_SECC_CMN_VTB_Abnormal_001(void)
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict = none;
  bool isShutdownOSC = false;
  std::shared_ptr<TestBehavior_SECC_CurrentDemand> tb_curDemand = std::make_shared<TestBehavior_SECC_CurrentDemand>(this->mtc, this->stc);
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_CMN_PR_SetProximityPilot_001(v_HAL_61851_Listener);
  if (!PICS_CMN_CMN_CombinedTesting)
  {
    if (preConVerdict == pass)
    {
      // check state
      f_SECC_changeValidStateCondition(B);
      // change to state B
      preConVerdict = f_SECC_setState(this->stc, B, v_HAL_61851_Listener);
      this->stc->_pBCIf->setRelay(SeccBasicSignaling::RELAY_DIODE, SeccBasicSignaling::RELAY_VAL_ON);
      // wait 0.5s (plug in)
      PAsleep(par_CMN_waitForNextHAL);
      // if combinedTesting enable -> this PLC function already establish DataLink and in state B
      preConVerdict = f_SECC_CMN_PR_PLCLinkStatus_001(this->stc, this->mtc);
      if (preConVerdict == fail)
      {
        this->mtc->setverdict(pass, "SUT does establish slac connection with lost diode");
      }
      else
      {
        this->mtc->setverdict(fail, "SUT still establish slac connection with lost diode");
        // iso1Part4_Security_TYPE v_security = cc_hexTcp;
        // std::shared_ptr<TestBehavior_SECC_SDP> tb = std::make_shared<TestBehavior_SECC_SDP>(this->mtc, this->stc);
        // verdict = tb->f_SECC_CMN_TB_VTB_SDP_001(v_security, pass);
      }
    }
  }
  //------------- Post Conditions--------------------------------------------------------
  this->post->f_SECC_CMN_PO_InitialState_001(v_HAL_61851_Listener);
  this->cfg->f_SECC_CMN_PO_ShutdownConfiguration_001(v_HAL_61851_Listener, this->stc);
  Logging::info(LogTc_ENABLE, "----- TEST CASE END -----");
  return this->mtc->dumpverdict();
}


/**
1. CONDITION: short CP-PE
2. EXPECTED:
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Abnormal::TC_SECC_AC_VTB_Abnormal_001(void)
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict = none;
  bool isShutdownOSC = false;
  std::shared_ptr<TestBehavior_SECC_ChargingStatus> tb_chargeSts = std::make_shared<TestBehavior_SECC_ChargingStatus>(this->mtc, this->stc);
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    uint32_t loopCounter = 0;
    while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter))
    {
      // ChargingStatus
      if (preConVerdict == pass)
      {
        preConVerdict = tb_chargeSts->f_SECC_AC_TB_VTB_ChargingStatus_001(inconc);
      }
      else
      {
        return preConVerdict;
      }
      if (loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication)
      {
        this->stc->_pBCIf->setRelay(SeccBasicSignaling::RELAY_SHORT_CIRCUIT, SeccBasicSignaling::RELAY_VAL_ON);
        PAsleep(par_CMN_waitForNextHAL);
        // error occur TCP should be shutdown after this
        // verify TCP disconnect
        this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
        while (true)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
          if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
          {
            if (isShutdownOSC == false)
            {
              Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
            }
            this->mtc->pt_HAL_61851_Internal_Port->clear();
            break;
          }
          if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
          {
            break;
          }
          if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
          {
            break;
          }
        }
        // return ControlPilot state to b
        this->stc->_pBCIf->setState(DataStructure_HAL_61851::IEC_61851_States::B);
        PAsleep(par_CMN_waitForNextHAL);
        break;
      }
      loopCounter = loopCounter + 1;
      if (preConVerdict == pass)
      {
        Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> ChargingStatus: {}", loopCounter));
        PAsleep(par_SECC_chargingLoop_pause);
      }
    }
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
1. CONDITION: lost pe
2. EXPECTED:
3. PICS selection:
4. PIXIT selection:
*/
verdict_val TestCases_SECC_Abnormal::TC_SECC_AC_VTB_Abnormal_002(void)
{
  Logging::info(LogTc_ENABLE, fmt::format("----- TEST CASE {} START -----",__FUNCTION__));
  std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener;
  verdict_val preConVerdict = none;
  bool isShutdownOSC = false;
  std::shared_ptr<TestBehavior_SECC_ChargingStatus> tb_chargeSts = std::make_shared<TestBehavior_SECC_ChargingStatus>(this->mtc, this->stc);
  // -------------- Pre Conditions-------------------------------------------------------
  this->cfg->f_SECC_CMN_PR_InitConfiguration_001(v_HAL_61851_Listener, this->stc);
  preConVerdict = this->pre->f_SECC_AC_PR_PowerDeliveryStart_001(v_HAL_61851_Listener);
  //-------------- Test behavior---------------------------------------------------------
  if (preConVerdict == pass)
  {
    uint32_t loopCounter = 0;
    while ((this->mtc->vc_EVSENotification == iso1Part4_EVSENotificationType::none_) && (loopCounter < PICS_CMN_CMN_LoopCounter))
    {
      // ChargingStatus
      if (preConVerdict == pass)
      {
        preConVerdict = tb_chargeSts->f_SECC_AC_TB_VTB_ChargingStatus_001(inconc);
      }
      else
      {
        return preConVerdict;
      }
      if (loopCounter == PICS_CMN_CMN_RenegotiationLoopIndication)
      {
        this->stc->_pBCIf->setRelay(SeccBasicSignaling::RELAY_PE_LINE, SeccBasicSignaling::RELAY_VAL_OFF);
        PAsleep(par_CMN_waitForNextHAL);
        // error occur TCP should be shutdown after this
        // verify TCP disconnect
        this->mtc->tc_CMN_TCP_Connection_Termination_Timer->start(par_CMN_TCP_Connection_Termination_Timeout);
        while (true)
        {
          if (a_CMN_shutdownOscillator(this->mtc->pt_HAL_61851_Internal_Port))
          {
            isShutdownOSC = true;
          }
          if (this->cmn->a_SECC_TCPConnection_Status_Listener(pass, "TCP connection was terminated by the SUT."))
          {
            if (isShutdownOSC == false)
            {
              Logging::error(LogTbFnc_ENABLE, "SECC oscillator was not shut down before the TCP connection was terminated.");
            }
            this->mtc->pt_HAL_61851_Internal_Port->clear();
            break;
          }
          if (this->cmn->a_SECC_Unexpected_Message_Content_002(fail, "Received any message, but TCP connection was >>NOT<< terminated by the SUT"))
          {
            break;
          }
          if (this->cmn->a_SECC_TCP_Connection_Termination_Timeout())
          {
            break;
          }
        }
        // return ControlPilot state to b
        this->stc->_pBCIf->setState(DataStructure_HAL_61851::IEC_61851_States::B);
        PAsleep(par_CMN_waitForNextHAL);
        break;
      }
      loopCounter = loopCounter + 1;
      if (preConVerdict == pass)
      {
        Logging::info(LogPreFnc_ENABLE, fmt::format("loopcounter -> ChargingStatus: {}", loopCounter));
        PAsleep(par_SECC_chargingLoop_pause);
      }
    }
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