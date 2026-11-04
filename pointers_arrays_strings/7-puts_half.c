#include "main.h"

/**
 * puts_half - prints half of a string, followed by a new line.
 * @str: string to print
 */
void puts_half(char *str)
{
    int i;
    int len;

    len = 0;
    while (str[len] != '\0')
        len = len + 1;
    i = len / 2;
    while (i < len)
    {

        _putchar(str[i]);
        i = i + 1;
    }
    _putchar('\n');
}
