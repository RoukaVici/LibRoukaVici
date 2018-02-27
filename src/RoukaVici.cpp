#include <iostream>
#include "RoukaVici.hh"
#include "TextManager.hh"

RoukaVici::RoukaVici() : dm(new TextManager())
{
  int err = dm->FindRPi();
}

void RoukaVici::Write(const std::string& msg)
{
  dm->WriteToRPi(msg);
}

RoukaVici::~RoukaVici()
{
  delete dm;
}
