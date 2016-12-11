snake: src/*.cpp inc/*.h
	g++ --std=c++11 -o snake -lSDL2 -lGL -lGLEW src/*.cpp inc/*.h
