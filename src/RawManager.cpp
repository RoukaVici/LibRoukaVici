#include <iostream>
#include "RawManager.hh"

RawManager::RawManager()
{
  std::cout.setf( std::ios_base::unitbuf );
}

RawManager::~RawManager()
{
}

int RawManager::FindDevice()
{
  return 0; // Always succeed
}

int RawManager::Write(const std::string& msg) const
{
  return this->Write(msg.c_str(), msg.length());
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
  char msg[2] = {motor, intensity};
  return this->Write(msg, 2);
} 

DeviceManager* RawManager::create()
{
  return new RawManager();
}
