snake: src/*.cpp inc/*.h
	g++ -o snake --std=c++11 src/*.cpp inc/*.h -lSDL2 -lGL -lGLEW
