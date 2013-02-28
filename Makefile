

.PHONY: all clean

all: pivot

pivot: pivot.c
	gcc -g -lXrandr -o pivot pivot.c

clean:
	rm -f pivot
