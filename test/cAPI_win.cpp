#include <windows.h>
#include <iostream>

typedef void* (__stdcall *INIT)();
typedef void (__stdcall *END)();

int main() {
    HINSTANCE lib = LoadLibrary("roukavici.dll");

    if (lib == NULL) {
        std::cerr << "cannot locate the .dll file" << std::endl;
        return 1;
    }
    INIT init = (INIT)GetProcAddress(lib, "InitRVici");
    END end = (END)GetProcAddress(lib, "StopRVici");
    if (!init || !end)
    {
        std::cerr << "Couldn't find function" << std::endl;
        return 1;
    }
    init();
    end();
    return 0;
}