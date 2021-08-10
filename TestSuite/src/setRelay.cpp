#include <iostream>
#include <string>
#include <vector>
#include "IfRuntime.h"
#include "SeccBasicSignaling.h"
#include "TestSystemLogging.h"

std::string temp[] = {
  [DataStructure_HAL_61851::IEC_61851_States::A] = "STATE A",
  [DataStructure_HAL_61851::IEC_61851_States::B] = "STATE B",
  [DataStructure_HAL_61851::IEC_61851_States::C] = "STATE C",
  [DataStructure_HAL_61851::IEC_61851_States::D] = "STATE D",
};
int main(int argc, char *argv[])
{
  Logging::LogCfg.value = LogSut61851_ENABLE;
  Logging::setLogLevel(LOG_DEBUG);
  Logging::setLogOutput(LOG_OUT_CONSOLE);
  IfRuntime runenv = IfRuntime();
  std::shared_ptr<SeccBasicSignaling> BC = std::make_shared<SeccBasicSignaling>(runenv.getService());

  if (!strcmp(argv[1], "A")) {
    BC->setState(DataStructure_HAL_61851::IEC_61851_States::A);
  }
  if (!strcmp(argv[1], "B")) {
    BC->setState(DataStructure_HAL_61851::IEC_61851_States::B);
  }
  if (!strcmp(argv[1], "C")) {
    BC->setState(DataStructure_HAL_61851::IEC_61851_States::C);
  }
  if (!strcmp(argv[1], "D")) {
    BC->setState(DataStructure_HAL_61851::IEC_61851_States::D);
  }
  if (!strcmp(argv[1], "CP")) {
    BC->setErrorState(DataStructure_HAL_61851::IEC_61851_ErrStates::LOST_CP);
  }
  if (!strcmp(argv[1], "PE")) {
    BC->setRelay(SeccBasicSignaling::RELAY_PE_LINE, SeccBasicSignaling::RELAY_VAL_OFF);
  }
  if (!strcmp(argv[1], "DI")) {
    BC->setRelay(SeccBasicSignaling::RELAY_DIODE, SeccBasicSignaling::RELAY_VAL_ON);
  }
  if (!strcmp(argv[1], "SH")) {
    BC->setRelay(SeccBasicSignaling::RELAY_SHORT_CIRCUIT, SeccBasicSignaling::RELAY_VAL_ON);
  }
  return 0;
}