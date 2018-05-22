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
`mkdir build && cd build/ && cmake .. [flags]`

### Build flags
- `-DLIBUSB`: Boolean, decides if the lib is compiled with USB support. FALSE by default.
- `-DTEST`: Boolean, decides if the test binary should be compiled. TRUE on Linux, FALSE otherwise by default.
- `-DLIBBT`: Boolean, decides if the lib should be compiled with Bluetooth support. TRUE by default