cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME core)
set(SUBLIBRARY_NAME print)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})

add_library(${TARGET} SHARED
    include/cless/core/print/ansi_escape.h
    src/ansi_escape.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/core/print/include
)
target_link_libraries(${TARGET} PUBLIC
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
