#include "exported.hh"
#include "RoukaVici.hh"

RoukaVici *rv;

extern "C"
{
  EXPORTED int InitRVici()
  {
    rv = RoukaVici::get();
    return rv->Status();
  }

  EXPORTED int FindDevice()
  {
    return rv->FindDevice();
  }

  EXPORTED int Status()
  {
    return rv->Status();
  }

  EXPORTED void StopRVici()
  {
    delete rv;
  }

  EXPORTED void Write(const char * const msg)
  {
    std::string cppmsg(msg);
    rv->Write(cppmsg);
  }

  EXPORTED void Vibrate(char motor, char intensity)
  {
    rv->Vibrate(motor, intensity);
  }

  EXPORTED int NewGroup(const char * const name)
  {
    std::string cppname(name);
    return rv->NewGroup(cppname);
  }

  EXPORTED int AddToGroup(const char * const name, char motor)
  {
    std::string cppname(name);
    return rv->AddToGroup(cppname, motor);
  }

  EXPORTED int RmFromGroup(const char * const name, char motor)
  {
    std::string cppname(name);
    return rv->RmFromGroup(cppname, motor);
  }

  EXPORTED void VibrateGroup(const char* const name, char intensity)
  {
    std::string cppname(name);
    rv->VibrateGroup(cppname, intensity);
  }
}
