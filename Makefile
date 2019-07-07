simulator.out: mat.o test2.o multiThread.o matOperations.o
	g++ -std=gnu++11 -g -w -lm -o simulator.out mat.o test2.o multiThread.o matOperations.o

multiThread.o: multiThread.h multiThread.cpp
	g++ -std=gnu++11 -g -w -c multiThread.cpp

matOperations.o: matOperations.h matOperations.cpp
	g++ -std=gnu++11 -g -w -c matOperations.cpp

mat.o: mat.h mat.cpp
	g++ -std=gnu++11 -g -w -c mat.cpp

test2.o: test2.cpp
	g++ -std=gnu++11 -g -w -c test2.cpp

run:
	./simulator.out

clean:
	rm -f simulator.out mat.o test.o mocktest.o multiThread.o matOperations.o test2.o ./file/*.txt
