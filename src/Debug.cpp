#include <iostream>
#include "Debug.hh"

DebugCallback cb = nullptr;

void Debug::RegisterCallback(DebugCallback callback)
{
  if (callback)
    {
      cb = callback;
    }
}

void Debug::Log(const std::string& msg, bool force)
{
  if (cb)
    {
#ifndef ROUKAVERBOSE
      if (force)
#else
        (void)(force);
#endif
        cb(msg.c_str());
    }
}

// Prints on stdout
void Debug::defaultLog(const char* msg)
{
  std::cout << msg << std::endl;
}
