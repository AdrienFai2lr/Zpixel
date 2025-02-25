CC = gcc
CCFLAGS = -W -Wall -g

prog: zpixel.o main.o
	$(CC) zpixel.o main.o -o prog -lm

zpixel.o: zpixel.h zpixel.c
	$(CC) -c $(CCFLAGS) zpixel.c

main.o: zpixel.h main.c
	$(CC) -c $(CCFLAGS) main.c

clean:
	rm -f prog *.o
