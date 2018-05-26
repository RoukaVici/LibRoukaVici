#include "RoukaVici.hh"
#include <unistd.h>
#include <iostream>

int vibrateMotor(RoukaVici *rv, char motor) {
  res = rv->Vibrate(0, 255); // Send vibration to motor 0, at full strength
  if (res != 0) {
    std::cerr << "Write on failed" << std::endl;
    return 1;
  }
  usleep(1000000);
  res = rv->Vibrate(0, 0); // Stop motor 0
  if (res != 0) {
    std::cerr << "Write off failed" << std::endl;
    return 1;
  }
  return 0;
}

int main() {
  int res;
  RoukaVici *rv = new RoukaVici();  // Initialize the library
  // Library is now in text mode, it will print vibrations to the standard output in human-readable format

  res = rv->ChangeDeviceManager("BTManager"); // Change to Bluetooth mode.
  if (res != 0) {
    std::cerr << "Could not change device manager, error code: " << res << std::endl;
    goto finish;
  }
  res = rv->FindDevice(); // Attempt to find the glove
  if (res != 0) {
    // Print error message. We're using BTManager so the error code will be explained in BTManager.hh
    std::cerr << "Could not find Bluetooth device, error code: " << res << std::endl;
    goto finish;
  }
  // Vibrate all 5 fingers
  if (vibrateMotor(0) || vibrateMotor(1) || vibrateMotor(2) || vibrateMotor(3) || vibrateMotor(4)) {
    goto finish;
  }

 finish:
  delete rv;
  return res;
}
