#include <algorithm>
#include "VibrationGroup.hh"
#include "DeviceManager.hh"

VibrationGroup::VibrationGroup(const std::string& n) : name(n)
{
}

VibrationGroup::~VibrationGroup()
{
}

int VibrationGroup::Add(char motor)
{
  if (std::find(motors.begin(), motors.end(), motor) != motors.end())
    return 1;
  motors.push_back(motor);
  return 0;
}

int VibrationGroup::Rm(char motor)
{
  auto mtr = std::find(motors.begin(), motors.end(), motor);
  if (mtr == motors.end())
    return 1;
  motors.erase(mtr);
  return 0;
}

int VibrationGroup::Vibrate(char intensity, const DeviceManager* dm) const
{
  for (auto motor = motors.begin() ; motor != motors.end() ; motor++)
    {
      int ret = dm->Vibrate(*motor, intensity);
      if (ret != 0)
        return ret;
    }
  return 0;
}
