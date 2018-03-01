#pragma once

#include <string>
#include <vector>

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
  int Add(int motor);
  /// Removes a motor from the current group
  /**
   * 0: Success
   * 1: Motor not in the group
   */
  int Rm(int motor);

private:
  const std::string name;
  std::vector<int>  motors;
};
