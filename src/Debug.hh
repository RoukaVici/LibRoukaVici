#pragma once

#include "DebugCallback.h"

namespace Debug {
  void RegisterCallback(DebugCallback callback);
  void Log(const std::string& msg, bool force = false);
  void defaultLog(const char* msg);
};
