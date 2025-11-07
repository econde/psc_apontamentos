#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

static size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size);

int mini_snprintf(char *buffer, size_t buffer_size, const char *fmt, ...) {
	if (buffer_size == 0)
		return 0;
	va_list ap;
	va_start(ap, fmt);
	char *str = buffer;
	size_t str_size = 0;
	for (const char *p = fmt; *p && buffer_size > 1; p++) {
		if (*p != '%') {
			*str++ = *p;
			str_size++;
			buffer_size--;
			continue;
		}
		switch (*++p) {
			case 'd': {
				int ival = va_arg(ap, int);
				size_t nbytes = int_to_string(ival, 10, str, buffer_size);
				if (nbytes == 0)
					goto ret;
				str_size += nbytes;
				str += nbytes;
				buffer_size -= nbytes;
				break;
			}
			case 'x': {
				int ival = va_arg(ap, int);
				size_t nbytes = int_to_string(ival, 16, str, buffer_size);
				if (nbytes == 0)
					goto ret;
				str_size += nbytes;
				str += nbytes;
				buffer_size -= nbytes;
				break;
			}
			case 'c': {
				char cval = va_arg(ap, int);
				if (buffer_size < 2)
					goto ret;
				*str++ = cval;
				str_size++;
				buffer_size--;
				break;
			}
			case 's': {
				char *sval = va_arg(ap, char *);
				size_t str_len = strlen(sval);
				if (buffer_size < str_len + 1)
					goto ret;
				strcpy(str, sval);
				str += str_len;
				str_size += str_len;
				buffer_size -= str_len;
				break;
			}
			default:
				*str++ = *p;
				str_size++;
				buffer_size--;
		}
	}
ret:
	*str = '\0';
	va_end(ap);
	return str_size;
}

static size_t int_to_string(unsigned value, int base, char buffer[], size_t buffer_size) {
	if (base == 0 || buffer_size < 2)
		return 0;
	size_t initial = 0, index = 0;
	if (base == 2) {
		if (buffer_size < 4)
			return 0;
		buffer[0] = '0';
		buffer[1] = 'b';
		initial = 2;
		index = 2;
	}
	if (base == 8) {
		if (buffer_size < 3)
			return 0;
		buffer[0] = '0';
		initial = 1;
		index = 1;
	}
	if (base == 16) {
		if (buffer_size < 4)
			return 0;
		buffer[0] = '0';
		buffer[1] = 'x';
		initial = 2;
		index = 2;
	}
	ldiv_t aux = { .quot = value };
	while (aux.quot >= base) {
		if (index == buffer_size)
			return 0;
		aux = ldiv(aux.quot, base);
		buffer[index] = aux.rem > 9 ? aux.rem - 10 + 'a' : aux.rem + '0';
		index++;
	}
	if (index == buffer_size)	/* a dimensão do buffer não é suficiente */
		return 0;
	buffer[index] = aux.quot > 9 ? aux.quot - 10 + 'a' : aux.quot + '0';
	index++;
	buffer[index] = '\0';
	for (size_t j = initial, i = index - 1; j < i; ++j, --i) {
		char tmp = buffer[i];
		buffer[i] = buffer[j];
		buffer[j] = tmp;
	}
	return index;
}

