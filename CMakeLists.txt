cmake_minimum_required(VERSION 3.9)

SET (PROJECT_VERSION "0.3")
SET (PROJ_NAME "roukavici")

# Define project name & version
project(${PROJ_NAME} VERSION ${PROJECT_VERSION})

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)


SET (PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
SET (PROJECT_SRC "${PROJECT_ROOT}/src")
SET (LIB_DIR "${PROJECT_ROOT}/lib")

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
  ${PROJECT_SRC}/Debug.cpp
  ${PROJECT_SRC}/RoukaViciAPI.cpp
  ${PROJECT_SRC}/RoukaVici.cpp
  ${PROJECT_SRC}/GroupManager.cpp
  ${PROJECT_SRC}/ManagerFactory.cpp
  ${PROJECT_SRC}/TextManager.cpp
  ${PROJECT_SRC}/RawManager.cpp
  ${PROJECT_SRC}/VibrationGroup.cpp
  )

# Set output directory for the library & binary files
SET(OUTPUT_DIR "${PROJECT_ROOT}/output")

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})


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
  include_directories(${LIBUSB_INCLUDE_DIR})
endif (${LUSBOPT})


## Setting the name of the test option
set (TESTOPT "TEST")
## Define it. True by default on unix, false on windows
if (UNIX)
  option (${TESTOPT} "Build test executables" ON)
else()
  option (${TESTOPT} "Build test executables" OFF)
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

## Verbose output for the lib
set (VERBOPT "VERB")
option (${VERBOPT} "Verbose output for the library. Library is silent otherwise" ON)
## Options if true
if (${VERBOPT})
  MESSAGE( STATUS "Building in verbose mode, get used to me talking")
  add_definitions(-DROUKAVERBOSE)
endif(${VERBOPT})


include_directories(${PROJECT_SRC})

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

set_target_properties(${PROJ_NAME}
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SOVERSION ${PROJECT_VERSION})
## If the testing option is true
SET (TEST_FOLDER "${PROJECT_ROOT}/test")

if (${TESTOPT})
  MESSAGE( STATUS "Building test executables")
   ###
   # test executable
   ###
   SET (CTEST c_test)
   SET (CPPTEST cpp_test)

   ## Necessary for testing
   add_executable(${CTEST} ${TEST_FOLDER}/main.cpp)
   add_executable(${CPPTEST} ${TEST_FOLDER}/maincpp.cpp)

   target_link_libraries(${CTEST} ${PROJ_NAME} ${CMAKE_DL_LIBS})
   target_link_libraries(${CPPTEST} ${PROJ_NAME} ${CMAKE_DL_LIBS})
endif (${TESTOPT})

###
# Interactive command line
###
SET (INTERACT interactive)

add_executable(${INTERACT} ${TEST_FOLDER}/interactive.cpp)
target_link_libraries(${INTERACT} ${PROJ_NAME} ${CMAKE_DL_LIBS})
