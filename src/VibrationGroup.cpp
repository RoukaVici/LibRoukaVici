#include <algorithm>
#include "VibrationGroup.hh"

VibrationGroup::VibrationGroup(const std::string& name) : name(name)
{
}

VibrationGroup::~VibrationGroup()
{
}

/// Adds a motor to the current group
/**
 * 0: Success
 * 1: Motor already in the group
 */
int VibrationGroup::Add(int motor)
{
  if (std::find(motors.begin(), motors.end(), motor) != motors.end())
    return 1;
  motors.push_back(motor);
  return 0;
}

/// Removes a motor from the current group
/**
 * 0: Success
 * 1: Motor not in the group
 */
int VibrationGroup::Rm(int motor)
{
  auto mtr = std::find(motors.begin(), motors.end(), motor);
  if (mtr == motors.end())
    return 1;
  motors.erase(mtr);
  return 0;
}
