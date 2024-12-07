CMAKE_MINIMUM_REQUIRED(VERSION 3.20.2)

set(CMAKE_FOLDER "${CMAKE_CURRENT_LIST_DIR}/cmake")

include("${CMAKE_FOLDER}/variables.cmake")

option(MODULE_NAME "Name of the module" AppCore)
option(BUILD_TARGET "The type of build" IOS) # EXECUTABLE, IOS, ANDROID

PROJECT("${MODULE_NAME}")

set(SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/cpp/src/AppCore.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/src/database/db.cpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/src/database/schemas/user.cpp
)

set(HEADERS
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/AppCore.hpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/macros.hpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/database/db.hpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/database/base.hpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/database/schemas.hpp
  ${CMAKE_CURRENT_LIST_DIR}/cpp/include/AppCore/database/schemas/user.hpp
)

add_library("${MODULE_NAME}" SHARED ${HEADERS} ${SOURCES})

target_include_directories("${MODULE_NAME}"
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/cpp/include
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/cpp/src
)

### DEPENDENCIES

include(FetchContent)

FetchContent_Declare(
        mmkv
        GIT_REPOSITORY https://github.com/Tencent/MMKV.git
        GIT_TAG        v2.0.1
)
FetchContent_Declare(
        cpprealm
        GIT_REPOSITORY https://github.com/realm/realm-cpp.git
        GIT_TAG        v2.2.0
)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.15.0
)

FetchContent_GetProperties(mmkv)
if(NOT mmkv_POPULATED)
    FetchContent_Populate(mmkv)
  add_subdirectory(${mmkv_SOURCE_DIR}/Core ${mmkv_BINARY_DIR}/Core)
endif()

FetchContent_MakeAvailable(spdlog cpprealm)

target_link_libraries("${MODULE_NAME}" spdlog::spdlog cpprealm core)

###

if(BUILD_TARGET STREQUAL "EXECUTABLE")
  include("${CMAKE_FOLDER}/executable.cmake")
elseif(BUILD_TARGET STREQUAL "IOS")
  include("${CMAKE_FOLDER}/framework.cmake")
elseif(BUILD_TARGET STREQUAL "ANDROID")
  target_sources("${MODULE_NAME}" PUBLIC ${CMAKE_CURRENT_LIST_DIR}/android/src/main/cpp/cpp-adapter.cpp)
endif()
