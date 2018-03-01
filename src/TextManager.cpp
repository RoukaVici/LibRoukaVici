#include <iostream>
#include "TextManager.hh"

TextManager::TextManager()
{
}

TextManager::~TextManager()
{
}

int TextManager::FindDevice()
{
  return 0; // Always succeed
}

void TextManager::Write(const std::string& msg) const
{
  std::cout << msg.c_str();
}

bool TextManager::HasDevice() const
{
  return true; // No actuall device to connect to, this is always true
}

void TextManager::Vibrate(char motor, char intensity) const
{
  std::cout << motor << intensity;
}
