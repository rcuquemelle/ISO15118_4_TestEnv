#include "TestSystemLogging.h"

LogLevelType Logging::logLevel = LOG_NONE;
LogOutputType Logging::logOutDest = LOG_OUT_NONE;
std::FILE *Logging::outputLog = NULL;
LogModuleCfg Logging::LogCfg = {0};