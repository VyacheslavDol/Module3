all: task1_2

task1_2: task1_2.o square.o
	gcc task1_2.o square.o -o task1_2

task1_2.o: task1_2.c
	gcc -c task1_2.c -o task1_2.o

square.o: square.c
	gcc -c square.c -o square.o

clean:
	rm -f *.o task1_2