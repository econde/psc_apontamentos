/*
Person *get_lighter(Person *people, size_t n_people) {
rax                         rdi             rsi
	size_t lighter = 0;
	        rax
	for (size_t i = 1; i < n_people; ++i)
	           rdx
		if (people[i].weight > people[lighter].weight)
			lighter = i;
	return &people[lighter];
}
*/

	.global	get_lighter
get_lighter:
	movq	$0, %rax		#	size_t lighter = 0;
	movq	$1, %rdx		#	for (size_t i = 1; ...
	jmp	for_cond
for:
	addq	$1, %rdx		#	for (... ; ... ; ++i)
for_cond:					#	for ( ...; i < n_people; ...)
	cmpq	%rsi, %rdx
	jnb	for_end
	movq	%rdx, %r8
	salq	$5, %r8			#	r8 = i * sizeof people[0]
	movq	%rax, %rcx
	salq	$5, %rcx		#	rcx = lighter * sizeof people[0]
	movl	24(%rdi, %rcx), %ecx	#	ecx = people[lighter].weight
	cmpl	%ecx, 24(%rdi, %r8)		#	if (people[i].weight < ecx)
	jge	for
	movq	%rdx, %rax			#	lighter = i;
	jmp	for
for_end:
	salq	$5, %rax			# rax = lighter * sizeof people[0]
	addq	%rdi, %rax			# rax = &people[lighter]
	ret
