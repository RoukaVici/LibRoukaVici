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

#ifdef ROUKAVERBOSE
  std::cout << "[LibRoukaVici][" << this << "] Looking for Bluetooth devices" << std::endl;
#endif

  // TODO: If this takes too long, just put it in a separate thread and have a mechanism to check
  // Maybe replace HasDevice() with Status(), returning a manager-specific int
  std::vector<device> devices = inq->Inquire(3);
  for (const auto& d: devices)
    {
#ifdef ROUKAVERBOSE
      std::cout << "[LibRoukaVici]\tFound: " << d.name << "/" << d.address<< std::endl;
#endif
      if (d.name.compare("RoukaVici") == 0)
        {
          // int channelId = inq->SdpSearch(d.address);
          int channelId = 1; // This somehow works better??
          if (channelId == -1)
            {
              std::cerr << "[LibRoukaVici] Failed to get device channel ID" << std::endl;
              return 2;
            }
#ifdef ROUKAVERBOSE
          std::cout << "[LibRoukaVici] Channel ID: " << channelId << std::endl;
#endif
          port = BTSerialPortBinding::Create(d.address, channelId);
          try {
            port->Connect();
          }
          catch (BluetoothException& e)
            {
              std::cerr << "[LibRoukaVici] Could not connect to the device, did you enter the right PIN?" << std::endl;
              delete port;
              port = nullptr;
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
  return this->Write(msg, 2);
}

int BTManager::Write(const char* msg, int length) const
{
  if (port == nullptr)
    return 1;
  try {
    port->Write(msg, length);
  }
  catch (BluetoothException& e) {
      return 2;
  }
  return 0;
}


int BTManager::Write(const std::string& msg) const
{
  return this->Write(msg.c_str(), msg.length());
}
