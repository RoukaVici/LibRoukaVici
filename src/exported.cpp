#include "exported.hh"
#include "RoukaVici.hh"

RoukaVici *rv;

extern "C"
{
  EXPORTED void InitRVici()
  {
    rv = new RoukaVici();
  }

  EXPORTED void StopRVici()
  {
    delete rv;
  }
}
