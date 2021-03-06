# RoukaVici Library
This library provides an API between the computer and the RoukaVici glove. It aims to function both on Linux and on Windows.

# Dependencies
## Linux & MacOS
- `cmake >= 3.9`
- `g++` (not tested with `clang` yet)
- `libdl` (Optional, for tests. Can be ignored by setting off tests with -DTEST=FALSE)
- Bluetooth headers (Optional but strongly recommended to be able to build with Bluetooth support)

## Windows
- `cmake >= 3.9`
- `Visual Studio` with `C++ Build Tools` installed (in other words, you need to have MSVC++ installed)

# Building
## Build instructions
These instructions are valid on all platforms, including Windows (using Powershell)
- `git submodule update --init`: Start by making sure you have all submodules
- `mkdir build && cd build/`
- `cmake [-G "<Generator>"] [flags] ..`: Generate build files. See Flags and Generators sections for build options, default should be fine for most uses.
- `cmake --build .`: Build libraries and binaries
- Output files for Linux & MacOS: `build/libroukavici.so` and `build/lib/bluetooth-serial-port/bluetoothserialport.so`
- Output files for Windows: `build/Debug/roukavici.dll`, `build/Debug/roukavici.lib` and `build/Debug/lib/bluetooth-serial-port/bluetoothserialport.dll`.
- If you've built test binaries, running `ctest` in the `build/` directory will run a suite of unit tests. See Executables - Unit Tests section.
- The interactive command shell, `interactive`, provides you with a quick way to send signals to the glove without building an application yourself. Run it and follow the instructions on screen.

**Note**: As of this writing, MacOS cannot compile the Bluetooth library. Run cmake with `-DBT=FALSE` option if build fails.

## Generators
Your platform has a default generator (compiler) they're using, but you may want to use a different one. For example, Windows builds binaries in 32bit by default. If you want them in 64bit, you have to use the 64bit version of your compiler. `cmake --help` will give you a list of all available generators on your platform, here are some common ones you might want to use:
- `cmake -G "Unix Makefiles"`: Default on unix systems, generates a standard Makefile.
- `cmake -G "Visual Studio 15 2017"`: Default on Windows, builds using MSVC++ in 32bit.
- `cmake -G "Visual Studio 15 2017 Win64"`: MSVC++ in 64bit.

## Build flags
- `-DTESTS`: Combile test binaries, see Executables section for more info. TRUE on Linux, FALSE otherwise by default.
- `-DBT`: Compile with Bluetooth support. TRUE by default
- `-DVERB`: Compile in verbose mode. If set to FALSE, the library will print no log messages to the standard output, only displaying errors on the error output. TRUE by default.

# Project Folders Overview
- `include/` contains all the public header you might need to interact with the library. Just copy them wherever you want AFTER compiling. Note that you need to compile using `cmake` in order to generate one of the headers for your platform, `roukavici_export.h`.
- `lib/` contains RoukaVici's dependencies' sources. They're submodules, so if there's nothing there you forgot to initialize the gut submodules.
- `output/` will contain the compiled libraries and executables. Note that test binaries won't be put there since there's a lot of them - they go in the build directory.
- `src/` contains RoukaVici's source files as well as private headers. This is where you'll go if you want to learn more about RoukaVici internals.
- `test/` contains source files for test files and for the interactive command line.
- `toolchain/` contains files for cross-platform build (for example, building for Windows on Linux)

# How to use
## C++
Link to the dynamic library and use the header `RoukaVici.hh`. You have to create the RoukaVici object, whose destruction *you* are responsible for. From there, you can call all of the `RoukaVici` class' methods contained in the header:
```cpp
#include "RoukaVici.hh"
#include <unistd.h>
#include <iostream>

int main() {
  int res;
  RoukaVici *rv = new RoukaVici();  // Initialize the library
  // Library is now in text mode, it will print vibrations to the standard output in human-readable format

  res = rv->Vibrate(0, 255); // Send vibration to motor 0, at full strength (intensity values are 0-255)
  if (res != 0) {
    std::cerr << "Write on failed" << std::endl;
    goto finish;
  }
  usleep(1000000);
  res = rv->Vibrate(0, 0); // Stop motor 0
  if (res != 0) {
    std::cerr << "Write off failed" << std::endl;
    goto finish;
  }
 finish:
  delete rv;
  return res;
}
```

The file `test/Groups.cpp` very similarly shows how to establish a connection to the device in Bluetooth using the CPP object directly. In the rest of this document, the `RoukaVici.X` method will simply refer to the method named `X` of the RoukaVici object.

## Other Languages: The C API
If your language can import C functions through a dynamic library, then you can use RoukaVici through its C API. You might want to use the `RoukaViciAPI.h` header for reference. It has all exposed library functions. From there, you can call these functions by name by using whatever dynamic library system your language and OS use. Here's a snippet of how to do this on Linux, in C:

