#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int array[] = { 20, 4, 6, 2, 325, 24, 45};

int main() {
	for (int i = 0; i < ARRAY_SIZE(array); ++i)
		printf("[%d] - %d\n", i, array[i]);
	putchar('\n');

	memmove(array + 1, array, sizeof array - sizeof array[0]);

	for (int i = 0; i < ARRAY_SIZE(array); ++i)
		printf("[%d] - %d\n", i, array[i]);
}
