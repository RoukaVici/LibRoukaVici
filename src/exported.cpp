#include "exported.hh"
#include "RoukaVici.hh"

RoukaVici *rv;

extern "C"
{
  /// InitRVici initializes the library
  /**
   * Return codes:
   * 0: Success
   * 1: Could not find RoukaVici box
   */
  EXPORTED int InitRVici()
  {
    rv = new RoukaVici();
  }

  /// StopRVici frees all data used up by the library
  EXPORTED void StopRVici()
  {
    delete rv;
  }

  EXPORTED void Write(const char * const msg)
  {
    std::string cppmsg(msg);
    rv->Write(cppmsg);
  }
}
