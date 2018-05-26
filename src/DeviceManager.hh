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

  /// Writes a string to the device
  /**
   * 0: Write succeeded
   * 1: Not connected to device
   * 2: Error while writing
   */
  virtual int Write(const std::string& msg) const = 0;
  virtual int Write(const char* msg, int length) const = 0;

  /// Vibrate given motor with given intensity
  /**
   * 0: Write succeeded
   * 1: Not connected to device
   * 2: Error while writing
   */

  virtual int Vibrate(char motor, char intensity) const = 0;
};
