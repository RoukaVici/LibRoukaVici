// Tests a C++ thread with C++ api, with data started & deleted in the same thread

#include <thread>
#include "RoukaVici.hh"
#include <string.h>

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

void   test1()
{
    RoukaVici* rv = new RoukaVici();
    if (rv->Vibrate(0, 255))
        result = -1;
    delete rv;
}

int main() {
    RoukaVici::SetLogMode(2);
    RoukaVici::RegisterDebugCallback(&callbackFunc);
    std::thread first(test1);
    first.join();
    return result;
}