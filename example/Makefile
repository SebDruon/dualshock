CC=gcc
CFLAGS= -g -Wall -I/usr/local/include
LD_FLAGS= -L/usr/local/lib -ldualshock
EXEC=test

all:dualshock

dualshock: main.o
	    $(CC) -o $(EXEC) main.o $(LD_FLAGS)

main.o: main.c
	    $(CC) $(CFLAGS) -c $<
clean: 
	    rm -rf $(EXEC)
	    rm -rf *.o
