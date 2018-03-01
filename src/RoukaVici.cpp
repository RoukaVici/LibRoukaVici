#include <iostream>
#include "RoukaVici.hh"
#include "TextManager.hh"
#include "VibrationGroup.hh"

RoukaVici::RoukaVici() : dm(new TextManager())
{
  int err = dm->FindRPi();
}

RoukaVici::~RoukaVici()
{
  for (auto grp = groups.begin(); grp != groups.end() ; grp++)
    {
      delete grp->second;
    }
  delete dm;
}

/// Lets the developer write any string to the device.
/**
 * Used for debugging purposes
 */
void RoukaVici::Write(const std::string& msg)
{
  dm->WriteToRPi(msg);
}

/// Create a new vibration group
/**
 * 0: Success
 * 1: Group already exists
 */
int RoukaVici::NewGroup(const std::string& name)
{
  if (groups.find(name) != groups.end())
    return 1;
  groups[name] = new VibrationGroup(name);
  return 0;
}

/// Add motor to group
/**
 * 0: Success
 * 1: Motor already in group
 * 2: No such group
 */
int RoukaVici::AddToGroup(const std::string& name, int motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Add(motor);
}

/// Remove motor from group
/**
 * 0: Success
 * 1: Motor not in group
 * 2: No such group
 */
int RoukaVici::RmFromGroup(const std::string& name, int motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Rm(motor);
}
