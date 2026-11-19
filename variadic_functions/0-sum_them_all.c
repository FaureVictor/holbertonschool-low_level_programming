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
	unsigned int i;

	if (n == 0)
	{
		return (0);
	}
	va_start(args, n);
	somme = 0;
	i = 0;
	while (i < n)
	{
		somme = somme + va_arg(args, int);
		i++;
	}
	va_end(args);
	return (somme);
}
