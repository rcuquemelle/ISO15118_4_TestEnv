#ifndef __TB_SECC_CURRENTDEMAND_H__
#define __TB_SECC_CURRENTDEMAND_H__

#include "Components.h"
#include "TB_SECC_CommonBehavior.h"
#include "TsDataType.h"
#include "V2gCodecs.h"
#include "CommonLib.h"

class TestBehavior_SECC_CurrentDemand {
public:
  TestBehavior_SECC_CurrentDemand(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC>& _system);
  ~TestBehavior_SECC_CurrentDemand();
  verdict_val f_SECC_DC_TB_VTB_CurrentDemand_001(verdict_val v_vct);
  verdict_val f_SECC_DC_TB_VTB_CurrentDemand_002(void);
  verdict_val f_SECC_DC_TB_VTB_CurrentDemand_003(void);
  verdict_val f_SECC_DC_TB_VTB_CurrentDemand_004(void);
  verdict_val f_SECC_DC_TB_VTB_CurrentDemand_005(void);
private:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
  std::shared_ptr<TestBehavior_SECC_CommonBehavior> cmn;
};

#endif // __TB_SECC_CURRENTDEMAND_H__
