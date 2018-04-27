#pragma once

#include <string>

/// Device Manager is a device communication interface
/**
 * Each child class is a different way of communicating
 * with the device
 */
class DeviceManager
{
public:
  virtual ~DeviceManager() {}

  /// Finds the device
  /**
   * Returns 0 on success, see child classes for error codes
   */
  virtual int FindDevice() = 0;

  /// Indicates whether the manager has found the device
  virtual bool HasDevice() const = 0;

  /// Writes a string to the device directly
  virtual void Write(const std::string& msg) const = 0;

  // Vibrate given motor with given intensity
  virtual void Vibrate(char motor, char intensity) const = 0;
};
