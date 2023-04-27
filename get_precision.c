#include "main.h"

/**
 * get_precision - extracts the precision specifier from the
 * format string
 *
 * @format: the format string to extract the specifier from
 *
 * @i: a pointer to the current position in the format string
 *
 * @args: the va_list object containing the variable arguments
 *
 * Return: the value of the precision specifier, or -1 if no
 * precision was specified
 */
int get_precision(const char *format, int *i, va_list args)
{
	int curr_i = *i + 1;
	int precision = -1;

	if (format[curr_i] != '.')
		return (precision);

	precision = 0;

	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (precision);
}
