#include <stdio.h>

int var = 23;

int main() {
	int *ptr = &var;
	printf("Ponteiro para var tem o valor = %p\n"
		"O conteúdo de var é = %d\n", ptr, *ptr);
}