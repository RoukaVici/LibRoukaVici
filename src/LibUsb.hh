#pragma once

#include "DeviceManager.hh"

struct libusb_device;
struct libusb_device_handle;
struct libusb_context;

// This class attempts to find RoukaVici through USB
class LibUsb : public DeviceManager
{
public:
  LibUsb();
  ~LibUsb();

  virtual int FindRPi();
  virtual void WriteToRPi(const std::string& msg);
private:
  bool isRPi(libusb_device* device);

  libusb_device_handle* rpi;
  libusb_context* context;
};
