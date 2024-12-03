set(OPENSSL_PATH "/opt/homebrew/opt/openssl@3")
set(DEPS_DIR "${CMAKE_CURRENT_LIST_DIR}/../_deps/${CMAKE_GENERATOR}")

# Add OpenSSL directories
set(OPENSSL_ROOT_DIR ${OPENSSL_PATH})
set(OPENSSL_INCLUDE_DIR ${OPENSSL_PATH}/include)
set(OPENSSL_LIBRARIES ${OPENSSL_PATH}/lib)
set(OPENSSL_SSL_LIBRARY ${OPENSSL_LIBRARIES})
set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_LIBRARIES})

# FetchContent options
set(FETCHCONTENT_BASE_DIR ${DEPS_DIR})

# CXX options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_definitions(FORCE_POSIX)

# Custom options
set(CMAKE_MESSAGE_LOG_LEVEL WARNING)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CODE_SIGNING_ALLOWED "NO")