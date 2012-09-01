#ifndef OUTPUT_H
#define OUTPUT_H

#define OUTPUT_COLUMNS			80
#define OUTPUT_LINES			24
#define OUTPUT_ATTRIBUTE		7

void output_putchar (const char ch);
void output_clear (void);
void output_write (const char *string);
void output_printf (const char *format, ...);

#endif
