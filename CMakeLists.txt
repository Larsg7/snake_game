cmake_minimum_required(VERSION 3.6)
project(snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -lGLEW -lGL")

set(SOURCE_FILES src/main.cpp src/snake_game.cpp inc/snake_game.h inc/Snake_Error.h src/sprite.cpp inc/sprite.h src/GLSLCompiler.cpp inc/GLSLCompiler.h src/snake_error.cpp inc/vertex.h src/iomanager.cpp inc/iomanager.h inc/picoPNG.h src/picoPNG.cpp inc/gl_texture.h src/Image_loader.cpp inc/Image_loader.h)
add_executable(snake ${SOURCE_FILES})