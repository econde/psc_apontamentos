	.file	"main.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	cmpl	$89, %edi
	je	.L3
	cmpl	$89, %edi
	jle	.L8
	cmpl	$155, %edi
	je	.L6
	cmpl	$347, %edi
	jne	.L2
	movl	$48, c(%rip)
	jmp	.L2
.L8:
	cmpl	$10, %edi
	jne	.L2
	movl	$20, a(%rip)
.L2:
	movl	$0, %eax
	ret
.L6:
	movl	$33, b(%rip)
	jmp	.L2
.L3:
	movl	$685, b(%rip)
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.comm	d,4,4
	.comm	c,4,4
	.comm	b,4,4
	.comm	a,4,4
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
