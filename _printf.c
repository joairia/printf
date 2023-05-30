#include "main.h"
#include <stdio.h>
#include <stdarg.h>

void print_buffer(char buffer[], int *i);

/**
 * _printf - Printf function
 * @format: format des arguments
 * Return: char
 */

int _printf(const char *format, ...)
{
	int i, flags, width, size, precision, printed, printed_chars, buff_ind;
	va_list list;
	char buffer[BUFF_SIZE];

	printed = 0;
	printed_chars = 0;
	buff_ind = 0;

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);

			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buffer - Prints the buffer
 * @buffer: input Array
 * @i: lenght
 */

void print_buffer(char buffer[], int *i)
{
	if (*i > 0)
		write(1, &buffer[0], *i);

	*i = 0;
}
