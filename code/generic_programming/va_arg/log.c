#include <stdio.h>
#include <stdarg.h>
#include <time.h>

void trace(const char *fmt, ...) {
	struct timespec time;
	timespec_get(&time, TIME_UTC);

	va_list ap;
	va_start(ap, fmt);
	printf("[%ld.%ld] ", time.tv_sec, time.tv_nsec / 1000000);
	vprintf(fmt, ap);
	putchar('\n');
	va_end(ap);
}


int main() {
	trace("%s", "Mensagem");
}
