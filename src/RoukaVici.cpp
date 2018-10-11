#include <sstream>
#include "RoukaVici.hh"
#include "ManagerFactory.hh"
#include "DeviceManager.hh"
#include "GroupManager.hh"
#include "Debug.hh"

RoukaVici::RoukaVici()
{
  mf = new ManagerFactory();
  dm = mf->get("TextManager");
  grps = new GroupManager();
  std::stringstream ss;
  ss <<  "[" << this << "] RoukaVici successfully initiated(dm=" << dm << ")";
  Debug::Log(ss.str());
}

RoukaVici::~RoukaVici()
{
  std::stringstream ss;
  ss << "[" << this << "] Closing library. Obama out.";
  Debug::Log(ss.str());
  delete grps;
  delete dm;
  delete mf;
}

int RoukaVici::Status()
{
  std::stringstream ss;
  ss << "[" << this << "] Checking RoukaVici status";
  Debug::Log(ss.str());
  if (!dm->HasDevice())
    return 1;
  return 0;
}

int RoukaVici::FindDevice()
{
  std::stringstream ss;
  ss << "[" << this << "] Finding device";
  Debug::Log(ss.str());
  dm->FindDevice();
  return dm->HasDevice() ? 0 : 1;
}

int RoukaVici::Write(const std::string& msg) const
{
  return dm->Write(msg);
}

int RoukaVici::Vibrate(char motor, char intensity) const
{
  std::stringstream ss;
  ss << "[" << this << "] Vibration order received: " << static_cast<int>(motor) << ":" << static_cast<int>(static_cast<unsigned char>(intensity));
  Debug::Log(ss.str());
  return dm->Vibrate(motor, intensity);
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

int RoukaVici::VibrateGroup(const std::string& name, char intensity) const
{
  return grps->VibrateGroup(name, intensity, dm);
}

int RoukaVici::ChangeDeviceManager(const std::string& name)
{
  {
    std::stringstream ss;
    ss << "[" << this << "] Changing DeviceManager";
    Debug::Log(ss.str());
  }
  DeviceManager* temp = mf->get(name);
  if (temp == nullptr)
    return 1;
  {
    std::stringstream ss;
    ss << "Old dm=" << dm << "\tNew dm=" << temp;
    Debug::Log(ss.str());
  }
  delete dm;
  dm = temp;
  return 0;
}

int RoukaVici::GetLogMode()
{
  return Debug::GetLogMode();
}

void RoukaVici::SetLogMode(const int mode)
{
  Debug::SetLogMode(mode);
}

void RoukaVici::SetLogFile(const std::string& name)
{
  Debug::SetLogFile(name);
}

void RoukaVici::RegisterDebugCallback(DebugCallback callback)
{
  Debug::RegisterCallback(callback);
}

void RoukaVici::RegisterUnityDebugCallback(DebugCallback callback)
{
  Debug::RegisterCallback(callback);
}