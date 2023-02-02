cmake_minimum_required(VERSION 3.20)

add_library(cless-core-types SHARED
    include/cless-core/types/token.h
    src/token.cpp
)

target_include_directories(cless-core-types PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/core/types/include
)
target_link_libraries(cless-core-types PUBLIC
)
add_library(cless::core::types ALIAS cless-core-types)
