cmake_minimum_required(VERSION 3.15)

project(00_HelloWorld)
find_package(raylib)

set(CMAKE_CXX_STANDARD 14)

add_executable(00_HelloWorld main.cpp)
target_link_libraries(00_HelloWorld raylib)