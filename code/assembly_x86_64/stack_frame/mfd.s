	.file	"mfd.c"
	.text
	.globl	must_frequent_digit
	.type	must_frequent_digit, @function
must_frequent_digit:
.LFB16:
	.cfi_startproc
	endbr64
	subq	$56, %rsp
	.cfi_def_cfa_offset 64
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	jmp	.L2
.L3:
	movl	$0, (%rsp,%rax,4)
	addq	$1, %rax
.L2:
	cmpq	$9, %rax
	jbe	.L3
	jmp	.L4
.L5:
	movq	%rdx, %rdi
.L4:
	leaq	1(%rdi), %rdx
	cmpb	$0, (%rdi)
	je	.L13
	movzbl	1(%rdi), %eax
	leal	-48(%rax), %ecx
	cmpb	$9, %cl
	ja	.L5
	movsbl	%al, %eax
	subl	$48, %eax
	cltq
	movl	(%rsp,%rax,4), %esi
	leal	1(%rsi), %ecx
	movl	%ecx, (%rsp,%rax,4)
	jmp	.L5
.L13:
	movl	$1, %edx
	movl	$0, %eax
	jmp	.L7
.L8:
	addq	$1, %rdx
.L7:
	cmpq	$9, %rdx
	ja	.L14
	movl	(%rsp,%rdx,4), %esi
	cmpl	%esi, (%rsp,%rax,4)
	jge	.L8
	movq	%rdx, %rax
	jmp	.L8
.L14:
	movq	40(%rsp), %rdx
	subq	%fs:40, %rdx
	jne	.L15
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE16:
	.size	must_frequent_digit, .-must_frequent_digit
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
