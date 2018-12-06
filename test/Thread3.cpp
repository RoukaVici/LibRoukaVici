// Tests a C++ thread with C++ api, with data started & deleted in the same thread
#include <vector>
#include <thread>
#include "RoukaVici.hh"
#include <string.h>
#include <cstdlib>
#include <ctime>

int result = 0;
const char* err = "[LibRV.ERR]";
const size_t errLen = strlen(err);

RoukaVici* rv = new RoukaVici();

typedef void (*threadFunc)();

void callbackFunc(const char* str)
{
    if (strncmp(str, err, errLen) == 0) {
        result = 1;
    }
}

void   vibrate()
{
    if (rv->Vibrate(0, 255)) {
        result = 2;
    }
}

void changedevice()
{
    std::string devices[2] = {"TextManager", "RawManager"};
    if (rv->ChangeDeviceManager(devices[std::rand() % 2])) {
        result = 3;
    }
}

int main() {
    std::srand(std::time(0));
    RoukaVici::SetLogMode(2);
    RoukaVici::RegisterDebugCallback(&callbackFunc);
    std::vector<std::thread *> threads;
    const int functionCount = 2;
    threadFunc functions[functionCount] = {&vibrate, &changedevice};
    for (int i=0 ; i < 100 ; i++) {
        threads.push_back(new std::thread(functions[std::rand() % functionCount]));
    }
    for (auto thr : threads) {
        thr->join();
        delete thr;
    }
    delete rv;
    return result;
}