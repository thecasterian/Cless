cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME core)
set(SUBLIBRARY_NAME types)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})

add_library(${TARGET} SHARED
    include/cless/core/types/exception.h
    src/exception.cpp
    include/cless/core/types/token.h
    src/token.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/core/types/include
)
target_link_libraries(${TARGET} PUBLIC
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
