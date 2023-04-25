#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include "main.h"

/**
 * write_and_count - writes to the stdout
 * @fd: file descriptor -> 1 for the std output
 * @buf: buffer to be written to the output stream
 * @n: size of the buffer
 * @count: number of characters written to the output stream
 *
 * Return: returns the count;
 */

int write_and_count(int fd, void *buf, size_t n, int count)
{
	write(fd, buf, n);
	count++;
	return (count);
}

/**
 * handle_integers - formats signed decimal integers
 * @args: list of arguments to be formatted
 * @char_printed_count: number of characters printed to the output stream
 *
 * Return: retuns char_printd_count
 */

int handle_integers(int char_printed_count, va_list args)
{
	char buf[32];
	int num, len, write_res;

	num = va_arg(args, int);
	len = sprintf(buf, "%d", num);
	write_res = write(1, buf, len);
	if (write_res < 0)
	{
		return (char_printed_count);
	}
	char_printed_count += write_res;
	return (char_printed_count);
}

/**
 * handle_strings - formats strings
 * @char_printed_count: number of characters printed to the output stream
 * @args: arguments to be formatted
 * @type: either character or string
 *
 * Return: returns char_printed_count
 */

int handle_strings(int char_printed_count, va_list args, char type)
{
	char c, *s;
	int write_res;

	if (type == 'c')
	{
		c = va_arg(args, int);
		write_res = write(1, &c, 1);
		if (write_res < 0)
			return (char_printed_count);
		char_printed_count++;
		return (char_printed_count);
	}
	else if (type == 's')
	{
		s = va_arg(args, char *);
		while (*s != '\0')
		{
			write_res = write(1, s, 1);
			if (write_res < 0)
				return (char_printed_count);
			s++;
			char_printed_count++;

		}
	}
	return (char_printed_count);
}

/**
 * _printf - prints formated text to the stdout
 * @format: how the text will be formatted
 *
 * Return: the number of characters printed
 */

int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, char_printed_count = 0;
	char c;

	va_start(args, format);
	while (format && format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			switch (format[i])
			{
				case 'd':
				case 'i':
					char_printed_count = handle_integers(char_printed_count, args);
					break;
				case 'b':
					char_printed_count = handle_binary_conversion(char_printed_count, args);
					break;
				case 'c':
					char_printed_count = handle_strings(char_printed_count, args, 'c');
					break;
				case 's':
					char_printed_count = handle_strings(char_printed_count, args, 's');
					break;
				case '%':
					char_printed_count = write_and_count(1, "%", 1, char_printed_count);
					break;
				default:
					break;
			}
		}
		else
		{
			c = format[i];
			char_printed_count = write_and_count(1, &c, 1, char_printed_count);
		}
		i++;
	}
	va_end(args);
	return (char_printed_count);
}
