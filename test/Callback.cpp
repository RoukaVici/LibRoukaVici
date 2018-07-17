#include "RoukaVici.hh"

int callbacks = 0;

void callbackFunc(const char* str)
{
    callbacks += 1;
}

int main()
{
    RoukaVici::RegisterDebugCallback(&callbackFunc);
    RoukaVici *rv = new RoukaVici();
    delete rv;
    return callbacks > 0 ? 1 : 0;
}