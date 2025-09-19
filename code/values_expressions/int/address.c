#include <stdio.h>

char alpha = 'a';
int integer = 23;

int main() {
	printf("Endereço de alpha = %p\n", &alpha);
	printf("Endereço de integer = %p\n", &integer);
}
