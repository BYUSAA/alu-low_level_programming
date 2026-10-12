
#include <stdlib.h>
#include "main.h"

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to the duplicated string, or NULL
 */
char *_strdup(char *str)
{
	char *copy;
	unsigned int i;
	unsigned int length;

	if (str == NULL)
		return (NULL);

	length = 0;
	while (str[length] != '\0')
		length++;

	copy = malloc(sizeof(char) * (length + 1));
	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= length; i++)
		copy[i] = str[i];

	return (copy);
}
