# RoukaVici Library
This library provides an API between the computer and the RoukaVici glove. It aims to function both on Linux and on Windows.

# Dependencies
## Linux
- `cmake >= 3.9`
- `libdl` (for tests, canbe ignored by setting off tests with -DTEST=FALSE)

## Windows
- `cmake >= 3.9`
- `Visual Studio` with `C++ Build Tools` installed

# Building
## Linux & MacOS
- `mkdir build && cd build/ && cmake .. [flags]`
- `make`
- Output file: `libroukavici.so`

**Note**: As of this writing, MacOS cannot compile the Bluetooth library. Run cmake with `-DBT=FALSE` option if build fails.

## Windows (Powershell)
- `mkdir build && cd build/ && cmake .. [flags]`
- Open Visual Studio and open the `.sln` file generated in the project's `build/` folder. Build the solution.
- Output files: `Debug/roukavici.dll` and `Debug/roukavici.lib`

## Build flags
- `-DUSB`: Boolean, decides if the lib is compiled with USB support. FALSE by default.
- `-DTEST`: Boolean, decides if the test binary should be compiled. TRUE on Linux, FALSE otherwise by default.
- `-DBT`: Boolean, decides if the lib should be compiled with Bluetooth support. TRUE by default
- `-DTCP`: Boolean, decides if the lib should be compiled with TCP support. FALSE by default

# How to use
## C++
Link to the dynamic library and use the header `RoukaVici.hh`. From there, you can call all of the `RoukaVici` class' methods contained in the header.

## Other Languages
If your language can import C functions through a dynamic library, then you can use RoukaVici through its C API.

You want to use the `RoukaViciAPI.h` header for reference. It has all exposed library functions. From there, you can call these functions by name by using whatever dynamic library system your language and OS use.

This method exposes no more or less functions than using the C++ one. The C API is a perfect mirror of every public method in the `RoukaVici` class, and is simply less convenient.

`test/main.cpp` has an example of how to do this on Linux, in C.

# How does it work?
## Flow
- Initialize the library, either by creating a new `RoukaVici` object or by calling `InitRVici()` if you're using the C API.
- Change to the device manager of your choice using `RoukaVici.ChangeDeviceManager`. If you'd like to use the text (debug) mode, skip this step. More info about device managers in the next subsection.
- You can now call `Roukavici.FindDevice` to allow the manager to find and connect to the device. This could take a while depending on which manager you're using.
- Check that the device was found using `RoukaVici.HasDevice`, which returns a boolean.
- You can now call the `RoukaVici.Vibrate` function. Congratulations, you can now communicate with RoukaVici. You can also set groups, every function you have access to is in the `RoukaVici` header file you're using.

## Device Managers
The RoukaVici library uses different DeviceManagers to connect to the glove. This is useful for debugging, as the lib provides you with multiple means of communicating between yourself and the glove. The two supported ones as of this writing are:

- TextManager (default): Doesn't connect to the glove at all. This manager is on when the library is initialized. If you send vibrations through the TextManager, it prints the motor number and the intensity in the console. Very useful for debugging.
- BTManager: Connects to the glove through Bluetooth, using a cross-platform library (`lib/bluetooth-serial-port`).

You can change to any device manager at any time by calling `RoukaVici.ChangeDeviceManager` with the name of the device as parameter. Keep in mind that if this fails, you may not have built the library with support for that device (see Build Flags).

