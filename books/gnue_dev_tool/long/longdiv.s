	.file	"longdiv.c"
	.globl	a
	.data
	.align 8
	.type	a, @object
	.size	a, 8
a:
	.quad	12340000
	.globl	b
	.align 8
	.type	b, @object
	.size	b, 8
b:
	.quad	10000
	.section	.rodata
	.align 8
.LC0:
	.string	"sizeof(unsigned logn long) is %d bytes\n"
.LC1:
	.string	"a / b = %ld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$8, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movq	a(%rip), %rax
	movq	b(%rip), %rcx
	movl	$0, %edx
	divq	%rcx
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-4)"
	.section	.note.GNU-stack,"",@progbits
