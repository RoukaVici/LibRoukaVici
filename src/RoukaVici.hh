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
  void Write(const std::string& msg);

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
  int AddToGroup(const std::string& name, int motor);
  /// Remove motor from group
  /**
   * 0: Success
   * 1: Motor not in group
   * 2: No such group
   */
  int RmFromGroup(const std::string& name, int motor);

private:
  DeviceManager                 *dm;
  std::map<std::string, VibrationGroup*>  groups;
};
