#include <vector>
#include <iostream>

#include <sstream>
#include "Debug.hh"
#include "Packet.hh"
#include "BTManager.hh"
#include "DeviceINQ.h"
#include "BTSerialPortBinding.h"
#include "BluetoothException.h"

BTManager::BTManager() : inq(DeviceINQ::Create()), port(nullptr) {
}

/// Search for bluetooth devices, if we find the glove connect to it
/**
 * Return codes:
 * 0: Everything OK
 * 1: No device found
 * 2: Device found, could not get channel Id
 * 3: Device found, connection failed (Wrong PIN most likely cause)
 * 4: Handshake failed
 */
int BTManager::FindDevice()
{
  if (port != nullptr)
    {
      delete port;
      port = nullptr;
    }

  {
    std::stringstream ss;
    ss << "[" << this << "] Looking for Bluetooth devices";
    Debug::Log(ss.str());
  }
  // TODO: If this takes too long, just put it in a separate thread and have a mechanism to check
  // Maybe replace HasDevice() with Status(), returning a manager-specific int
  std::vector<device> devices;
    try {
      devices = inq->Inquire(5);
    } catch (BluetoothException& e) {
    std::stringstream ss;
    ss << "Unable to perform inquiry. Do you have a bluetooth device on? BluetoothSerialPort had this to say: " << e.what();
    Debug::Err(ss.str());
  }  
  for (const auto& d: devices)
    {
      {
        std::stringstream ss;
        ss << "\tFound: " << d.name << "(" << d.address << ")" << std::endl;
        Debug::Log(ss.str());
      }
      if (d.name.compare("RoukaVici") == 0)
        {
          // int channelId = inq->SdpSearch(d.address);
          int channelId = 1; // This somehow works better??
          if (channelId == -1)
            {
              Debug::Err("Failed to get device channel ID");
              return 2;
            }
          {
            std::stringstream ss;
            ss << " Channel ID: " << channelId << std::endl;
            Debug::Log(ss.str());
          }
          port = BTSerialPortBinding::Create(d.address, channelId);
          try {
            port->Connect();
            this->Write(Packet::Handshake(1, 1));
            char buffer[2];
            if (this->Read(buffer, 2) < 2 || Packet::HandshakeResult(buffer, 1, 1) != 1)
            {
              Debug::Err("Not enough bytes read");
              delete port;
              port = nullptr;
              return 4;
            }
            return 0;
          }
          catch (BluetoothException&)
            {
              std::stringstream ss;
              ss << "Channel ID: " << channelId;
              Debug::Log(ss.str(), true);
              delete port;
              port = nullptr;
              return 3;
            }
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
  return this->Write(Packet::v1(motor, intensity));
}

int BTManager::Write(const char* msg, int length) const
{
  if (port == nullptr)
    return 1;
  try {
    port->Write(msg, length);
  }
  catch (BluetoothException&) {
      return 2;
  }
  return 0;
}

int BTManager::Write(const std::string& msg) const
{
  return this->Write(msg.c_str(), static_cast<int32_t>(msg.length()));
}

int BTManager::Read(char buffer[], int len) const
{
  if (port == nullptr)
    return -1;
  try {
    return port->Read(buffer, len);
  }
  catch (BluetoothException&) {
    Debug::Err("Failed to read from arduino");
    return -1;
  }
}