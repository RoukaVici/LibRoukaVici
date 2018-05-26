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

  /// Return a pointer to the given DeviceManager
  /**
   * Possible DeviceManagers:
   * - TextManager (Default)
   * - RawManager
   * - BTManager
   * See each .hh file for description of each manager
   */
  DeviceManager* get(const std::string& name);

private:
  std::map<std::string, DMNGR_CREATOR> managers;
};
