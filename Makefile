simulator.out: mat.o main.o
	g++ -Wall -ansi -g -lm -o simulator.out mat.o main.o

mat.o: mat.h mat.cpp
	g++ -Wall -ansi -g -c mat.cpp

main.o: main.cpp mat.h
	g++ -Wall -ansi -g -c main.cpp

run:
	./simulator.out

clean:
	rm -f simulator.out mat.o main.o
