#include <iostream>
#include "exported.hh"
#include "RoukaVici.hh"
#include "Debug.hh"

RoukaVici *rv = 0;

extern "C"
{
  EXPORTED int InitRVici()
  {
#ifdef ROUKAVERBOSE
    std::cout <<  "[LibRoukaVici] Starting library" << std::endl;
#endif
    rv = new RoukaVici();
    return rv->Status();
  }

  EXPORTED int FindDevice()
  {
    if (rv == 0)
      return -1;
    return rv->FindDevice();
  }

  EXPORTED int Status()
  {
    if (rv == 0)
      return -1;
    return rv->Status();
  }

  EXPORTED void StopRVici()
  {
#ifdef ROUKAVERBOSE
    std::cout <<  "[LibRoukaVici] Stopping library..." << std::endl;
#endif
    if (rv != 0)
      delete rv;
#ifdef ROUKAVERBOSE
    std::cout <<  "[LibRoukaVici] Library stopped" << std::endl;
#endif
  }

 EXPORTED int Write(const char * const msg)
  {
    if (rv == 0)
      return -1;
    std::string cppmsg(msg);
    return rv->Write(cppmsg);
  }

  EXPORTED int Vibrate(char motor, char intensity)
  {
    if (rv == 0)
      return -1;

    return rv->Vibrate(motor, intensity);
  }

  EXPORTED int NewGroup(const char * const name)
  {
    if (rv == 0)
      return -1;

    std::string cppname(name);
    return rv->NewGroup(cppname);
  }

  EXPORTED int AddToGroup(const char * const name, char motor)
  {
    if (rv == 0)
      return -1;

    std::string cppname(name);
    return rv->AddToGroup(cppname, motor);
  }

  EXPORTED int RmFromGroup(const char * const name, char motor)
  {
    if (rv == 0)
      return -1;
    std::string cppname(name);
    return rv->RmFromGroup(cppname, motor);
  }

  EXPORTED int VibrateGroup(const char* const name, char intensity)
  {
    if (rv == 0)
      return -1;
    std::string cppname(name);
    return rv->VibrateGroup(cppname, intensity);
  }

  EXPORTED int ChangeDeviceManager(const int idx)
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

  EXPORTED int RegisterDebugCallback(DebugCallback cb)
  {
    Debug::RegisterCallback(cb);
    return 0;
  }
}
