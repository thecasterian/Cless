cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME front-end)
set(SUBLIBRARY_NAME file)
set(TARGET cless-${LIBRARY_NAME}-${SUBLIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME}::${SUBLIBRARY_NAME})
set(TEST ${TARGET}-test)

add_library(${TARGET} SHARED
    include/cless/front-end/file/file.h
    src/file.cpp
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/cless/front-end/file/include
)
target_link_libraries(${TARGET} PUBLIC
    cless::core::types
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})

add_executable(${TEST}
    test/file_test.cpp
)
target_link_libraries(${TEST} PRIVATE
    GTest::gtest_main
    ${TARGET}
    cless::configure
)
include(GoogleTest)
gtest_discover_tests(${TEST})
