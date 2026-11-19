#include <stdio.h>
#include <stdlib.h>

/**
 * main - adds positive numbers
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0 on success, 1 if an argument is not a number
 */
int main(int argc, char *argv[])
{
	int mots;
	int lettres;
	int somme;

	mots = 1;
	lettres = 0;
	somme = 0;
	while (mots < argc)
	{
		lettres = 0;
		while (argv[mots][lettres] != '\0')
		{
			if (argv[mots][lettres] < '0' || argv[mots][lettres] > '9')
			{
				printf("Error\n");
				return (1);
			}
			lettres++;
		}
		somme = somme + atoi(argv[mots]);
		mots++;
	}
	printf("%d\n", somme);
	return (0);
}
