cmake_minimum_required(VERSION 3.6)
project(zombie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lGLEW -lGL")

include_directories("/home/lars/Documents/programming/")
link_directories("/home/lars/Documents/programming/jaogll")

set(SOURCE_FILES src/main.cpp src/main_game.cpp inc/main_game.h src/level.cpp inc/level.h src/agent.cpp inc/agent.h src/player.cpp inc/player.h src/bullet.cpp inc/bullet.h)
add_executable(zombie ${SOURCE_FILES})

target_link_libraries(zombie jaogll)