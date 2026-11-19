#include "variadic_functions.h"
#include <stdarg.h>

/**
 * sum_them_all - returns the sum of all its parameters
 * @n: number of parameters
 * @...: the parameters to add
 *
 * Return: the sum of all parameters, or 0 if n is 0
 */
int sum_them_all(const unsigned int n, ...)
{
	va_list args;
	int somme;
	int i;

	i = 0;
	va_start(args, n);
	somme = va_arg(args, int);
	i = 0;
	while (i < n)
	{
		somme + va_arg(args, n);
		i++;
	}
	va_end;
	return (somme);
}
