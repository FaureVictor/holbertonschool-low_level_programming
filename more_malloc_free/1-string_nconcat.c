#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes to concatenate from s2
 * 
 * Return: pointer to the newly allocated space in memory containing the concatenated string
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
{
	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	while (s1[n] != '\0')
		n++;
	char *concat = malloc((n + 1) * sizeof(char));
	if (concat == NULL)
		return (NULL);
	cpy_string(concat, s1);
	cpy_string(concat + n, s2);
	return (concat);
}
