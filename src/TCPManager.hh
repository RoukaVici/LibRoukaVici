#pragma once

#include "DeviceManager.hh"

// This class attempts a TCP connection
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
