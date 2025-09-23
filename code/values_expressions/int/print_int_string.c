#include <limits.h>
#include <stdio.h>

void int_to_string_binary(int value, char buffer[]) {
	for (int i = CHAR_BIT * sizeof value - 1; i >= 0; --i)
		buffer[CHAR_BIT * sizeof value - 1 - i] = '0' + ((value & 1 << i) != 0);
}

void int_to_string_decimal(int value, char buffer[]) {
	int i;
	for (i = 0; value != 0; ++i) {
		buffer[i] = value % 10 + '0';
		value /= 10;
	}
	buffer[i] = '\0';
	int j;
	for (i--, j = 0; i > j; j++, i--) {
		char tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}
}

int main() {
	char string_number[50];
	int_to_string_decimal(235, string_number);
	puts(string_number);
	int_to_string_binary(235, string_number);
	puts(string_number);
}