simulator.out: mat.o test.o multiThread.o
	g++ -Wall -ansi -g -lm -o simulator.out mat.o test.o multiThread.o

multiThread.o: multiThread.h multiThread.cpp
	g++ -Wall -ansi -g -c multiThread.cpp

mat.o: mat.h mat.cpp
	g++ -Wall -ansi -g -c mat.cpp

test.o: test.cpp mat.h
	g++ -Wall -ansi -g -c test.cpp

run:
	./simulator.out

clean:
	rm -f simulator.out mat.o test.o multiThread.o
