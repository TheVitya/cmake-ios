CMAKE_MINIMUM_REQUIRED(VERSION 3.29.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FOLDER "${CMAKE_CURRENT_LIST_DIR}/cmake")

option(MODULE_NAME "Name of the module" AppCore)
option(BUILD_EXACUTABLE "Build the executable" OFF)

PROJECT("${MODULE_NAME}")

set(SOURCES
  cpp/src/AppCore.cpp
)

set(HEADERS
  cpp/include/AppCore/AppCore.hpp
)

add_library("${MODULE_NAME}" SHARED ${HEADERS} ${SOURCES})

target_include_directories("${MODULE_NAME}"
    PUBLIC
        cpp/include
    PRIVATE
        cpp/src
)

if(BUILD_EXACUTABLE)
  include("${CMAKE_FOLDER}/executable.cmake")
else()
  include("${CMAKE_FOLDER}/framework.cmake")
endif()
