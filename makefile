zombie: src/*.cpp inc/*.h
	g++ -o zombie src/*.cpp inc/*.h -std=c++0x -ljaogll -lSDL2 -lGL -lGLEW
