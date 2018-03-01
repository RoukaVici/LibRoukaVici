#pragma once

#include <string>
#include <map>
#include "exported.hh"

class DeviceManager;
class VibrationGroup;

EXPORTED class RoukaVici
{
 public:
  RoukaVici();
  ~RoukaVici();
  /// Lets the developer write any string to the device.
  /**
   * Used for debugging purposes
   */
  void Write(const std::string& msg) const;

  /// Simple vibration
  void Vibrate(char motor, char intensity) const;

  /// Returns values indicating current status
  /**
   * 0: No errors
   * 1: Device not found
   */
  int Status();

  /// Orders the device manager to find a device
  /**
   * Returns 0 if found, 1 otherwise
   */
  int FindDevice();

  /// Create a new vibration group
  /**
   * 0: Success
   * 1: Group already exists
   */
  int NewGroup(const std::string& name);
  /// Add motor to group
  /**
   * 0: Success
   * 1: Motor already in group
   * 2: No such group
   */
  int AddToGroup(const std::string& name, char motor);
  /// Remove motor from group
  /**
   * 0: Success
   * 1: Motor not in group
   * 2: No such group
   */
  int RmFromGroup(const std::string& name, char motor);

  /// Vibrates the given group at the given intensity
  void VibrateGroup(const std::string& name, char intensity) const;

private:
  DeviceManager                 *dm;
  std::map<std::string, VibrationGroup*>  groups;
};
