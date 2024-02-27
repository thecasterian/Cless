cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME front-end)
set(SUBLIBRARY_NAME lexer)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})

add_library(${TARGET} SHARED
    include/cless/front-end/lexer/lexer.h
    src/lexer.cpp
    include/cless/front-end/lexer/utils.h
    src/utils.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/front-end/lexer/include
)
target_link_libraries(${TARGET} PUBLIC
    cless::core::types
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
