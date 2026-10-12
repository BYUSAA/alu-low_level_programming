
#include <stdlib.h>
#include "main.h"

/**
 * argstostr - concatenates program arguments into a string
 * @ac: number of arguments
 * @av: array of arguments
 *
 * Return: pointer to the new string, or NULL on failure
 */
char *argstostr(int ac, char **av)
{
	char *result;
	int i;
	int j;
	int length;
	int position;

	if (ac == 0 || av == NULL)
		return (NULL);

	length = 0;
	for (i = 0; i < ac; i++)
	{
		if (av[i] != NULL)
		{
			for (j = 0; av[i][j] != '\0'; j++)
				length++;
		}
		length++;
	}

	result = malloc(sizeof(char) * (length + 1));
	if (result == NULL)
		return (NULL);

	position = 0;
	for (i = 0; i < ac; i++)
	{
		if (av[i] != NULL)
		{
			for (j = 0; av[i][j] != '\0'; j++)
				result[position++] = av[i][j];
		}
		result[position++] = '\n';
	}

	result[position] = '\0';

	return (result);
}
