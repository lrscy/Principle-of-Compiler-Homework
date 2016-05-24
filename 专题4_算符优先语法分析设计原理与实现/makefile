parse: main.o parse.o
	g++ -std=c++11 -O2 -o $@ $^

main.o: main.cpp parse.h
	g++ -std=c++11 -O2 -c $<

parse.o: parse.cpp parse.h
	g++ -std=c++11 -O2 -c $<

clean:
	del *.o
