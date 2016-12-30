jaogll: JAOGLL/*.h JAOGLL/src/*.cpp JAOGLL/external/*
	g++ --std=c++11 -c JAOGLL/src/*.cpp JAOGLL/external/*.cpp -fpic
	g++ --std=c++11 --shared -o libjaogll.so *.o -lSDL2 -lGL -lGLEW

all: jaogll test

test: main.cpp
	g++ -o test main.cpp ./libjaogll.so

clean:
	rm *.o libjaogll.so
