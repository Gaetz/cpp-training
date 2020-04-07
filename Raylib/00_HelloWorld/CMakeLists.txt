cmake_minimum_required(VERSION 3.15)
project(00_HelloWorld)

find_package(raylib QUIET) # Let CMake search for a raylib-config.cmake

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)