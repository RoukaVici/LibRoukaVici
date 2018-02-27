cmake_minimum_required(VERSION 3.9)

SET (PROJECT_VERSION "0.1")
SET (PROJ_NAME "roukavici")

# Define project name & version
project(${PROJ_NAME} VERSION ${PROJECT_VERSION})

SET (PROJECT_ROOT ".")
SET (PROJECT_SRC "${PROJECT_ROOT}/src")

# # LibSUB is necessary to communicate with the rasp
# find_package(LibUSB)

include_directories(${PROJECT_SRC} ${LIBUSB_INCLUDE_DIR})

###
# libroukavici
###
add_library(${PROJ_NAME} SHARED
${PROJECT_SRC}/exported.cpp
${PROJECT_SRC}/RoukaVici.cpp
# ${PROJECT_SRC}/LibUsb.cpp
# ${PROJECT_SRC}/TCPManager.cpp
${PROJECT_SRC}/TextManager.cpp
)

if (WIN32)
    target_compile_definitions(${PROJ_NAME} WIN_EXPORT=1)
endif (WIN32)

# target_link_libraries(${PROJ_NAME} ${LIBUSB_LIBRARY})

set_target_properties(${PROJ_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 0)

if (UNIX)
   ###
   # test executable
   ###
   SET (TEST_FOLDER "${PROJECT_ROOT}/test")
   SET (TEST_BIN roukavici_test)

   find_package(LibDL)
   add_executable(${TEST_BIN}
   ${TEST_FOLDER}/main.cpp)
   target_link_libraries(${TEST_BIN} ${PROJ_NAME} ${LIBDL_LIBRARIES})
endif (UNIX)
