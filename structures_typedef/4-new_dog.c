#include "dog.h"
#include <stdlib.h>

/**
 * copy_text - makes a copy of a string in newly allocated memory
 * @s: string to copy
 *
 * Return: pointer to the copy, or NULL if it fails
 */
static char *copy_text(char *s)
{
	char *copy;
	int len;
	int i;

	if (s == NULL)
		return (NULL);

	len = 0;
	while (s[len] != '\0')
		len++;

	copy = malloc(len + 1);
	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = s[i];
	return (copy);
}

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: owner of the dog
 *
 * Return: pointer to the new dog, or NULL if it fails
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *my_dog;

	my_dog = malloc(sizeof(dog_t));
	if (my_dog == NULL)
		return (NULL);

	my_dog->name = copy_text(name);
	my_dog->age = age;
	my_dog->owner = copy_text(owner);

	if (my_dog->name == NULL || my_dog->owner == NULL)
	{
		free(my_dog->name);
		free(my_dog->owner);
		free(my_dog);
		return (NULL);
	}
	return (my_dog);
}
