#pragma once

#include "DebugCallback.h"

// This namespace defines functions for logging messages
/**
 * It allows for different logging methods
 */
namespace Debug {
  int   GetLogMode();
  void  SetLogMode(const int method);
  void  SetLogFile(const std::string& msg);
  void  RegisterCallback(DebugCallback callback);
#ifdef _WIN32
  void  RegisterUnityCallback(UnityDebugCallback callback);
#endif
  void  Log(const std::string& msg, bool force = false);
};
