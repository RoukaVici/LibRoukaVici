#include "exported.hh"
#include "RoukaVici.hh"

RoukaVici *rv;

extern "C"
{
  /// InitRVici initializes the library
  /**
   * Automatically starts trying to find the device
   * Return codes:
   * 0: Success
   * 1: Lib initialized, but could not find device
   */
  EXPORTED int InitRVici()
  {
    rv = new RoukaVici();
    return rv->Status();
  }

  /// Manually search for the device
  EXPORTED int FindDevice()
  {
    return rv->FindDevice();
  }

  EXPORTED int Status()
  {
    return rv->Status();
  }

  /// StopRVici frees all data used up by the library
  EXPORTED void StopRVici()
  {
    delete rv;
  }

  /// Write to the device directly
  EXPORTED void Write(const char * const msg)
  {
    std::string cppmsg(msg);
    rv->Write(cppmsg);
  }

  EXPORTED void Vibrate(char motor, char intensity)
  {
    rv->Vibrate(motor, intensity);
  }

  /// Create a new vibration group
  /**
   * 0: Success
   * 1: Group already exists
   */
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
