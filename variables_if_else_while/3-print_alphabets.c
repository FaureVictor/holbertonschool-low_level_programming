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
	int i;

	n = 0;
	while (n < 26)
	{
		putchar('a' + n);
		n = n + 1;
	}

        i = 0;
        while (i < 26)
        {
                putchar('A' + i);
                i = i + 1;
        }
	putchar('\n');
	return (0);
}
