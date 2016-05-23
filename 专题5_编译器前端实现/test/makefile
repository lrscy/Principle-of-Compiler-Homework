compiler: subdir main.o
	g++ -std=c++11 -O2 -o $@ ../lexer/*.o ../parse/*.o main.o

main.o: main.cpp main.h
	g++ -std=c++11 -O2 -c $<

subdir:
	$(MAKE) -C ../lexer
	$(MAKE) -C ../parse

.PHONY : clean
clean:
	$(MAKE) -C ../lexer clean
	$(MAKE) -C ../parse clean
	del *.o
