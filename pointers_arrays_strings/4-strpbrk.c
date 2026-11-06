#include "main.h"
/**
 * _strpbrk - locates the first occurrence of any character from a set in a string
 * @s: string to search
 * @accept: string containing the characters to match
 *
 * Return: pointer to the character in s that matches one of the characters in accept, or NULL if no such character is found
 */
char *_strpbrk(char *s, char *accept)
{
	while (*s)
	{
		char *a = accept;
		while (*a)
		{
			if (*s == *a)
				return (s);
			a++;
		}
		s++;
	}
	return (0);
}
