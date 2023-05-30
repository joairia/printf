#include "main.h"
#include <stdio.h>

/**
 * get_precision - pour calculer la precicion du print
 * @format: format pour print argument
 * @n: nombre d'argument à print
 * @list: list des arguments.
 *
 * Return: Precision.
 */
int get_precision(const char *format, int *n, va_list list)
{
	int i = *n + 1;
	int precision = -1;

	if (format[i] != '.')
		return (precision);

	precision = 0;

	for (i += 1; format[i] != '\0'; i++)
	{
		if (is_digit(format[i]))
		{
			precision *= 10;
			precision += format[i] - '0';
		}
		else if (format[i] == '*')
		{
			i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*n = i - 1;

	return (precision);
}
