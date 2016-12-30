cmake_minimum_required(VERSION 3.6)
project(snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lGLEW -lGL")

set(SOURCE_FILES main.cpp JAOGLL/src/main_game.cpp JAOGLL/main_game.h JAOGLL/jaogll_error.h JAOGLL/src/sprite.cpp JAOGLL/sprite.h JAOGLL/src/jaogll_glsl_compiler.cpp JAOGLL/jaogll_glsl_compiler.h JAOGLL/src/snake_error.cpp JAOGLL/jaogll_vertex.h JAOGLL/src/iomanager.cpp JAOGLL/iomanager.h JAOGLL/external/picoPNG.h JAOGLL/external/picoPNG.cpp JAOGLL/gl_texture.h JAOGLL/src/Image_loader.cpp JAOGLL/Image_loader.h JAOGLL/src/resource_manager.cpp JAOGLL/resource_manager.h JAOGLL/src/jaogll_texture_cache.cpp JAOGLL/jaogll_texture_cache.h)
add_executable(snake ${SOURCE_FILES})