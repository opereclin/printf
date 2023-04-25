#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include "main.h"

/**
 * binary_helper - helper function to convert unsigned to binary
 * @num: the number to be converted
 *
 * Return: returns the number of bits printed
 */

int binary_helper(int num)
{
	char c[33];
	int bits_printed = 0;

	if (num > 1)
	{
		bits_printed += binary_helper(num / 2);
	}
	sprintf(c, "%d", num % 2);
	write(1, c, 1);
	bits_printed++;
	return (bits_printed);
}


/**
 * handle_binary_conversion - converts unsigned int to binary
 * @count: number of characters to be printed to the output stream
 * @args: the arguments to be formatted
 *
 * Return: returns the char_printed_count
 */

int handle_binary_conversion(int count, va_list args)
{
	unsigned int num;
	int res;

	num = va_arg(args, unsigned int);
	res = binary_helper(num);
	count += res;
	return (count);
}
