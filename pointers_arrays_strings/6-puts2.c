#include "main.h"

/**
 * puts_2 - prints every other character of a string
 * @str: string to print
 */
void puts2(char *str)
{
    int i;
    int len;
    
    len = 0;
    while (str[len] != '\0')
    len = len + 1;
    i = 0;
    while (i < len)
    {
     _putchar(str[i]);
        i = i + 2;
    }
    _putchar('\n');
}