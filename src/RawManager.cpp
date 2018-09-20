#include <iostream>
#include "Packet.hh"
#include "RawManager.hh"

RawManager::RawManager()
{
  std::cout.setf( std::ios_base::unitbuf );
}

int RawManager::FindDevice()
{
  this->Write(Packet::Handshake(1, 1));
  return 0; // Always succeed, we can't read the result
}

int RawManager::Write(const std::string& msg) const
{
  return this->Write(msg.c_str(), static_cast<int32_t>(msg.length()));
}
int RawManager::Read(char* buffer, int length) const
{
  (void)buffer;
  (void)length;
  return 0; // Can't read in this mode for now
}

int RawManager::Write(const char* msg, int length) const
{
  int i=0;
  while (i < length) {
    std::cout << msg[i];
    i++;
  }
  return 0;
}

bool RawManager::HasDevice() const
{
  return true; // No actuall device to connect to, this is always true
}

int RawManager::Vibrate(char motor, char intensity) const
{
  return this->Write(Packet::v1(motor, intensity));
}

DeviceManager* RawManager::create()
{
  return new RawManager();
}
