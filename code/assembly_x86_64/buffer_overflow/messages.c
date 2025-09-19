#include <stdio.h>
#include <string.h>

void print_message(int n) {
	static const char *message[] = {
		"Message A",
		"Message B"
	};
	puts(message[n]);
}

void message() {
	struct {
		int a;
		char buffer[7];
		short b;
	} x;

	x.a = ' ';
	x.b = ' ';

	gets(x.buffer);

	if (x.b == 'B')
		print_message(1);

	if (x.a == 'A')
		print_message(0);
}

int main() {
	printf("%p\n", main);
	message();
}
