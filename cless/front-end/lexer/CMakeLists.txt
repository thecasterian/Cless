cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME front-end)
set(SUBLIBRARY_NAME lexer)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})
set(TEST ${TARGET}-test)

add_library(${TARGET} SHARED
    include/cless/front-end/lexer/impl.h
    src/impl.cpp
    include/cless/front-end/lexer/lexer.h
    src/lexer.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/front-end/lexer/include
)
target_link_libraries(${TARGET} PUBLIC
    GTest::gtest_main
    cless::core::types
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})

add_executable(${TEST}
    test/character_constant_test.cpp
    test/floating_constant_test.cpp
    test/identifier_test.cpp
    test/integer_constant_test.cpp
    test/string_literal_test.cpp
)
target_link_libraries(${TEST} PRIVATE
    GTest::gtest_main
    ${TARGET}
)
include(GoogleTest)
gtest_discover_tests(${TEST})
