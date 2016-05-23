all: lexer.o lexermain.o

lexer.o: lexer.cpp lexer.h
	g++ -std=c++11 -O2 -c $<

lexermain.o: lexermain.cpp lexer.h
	g++ -std=c++11 -O2 -c $<

clean:
	del *.o
