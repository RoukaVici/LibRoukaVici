#include <iostream>
#include "LibUsb.hh"
#include "mylibusb.h"
LibUsb::LibUsb() : rpi(NULL), context(NULL)
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

LibUsb::~LibUsb()
{
  if (rpi != NULL)
    {
      libusb_close(rpi);
      rpi = NULL;
    }
  if (context != NULL)
    libusb_exit(context);
}

/// FindRPi finds the raspberry pi and stores it
/**
 * Return codes:
 * 0: Success
 * 1: Lib never initialized properly
 * 2: Couldn't get device list
 * 3: RPi not found
 * 4: Error opening raspberry pi
 */
int LibUsb::FindRPi()
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

bool LibUsb::isRPi(libusb_device* device)
{
  libusb_device_descriptor desc = {0};

  int err = libusb_get_device_descriptor(device, &desc);
  // TODO: check this err
  std::cout << "vendor: " << desc.idVendor << ", prod: "  << desc.idProduct << std::endl;
  return false;
}

void LibUsb::WriteToRPi(const std::string& msg)
{
  std::cout << "MSG: "<< msg << std::endl;
}
