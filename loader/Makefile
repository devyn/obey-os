include ../Makefile.inc

.PHONY: all clean

all: main.o loader.o

main.o: main.c multiboot.h main.h
	$(CC) $(CFLAGS) -c main.c

loader.o: loader.S
	$(CC) $(CFLAGS) -c loader.S

clean:
	-@$(RM) os.bin main.o loader.o
