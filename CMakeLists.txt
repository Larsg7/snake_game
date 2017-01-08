cmake_minimum_required(VERSION 3.6)
project(zombie)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lGLEW -lGL -ljaogll -Wall")

set(SOURCE_FILES src/main.cpp src/main_game.cpp inc/main_game.h src/level.cpp inc/level.h src/agent.cpp inc/agent.h inc/player.h src/bullet.cpp inc/bullet.h src/collision_manager.cpp inc/collision_manager.h inc/zombie.h src/agent_manager.cpp inc/agent_manager.h inc/human.h inc/constants.h)
add_executable(zombie ${SOURCE_FILES})