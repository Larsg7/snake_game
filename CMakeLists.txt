cmake_minimum_required(VERSION 3.6)
project(snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lGLEW -lGL")

set(SOURCE_FILES main.cpp main_game.cpp main_game.h JAOGLL/error.h JAOGLL/src/sprite.cpp JAOGLL/sprite.h JAOGLL/src/glsl_compiler.cpp JAOGLL/glsl_compiler.h JAOGLL/src/error.cpp JAOGLL/vertex.h JAOGLL/src/iomanager.cpp JAOGLL/iomanager.h JAOGLL/external/picoPNG.h JAOGLL/external/picoPNG.cpp JAOGLL/gl_texture.h JAOGLL/src/image_loader.cpp JAOGLL/image_loader.h JAOGLL/src/resource_manager.cpp JAOGLL/resource_manager.h JAOGLL/src/texture_cache.cpp JAOGLL/texture_cache.h JAOGLL/src/window.cpp JAOGLL/window.h JAOGLL/jaogll.h JAOGLL/src/jaogll.cpp JAOGLL/src/camera2D.cpp JAOGLL/camera2D.h JAOGLL/src/sprite_batch.cpp JAOGLL/sprite_batch.h JAOGLL/src/input_manager.cpp JAOGLL/input_manager.h JAOGLL/timing.h JAOGLL/src/timing.cpp JAOGLL/logger.h)
add_executable(snake ${SOURCE_FILES})