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
    }
    void* handle = init();
    end(handle);
    return 0;
}