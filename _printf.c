#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - produces output according to a format
 *
 * @format: format
 *
 * Return: number of characters printed, ommiting ('\0')
 */
int _printf(const char *format, ...)
{
	int i, count = 0, total_count = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (!format)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		switch (format[i])
		{
			case '%':
				print_buffer(buffer, &buff_ind);
				flags = get_flags(format, &i);
				width = get_width(format, &i, args);
				precision = get_precision(format, &i, args);
				size = get_size(format, &i);
				++i;
				count = handle_print(format, &i, args, buffer,
					flags, width, precision, size);
				if (count == -1)
					return (-1);
				total_count += count;
				break;
			default:
				buffer[buff_ind++] = format[i];
				if (buff_ind == BUFF_SIZE)
					print_buffer(buffer, &buff_ind);
				/* write(1, &format[i], 1); */
				total_count++;
				break;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(args);

	return (total_count);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 *
 * @buffer: An array of characters
 *
 * @buff_ind: Index at which to add next char(representing the length)
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
