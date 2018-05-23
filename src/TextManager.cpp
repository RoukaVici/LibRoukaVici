#include <iostream>
#include "TextManager.hh"

TextManager::TextManager()
{
  std::cout.setf( std::ios_base::unitbuf );
}

TextManager::~TextManager()
{
}

int TextManager::FindDevice()
{
  return 0; // Always succeed
}

int TextManager::Write(const std::string& msg) const
{
  std::cout << msg.c_str();
  return 0;
}

bool TextManager::HasDevice() const
{
  return true; // No actuall device to connect to, this is always true
}

int TextManager::Vibrate(char motor, char intensity) const
{
  std::cout << "Motor " << static_cast<int>(motor) << " vibrating at " << static_cast<int>(intensity) << std::endl;
  return 0;
}

DeviceManager* TextManager::create()
{
  return new TextManager();
}
