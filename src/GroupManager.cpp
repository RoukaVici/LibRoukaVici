#include "GroupManager.hh"
#include "VibrationGroup.hh"

GroupManager::GroupManager()
{
}

GroupManager::~GroupManager()
{
  for (auto grp = groups.begin(); grp != groups.end() ; grp++)
    {
      delete grp->second;
    }
}

int GroupManager::NewGroup(const std::string& name) {
  if (groups.find(name) != groups.end())
    return 1;
  groups[name] = new VibrationGroup(name);
  return 0;
}

int GroupManager::AddToGroup(const std::string& name, char motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Add(motor);
}

int GroupManager::RmFromGroup(const std::string& name, char motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Rm(motor);
}

int GroupManager::VibrateGroup(const std::string& name, char intensity, DeviceManager* dm) const
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 3;
  return grp->second->Vibrate(intensity, dm);
}
