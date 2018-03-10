cmake_minimum_required(VERSION 3.9)

SET (PROJECT_VERSION "0.1")
SET (PROJ_NAME "roukavici")

# Define project name & version
project(${PROJ_NAME} VERSION ${PROJECT_VERSION})

SET (PROJECT_ROOT ".")
SET (PROJECT_SRC "${PROJECT_ROOT}/src")
SET (PROJECT_EXPORTED "${PROJECT_SRC}/exported")

# Platform-specific compile flags
if (UNIX)
  # G++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
else()
  # MSVC
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHc-")
endif()

# Setting sources, more files will be added depending on options
set(LIBSRCS
${PROJECT_EXPORTED}/RoukaViciAPI.cpp
${PROJECT_SRC}/RoukaVici.cpp
${PROJECT_SRC}/ManagerFactory.cpp
${PROJECT_SRC}/TCPManager.cpp
${PROJECT_SRC}/TextManager.cpp
${PROJECT_SRC}/VibrationGroup.cpp
)

# Options
## Setting the name of the libusb option
set (LUSBOPT "LIBUSB")
## Define it
option(${LUSBOPT} "Compile with LibUSB support" ON)
## Conditions if true
if (${LUSBOPT})
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

include_directories(${PROJECT_SRC} ${LIBUSB_INCLUDE_DIR} ${PROJECT_EXPORTED})

###
# libroukavici
###
add_library(${PROJ_NAME} SHARED ${LIBSRCS})

if (WIN32)
    target_compile_definitions(${PROJ_NAME} WIN_EXPORT=1)
endif (WIN32)

target_link_libraries(${PROJ_NAME} ${LIBUSB_LIBRARY})

set_target_properties(${PROJ_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 0)

## If the testing option is true
if (${TESTOPT})
   ###
   # test executable
   ###
   SET (TEST_FOLDER "${PROJECT_ROOT}/test")
   SET (TEST_BIN roukavici_test)

   ## Necessary for testing
   find_package(LibDL)
   add_executable(${TEST_BIN}
   ${TEST_FOLDER}/main.cpp)
   target_link_libraries(${TEST_BIN} ${PROJ_NAME} ${LIBDL_LIBRARIES})
endif (${TESTOPT})
