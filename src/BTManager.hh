#pragma once

#include "DeviceManager.hh"

class DeviceINQ;
class BTSerialPortBinding;
/// Lets us interface with the device through Bluetooth
class BTManager : public DeviceManager
{
public:
  BTManager();
  ~BTManager();

  static DeviceManager* create();

  /// Finds the device to connect to
  /**
   * Return codes:
   * 0: Success
   */
  virtual int FindDevice();
  /// Returns true if the device was found
  virtual bool HasDevice() const;

  /// Write raw string to the device
  virtual int Write(const std::string& msg) const;
  virtual int Write(const char* msg, int length) const;
  /// Send vibration to a given motor with a given intensity
  virtual int Vibrate(char motor, char intensity) const;

private:
  // Inquire object, handles queries to the bluetooth api
  DeviceINQ*  inq;
  BTSerialPortBinding* port;
};
