#include "BTManager.hh"
#include "DeviceINQ.h"

BTManager::BTManager() {
  DeviceINQ* test = DeviceINQ::Create();
  delete test;
}

BTManager::~BTManager()
{
}

int BTManager::FindDevice()
{
}

bool BTManager::HasDevice() const
{
  return false;
}

DeviceManager* BTManager::create()
{
  return new BTManager();
}

void BTManager::Vibrate(char motor, char intensity) const
{
  // TODO: Send data
}

void BTManager::Write(const std::string& msg) const
{
  // TODO: Send data
}
