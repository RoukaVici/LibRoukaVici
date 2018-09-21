// Tests a C++ thread with C api, with data started & deleted in different threads

#include <thread>
#include "RoukaVici.hh"
#include <string.h>
#include <dlfcn.h>

# define GETFUNC(funchandle, lib, funcName) (*(void**)(&funchandle) = dlsym(lib, funcName))

int result = 1;
const char* err = "[LibRV.ERR]";
const size_t errLen = strlen(err);
const char* needle = "[LibRV.LOG] Motor 0 vibrating at 255";
const size_t len = strlen(needle);

void callbackFunc(const char* str)
{
    if (strncmp(str, err, errLen) == 0) {
        result = -1;
    }
    if (result >= 0 && strncmp(str, needle, len) == 0)
        result = 0;
}

void  test1(void* lib)
{
    void* (*initrvici)();
    if (!lib)
    {
        result = -2;
        return;
    }
    GETFUNC(initrvici, lib, "InitRVici");
    initrvici();
}

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

int main() {
    void (*stoprvici)();

    #if __linux
        void* lib = dlopen("libroukavici.so", RTLD_LAZY);
    #elif __APPLE__
        void* lib = dlopen("libroukavici.dylib", RTLD_LAZY);
    #endif

    RoukaVici::SetLogMode(2);
    RoukaVici::RegisterDebugCallback(&callbackFunc);
    GETFUNC(stoprvici, lib, "StopRVici");
    std::thread first(test1, lib);
    first.join();
    if (result < 0) {
        stoprvici();
        return result;
    }
    std::thread second(testVibrate, lib);
    second.join();
    return result;
}