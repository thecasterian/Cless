cmake_minimum_required(VERSION 3.20)

set(LIBRARY_NAME configure)
set(TARGET cless-${LIBRARY_NAME})
set(TARGET_ALIAS cless::${LIBRARY_NAME})

configure_file(configure.h.in ${PROJECT_BINARY_DIR}/cless/configure/include/cless/configure/configure.h)

add_library(${TARGET} SHARED
    ${PROJECT_BINARY_DIR}/cless/configure/include/cless/configure/configure.h
)

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${TARGET} PUBLIC
    ${PROJECT_BINARY_DIR}/cless/configure/include
)
target_link_libraries(${TARGET} PUBLIC
)
add_library(${TARGET_ALIAS} ALIAS ${TARGET})
