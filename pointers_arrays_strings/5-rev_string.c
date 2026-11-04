#include "main.h"

/**
 * rev_string - modifie the chain and reverse it in memory
 * @s: string to measure
 */
void rev_string(char *s)
{
    int i;
    int j;
    char tmp;

    i = 0;
    while (s[i] != '\0')
		i = i + 1;
    j = i - 1;
    i = 0;
    while (i < j)
    {
        tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i = i + 1;
        j = j - 1;
    }

}
