#include <stdlib.h>

int must_frequent_digit(char *str) {
	int digits[10] = {0};
	while (*str++)
		if (*str >= '0' && *str <= '9')
			digits[*str - '0']++;
	size_t index = 0;
	for (size_t i = 1; i < sizeof digits / sizeof digits[0]; ++i)
		if (digits[index] < digits[i])
			index = i;
	return digits[index];
}
