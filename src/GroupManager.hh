#pragma once

#include <string>
#include <map>

class VibrationGroup;
class DeviceManager;

class GroupManager
{
public:
  GroupManager();
  ~GroupManager();
  int NewGroup(const std::string& name);
  int AddToGroup(const std::string& name, char motor);
  int RmFromGroup(const std::string& name, char motor);
  void VibrateGroup(const std::string& name, char motor, DeviceManager* dm) const;
private:
  std::map<std::string, VibrationGroup*>  groups;
};
