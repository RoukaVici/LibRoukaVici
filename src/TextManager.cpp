#include <iostream>
#include "TextManager.hh"

TextManager::TextManager()
{
  
}

TextManager::~TextManager()
{
  
}

int TextManager::FindRPi()
{
  return 0;
}

void TextManager::WriteToRPi(const std::string& msg)
{
  std::cout << msg.c_str();
}
