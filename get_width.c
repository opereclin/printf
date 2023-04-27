#include "main.h"

/**
 * get_width - gets the width value specified.
 *
 * @format: A pointer to the format string being processed.
 *
 * @i: A pointer to the current position in the format string.
 *
 * @args: A va_list object containing the variable arguments
 * passed to the function.
 *
 * Return: The width value specified in the format string.
 */
int get_width(const char *format, int *i, va_list args)
{
	int curr_i;
	int width = 0;

	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = curr_i - 1;

	return (width);

}
