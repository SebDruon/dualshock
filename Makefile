CC=gcc
CFLAGS=-Wall
EXEC=test
BUILDDIR= build

all:dualshock

dualshock: createEnv dualshock.o main.o
	    $(CC) -g -o $(EXEC)  build/dualshock.o build/main.o $(CFLAGS) $(LIBFLAG)

createEnv:
	    mkdir -p $(BUILDDIR)


dualshock.o: dualshock.c
	    $(CC) -g -o $(BUILDDIR)/$@ -c $< $(CFLAGS) $(LIBFLAG)

main.o: main.c
	    $(CC) -g -o $(BUILDDIR)/$@ -c $< $(CFLAGS) $(LIBFLAG)
clean: 
	    rm -rf $(BUILDDIR) $(EXEC)
