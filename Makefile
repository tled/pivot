
.PHONY: all clean debug

all: pivot

pivot: pivot.c
	gcc -Wall -O2 -lXrandr -o pivot pivot.c

debug:
	gcc -Wall -DDEBUG -g -lXrandr -o pivot pivot.c

clean:
	rm -f pivot
