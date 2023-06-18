all: lab9 term.o polynomial.o

term.o: term.cpp
	g++ -c term.cpp

polynomial.o: polynomial.cpp
	g++ -c polynomial.cpp

lab9: lab9.cpp polynomial.o term.o
	g++ lab9.cpp polynomial.o term.o
