include ../Makefile.inc

.PHONY: all clean

all: output.o

output.o: output.c output.h
	$(CC) $(CFLAGS) -c output.c

clean:
	-@$(RM) output.o
