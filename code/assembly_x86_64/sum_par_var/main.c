#include <stdio.h>
#include <stdarg.h>

int i = 3;
int *pi = &i;

int sum(int n, ...) {
	va_list ap;
	va_start(ap, n);
	int res = 0;
	for( ; n; n--) 
		res += va_arg(ap, int);
	return res;
}

int main() {
	int a = sum(2, 4, 5);
	int b, i = sum(5, 1, 3, 5, 7, 9);
	printf("%d %d\n", a, b);
	pi = &i + 2;
}
