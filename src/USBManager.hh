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

  /// Finds the device to connect to
  /**
   * Return codes:
   * 0: Success
   * 1: Lib never initialized properly
   * 2: Couldn't get device list
   * 3: Device not found
   * 4: Error opening device
   */
  virtual int FindDevice();
  /// Returns true if the device was found
  virtual bool HasDevice() const;

  /// Write raw string to the device
  virtual void Write(const std::string& msg) const;
  /// Send vibration to a given motor with a given intensity
  virtual void Vibrate(char motor, char intensity) const;

private:
  bool isRPi(libusb_device* device);

  libusb_device_handle* rpi;
  libusb_context* context;
};
