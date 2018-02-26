cmake_minimum_required(VERSION 3.9)

SET (PROJECT_VERSION "0.1")
SET (PROJ_NAME "roukavici")

project(${PROJ_NAME} VERSION ${PROJECT_VERSION})

SET (PROJECT_ROOT ".")
SET (PROJECT_SRC "${PROJECT_ROOT}/src")
include_directories(${PROJECT_SRC})

###
# libroukavici
###
add_library(${PROJ_NAME} SHARED
${PROJECT_SRC}/exported.cpp
${PROJECT_SRC}/RoukaVici.cpp
)

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
