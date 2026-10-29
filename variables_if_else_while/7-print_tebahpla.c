#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	int n;
	int i;

	n = 0;
	while (n < 10)
	{
		putchar('0' + n);
		n = n + 1;

	}

	i = 0;
	while (i < 3)
	{
		putchar('a' + i);
		i = i + 1;
	}

	putchar('\n');
	return (0);
}
