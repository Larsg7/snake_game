zombie: src/*.cpp inc/*.h
	g++ -o zombie src/*.cpp inc/*.h -std=c++11 -ljaogll -lSDL2 -lGL -lGLEW
