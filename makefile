snake: src/*.cpp inc/*.h
	g++ src/*.cpp inc/*.h -o snake --std=c++11 -lSDL2 -lGL -lGLEW
