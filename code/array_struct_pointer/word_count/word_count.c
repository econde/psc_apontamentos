#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

unsigned get_time() {
	struct timespec time_point;
	timespec_get(&time_point, TIME_UTC);
	return time_point.tv_sec * 1000 + time_point.tv_nsec / 1000000;
}

#define  WORD_MAX_SIZE	1000

#define  WORDS_MAX	40000

struct word {
	char word[WORD_MAX_SIZE];
	int counter;
};

struct word words[WORDS_MAX];
size_t words_counter;

void word_insert(char *word) {
	size_t i;
	for (i = 0; i < words_counter; ++i) {
		if (strcmp(words[i].word, word) == 0) {
			words[i].counter++;
			break;
		}
	}
	if (i == words_counter) {
		strcpy(words[words_counter++].word, word);
		words[i].counter = 1;
	}
}

void sort(struct word words[], size_t n) {
	for (size_t i = 0; i < n - 1; ++i)
		for (size_t j = 0; j < n - i - 1; ++j)
			if (words[j].counter < words[j + 1].counter) {
				struct word tmp = words[j];
				words[j] = words[j + 1];
				words[j + 1] = tmp;
			}
}

void words_print(struct word words[], int n) {
	for (size_t i = 0; i < n; ++i)
		printf("%s - %d\n", words[i].word, words[i].counter);
}

char *separators = " .,;!?\t\n\f:-\"\'\\/(){}[]*=%<>#";

int word_read(char buffer[], size_t buffer_size) {
	int i = 0, c;
	do {
		c = getchar();
		if (c == EOF){
			return EOF;
		}
	} while (strchr(separators, c) != NULL);
	do {
		buffer[i++] = c;
		c = getchar();
		if (i == buffer_size - 1 || c == EOF)
			break;
	} while (strchr(separators, c) == NULL);
	buffer[i] = '\0';
	return i;
}

int main() {
	char word_buffer[WORD_MAX_SIZE];

	unsigned initial = get_time();

	while (word_read(word_buffer, sizeof word_buffer) != EOF)
		word_insert(word_buffer);

	unsigned elapsed = get_time() - initial;
	printf("Palavras diferentes = %zd\nInsersão de palavras = %d\n",
	       words_counter, elapsed);

	initial = get_time();
	sort(words, words_counter);
	elapsed = get_time() - initial;
	printf("Ordenação de palavras = %d\n", elapsed);

	words_print(words, 10);
}


