CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_FOLDER "${CMAKE_CURRENT_LIST_DIR}/cmake")

option(MODULE_NAME "Name of the module" {{.ModuleName}})
option(BUILD_TARGET "The type of build" IOS) # EXECUTABLE, IOS, ANDROID

PROJECT("${MODULE_NAME}")

set(SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/cpp/src/{{.ModuleName}}.cpp
)

set(HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/{{.ModuleName}}/{{.ModuleName}}.hpp
)

add_library("${MODULE_NAME}" SHARED ${HEADERS} ${SOURCES})

target_include_directories("${MODULE_NAME}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/cpp/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/cpp/src
)

if(BUILD_TARGET STREQUAL "EXECUTABLE")
  include("${CMAKE_FOLDER}/executable.cmake")
elseif(BUILD_TARGET STREQUAL "IOS")
  include("${CMAKE_FOLDER}/framework.cmake")
elseif(BUILD_TARGET STREQUAL "ANDROID")
  target_sources("${MODULE_NAME}" PUBLIC ${CMAKE_CURRENT_LIST_DIR}/android/src/main/cpp/cpp-adapter.cpp)
endif()