```c
  #include <dlfcn.h>
  #include <unistd.h>

int main()
{
  // This function returns the opaque handler to the library
  void* (*initrvici)();
  // Pass the handler to this function to stop the library
  void (*stoprvici)(void*);
  // Vibrate motor x with intensity n
  void (*vibrate)(void*, char x, char n);


  // Open the library  
  void* lib = dlopen("libroukavici.so", RTLD_LAZY);

  // Import functions from the library
  *(void**)(&initrvici) = dlsym(lib, "InitRVici");
  *(void**)(&stoprvici) = dlsym(lib, "StopRVici");
  *(void**)(&vibrate) = dlsym(lib, "Vibrate");

  void* handle = initrvici();
  vibrate(handle, 0, 255);
  vibrate(handle, 0, 0);
  stoprvici(handle);
  return 0;
}
```

This method exposes no more or less functions than using the C++ one. The C API is a perfect mirror of every public method in the `RoukaVici` class, and is simply less convenient to use. In the rest of this document, the `RoukaVici.X` method will simply refer to the method named `X` of the RoukaVici lib, which you can import directly from the shared object.

`test/cAPI.cpp` has a working example of how to do this __on Linux/Mac__ in C/C++. The windows version is `test/cAPI_win.cpp`.

# How does it work?
## Flow
- Before initialization, *you can call RoukaVici methods related to logging*, so that you can get accurate logging during initialization. More information in the "Logging" section.
- Initialize the library, either by creating a new `RoukaVici` object (in C++) or by calling `RoukaVici.InitRVici` (if you're using the C API). In the latter case, `InitRVici` returns an opaque handler which you have to use to interact with the library (it's the first argument for every function, except logging functions which don't need it).
- Change to the device manager of your choice using `RoukaVici.ChangeDeviceManager`. If you'd like to use the text (debug) mode, skip this step. More info about device managers in the Device Managers subsection.
- You can now call `RoukaVici.FindDevice` to allow the manager to find and connect to the device. This could take a while depending on which manager you're using.
- Check that the device was found using `RoukaVici.HasDevice`, which returns a boolean.
- You can now call the `RoukaVici.Vibrate` function. Congratulations, you can now communicate with RoukaVici. You can also set groups, every function you have access to is in whichever `RoukaVici` header file you're using.
- When you're done, delete the `RoukaVici` object (if you're in C++) or call `Roukavici.StopRVici` (if you're using the C API).

**Note**: Every function returns 0 in case of success, except InitRVici which returns a pointer to an opaque handler.

## Device Managers
The RoukaVici library uses different DeviceManagers to connect to the glove. This is useful for debugging, as the lib provides you with multiple means of communicating between yourself and the glove. The supported ones as of this writing are:

- TextManager (default): Doesn't connect to the glove at all. This manager is on when the library is initialized. If you send vibrations through the TextManager, it prints the motor number and the intensity in the console. Very useful for debugging.
- BTManager: Connects to the glove through Bluetooth, using a cross-platform library (`lib/bluetooth-serial-port`).
- RawManager: Prints out the motor number and intensity as raw bytes when a vibration order is sent. There's very few reasons anyone would use this, but you can use it to send data directly to the glove through whatever mean you want.

You can change to any device manager at any time by calling `RoukaVici.ChangeDeviceManager` with the name of the device as parameter. Keep in mind that if this fails, you may not have built the library with support for that device (see Build Flags).

## Logging
RoukaVici has multiple modes of logging available. You can change these by calling `RoukaVici.SetLogMode` with an int parameter equal to the log method you want:
- 0: Standard output
- 1: File
- 2: Callback
- 4: Silent

**Note**: RoukaVici will be silent (except for errors) if it is compiled without the VERBOSE flag, see compilation flags section!

### Standard Output (0, default)
By default, RoukaVici will output its messages to the standard output. Error messages will be printed to the standard error channel.

### File (1)
You can ask RoukaVici to log to file instead. By default, RoukaVici will log to the current directory in a file called `RoukaViciLog.txt`. You can change this by calling `RoukaVici.SetLogFile`.

### Callback (2)
If you enable this, RoukaVici will log its messages to a callback function of your choice. You pass the function to RoukaVici by using the `RoukaVici.SetDebugCallback` function. The function should be of the form:
```C
void function(const char* message);
```

### Silent (4)
Silent mode tells the library not to output logging and error messages.

# Executables
RoukaVici comes bundled with a few test suites as well as an interactive command-line utililty.

## Interactive Command Line
The interactive command line is a small program which provides a very barebones executable letting you interact with gloves easily. It lets you change Device Managers and lets you send vibration orders. This is particularly useful to debug issues with glove connection.
Launch the binary for usage. It is very barebones, and has no guarantee of functioning in every edge case. There is no guarantee that this binary will ever be backwards-compatible or even remain as is in the library, do not use it programatically to communicate with RoukaVici.

## Unit Tests
RoukaVici provides you with unit tests which run automatically after compilation if enabled. The argument to pass `cmake` is `-DTESTS=TRUE`, and once the library is built, you can run `ctest` to run the test suite. You can find their sources in the `test/` folder. These tests are all separate binaries, each testing a specific feature:
- `cAPI.cpp`: Tests the C API linking and function calling. Only on Unix systems for now.
- `BT.cpp`: Tests changing to the Bluetooth device manager, the handshake and a vibration order.
- `Callback.cpp`: Tests the callback system for logging.
- `Groups.cpp`: Tests vibration groups.