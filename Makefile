PROGRAM = AcceleratingBall
CC      = gcc
CFLAGS  = -g -std=c99  -Wall -I/usr/X11R6/include -I/usr/pkg/include
LDFLAGS = -L/usr/X11R6/lib -L/usr/pkg/lib
LDLIBS  = -lglut -lGLU -lGL -lm -O3

$(PROGRAM): main.o image.o
	$(CC) $(LDFLAGS) -o $(PROGRAM) image.o main.o $(LDLIBS)
	
image.o: image.c
	$(CC) -c image.c

.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)
