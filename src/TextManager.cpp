#include <iostream>
#include "TextManager.hh"
#include "Debug.hh"
#include "Packet.hh"
#include <sstream>

TextManager::TextManager()
{
  // std::cout.setf( std::ios_base::unitbuf );
}

TextManager::~TextManager()
{
}

std::string string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(4 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back('\\');
        output.push_back('x');
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

int TextManager::FindDevice()
{
  std::cout << "Handshake in APIv1: " + string_to_hex(Packet::Handshake(1, 1)) << std::endl;
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

int TextManager::Read(char* buffer, int length) const
{
  std::stringstream ss;
  ss << "Reading " << length << " bytes";
  Debug::Log(ss.str());
  return length;
}


bool TextManager::HasDevice() const
{
  return true; // No actuall device to connect to, this is always true
}

int TextManager::Vibrate(char motor, char intensity) const
{
  std::stringstream ss;
  ss << "Motor " << static_cast<int>(motor) << " vibrating at " <<
    static_cast<int>(static_cast<unsigned char>(intensity)) << ". Packet sent: " << string_to_hex(Packet::v1(motor, intensity));
  Debug::Log(ss.str(), true);
  return 0;
}

DeviceManager* TextManager::create()
{
  return new TextManager();
}
