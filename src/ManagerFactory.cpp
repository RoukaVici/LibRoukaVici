#include <sstream>
#include "Debug.hh"
#include "ManagerFactory.hh"

#include "TextManager.hh"
#include "RawManager.hh"
// If the user wants to use libusb
#ifdef LIBUSB_COMPILE
# include "USBManager.hh"
#endif

// If the user wants to use bluetooth
#ifdef BT_COMPILE
# include "BTManager.hh"
#endif

#ifdef TCP_COMPILE
# include "TCPManager.hh"
#endif

ManagerFactory::ManagerFactory()
{
  std::stringstream ss;
  ss << "Initializing with modules:";
  // Here we'll add every manager, including those in options
  managers["TextManager"] = TextManager::create;
  managers["RawManager"] = RawManager::create;
  // If the user asked to compile with an option, we add this option to the factory
#ifdef LIBUSB_COMPILE
  managers["USBManager"] = USBManager::create;
  ss << " USBManager";
#endif

#ifdef BT_COMPILE
  managers["BTManager"] = BTManager::create;
  ss << " BTManager";
#endif

#ifdef TCP_COMPILE
  managers["TCPManager"] = TCPManager::create;
  ss << " TCPManager";
#endif
  Debug::Log(ss.str());
}


ManagerFactory::~ManagerFactory()
{
}

DeviceManager* ManagerFactory::get(const std::string& name)
{
  // Managers is a map containing the create() functions of the proper class
  if (managers.find(name) == managers.end())
    {
      std::stringstream ss;
      ss << "No Manager by the name of:" << name;
      Debug::Log(ss.str());

      return nullptr;
    }
  // The functor exists, we return its value, which should be a pointer to the proper class
  return managers[name]();
}
