#ifndef __POSTCONDITIONS_SECC_H__
#define __POSTCONDITIONS_SECC_H__

#include "Components.h"


class PostConditions_SECC_15118_2 : public std::enable_shared_from_this<PostConditions_SECC_15118_2>
{
public:
  PostConditions_SECC_15118_2(std::shared_ptr<SECC_Tester>& _mtc, std::shared_ptr<System_SECC> _system): mtc(_mtc), systemSECC(_system) {}
  ~PostConditions_SECC_15118_2() {
  }
  void f_SECC_CMN_PO_InitialState_001(std::shared_ptr<HAL_61851_Listener> v_HAL_61851_Listener);
public:
  std::shared_ptr<SECC_Tester> mtc;
  std::shared_ptr<System_SECC> systemSECC;
};
#endif // __POSTCONDITIONS_SECC_H__