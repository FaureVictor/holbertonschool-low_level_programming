#include "main.h"

/**
 * _strlen - returns the length of a string
 * @s: string to measure
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
    int i;
    int total;

    i = 0;
    total = 0;
    while (s[i] != '\0')
    {
        i = i + 1;
    }
    return (total);
}