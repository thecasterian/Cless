cmake_minimum_required(VERSION 3.20)

add_library(cless-core INTERFACE)
target_link_libraries(cless-core INTERFACE
    cless::core::types
)
add_library(cless::core ALIAS cless-core)

add_subdirectory(types)
