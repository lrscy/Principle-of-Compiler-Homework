all: parse.o parsemain.o

parse.o: parse.cpp parse.h
	g++ -std=c++11 -O2 -c $<

parsemain.o: parsemain.cpp parse.h
	g++ -std=c++11 -O2 -c $<

clean:
	del *.o
