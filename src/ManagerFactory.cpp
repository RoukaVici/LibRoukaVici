#include "ManagerFactory.hh"

#include "TextManager.hh"
// If the user wants to use libusb
#ifdef LIBUSB_COMPILE
  #include "USBManager.hh"
#endif

ManagerFactory::ManagerFactory()
{
  // Here we'll add every manager, including those in options
  managers["TextManager"] = TextManager::create;
}


ManagerFactory::~ManagerFactory()
{
}

DeviceManager* ManagerFactory::get(const std::string& name)
{
  DMNGR_CREATOR cr = managers[name];
  // TODO: Check if it exists first.
  return cr();
}
