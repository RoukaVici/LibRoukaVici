#pragma once

#include "DeviceManager.hh"

/// This class prints out data sent to it.
/**
 * Can be used along with netcat and piping to do networking,
 * or for debugging purposes
 */
class TextManager : public DeviceManager
{
public:
  TextManager();
  ~TextManager();

  virtual int FindRPi();
  virtual void WriteToRPi(const std::string& msg);
};
