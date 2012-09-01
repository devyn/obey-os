	.file	"main.c"
	.text
	.globl	os_main
	.type	os_main, @function
os_main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	cmpl	$0, 12(%ebp)
	je	.L7
	cmpl	$732803074, 8(%ebp)
	jne	.L7
.L3:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L5
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	andl	$32, %eax
	testl	%eax, %eax
	jne	.L8
.L5:
	movl	12(%ebp), %eax
	movl	(%eax), %eax
	andl	$16, %eax
	testl	%eax, %eax
	jmp	.L1
.L7:
	nop
	jmp	.L1
.L8:
	nop
.L1:
	popl	%ebp
	.cfi_def_cfa 4, 4
	.cfi_restore 5
	ret
	.cfi_endproc
.LFE0:
	.size	os_main, .-os_main
	.ident	"GCC: (Ubuntu/Linaro 4.6.1-9ubuntu3) 4.6.1"
	.section	.note.GNU-stack,"",@progbits
