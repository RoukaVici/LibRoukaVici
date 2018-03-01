#include <iostream>
#include "RoukaVici.hh"
#include "TextManager.hh"
#include "VibrationGroup.hh"

RoukaVici::RoukaVici() : dm(new TextManager())
{
  dm->FindDevice();
}

RoukaVici::~RoukaVici()
{
  for (auto grp = groups.begin(); grp != groups.end() ; grp++)
    {
      delete grp->second;
    }
  delete dm;
}

int RoukaVici::Status()
{
  if (!dm->HasDevice())
    return 1;
  return 0;
}

int RoukaVici::FindDevice()
{
  dm->FindDevice();
  return dm->HasDevice() ? 0 : 1;
}

void RoukaVici::Write(const std::string& msg) const
{
  dm->Write(msg);
}

void RoukaVici::Vibrate(char motor, char intensity) const
{
  dm->Vibrate(motor, intensity);
}

int RoukaVici::NewGroup(const std::string& name)
{
  if (groups.find(name) != groups.end())
    return 1;
  groups[name] = new VibrationGroup(name);
  return 0;
}

int RoukaVici::AddToGroup(const std::string& name, char motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Add(motor);
}

int RoukaVici::RmFromGroup(const std::string& name, char motor)
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return 2;
  return grp->second->Rm(motor);
}

void RoukaVici::VibrateGroup(const std::string& name, char intensity) const
{
  auto grp = groups.find(name);
  if (grp == groups.end())
    return;
  grp->second->Vibrate(intensity, dm);
}
