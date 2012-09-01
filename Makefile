include Makefile.inc

DIRS := output

.PHONY: all run clean $(DIRS)

all: os.bin

os.bin: main.o loader.o linker.ld output
	$(LD) -T linker.ld -o os.bin loader.o main.o output/output.o

main.o: main.c multiboot.h main.h
	$(CC) $(CFLAGS) -c main.c

loader.o: loader.S
	$(CC) $(CFLAGS) -c loader.S

output:
	cd output && $(MAKE) $(MFLAGS)

run: os.bin
	-qemu -kernel os.bin

clean:
	-@$(RM) os.bin main.o loader.o
	-@for d in $(DIRS); do (cd $$d && $(MAKE) clean); done
