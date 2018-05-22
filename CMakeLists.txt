cmake_minimum_required(VERSION 3.9)

SET (PROJECT_VERSION "0.1")
SET (PROJ_NAME "roukavici")

# Define project name & version
project(${PROJ_NAME} VERSION ${PROJECT_VERSION})


# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

SET (PROJECT_ROOT ".")
SET (PROJECT_SRC "${PROJECT_ROOT}/src")
SET (PROJECT_EXPORTED "${PROJECT_SRC}")

SET (LIB_DIR "lib")

# Platform-specific compile flags
if (UNIX)
  # G++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
else()
  # MSVC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /MTd /W2 /c")
  # Set the DLLEXPORT variable to export symbols
  add_definitions(-DWIN_EXPORT)
endif()

# Setting sources, more files will be added depending on options
set(LIBSRCS
${PROJECT_EXPORTED}/RoukaViciAPI.cpp
${PROJECT_SRC}/RoukaVici.cpp
${PROJECT_SRC}/ManagerFactory.cpp
${PROJECT_SRC}/TextManager.cpp
${PROJECT_SRC}/VibrationGroup.cpp
)

###
# Options
###
## USB option is deprecated
## Setting the name of the libusb option
set (LUSBOPT "USB")
## Define it
option(${LUSBOPT} "Compile with LibUSB support" OFF)
## Conditions if true
if (${LUSBOPT})
  MESSAGE( STATUS "Building with USB support!")
  ## Find the right package
  find_package(LibUSB)
  ## Add the proper source file
  set(LIBSRCS ${LIBSRCS} ${PROJECT_SRC}/USBManager.cpp)
  ## Set the proper preprocessor defs
  add_definitions(-DLIBUSB_COMPILE)
endif (${LUSBOPT})


## Setting the name of the test option
set (TESTOPT "TEST")
## Define it. True by default on unix, false on windows
if (UNIX)
  option (${TESTOPT} "Build test executable" ON)
else()
  option (${TESTOPT} "Build test executable" OFF)
endif()


## Setting the name of the TCP option
set (TCPOPT "TCP")
## Define it. False by default
option (${TESTOPT} "Build with TCP support" OFF)

if (${TCPOPT})
  MESSAGE( STATUS "Building with TCP Support")
  # Set the compile flag
  add_definitions(-DTCP_COMPILE)
  # Add the source file
  set(LIBSRCS ${LIBSRCS} ${PROJECT_SRC}/TCPManager.cpp)
endif(${TCPOPT})

## Setting the name of the bluetooth option
set (BTOPT "BT")
## Define it. True by default
option (${BTOPT} "Build with Bluetooth support" ON)
## Conditions if true
if (${BTOPT})
  MESSAGE( STATUS "Building with Bluetooth Support")
  set (LIBSRCS ${LIBSRCS} ${PROJECT_SRC}/BTManager.cpp)
  set (BTLIB "bluetoothserialport")
  set (BTDIRNAME "bluetooth-serial-port")
  add_definitions(-DBT_COMPILE)
  include_directories(${LIB_DIR}/${BTDIRNAME}/src)

  add_subdirectory(${LIB_DIR}/${BTDIRNAME}) # Add bluetoothserialport cmake
endif (${BTOPT})

include_directories(${PROJECT_SRC} ${LIBUSB_INCLUDE_DIR} ${PROJECT_EXPORTED})

###
# libroukavici
###
add_library(${PROJ_NAME} SHARED ${LIBSRCS})

if (${LUSBOPT})
  target_link_libraries(${PROJ_NAME} ${LIBUSB_LIBRARY})
endif (${LUSBOPT})

if (${BTOPT})
  target_link_libraries(${PROJ_NAME} ${BTLIB})
endif (${BTOPT})

set_target_properties(${PROJ_NAME} PROPERTIES VERSION ${PROJECT_VERSION} VERSION 0)
## If the testing option is true
if (${TESTOPT})
  MESSAGE( STATUS "Building test executable")
   ###
   # test executable
   ###
   SET (TEST_FOLDER "${PROJECT_ROOT}/test")
   SET (TEST_BIN roukavici_test)

   ## Necessary for testing
   add_executable(${TEST_BIN} ${TEST_FOLDER}/main.cpp)
   target_link_libraries(${TEST_BIN} ${PROJ_NAME} ${CMAKE_DL_LIBS})
endif (${TESTOPT})
