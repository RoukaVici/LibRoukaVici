#pragma once

#include "DeviceManager.hh"

/// Lets us interface with the device through a TCP connection
class TCPManager : public DeviceManager
{
public:
  TCPManager();
  ~TCPManager();

  virtual int FindRPi();
  virtual void WriteToRPi(const std::string& msg);
private:
  int sd;
};
