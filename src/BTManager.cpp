#include <vector>
#include <iostream>

#include "BTManager.hh"
#include "DeviceINQ.h"
#include "BTSerialPortBinding.h"

BTManager::BTManager() : inq(DeviceINQ::Create()), port(nullptr) {
}

BTManager::~BTManager()
{
  if (port != nullptr)
    {
      delete port;
    }
  delete inq;
}

/// Search for bluetooth devices, if we find the glove connect to it
/**
 * Return codes:
 * 0: OK, device found
 * 1: No device found
 * 2: Device found, could not get channel Id
 */
int BTManager::FindDevice()
{
  if (port != nullptr)
    {
      delete port;
      port = nullptr;
    }

  // TODO: If this takes too long, just put it in a separate thread and have a mechanism to check
  // Maybe replace HasDevice() with Status(), returning a manager-specific int
  std::vector<device> devices = inq->Inquire();
  for (const auto& d: devices)
    {
      std::cout << "- Found: " << d.name << std::endl;
      if (d.name.compare("OnePlus 3") == 0)
        {
          int channelId = inq->SdpSearch(d.address);
          if (channelId == -1)
            {
              std::cerr << "Failed to get device channel ID" << std::endl;
              return 2;
            }
          port = BTSerialPortBinding::Create(d.address, channelId);
          port->Connect();
          return 0;
        }
    }
  return 1;
}

bool BTManager::HasDevice() const
{
  return port != nullptr;
}

DeviceManager* BTManager::create()
{
  return new BTManager();
}

void BTManager::Vibrate(char motor, char intensity) const
{
  if (port == nullptr)
    return ;
  char msg[2] = {motor, intensity};
  port->Write(msg, 2);
}

void BTManager::Write(const std::string& msg) const
{
  if (port == nullptr)
    return ;
  port->Write(msg.c_str(), msg.length());
}
