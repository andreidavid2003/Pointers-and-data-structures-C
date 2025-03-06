CC=gcc
CFLAGS=-I.
DEPS=main.c tema1.h

OBJ := tema1.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

tema1: $(OBJ) $(DEPS)
	$(CC) -o $@ -g $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o tema1
