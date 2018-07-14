#include <dlfcn.h>
#include <unistd.h>
#include <iostream>

void testVibrate(void* rv, void* lib)
{
  // std::cout << "## TEST 1" << std::endl;
  void (*vibrate)(void*, char, char);
  *(void**)(&vibrate) = dlsym(lib, "Vibrate");
  std::cerr << "Turning on motor 0" << std::endl;
  vibrate(rv, 0, 255);
  std::cerr << "Turning off motor 0" << std::endl;
  vibrate(rv, 0, 0);
  std::cerr << "Turning on motor 1" << std::endl;
  vibrate(rv, 1, 255);
  std::cerr << "Turning off motor 1" << std::endl;
  vibrate(rv, 1, 0);
}

void  testGroups(void* lib)
{
  // std::cout << "## TEST 2" << std::endl;
  void (*newGroup)(const char* const);
  void (*addToGroup)(const char* const, char);
  void (*vibrateGroup)(const char* const, char);
  *(void**)(&newGroup) = dlsym(lib, "NewGroup");
  *(void**)(&addToGroup) = dlsym(lib, "AddToGroup");
  *(void**)(&vibrateGroup) = dlsym(lib, "VibrateGroup");

  // Create a group which has motors 0 and 1, then make them vibrate for a second
  newGroup("mygroup");
  addToGroup("mygroup", 0);
  addToGroup("mygroup", 1);
  std::cerr << "Turning on motors 0+1" << std::endl;
  vibrateGroup("mygroup", 255);
  sleep(1);
  std::cerr << "Turning off motors 0+1" << std::endl;
  vibrateGroup("mygroup", 0);
  sleep(1);
}

int main()
{
  void* (*initrvici)();
  void (*stoprvici)(void*);
  int (*changeManager)(void*, const char*);
  int (*findDevice)(void*);
  #if __linux
    void* lib = dlopen("libroukavici.so", RTLD_LAZY);
  #elif __APPLE__
    void* lib = dlopen("libroukavici.dylib", RTLD_LAZY);
  #endif

  if (!lib)
    {
      std::cerr << "dlopen(): " << dlerror() << std::endl;
      return 1;
    }
  *(void**)(&initrvici) = dlsym(lib, "InitRVici");
  *(void**)(&stoprvici) = dlsym(lib, "StopRVici");
  *(void**)(&changeManager) = dlsym(lib, "ChangeDeviceManager");
  *(void**)(&findDevice) = dlsym(lib, "FindDevice");

  // Init the lib
  void* rv = initrvici();
  std::cout << "Testing text manager" << std::endl;
  testVibrate(rv, lib);
/*   std::cout << "Switching to BT Manager..." << std::endl;
  // Put in Bluetooth mode
  if (changeManager("BTManager") != 0)
    {
      std::cout << "No BT Manager detected. Stopping here" << std::endl;
      goto endtest;
    }
  if (findDevice() != 0)
    {
      std::cout << "BT Manager failed to connect. Stopping here" << std::endl;
      goto endtest;
    }
  std::cout << "Testing BT Manager" << std::endl;
  testVibrate(lib);
  testGroups(lib);
 */ endtest:
  stoprvici(rv);
  return 0;
}