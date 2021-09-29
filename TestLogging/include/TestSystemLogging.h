#ifndef __TESTSYSTEMLOGGING_H__
#define __TESTSYSTEMLOGGING_H__

#include "fmt/core.h"
#include "fmt/chrono.h"
#include "filesystem/filesystem.h"
// #include "time/time.h"
// #include "time/timezone.h"
#include <memory>
#include <cstdio>
#include <time.h>

typedef enum En_LogLevelType {
  LOG_NONE = 0,
  LOG_ERROR,
  LOG_INFO,
  LOG_DEBUG,
  LOG_NUM
} LogLevelType;

typedef enum En_LogOutputType {
  LOG_OUT_NONE = 0,
  LOG_OUT_CONSOLE,
  LOG_OUT_FILE,
  LOG_OUT_BOTH,
  LOG_OUT_NUM
} LogOutputType;

typedef union {
  struct {
    uint16_t LogPAIf : 1;       // 0
    uint16_t LogRunEnv : 1;     // 1
    uint16_t LogSut61851 : 1;   // 2
    uint16_t LogSutTCP : 1;     // 3
    uint16_t LogSutUDP : 1;     // 4
    uint16_t LogComponent : 1;  // 5
    uint16_t LogCmnFnc : 1;     // 6
    uint16_t LogCfgFnc : 1;     // 7
    uint16_t LogPreFnc : 1;     // 8
    uint16_t LogPosFnc : 1;     // 9
    uint16_t LogTbFnc : 1;      // 10
    uint16_t LogTc : 1;         // 11
    uint16_t LogCmnLib : 1;     // 12
    uint16_t LogMsgTPDump : 1;     // 13
    uint16_t LogMsgDump : 1;     // 14
    uint16_t LogSLAC : 1;     // 15
  };
  uint16_t value;
} LogModuleCfg;

#define LogPAIf_ENABLE      ((uint16_t)0x0001)
#define LogRunEnv_ENABLE    ((uint16_t)0x0002)
#define LogSut61851_ENABLE  ((uint16_t)0x0004)
#define LogSutTCP_ENABLE    ((uint16_t)0x0008)
#define LogSutUDP_ENABLE    ((uint16_t)0x0010)
#define LogComponent_ENABLE ((uint16_t)0x0020)
#define LogCmnFnc_ENABLE    ((uint16_t)0x0040)
#define LogCfgFnc_ENABLE    ((uint16_t)0x0080)
#define LogPreFnc_ENABLE    ((uint16_t)0x0100)
#define LogPosFnc_ENABLE    ((uint16_t)0x0200)
#define LogTbFnc_ENABLE     ((uint16_t)0x0400)
#define LogTc_ENABLE        ((uint16_t)0x0800)
#define LogCmnLib_ENABLE    ((uint16_t)0x1000)
#define LogMsgDump_ENABLE   ((uint16_t)0x2000)
#define LogSLAC_ENABLE      ((uint16_t)0x4000)
#define LogMsgTPDump_ENABLE ((uint16_t)0x8000)
#define LogAll_ENABLE       ((uint16_t)0xFFFF)

// logging class
class Logging {
// static variable for class to config output to screen/ log file
private:
  static LogLevelType logLevel;
  static LogOutputType logOutDest;
  static std::FILE *outputLog;
  // static std::shared_ptr<CppCommon::File> mFile;
public:
  static LogModuleCfg LogCfg;
  Logging() {
  };
  ~Logging() {
    fclose(Logging::outputLog);
  };
  static std::string time_inMicroSec(void)
  {
    auto now = std::chrono::system_clock::now();
    unsigned long us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count() % 1e6;
    // auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    auto t = fmt::localtime(timer);
    std::string temp = fmt::format("{0:%H:%M:%S}:{1}", t, us);
    // std::string tempms = fmt::format("{0:%H:%M:%S}:{1}", t, ms);
    // fmt::print(temp);
    // fmt::print(tempms);
    return temp;
  }
  static void setLogLevel(LogLevelType level) {
    Logging::logLevel = level;
  }
  static void setLogOutput(LogOutputType type) {
    Logging::logOutDest = type;
  }
  static void setLogFile(const std::string _file) {
    CppCommon::Path path = CppCommon::Path(_file);
    if (!path.IsDirectory()) {
      if (path.IsRelative()) {
        path = path.canonical();
      }
      if (path.IsExists()){
        CppCommon::Path::Remove(path);
      }
      else {
        if (!path.parent().IsExists())
          CppCommon::Directory::Create(path.parent());
      }
      // Logging::mFile = std::make_shared<CppCommon::File>(path);
      Logging::outputLog = fopen(path.string().c_str() , "w");
    }
    else {

    }
  }
  static void closeLogFile(void){
    fclose(Logging::outputLog);
  }
  // take string value from fmt::format
  static void debug(uint16_t module, const std::string value) {
    // logic push log to console or file
    // and base on log level
    if (LOG_INFO < Logging::logLevel) {
      if ((LOG_OUT_CONSOLE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)){
        if (module == (Logging::LogCfg.value & module)){
          // to console
          fmt::print("{0}[DEBUG]:{1}\r\n", Logging::time_inMicroSec(), value);
        }
      }
      if ((LOG_OUT_FILE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)) {
        // to file
        if (Logging::outputLog != nullptr){
          if (module == (Logging::LogCfg.value & module)){
            fmt::print(Logging::outputLog, "{0}[DEBUG]:{1}\r\n", Logging::time_inMicroSec(), value);
            // fmt::print(Logging::outputLog, "[DEBUG]:{}\r\n",value);
          }
        }
      }
    }
  }
  static void info(uint16_t module, const std::string value) {
    // std::time_t curr_time = std::time(nullptr);
    if (LOG_ERROR < Logging::logLevel) {
      if ((LOG_OUT_CONSOLE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)) {
        if (module == (Logging::LogCfg.value & module)){
          // to console
          fmt::print("{0}[ INFO]:{1}\r\n", Logging::time_inMicroSec(), value);
          // fmt::print("[ INFO]:{}\r\n",value);
        }
      }
      if ((LOG_OUT_FILE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)) {
        // to file
        if (Logging::outputLog != nullptr){
          if (module == (Logging::LogCfg.value & module)){
            fmt::print(Logging::outputLog, "{0}[ INFO]:{1}\r\n", Logging::time_inMicroSec(), value);
            // fmt::print(Logging::outputLog, "[ INFO]:{}\r\n",value);
          }
        }
      }
    }
  }
  static void error(uint16_t module, const std::string value) {
    // std::time_t curr_time = std::time(nullptr);
    if (LOG_NONE < Logging::logLevel) {
      if ((LOG_OUT_CONSOLE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)) {
        if (module == (Logging::LogCfg.value & module)){
          // to console
          fmt::print("{0}[ERROR]:{1}\r\n", Logging::time_inMicroSec(), value);
          // fmt::print("[ERROR]:{}\r\n",value);
        }
      }
      if ((LOG_OUT_FILE == Logging::logOutDest) ||
          (LOG_OUT_BOTH == Logging::logOutDest)) {
        // to file
        if (Logging::outputLog != nullptr){
          if (module == (Logging::LogCfg.value & module)){
            fmt::print(Logging::outputLog, "{0}[ERROR]:{1}\r\n", Logging::time_inMicroSec(), value);
            // fmt::print(Logging::outputLog, "[ERROR]:{}\r\n",value);
          }
        }
      }
    }
  }
};

#endif // __TESTSYSTEMLOGGING_H__