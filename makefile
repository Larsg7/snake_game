zombie: src/*.cpp inc/*.h
	g++ -o zombie src/*.cpp inc/*.h -std=c++0x  -ljaogll -lGL -lGLEW -lSDL2

local: src/*.cpp inc/*.h
	g++ -o zombie src/*.cpp inc/*.h -std=c++0x  -ljaogll ./jaogll-dep/lib/libSDL2.so ./jaogll-dep/lib/libGLEW.so -lGL
