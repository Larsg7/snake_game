jaogll: JAOGLL/*.h JAOGLL/src/*.cpp JAOGLL/external/*
	g++ -c JAOGLL/src/*.cpp JAOGLL/external/*.cpp -fpic -std=c++11
	g++ --shared -o libjaogll.so *.o -lSDL2 -lGL -lGLEW -std=c++11

all: jaogll test

test: main.cpp
	g++ -o test main.cpp ./libjaogll.so

clean:
	rm *.o libjaogll.so
