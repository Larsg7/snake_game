cmake_minimum_required(VERSION 3.6)
project(snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2")

set(SOURCE_FILES main.cpp src/snake_game.cpp inc/snake_game.h inc/Snake_Error.h)
add_executable(snake ${SOURCE_FILES})