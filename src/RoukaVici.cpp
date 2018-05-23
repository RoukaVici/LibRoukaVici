#include <iostream>
#include "RoukaVici.hh"
#include "ManagerFactory.hh"
#include "DeviceManager.hh"
#include "GroupManager.hh"

// Returns a RoukaVici singleton
RoukaVici* RoukaVici::get()
{
  static RoukaVici *rv;
  return rv ? rv : (rv = new RoukaVici());
}

RoukaVici::RoukaVici() : mf(new ManagerFactory()),
                         dm(mf->get("TextManager")),
                         grps(new GroupManager())
{
  dm->FindDevice();
}

RoukaVici::~RoukaVici()
{
  delete grps;
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
  return grps->NewGroup(name);
}

int RoukaVici::AddToGroup(const std::string& name, char motor)
{
  return grps->AddToGroup(name, motor);
}

int RoukaVici::RmFromGroup(const std::string& name, char motor)
{
  return grps->RmFromGroup(name, motor);
}

void RoukaVici::VibrateGroup(const std::string& name, char intensity) const
{
  grps->VibrateGroup(name, intensity, dm);
}

int RoukaVici::ChangeDeviceManager(const std::string& name)
{
  DeviceManager* temp = mf->get(name);
  if (temp == nullptr)
    return 1;
  delete dm;
  dm = temp;
  return 0;
}
