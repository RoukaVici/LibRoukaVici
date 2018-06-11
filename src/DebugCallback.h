#pragma once

#ifdef _WIN32
// This allows us to receive functions from Unity
typedef void(__stdcall * UnityDebugCallback) (const char * str);
#else
typedef void (*UnityDebugCallback)(const char* str);
#endif

typedef void (*DebugCallback)(const char* str);
