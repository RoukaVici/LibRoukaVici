cmake_minimum_required(VERSION 3.1)
set(PROJECT_VERSION "1.0")
# Define project name & version
project(roukavici VERSION ${PROJECT_VERSION} LANGUAGES CXX)

# To build shared libraries in Windows, we set CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS to TRUE.
# See https://cmake.org/cmake/help/v3.4/variable/CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS.html
# See https://blog.kitware.com/create-dlls-on-windows-without-declspec-using-new-cmake-export-all-feature/
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(roukavici SHARED)

target_include_directories(roukavici
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_target_properties(roukavici
PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION}
)

target_sources(roukavici
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Debug.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RoukaViciAPI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RoukaVici.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GroupManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ManagerFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/TextManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/RawManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/VibrationGroup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Packet.cpp
  )

include(GenerateExportHeader)
# Generate our EXPORT and NO_EXPORT macros in roukavici_exported.h
generate_export_header(roukavici)

message("ID: " ${CMAKE_CXX_COMPILER_ID})

# Platform-specific compile flags
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    message(STATUS "Setting G++ flags")
    # G++
    target_compile_options(roukavici PRIVATE -Wall -Wextra)
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    message(STATUS "Setting MSVC flags")
    # MSVC
    target_compile_options(roukavici PRIVATE /EHsc /MTd /W2 /c)
    # Set the DLLEXPORT variable to export symbols
    target_compile_definitions(roukavici PRIVATE WIN_EXPORT)
endif()

##
# Options
##
# Bluetooth support. True by default
option (BT "Build with Bluetooth support" ON)
## Conditions if true
if (BT)
    message( STATUS "Building with Bluetooth Support")
    target_sources(roukavici PRIVATE src/BTManager.cpp)
    target_include_directories(roukavici PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/bluetooth-serial-port/src)
    target_compile_definitions(roukavici PRIVATE DBT_COMPILE)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/bluetooth-serial-port) # Add bluetoothserialport cmake
    target_link_libraries(roukavici bluetoothserialport)
endif (BT)

option (VERB "Verbose output for the library. Library is silent otherwise" ON)
## Options if true
if (VERB)
  MESSAGE( STATUS "Building in verbose mode, get used to me talking")
  target_compile_definitions(roukavici PRIVATE ROUKAVERBOSE)
endif(VERB)


option (TEST "Verbose output for the library. Library is silent otherwise" OFF)
## Options if true
if (TEST)
    enable_testing()
    add_executable(unittests ./test/tests.cpp)
    target_link_libraries(unittests ${CMAKE_DL_LIBS} roukavici)
    add_test(vibrationTest unittests "vibration")
    add_test(vibrationTest unittests "groups")
endif(TEST)

# Always build the interactive command line
add_executable(interactive ${CMAKE_CURRENT_SOURCE_DIR}/test/interactive.cpp)
target_link_libraries(interactive roukavici ${CMAKE_DL_LIBS})