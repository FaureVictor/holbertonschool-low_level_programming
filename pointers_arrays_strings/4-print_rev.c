#include "main.h"

/**
 * print_rev - string a chain in reverse
 * @s: string to measure
 */
void print_rev(char *s)
{
    int i;

    i = 0;
    while (s[i] != '\0')
		i = i + 1;
    i = i - 1;
    while (i >= 0)
    {
        _putchar(s[i]);
        i = i - 1;
	 }
    _putchar('\n');
}
