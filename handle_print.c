#include "main.h"
/**
 * handle_print - Handles the printing of a single format specifier.
 *
 * @fmt: A pointer to a string containing the format specifier.
 *
 * @ind: A pointer to the current index position in the format string.
 *
 * @args: A va_list containing the arguments for the format specifier.
 *
 * @buffer: A buffer to store the output string.
 *
 * @flags: Flags for the format specifier.
 *
 * @width: Width for the format specifier.
 *
 * @precision: Precision for the format specifier.
 *
 * @size: Size modifier for the format specifier.
 *
 * Return: The number of characters printed, or -1 on error.
 */
int handle_print(const char *fmt, int *ind, va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_len = 0, total_count = -1;
	fmt_t fmt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(args, buffer, flags, width, precision, size));

	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		unknown_len += write(1, "%%", 1);
		if (fmt[*ind - 1] == ' ')
			unknown_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (fmt[*ind] != ' ' && fmt[*ind] != '%')
				--(*ind);
			if (fmt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		unknown_len += write(1, &fmt[*ind], 1);
		return (unknown_len);
	}
	return (total_count);
}
