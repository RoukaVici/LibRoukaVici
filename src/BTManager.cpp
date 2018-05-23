#include <vector>
#include <iostream>

#include "BTManager.hh"
#include "DeviceINQ.h"
#include "BTSerialPortBinding.h"
#include "BluetoothException.h"

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
 * 3: Device found, connection failed (Wrong PIN most likely cause)
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
      if (d.name.compare("RoukaVici") == 0)
        {
          int channelId = inq->SdpSearch(d.address);
          if (channelId == -1)
            {
              std::cerr << "Failed to get device channel ID" << std::endl;
              return 2;
            }
          std::cout << "Channel ID: " << channelId << std::endl;
          port = BTSerialPortBinding::Create(d.address, channelId);
          try {
            port->Connect();
          }
          catch (BluetoothException& e)
            {
              std::cerr << "Could not connect to the device, did you enter the right PIN?" << std::endl;
              return 3;
            }
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

int BTManager::Vibrate(char motor, char intensity) const
{
  char msg[2] = {motor, intensity};
  return this->Write(msg);
}

int BTManager::Write(const std::string& msg) const
{
  if (port == nullptr)
    return 1;
  try {
    port->Write(msg.c_str(), msg.length());
  }
  catch (BluetoothException& e)
    {
      return 2;
    }
  return 0;
}
