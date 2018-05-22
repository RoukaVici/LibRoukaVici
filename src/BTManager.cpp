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

  std::vector<device> devices = inq->Inquire();
  for (const auto& d: devices)
    {
      if (d.name.compare("OnePlus 3") == 0)
        {
          int channelId = inq->SdpSearch(d.address);
          if (channelId == -1)
            {
              std::cerr << "Failed to get device channel ID" << std::cerr;
              return 2;
            }
          port = BTSerialPortBinding::create(d.address, channelId);
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
  // TODO: Send data
}

void BTManager::Write(const std::string& msg) const
{
  if (port == nullptr)
    return ;
  port->Write(msg.c_str(), msg.length);
}
