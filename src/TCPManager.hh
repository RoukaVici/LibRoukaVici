#pragma once

#include "DeviceManager.hh"

/// Lets us interface with the device through a TCP connection
class TCPManager : public DeviceManager
{
public:
  TCPManager();
  ~TCPManager();

  static DeviceManager* create();

  virtual int FindDevice();
  virtual bool HasDevice() const;
  virtual int Write(const std::string& msg) const;
  virtual int Vibrate(char motor, char intensity) const;
private:
  int sd;
};
