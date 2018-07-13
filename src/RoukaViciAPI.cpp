#include <iostream>
#include "roukavici_export.h"
#include "RoukaVici.hh"
#include "Debug.hh"

RoukaVici *rv = 0;

extern "C"
{
  ROUKAVICI_EXPORT int InitRVici()
  {
    Debug::Log("Starting library");
    rv = new RoukaVici();
    return rv->Status();
  }

  ROUKAVICI_EXPORT int FindDevice()
  {
    if (rv == 0)
      return -1;
    return rv->FindDevice();
  }

  ROUKAVICI_EXPORT int Status()
  {
    if (rv == 0)
      return -1;
    return rv->Status();
  }

  ROUKAVICI_EXPORT void StopRVici()
  {
    Debug::Log("Stopping library...");
    if (rv != 0)
      delete rv;
    Debug::Log("Library stopped.");
  }

 ROUKAVICI_EXPORT int Write(const char * const msg)
  {
    if (rv == 0)
      return -1;
    const std::string cppmsg(msg);
    return rv->Write(cppmsg);
  }

  ROUKAVICI_EXPORT int Vibrate(char motor, char intensity)
  {
    if (rv == 0)
      return -1;

    return rv->Vibrate(motor, intensity);
  }

  ROUKAVICI_EXPORT int NewGroup(const char * const name)
  {
    if (rv == 0)
      return -1;

    const std::string cppname(name);
    return rv->NewGroup(cppname);
  }

  ROUKAVICI_EXPORT int AddToGroup(const char * const name, char motor)
  {
    if (rv == 0)
      return -1;

    const std::string cppname(name);
    return rv->AddToGroup(cppname, motor);
  }

  ROUKAVICI_EXPORT int RmFromGroup(const char * const name, char motor)
  {
    if (rv == 0)
      return -1;
    const std::string cppname(name);
    return rv->RmFromGroup(cppname, motor);
  }

  ROUKAVICI_EXPORT int VibrateGroup(const char* const name, char intensity)
  {
    if (rv == 0)
      return -1;
    const std::string cppname(name);
    return rv->VibrateGroup(cppname, intensity);
  }

  ROUKAVICI_EXPORT int ChangeDeviceManager(const int idx)
  {
    if (rv == 0)
      return -1;
    std::string name;
    switch (idx) {
      case 0:
        name = "TextManager";
        break;
      case 1:
        name = "RawManager";
        break;
      case 2:
        name = "BTManager";
        break;
      default:
        return -2;
    }
    return rv->ChangeDeviceManager(name);
  }

  ROUKAVICI_EXPORT void SetLogMode(const int mode)
  {
    RoukaVici::SetLogMode(mode);
  }

  ROUKAVICI_EXPORT int GetLogMode()
  {
    return RoukaVici::GetLogMode();
  }

  ROUKAVICI_EXPORT void SetLogFile(const char* const name)
  {
    const std::string cppname(name);
    RoukaVici::SetLogFile(cppname);
  }


  ROUKAVICI_EXPORT void RegisterDebugCallback(DebugCallback cb)
  {
    RoukaVici::RegisterDebugCallback(cb);
  }

  ROUKAVICI_EXPORT void RegisterUnityDebugCallback(UnityDebugCallback cb)
  {
    RoukaVici::RegisterUnityDebugCallback(cb);
  }

}
