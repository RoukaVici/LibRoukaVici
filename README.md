# RoukaVici Library
This library provides an API between the computer and the RoukaVici glove. It aims to function both on Linux and on Windows.

# Dependencies
## Linux & MacOS
- `cmake >= 3.9`
- `g++` (not tested with `clang` yet)
- `libdl` (Optional, for tests. Can be ignored by setting off tests with -DTEST=FALSE)

## Windows
- `cmake >= 3.9`
- `Visual Studio` with `C++ Build Tools` installed (in other words, you need to have MSVC++ installed)

# Building
## Linux & MacOS
- `mkdir build && cd build/ && cmake .. [flags]`
- `cmake --build .`
- Output files: `build/libroukavici.so` and `build/lib/bluetooth-serial-port/bluetoothserialport.so`

**Note**: As of this writing, MacOS cannot compile the Bluetooth library. Run cmake with `-DBT=FALSE` option if build fails.

## Windows (Powershell)
- `mkdir build && cd build/ && cmake .. [flags]`
- `cmake --build .`
- Output files: `build/Debug/roukavici.dll`, `build/Debug/roukavici.lib` and `build/Debug/lib/bluetooth-serial-port/bluetoothserialport.dll`.

## Build flags
- `-DTEST`: Decides if the test binaries should be compiled. TRUE on Linux, FALSE otherwise by default.
- `-DBT`: Decides if the lib should be compiled with Bluetooth support. TRUE by default
- `-DVERB`: Decides if the lib should be compiled in verbose mode. If set to FALSE, the library will print no log messages to the standard output, only displaying errors on the error output. TRUE by default.

Not currently maintained, but still in the CMake:
- `-DUSB`: Decides if the lib is compiled with USB support. FALSE by default.
- `-DTCP`: Decides if the lib should be compiled with TCP support. FALSE by default

# How to use
## C++
Link to the dynamic library and use the header `RoukaVici.hh`. From there, you can call all of the `RoukaVici` class' methods contained in the header:
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

The file `test/maincpp.cpp` very similarly shows how to establish a connection to the device in Bluetooth using the CPP object directly.

## Other Languages
If your language can import C functions through a dynamic library, then you can use RoukaVici through its C API. You want to use the `RoukaViciAPI.h` header for reference. It has all exposed library functions. From there, you can call these functions by name by using whatever dynamic library system your language and OS use.

This method exposes no more or less functions than using the C++ one. The C API is a perfect mirror of every public method in the `RoukaVici` class, and is simply less convenient. In the rest of this document, the `RoukaVici.X` method will simply refer to the method named `X` of the RoukaVici lib, which you can import directly from the shared object.

`test/main.cpp` has an example of how to do this __on Linux__ in C/C++, your mileage may vary.

# How does it work?
## Flow
- Initialize the library, either by creating a new `RoukaVici` object (in C++) or by calling `RoukaVici.InitRVici` (if you're using the C API).
- Change to the device manager of your choice using `RoukaVici.ChangeDeviceManager`. If you'd like to use the text (debug) mode, skip this step. More info about device managers in the next subsection.
- You can now call `Roukavici.FindDevice` to allow the manager to find and connect to the device. This could take a while depending on which manager you're using.
- Check that the device was found using `RoukaVici.HasDevice`, which returns a boolean.
- You can now call the `RoukaVici.Vibrate` function. Congratulations, you can now communicate with RoukaVici. You can also set groups, every function you have access to is in whichever `RoukaVici` header file you're using.

## Device Managers
The RoukaVici library uses different DeviceManagers to connect to the glove. This is useful for debugging, as the lib provides you with multiple means of communicating between yourself and the glove. The supported ones as of this writing are:

- TextManager (default): Doesn't connect to the glove at all. This manager is on when the library is initialized. If you send vibrations through the TextManager, it prints the motor number and the intensity in the console. Very useful for debugging.
- BTManager: Connects to the glove through Bluetooth, using a cross-platform library (`lib/bluetooth-serial-port`).
- RawManager: Prints out the motor number and intensity as raw bytes when a vibration order is sent. There's very few reasons anyone would use this, but you can use it to send data directly to the glove through whatever mean you want.

You can change to any device manager at any time by calling `RoukaVici.ChangeDeviceManager` with the name of the device as parameter. Keep in mind that if this fails, you may not have built the library with support for that device (see Build Flags).
