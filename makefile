snake: src/*.cpp inc/*.h
	g++ -o snake -std=c++0x src/*.cpp inc/*.h -lSDL2 -lGL -lGLEW
