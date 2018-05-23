#include <dlfcn.h>
#include <unistd.h>
#include <iostream>

void testVibrate(void* handle)
{
  // std::cout << "## TEST 1" << std::endl;
  void (*vibrate)(char, char);
  *(void**)(&vibrate) = dlsym(handle, "Vibrate");
  std::cerr << "Turning on motor 0" << std::endl;
  vibrate(0, 255);
  sleep(1);
  std::cerr << "Turning off motor 0" << std::endl;
  vibrate(0, 0);
  sleep(1);
  std::cerr << "Turning on motor 1" << std::endl;
  vibrate(1, 255);
  sleep(1);
  std::cerr << "Turning off motor 1" << std::endl;
  vibrate(1, 0);
  sleep(1);
}

void  testGroups(void* handle)
{
  // std::cout << "## TEST 2" << std::endl;
  void (*newGroup)(const char* const);
  void (*addToGroup)(const char* const, char);
  void (*vibrateGroup)(const char* const, char);
  *(void**)(&newGroup) = dlsym(handle, "NewGroup");
  *(void**)(&addToGroup) = dlsym(handle, "AddToGroup");
  *(void**)(&vibrateGroup) = dlsym(handle, "VibrateGroup");

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
  void (*initrvici)();
  void (*stoprvici)();
  int (*changeManager)(const char* const);
  int (*findDevice)();
  #if __linux
    void* handle = dlopen("libroukavici.so", RTLD_LAZY);
  #elif __APPLE__
    void* handle = dlopen("libroukavici.dylib", RTLD_LAZY);
  #endif

  if (!handle)
    {
      std::cerr << "dlopen(): " << dlerror() << std::endl;
      return 1;
    }
  *(void**)(&initrvici) = dlsym(handle, "InitRVici");
  *(void**)(&stoprvici) = dlsym(handle, "StopRVici");
  *(void**)(&changeManager) = dlsym(handle, "ChangeDeviceManager");
  *(void**)(&findDevice) = dlsym(handle, "FindDevice");

  // Init the lib
  initrvici();
  std::cout << "Testing text manager" << std::endl;
  testVibrate(handle);
  testGroups(handle);
  std::cout << "Switching to BT Manager..." << std::endl;
  // Put in Bluetooth mode
  if (changeManager("BTManager") != 0)
    {
      std::cout << "No BT Manager detected. Stopping here" << std::endl;
      return 1;
    }
  if (findDevice() != 0)
    {
      std::cout << "BT Manager failed to connect. Stopping here" << std::endl;
      return 1;
    }
  std::cout << "Testing BT Manager" << std::endl;
  testVibrate(handle);
  testGroups(handle);
  stoprvici();
  return 0;
}
