all: lexer.o lexerProcessor.o

lexerProcessor.o: lexerProcessor.cpp lexerProcessor.h
	g++ -std=c++11 -O2 -c $<

lexer.o: lexer.cpp lexer.h lexerProcessor.h
	g++ -std=c++11 -O2 -c $<

clean:
	del *.o
