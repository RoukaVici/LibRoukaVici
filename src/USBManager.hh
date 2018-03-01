#pragma once

#include "DeviceManager.hh"

struct libusb_device;
struct libusb_device_handle;
struct libusb_context;

/// Lets us interface with the device through USB
class USBManager : public DeviceManager
{
public:
  USBManager();
  ~USBManager();

  /// FindRPi finds the raspberry pi and stores it
  /**
   * Return codes:
   * 0: Success
   * 1: Lib never initialized properly
   * 2: Couldn't get device list
   * 3: RPi not found
   * 4: Error opening raspberry pi
   */
  virtual int FindRPi();
  virtual void WriteToRPi(const std::string& msg);
private:
  bool isRPi(libusb_device* device);

  libusb_device_handle* rpi;
  libusb_context* context;
};
