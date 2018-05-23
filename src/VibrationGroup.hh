#pragma once

#include <string>
#include <vector>

class DeviceManager;

/// Represents a single vibration group
/**
 * Vibration groups let the user define
 * groups of motors which should vibrate together
 */
class VibrationGroup
{
public:
  VibrationGroup(const std::string& name);
  ~VibrationGroup();

  /// Adds a motor to the current group
  /**
   * 0: Success
   * 1: Motor already in the group
   */
  int Add(char motor);
  /// Removes a motor from the current group
  /**
   * 0: Success
   * 1: Motor not in the group
   */
  int Rm(char motor);

  /// Vibrates the whole group.
  /**
   * Second parameter lets the group write to the device
   */
  int Vibrate(char intensity, const DeviceManager* dm) const;
private:
  const std::string name;
  std::vector<char>  motors;
};
