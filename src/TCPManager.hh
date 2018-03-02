#pragma once

#include "DeviceManager.hh"

/// Lets us interface with the device through a TCP connection
class TCPManager : public DeviceManager
{
public:
  TCPManager();
  ~TCPManager();

  virtual int FindDevice();
  virtual bool HasDevice() const;
  virtual void Write(const std::string& msg) const;
  virtual void Vibrate(char motor, char intensity) const;
private:
  int sd;
};
