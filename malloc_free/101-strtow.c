
#include <stdlib.h>
#include "main.h"

/**
 * count_words - counts words separated by spaces
 * @str: string to examine
 *
 * Return: number of words
 */
static int count_words(char *str)
{
	int count;
	int in_word;

	count = 0;
	in_word = 0;

	while (*str != '\0')
	{
		if (*str != ' ')
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;

		str++;
	}

	return (count);
}

/**
 * word_length - calculates the length of a word
 * @str: start of the word
 *
 * Return: length of the word
 */
static int word_length(char *str)
{
	int length;

	length = 0;
	while (str[length] != '\0' && str[length] != ' ')
		length++;

	return (length);
}

/**
 * free_words - frees allocated words and their array
 * @words: array of strings
 * @count: number of allocated words
 *
 * Return: nothing
 */
static void free_words(char **words, int count)
{
	int i;

	for (i = 0; i < count; i++)
		free(words[i]);

	free(words);
}

/**
 * strtow - splits a string into words
 * @str: string to split
 *
 * Return: array of words, or NULL on failure
 */
char **strtow(char *str)
{
	char **words;
	int count;
	int i;
	int j;
	int length;
	int index;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	count = count_words(str);
	if (count == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (count + 1));
	if (words == NULL)
		return (NULL);

	i = 0;
	index = 0;

	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			i++;
			continue;
		}

		length = word_length(&str[i]);
		words[index] = malloc(sizeof(char) * (length + 1));
		if (words[index] == NULL)
		{
			free_words(words, index);
			return (NULL);
		}

		for (j = 0; j < length; j++)
			words[index][j] = str[i + j];

		words[index][length] = '\0';
		index++;
		i += length;
	}

	words[index] = NULL;
	return (words);
}
