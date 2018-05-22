# RoukaVici Library
This library provides an API between the computer and the RoukaVici box.
It aims to function both on Linux and on Windows.

## Dependencies
### Linux
- `cmake >= 3.9`
- `libdl` (for tests, canbe ignored by setting off tests with -DTEST=FALSE)

### Windows
- `cmake >= 3.9`
- `Visual Studio` with `C++ Build Tools` installed

## Installation
### Linux
- `mkdir build && cd build/ && cmake .. [flags]`
- `make`
Output file: `libroukavici.so`

### Windows (Powershell)
- `mkdir build && cd build/ && cmake .. [flags]`
- Open Visual Studio and open the `.sln` file generated in the project's `build/` folder. Build the solution.
Output file: `libroukavici.dll`

### Build flags
- `-DUSB`: Boolean, decides if the lib is compiled with USB support. FALSE by default.
- `-DTEST`: Boolean, decides if the test binary should be compiled. TRUE on Linux, FALSE otherwise by default.
- `-DBBT`: Boolean, decides if the lib should be compiled with Bluetooth support. TRUE by default
- `-DTCP`: Bollean, decides if the lib should be compiled with TCP support. FALSE by default

