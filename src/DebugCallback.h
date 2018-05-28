#pragma once

#ifdef _WIN32
typedef void(__stdcall * DebugCallback) (const char * str);
#else
typedef void (*DebugCallback)(const char * str);
#endif
