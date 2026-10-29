#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
		if ('a' + n != 'e' && 'a' + n != 'q')
			putchar('a' + n);
		n = n + 1;
	}
putchar('\n');
	return (0);
}
