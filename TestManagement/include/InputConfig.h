#ifndef __CONFIGINPUT_H__
#define __CONFIGINPUT_H__
#include <string>
#include "PICSCfg.h"
#include "PIXITCfg.h"
#include "TimerCfg.h"

int load_config(const std::string &testconfig, const std::string &slac_config);

#endif // __CONFIGINPUT_H__