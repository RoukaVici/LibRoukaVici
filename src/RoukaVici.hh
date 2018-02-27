#pragma once

#include <string>
#include "exported.hh"

class DeviceManager;

EXPORTED class RoukaVici
{
 public:
  RoukaVici();
  ~RoukaVici();
  void Write(const std::string& msg);
private:
  DeviceManager *dm;
};
