#define ASM_FILE 1
#include "multiboot.h"

#define STACK_SIZE 0x4000

/* The flags for the Multiboot header.  */
#ifdef __ELF__
# define MULTIBOOT_HEADER_FLAGS 0x00000003
#else
# define MULTIBOOT_HEADER_FLAGS 0x00010003
#endif

	.text

	.globl start, _start

start:
_start:
	jmp	multiboot_entry
	.align 4

multiboot_header:
	.long MULTIBOOT_HEADER_MAGIC
	.long MULTIBOOT_HEADER_FLAGS
	.long -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

#ifndef __ELF__
	.long multiboot_header
	.long _start
	.long _edata
	.long _end
	.long multiboot_entry
#endif /* ! __ELF__ */

multiboot_entry:
	/* Initialize the stack pointer.  */
	movl	$(stack + STACK_SIZE), %esp

	/* Reset EFLAGS.  */
	pushl	$0
	popf

	/* Push the pointer to the Multiboot information structure.  */
	pushl	%ebx
	/* Push the magic value.  */
	pushl	%eax

	/* Now enter the C main function...  */
	call	os_main

	cli
hang:
	hlt
	jmp hang

	.comm stack, STACK_SIZE

