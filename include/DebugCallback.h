#pragma once

#ifdef _WIN32
    // This allows us to receive functions from Windows
    typedef void (__stdcall * DebugCallback) (const char * str);
#else
    typedef void (*DebugCallback) (const char* str);
#endif