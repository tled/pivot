
O = -Wall -O2 #-g -DDEBUG
LIBS = -lXrandr -lX11

.PHONY: all clean debug

all: pivot

pivot.o: pivot.c
	gcc ${O} -c pivot.c

pivot: pivot.o
	gcc -o pivot pivot.o ${LIBS}

clean:
	rm -f pivot
	rm -f *.o
