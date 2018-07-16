#pragma once

#include "DeviceManager.hh"

/// This class prints out data sent to it in a human-readable format.
/**
 * Used for debugging purposes
 */
class TextManager : public DeviceManager
{
public:
  TextManager();
  ~TextManager();

  static DeviceManager* create();

  virtual int FindDevice();
  virtual bool HasDevice() const;
  virtual int Write(const std::string& msg) const;
  virtual int Write(const char* msg, int length) const;
  virtual int Read(char* buffer, int length) const;
  virtual int Vibrate(char motor, char intensity) const;
};
