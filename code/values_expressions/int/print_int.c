#include <limits.h>
#include <stdio.h>

void print_binary(int value) {
	for (int i = CHAR_BIT * sizeof value - 1; i >= 0; --i)
		putchar('0' + ((value & 1 << i) != 0));
	putchar('\n');
}

void print_decimal(int value) {
	char buffer[20];
	int i;
	for(i = 0; value > 0; ++i) {
		buffer[i] = '0' + value % 10;
		value = value / 10;
	}
	for (i--; i >=0; i--)
		putchar(buffer[i]);
	putchar('\n');
}

int main() {
	int i = 2045;
	print_binary(i);
	print_decimal(i);
}