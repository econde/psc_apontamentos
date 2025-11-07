#include <stdio.h>

int mini_snprintf(char *buffer, size_t buffer_size, const char *fmt, ...);

int main() {
	char buffer[100];
	
	mini_snprintf(buffer, sizeof buffer,
		"Número = %d = %x, caratere = %c, string = %s\n",
			34, 34, 'j', "aabbccdd");
	printf("%s\n", buffer);
}
