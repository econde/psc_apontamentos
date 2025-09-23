#include <stdio.h>
#include <string.h>

int word_read(char buffer[], size_t buffer_size, const char *separators, FILE *fd) {
	if (buffer_size == 0)
		return -3;
	if (0 == buffer_size - 1) {
		buffer[0] = '\0';
		return -2;
	}
	int i = 0, c;
	do {
		c = fgetc(fd);
		if (c == EOF) {
			buffer[0] = '\0';
			return -1;
		}
	} while (strchr(separators, c) != NULL);
	do {
		buffer[i++] = c;
		c = fgetc(fd);
		if (c == EOF) {
			buffer[i] = '\0';
			return -1;
		}
		if (i == buffer_size - 1) {
			buffer[i] = '\0';
			return -2;
		}
	} while (strchr(separators, c) == NULL);
	buffer[i] = '\0';
	return i;
}

int main() {
	char word_buffer[30];
	char *separators = " .,;!?\t\n\f:-\"\'\\/(){}[]*=%<>#";
	while (word_read(word_buffer, sizeof word_buffer, separators, stdin) >= 0)
		puts(word_buffer);
}
