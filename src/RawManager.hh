#pragma once

#include "DeviceManager.hh"

/// This class prints out data sent to it as raw bytes
/**
 * Used for debugging, you can pipe the output to the glove in whatever way you want
 */
class RawManager : public DeviceManager
{
public:
  RawManager();
  ~RawManager();

  static DeviceManager* create();

  virtual int FindDevice();
  virtual bool HasDevice() const;
  virtual int Write(const std::string& msg) const;
  virtual int Write(const char* msg, int length) const;
  virtual int Vibrate(char motor, char intensity) const;
};
