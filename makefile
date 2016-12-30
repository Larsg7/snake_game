snake: main.cpp JAOGLL/*.h JAOGLL/src/*.cpp JAOGLL/external/*
	g++ -o snake -std=c++0x main.cpp JAOGLL/*.h JAOGLL/src/*.cpp JAOGLL/external/* -lSDL2 -lGL -lGLEW
