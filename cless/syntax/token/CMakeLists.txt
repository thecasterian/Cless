cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME syntax)
set(SUBLIBRARY_NAME token)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})

add_library(${TARGET} SHARED
    include/cless/syntax/token/tokenbase.h
    src/tokenbase.cpp
    include/cless/syntax/token/keyword.h
    src/keyword.cpp
    include/cless/syntax/token/punctuation.h
    src/punctuation.cpp
    include/cless/syntax/token/identifier.h
    src/identifier.cpp
    include/cless/syntax/token/constant.h
    src/constant.cpp
    include/cless/syntax/token/string_literal.h
    src/string_literal.cpp
    include/cless/syntax/token/header_name.h
    src/header_name.cpp
    include/cless/syntax/token/token.h
    src/token.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/syntax/token/include
)
target_link_libraries(${TARGET} PUBLIC
    cless::core::types
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
