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

  virtual int FindDevice();
  virtual bool HasDevice() const;
  virtual void Write(const std::string& msg) const;
  virtual void Vibrate(char motor, char intensity) const;
};
