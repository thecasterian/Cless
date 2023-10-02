cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME core)
set(TARGET cless-${LIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME})

add_library(${TARGET} INTERFACE)
target_link_libraries(${TARGET} INTERFACE
    cless::core::types
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})

add_subdirectory(types)
