#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void trace(const char *format, ...) {
	struct timespec time;
	timespec_get(&time, TIME_UTC);

	va_list ap;
	va_start(ap, format);
	printf("[%ld.%ld] ", time.tv_sec, time.tv_nsec / 1000000);
	vprintf(format, ap);
	putchar('\n');
	va_end(ap);
}


int main() {
	trace("Informação = %d", 123);
}
