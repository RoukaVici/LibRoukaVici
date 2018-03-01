#pragma once

#include <string>

/// Device Manager isa device communication interface
/**
 * Each child class is a different way of communicating
 * with the device
 */
class DeviceManager
{
public:
  /// Finds the device
  /**
   * Returns 0 on success, see child classes for error codes
   */
  virtual int FindRPi() = 0;

  /// Writes a string to the device directly
  /**
   * Mostly used for debugging
   */
  virtual void WriteToRPi(const std::string& msg) = 0;
};
