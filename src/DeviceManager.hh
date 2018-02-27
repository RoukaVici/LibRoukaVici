#pragma once

#include <string>

class DeviceManager
{
public:
  virtual int FindRPi() = 0;
  virtual void WriteToRPi(const std::string& msg) = 0;
};
