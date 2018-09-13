/// THIS FILE DOES NOT INTERACT WITH ANY OTHER FILE DIRECTLY
/**
 * It is just here to centralize device manager destructors
 */
#include "DeviceManager.hh"
#include "BTManager.hh"
#include "RawManager.hh"
#include "TextManager.hh"
#include "DeviceINQ.h"
#include "BTSerialPortBinding.h"

DeviceManager::~DeviceManager() {}

BTManager::~BTManager()
{
  if (port != nullptr)
    {
      delete port;
    }
  delete inq;
}

RawManager::~RawManager()
{
}

TextManager::~TextManager()
{
}

