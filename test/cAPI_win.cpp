#include <windows.h>
#include <iostream>

typedef void* (__stdcall *INIT)();
typedef void (__stdcall *END)(void*);

int main() {
    HINSTANCE lib = LoadLibrary("roukavici.dll");

    if (lib == NULL) {
        std::cout << "cannot locate the .dll file" << std::endl;
        return 1;
    }
    INIT init = (INIT)GetProcAddress(lib, "InitRVici");
    END end = (END)GetProcAddress(lib, "StopRVici");
    if (!init || !end)
    {
        std::cout << "Couldn't find function" << std::endl;
        return 1;
    }
    void* handle = init();
    if (!handle)
    {
        std::cout << "Initialization failed" << std::endl;
        return 1;
    }
    end(handle);
    return 0;
}