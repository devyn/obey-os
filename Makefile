include Makefile.inc

DIRS := loader output

.PHONY: all run clean $(DIRS)

all: os.bin

os.bin: loader output
	$(LD) -T loader/linker.ld -o os.bin loader/loader.o loader/main.o output/output.o

loader:
	cd loader && $(MAKE) $(MFLAGS)

output:
	cd output && $(MAKE) $(MFLAGS)

run: os.bin
	-qemu -kernel os.bin

clean:
	-@rm -f os.bin
	-@for d in $(DIRS); do (cd $$d && $(MAKE) clean); done
