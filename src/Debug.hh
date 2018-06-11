#pragma once

#include "DebugCallback.h"

// This namespace defines functions for logging messages
/**
 * It allows for different logging methods
 */
namespace Debug {
  /// Return the Log mode
  /**
   * 0: Write to std::cout
   * 1: Write to file
   * 2: Use DebugCallback
   * 3: Use UnityDebugCallback (Windows only!)
   */
  int   GetLogMode();
  /// Sets the log mode
  /**
   * 0: Write to std::cout/std::cerr
   * 1: Write to file
   * 2: Use DebugCallback
   * 3: Use UnityDebugCallback (Windows only!)
   * Note: if value is invalid, mode 0 is set instead
   */
  void  SetLogMode(const int method);
  /// Sets the log file
  /**
   * Used when logging in file mode
   */
  void  SetLogFile(const std::string& msg);
  /// Sets the callback function
  /**
   * function should return void and take const char* as parameter
   * Used when logging in callback mode
   */
  void  RegisterCallback(DebugCallback callback);
  /// Sets the Unity callback function
  /**
   * function should return void and take const char* as parameter
   * Used when logging in unity callback mode
   */
  void  RegisterUnityCallback(UnityDebugCallback callback);

  /// Use this function to write a log-level message
  void  Log(const std::string& msg, bool force = false);

  /// Use this function to write an error-level message
  void  Err(const std::string& msg);
};
