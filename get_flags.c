#include "main.h"

/**
 * get_flags - returns a set of flags for a format specifier string
 *
 * @format: the format specifier string
 *
 * @i: a pointer to the current index in the format string
 *
 * Return: the set of flags as integer
 */
int get_flags(const char *format, int *i)
{
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	j = 0;
	curr_i = *i + 1;
	while (format[curr_i] != '\0')
	{
		while (FLAGS_CH[j] != '\0')
		{
			if (format[curr_i] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

			j++;
		}
		if (!FLAGS_CH[j])
			break;
		curr_i++;
		j = 0; /* resetting j for the next iteration of the outer loop */
	}
	*i = curr_i - 1;

	return (flags);
}
