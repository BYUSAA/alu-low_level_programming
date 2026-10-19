
#include <stdlib.h>
#include "dog.h"

/**
 * copy_string - copies a string into newly allocated memory
 * @str: string to copy
 *
 * Return: pointer to the copy, or NULL on failure
 */
static char *copy_string(char *str)
{
	char *copy;
	int i;
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;

	copy = malloc(sizeof(char) * (len + 1));
	if (copy == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		copy[i] = str[i];

	return (copy);
}

/**
 * new_dog - creates a new dog
 * @name: name of the dog
 * @age: age of the dog
 * @owner: name of the dog's owner
 *
 * Return: pointer to the new dog, or NULL on failure
 */
dog_t *new_dog(char *name, float age, char *owner)
{
	dog_t *d;

	if (name == NULL || owner == NULL)
		return (NULL);

	d = malloc(sizeof(dog_t));
	if (d == NULL)
		return (NULL);

	d->name = copy_string(name);
	if (d->name == NULL)
	{
		free(d);
		return (NULL);
	}

	d->owner = copy_string(owner);
	if (d->owner == NULL)
	{
		free(d->name);
		free(d);
		return (NULL);
	}

	d->age = age;

	return (d);
}
