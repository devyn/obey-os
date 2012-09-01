#include <stdarg.h>
#include <stddef.h>

#include "output.h"

static unsigned char *output_video = (unsigned char *) 0xB8000;

static int output_x = 0;
static int output_y = 0;

static void output_write_int (int num, unsigned int base) {
	char buffer[38] = { '\0' };
	unsigned int unum;
	char *b = (char *) buffer;
	char *p = b;

	if (base < 2 && base > 36) {
		output_write ("(invalid radix)");
		return;
	}

	if (num < 0) {
		*p++ = '-';
		b++;
		unum = (unsigned int) -num;
	} else { 
		unum = (unsigned int) num;
	}

	do {
		int rem = (int) (unum % base);
		*p++ = (char) (rem < 10 ? rem + '0' : rem + 'a' - 10);
	} while (unum /= base);

	/* Reverse buffer */
	char *p1 = b;
	char *p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	output_write ((char *) buffer);
}

#ifdef TESTS

#include <stdio.h>

void output_putchar (const char ch) {
	putchar ((int) ch);
}

#else

void output_putchar (const char ch) {
	if (ch == '\n' || ch == '\r') {
		newline:
			output_x = 0;
			output_y++;
			if (output_y > OUTPUT_LINES) {
				output_y = 0;
			}
		return;
	}
	
	*(output_video + (output_x + output_y * OUTPUT_COLUMNS) * 2) = ((unsigned char) ch) & 0xFF;
	*(output_video + (output_x + output_y * OUTPUT_COLUMNS) * 2 + 1) = OUTPUT_ATTRIBUTE;

	output_x++;
	if (output_x > OUTPUT_COLUMNS) {
		goto newline;
	}
}

#endif


void output_clear (void) {
	int i;
	for (i = 0; i < OUTPUT_COLUMNS * OUTPUT_LINES * 2; i++) {
		*(output_video + i) = 0;
	}

	output_x = 0;
	output_y = 0;
}

void output_write (const char *string) {
	if (string) {
		while (*string) {
			output_putchar (*string);
			string++;
		}
	}
}

void output_printf (const char *format, ...) {
	const char *ch;
	va_list list;

	if (format) {
		va_start (list, format);

		ch = format;
		while (*ch) {
			if (*ch != '%') {
				output_putchar (*ch);
			} else {
				int number = 0;
				const char *string = NULL;

				ch++;
				switch (*ch) {
				case 'b':
				case 'd':
				case 'x':
					number = va_arg (list, int);
					output_write_int (number, *ch == 'd' ? 10 : (*ch == 'x' ? 16 : 2));
					break;

				case 's':
					string = va_arg (list, const char*);
					if (string) {
						output_write (string);
					} else {
						output_write ("(null)");
					}
					break;
				}
			}
			ch++;
		}

		va_end (list);
	}
}


#ifdef TESTS
int main (void) {

	int n = 0;

	while (n < 256) {
		output_write_int (n, 2);
		output_putchar ('\n');
		n++;
	}

	return 0;
}
#endif
