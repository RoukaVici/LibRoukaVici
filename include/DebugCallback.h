#pragma once

#ifdef _WIN32
    // This allows us to receive functions from Unity
    typedef void(__stdcall * UnityDebugCallback) (const char * str);
    typedef void(__stdcall * DebugCallback) (const char * str);
#else
    typedef void (*UnityDebugCallback)(const char* str);
    typedef void (*DebugCallback)(const char* str);
#endif