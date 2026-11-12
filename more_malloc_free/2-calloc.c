#include "main.h"
#include <stdlib.h>

/**
 * _calloc - allocates memory for an array of a certain number of elements
 * @nmemb: number of elements
 * @size: size of each element
 *
 * Return: pointer to the allocated memory, or NULL if it fails
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *ptr;
	unsigned int total_size;

	total_size = nmemb * size;
	if (total_size == 0)
		return (NULL);

	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);

	return (ptr);
}
