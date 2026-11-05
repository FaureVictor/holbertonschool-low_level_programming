#include "main.h"

/**
 * cap_string - capitalizes the first letter of each word in a string
 * @str: string to modify
 *
 * Return: pointer to the modified string
 */
char *cap_string(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			if (i == 0 || str[i - 1] == ' ' || str[i - 1] == '\t' || str[i - 1] == '\n')
			{
				str[i] = str[i] - ('a' - 'A');
			}
		}
		i++;
	}
	return (str);
}
