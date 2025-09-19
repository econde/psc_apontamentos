	.text
	.globl	must_frequent_digit
must_frequent_digit:
	endbr64
	mov	$0, %eax		# Inicializar o array digits com o valor zero
	jmp	mfd_for1_cond		# O array digits é alojado na red zone
mfd_for1_do:
	movl	$0, -40(%rsp,%rax,4)
	add	$1, %rax
mfd_for1_cond:
	cmp	$9, %rax
	jbe	mfd_for1_do
mfd_while_do:
	cmpb	$0, (%rdi)		# While (*str++)
	je	mfd_while_exit
	inc	%rdi
	movzbl	(%rdi), %eax
	sub	$'0', %eax
	cmp	$9, %al			# if (*str >= '0' && *str <= '9')
	ja	mfd_while_do
	movsbl	(%rdi), %eax		# digits[*str - '0']++;
	sub	$'0', %eax
	cltq
	incl	-40(%rsp,%rax,4)
	jmp	mfd_while_do
mfd_while_exit:
	mov	$1, %edx		# for (size_t i = 1; ... ; ...)
	mov	$0, %eax
	jmp	mfd_for2_cond
mfd_for2_do:
	add	$1, %rdx		# for (... ; ... ; ++i)
mfd_for2_cond:			# for (... ; i < sizeof digits / sizeof digits[0]; ...)
	cmp	$9, %rdx		# if (digits[index] < digits[i])
	ja	mfd_for2_exit		
	mov	-40(%rsp,%rdx,4), %esi
	cmp	%esi, -40(%rsp,%rax,4)
	jge	mfd_for2_do
	mov	%rdx, %rax		# index = i;
	jmp	mfd_for2_do
mfd_for2_exit:
	mov	-40(%rsp,%rax,4), %eax
	ret

	.section .note.GNU-stack
