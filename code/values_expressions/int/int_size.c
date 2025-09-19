#include <stdio.h>

int main() {
	unsigned int value = ~0;
	int counter = 0;
	while (value != 0) {
		value = value >> 1;
		counter++;
	}
	printf("Número de bits de um int = %d\n", counter);
}
