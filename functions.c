#include "main.h"
#include <stdio.h>
#include <stdarg.h>


/**
 * print_char - Prints a char
 * @type: List a of arguments
 * @buffer: Buffer array
 * @flag: input flags
 * @width: input 4
 * @precision: Precision specification
 * @size: Size specifier
 * Return: output nbr char
 */
int print_char(va_list type, char buffer[],
	int flag, int width, int precision, int size)
{
	char c = va_arg(type, int);

	return (handle_write_char(c, buffer, flag, width, precision, size));
}


/**
 * print_string - Prints a string
 * @type: List a of arguments
 * @buffer: Buffer array
 * @flag:  input nbr active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: output nbr char
 */
int print_string(va_list type, char buffer[],
	int flag, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(type, char *);

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flag & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}


/**
 * print_percent - Prints a percent sign
 * @type: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flag:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_percent(va_list type, char buffer[],
	int flag, int width, int precision, int size)
{
	UNUSED(type);
	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - Print int
 * @type: Lista of arguments
 * @buffer: Buffer array
 * @flag: active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */

int print_int(va_list type, char buffer[],
	int flag, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(type, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flag, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @type: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flag:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list type, char buffer[],
	int flag, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flag);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(type, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
