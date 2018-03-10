#pragma once

#include <string>
#include <map>

class DeviceManager;

typedef DeviceManager* (*DMNGR_CREATOR)();

class ManagerFactory
{
public:
  ManagerFactory();
  ~ManagerFactory();

  DeviceManager* get(const std::string& name);

private:
  std::map<std::string, DMNGR_CREATOR> managers;
};
