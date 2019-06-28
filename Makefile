simulator.out: mat.o test2.o multiThread.o matOperations.o
	g++ -Wall -ansi -g -lm -o simulator.out mat.o test2.o multiThread.o matOperations.o

multiThread.o: multiThread.h multiThread.cpp
	g++ -Wall -ansi -g -c multiThread.cpp

matOperations.o: matOperations.h matOperations.cpp
	g++ -Wall -ansi -g -c matOperations.cpp

mat.o: mat.h mat.cpp
	g++ -Wall -ansi -g -c mat.cpp

test2.o: test2.cpp
	g++ -Wall -ansi -g -c test2.cpp

run:
	./simulator.out

clean:
	rm -f simulator.out mat.o test.o test2.o multiThread.o matOperations.o
