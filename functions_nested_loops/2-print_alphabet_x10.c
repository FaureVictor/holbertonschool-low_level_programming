#include "main.h"

/**
 * print_alphabet_x10 - prints the alphabet 10 times, in lowercase
 */
void print_alphabet_x10(void)
{
	int n;
	int b;

	b = 0;
	while (b < 10)
	{
		n = 0;
		while (n < 26)
		{
			_putchar('a' + n);
			n = n + 1;
		}
		b = b + 1;
		_putchar('\n');
	}
}
