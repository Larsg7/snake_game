jaogll: JAOGLL/*.h JAOGLL/src/*.cpp JAOGLL/external/*
	g++ -c JAOGLL/src/*.cpp JAOGLL/external/*.cpp -fpic
	g++ --shared -std=c++11 -o libjaogll.so *.o -lSDL2 -lGL -lGLEW

all: jaogll test

test: main.cpp
	g++ -o test main.cpp ./libjaogll.so
	export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

clean:
	rm *.o libjaogll.so
