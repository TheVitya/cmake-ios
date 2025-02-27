CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2)

set(CMAKE_FOLDER "${CMAKE_CURRENT_LIST_DIR}/cmake")

include("${CMAKE_FOLDER}/variables.cmake")

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

### DEPENDENCIES

# include(FetchContent)
#
# FetchContent_Declare(
#         cpprealm
#         GIT_REPOSITORY https://github.com/realm/realm-cpp.git
#         GIT_TAG        v2.2.0
# )
#
# FetchContent_MakeAvailable(cpprealm)
#
# target_link_libraries("${MODULE_NAME}" cpprealm)

###

### RUST SUPPORT

include(FetchContent)

FetchContent_Declare(
    Corrosion
    GIT_REPOSITORY https://github.com/TheVitya/corrosion.git
)
FetchContent_MakeAvailable(Corrosion)

corrosion_import_crate(MANIFEST_PATH ${CMAKE_CURRENT_LIST_DIR}/rust/Cargo.toml)

# {{.ModuleName}}Rust should be dynamic
corrosion_add_cxxbridge({{.ModuleName}}Rust
        CRATE {{.ModuleName}}_rust # the name of the package inside Cargo.toml, cannot be the same as the target 
        FILES lib.rs
)
target_include_directories({{.ModuleName}}Rust PRIVATE "cpp/include")

target_link_libraries("${MODULE_NAME}" {{.ModuleName}}Rust)

###

if(BUILD_TARGET STREQUAL "EXECUTABLE")
  include("${CMAKE_FOLDER}/executable.cmake")
elseif(BUILD_TARGET STREQUAL "IOS")
  include("${CMAKE_FOLDER}/framework.cmake")
elseif(BUILD_TARGET STREQUAL "ANDROID")
  target_sources("${MODULE_NAME}" PUBLIC ${CMAKE_CURRENT_LIST_DIR}/android/src/main/cpp/cpp-adapter.cpp)
endif()
