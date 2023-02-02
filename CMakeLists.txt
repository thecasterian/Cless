cmake_minimum_required(VERSION 3.20)

project(Cless LANGUAGES CXX)
set(CMAKE_GENERATOR "Unix Makefiles" CACHE INTERNAL "" FORCE)

add_subdirectory(cless)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cless::core)
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
