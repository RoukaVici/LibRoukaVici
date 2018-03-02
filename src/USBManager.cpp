#include <iostream>
#include "USBManager.hh"
#include "mylibusb.h"

USBManager::USBManager() : rpi(NULL), context(NULL)
{
  // Initialize libusb
  int err = 0;
  err = libusb_init(&context);
  if (err != 0)
    {
      std::cerr << "Could not initialize libusb" << std::endl;
      context = NULL;
    }
}

USBManager::~USBManager()
{
  if (rpi != NULL)
    {
      libusb_close(rpi);
      rpi = NULL;
    }
  if (context != NULL)
    libusb_exit(context);
}

int USBManager::FindDevice()
{
  int errCode = 0;
  if (context == NULL)
    return 1;
  // Find the raspberry, put it in rpi if we do
  libusb_device**  list;
  ssize_t cnt = libusb_get_device_list(NULL, &list);
  ssize_t i = 0;
  if (cnt < 0)
    {
      std::cerr << "Error getting device list" << std::endl;
      errCode = 2;
    }
  //Put the raspberry pi in "rpi" if we can find it
  for (i=0 ; i<cnt ; i++)
    {
      libusb_device* device = list[i];
      if (isRPi(device))
        {
          int err = libusb_open(device, &rpi);
          if (err)
            {
              std::cerr << "Error opening the USB device" << std::endl;
              rpi = NULL;
              errCode = 4;
            }
          break;
        }
    }
  if (errCode == 0 && rpi == NULL)
    {
      std::cerr << "Raspberry pi not found" << std::endl;
      errCode = 3;
    }
  libusb_free_device_list(list, 1);
  return errCode;
}

bool USBManager::isRPi(libusb_device* device)
{
  libusb_device_descriptor desc = {0};

  int err = libusb_get_device_descriptor(device, &desc);
  // TODO: check this err
  std::cout << "vendor: " << desc.idVendor << ", prod: "  << desc.idProduct << std::endl;
  return false;
}

bool USBManager::HasDevice() const
{
  return rpi != NULL;
}

void USBManager::Vibrate(char motor, char intensity) const
{
  // TODO: Send data
}

void USBManager::Write(const std::string& msg) const
{
  // TODO: Send data
}
