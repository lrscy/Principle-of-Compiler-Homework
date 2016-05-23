all: parse.o parseProcessor.o

parseProcessor.o: parseProcessor.cpp parseProcessor.h
	g++ -std=c++11 -O2 -c $<

parse.o: parse.cpp parse.h parseProcessor.h
	g++ -std=c++11 -O2 -c $<

clean:
	del *.o
