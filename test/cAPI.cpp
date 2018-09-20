#include <iostream>
# include <dlfcn.h>
# include <unistd.h>

# define GETFUNC(funchandle, lib, funcName) (*(void**)(&funchandle) = dlsym(lib, funcName))

int testVibrate(void* lib)
{
  int (*vibrate)(char, char);
  GETFUNC(vibrate, lib, "Vibrate");
  if (vibrate(0, 255)) goto error;
  if (vibrate(0, 0)) goto error;
  return 0;
error:
  return 1;
}

int main(int argc, const char** argv)
{
  int ret = 0;
  void* (*initrvici)();
  void (*stoprvici)();

  #if __linux
    void* lib = dlopen("libroukavici.so", RTLD_LAZY);
  #elif __APPLE__
    void* lib = dlopen("libroukavici.dylib", RTLD_LAZY);
  #endif

  if (!lib)
    {
      std::cerr << "Could not open library" << std::endl;
      return 2;
    }
  GETFUNC(initrvici, lib, "InitRVici");
  GETFUNC(stoprvici, lib, "StopRVici");

  // Init the lib
  initrvici();
  if (testVibrate(lib)) {
      std::cerr << "Vibration order failed" << std::endl;
    ret = 1;
  }
  stoprvici();
  return ret;
}
