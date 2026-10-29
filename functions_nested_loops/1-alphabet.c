#include "main.h"

/**
 * print_alphabet - prints the alphabet
 *
 * Return: Always 0 (Success)
 */

void print_alphabet(void)
{
	int n;

	n = 0;
	while (n < 26)
	{
		_putchar('a' + n);
		n = n + 1;
	}
	_putchar('\n');
}
