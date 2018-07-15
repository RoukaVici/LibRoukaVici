#include <iostream>
#include "roukavici_export.h"
#include "RoukaVici.hh"
#include "Debug.hh"

#define RV(x) static_cast<RoukaVici*>(x)

extern "C"
{
  ROUKAVICI_EXPORT void* InitRVici()
  {
    Debug::Log("Starting library");
    return static_cast<void*>(new RoukaVici());
  }

  ROUKAVICI_EXPORT int FindDevice(void* handle)
  {
    return RV(handle)->FindDevice();
  }

  ROUKAVICI_EXPORT int Status(void* handle)
  {
    return RV(handle)->Status();
  }

  ROUKAVICI_EXPORT void StopRVici(void* handle)
  {
    Debug::Log("Stopping library...");
    delete RV(handle);
    Debug::Log("Library stopped.");
  }

 ROUKAVICI_EXPORT int Write(void* handle, const char * const msg)
  {
    const std::string cppmsg(msg);
    return RV(handle)->Write(cppmsg);
  }

  ROUKAVICI_EXPORT int Vibrate(void* handle, char motor, char intensity)
  {
    return RV(handle)->Vibrate(motor, intensity);
  }

  ROUKAVICI_EXPORT int NewGroup(void* handle, const char * const name)
  {
    const std::string cppname(name);
    return RV(handle)->NewGroup(cppname);
  }

  ROUKAVICI_EXPORT int AddToGroup(void* handle, const char * const name, char motor)
  {
    const std::string cppname(name);
    return RV(handle)->AddToGroup(cppname, motor);
  }

  ROUKAVICI_EXPORT int RmFromGroup(void* handle, const char * const name, char motor)
  {
    const std::string cppname(name);
    return RV(handle)->RmFromGroup(cppname, motor);
  }

  ROUKAVICI_EXPORT int VibrateGroup(void* handle, const char* const name, char intensity)
  {
    const std::string cppname(name);
    return RV(handle)->VibrateGroup(cppname, intensity);
  }

  ROUKAVICI_EXPORT int ChangeDeviceManager(void* handle, const int idx)
  {
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
    return RV(handle)->ChangeDeviceManager(name);
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
