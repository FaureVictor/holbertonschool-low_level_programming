#include <stdio.h>

/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
        int n;

	n = 0;
	while (n < 26)
	{
		putchar('z' - n);
		n = n + 1;
	}
	putchar('\n');
	return (0);
}
