objects = main.o lexer.o

lexer: $(objects)
	g++ -std=c++11 -O2 -o lexer $(objects)
main.o: lexer.h main.cpp
	g++ -std=c++11 -O2 -c main.cpp
lexer.o: lexer.h lexer.cpp
	g++ -std=c++11 -O2 -c lexer.cpp

clean:
	del $(objects)
