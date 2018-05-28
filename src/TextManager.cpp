#include <iostream>
#include "TextManager.hh"
#include "Debug.hh"
#include <sstream>

TextManager::TextManager()
{
  // std::cout.setf( std::ios_base::unitbuf );
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
  return this->Write(msg.c_str(), msg.length());
}

int TextManager::Write(const char* msg, int length) const
{

  std::stringstream ss;
  ss << "Wrote: '" << msg << "' with length " << length;
  Debug::Log(ss.str());
  return 0;
}


bool TextManager::HasDevice() const
{
  return true; // No actuall device to connect to, this is always true
}

int TextManager::Vibrate(char motor, char intensity) const
{
  std::stringstream ss;
  ss << "[LibRoukaVici] Motor " << static_cast<int>(motor) << " vibrating at " <<
    static_cast<int>(static_cast<unsigned char>(intensity));
  Debug::Log(ss.str(), true);
  return 0;
}

DeviceManager* TextManager::create()
{
  return new TextManager();
}
