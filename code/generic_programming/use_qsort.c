#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int array[] = { 20, 4, 6, 2, 325, 24, 45};

int cmp_int(const void *a, const void *b) {
	if (*(int *)a > *(int*) b)
		return 1;
	else if (*(int *)a < *(int*) b)
		return -1;
	return 0;
}

int main() {
	for (int i = 0; i < ARRAY_SIZE(array); ++i)
		printf("%d\n", array[i]);
	putchar('\n');
	qsort(array, ARRAY_SIZE(array), sizeof(array[0]), cmp_int);

	for (int i = 0; i < ARRAY_SIZE(array); ++i)
		printf("%d\n", array[i]);
}
