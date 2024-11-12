set(LIB_EXEC_NAME "_${MODULE_NAME}")

add_executable("${LIB_EXEC_NAME}" cpp/main.cpp)
target_link_libraries("${LIB_EXEC_NAME}" PRIVATE "${MODULE_NAME}")
set_target_properties("${LIB_EXEC_NAME}" PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../../executables
)
