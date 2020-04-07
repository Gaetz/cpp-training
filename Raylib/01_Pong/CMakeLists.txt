cmake_minimum_required(VERSION 3.11)
project(01_Pong)

find_package(raylib QUIET) # Let CMake search for a raylib-config.cmake

add_executable(${PROJECT_NAME} main.cpp Ball.cpp Ball.h Paddle.cpp Paddle.h Collisions.h RectangleI.h Text.cpp Text.h)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})