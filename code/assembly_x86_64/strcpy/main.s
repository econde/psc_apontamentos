    .bss
dst:
    .zero	100

    .section .rodata
.LC0:
    .string "abcdefghijk"

    .data
src:
    .quad   .LC0

    .text
    .global main
main:
    mov	src(%rip), %rsi
    lea	dst(%rip), %rdi
    call	my_strcpy
    mov	$0, %eax
    ret
