#include "RoukaVici.hh"
#include <unistd.h>
#include <iostream>

int main() {
  RoukaVici *rv = new RoukaVici();
  rv->ChangeDeviceManager("RawManager");
  rv->FindDevice();
  int res = rv->Vibrate(0, 255);
  if (res) {
    std::cerr << "Write on failed" << std::endl;
  }
  usleep(1000000);
  res = rv->Vibrate(0, 0);
  if (res) {
    std::cerr << "Write off failed" << std::endl;
  }
  delete rv;
  return 0;
}
