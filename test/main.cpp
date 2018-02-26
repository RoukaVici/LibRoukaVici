#include <dlfcn.h>
#include <iostream>

int main(int argc, char **argv)
{
  void (*initrvici)();
  void (*stoprvici)();

  void* handle = dlopen("libroukavici.so", RTLD_LAZY);
  if (!handle)
    {
      std::cerr << "dlopen(): " << dlerror() << std::endl;
      return 1;
    }
  *(void**)(&initrvici) = dlsym(handle, "InitRVici");
  *(void**)(&stoprvici) = dlsym(handle, "StopRVici");
  initrvici();
  stoprvici();
  return 0;
}
