#include "main.h"

/**
 * get_precision - Calculates the precision for printing
 * @p: format
 * @params: argu structure
 * @a: argum
 *
 * Return: pointer
 */
char *get_precision(char *p, params_t *params, va_list a)
{
	int d = 0;

	if (*p != '.')
		return (p);
	p++;
	if (*p == '*')
	{
		d = va_arg(a, int);
		p++;
	}
	else
	{
		while (is_digit(*p))
			d = d * 10 + (*p++ - '0');
	}
	params->precision = d;
	return (p);
}
