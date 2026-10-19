
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
 * copy_word - copies a word into allocated memory
 * @str: pointer to the start of the word
 *
 * Return: pointer to the copied word, or NULL on failure
 */
static char *copy_word(char **str)
{
	char *word;
	int length;
	int i;

	length = 0;
	while ((*str)[length] != '\0' && (*str)[length] != ' ')
		length++;

	word = malloc(sizeof(char) * (length + 1));
	if (word == NULL)
		return (NULL);

	for (i = 0; i < length; i++)
		word[i] = (*str)[i];

	word[length] = '\0';
	*str += length;

	return (word);
}

/**
 * fill_words - fills an array with copied words
 * @words: array to fill
 * @str: string to split
 *
 * Return: array of words, or NULL on failure
 */
static char **fill_words(char **words, char *str)
{
	int index;

	index = 0;
	while (*str != '\0')
	{
		if (*str == ' ')
		{
			str++;
			continue;
		}

		words[index] = copy_word(&str);
		if (words[index] == NULL)
		{
			free_words(words, index);
			return (NULL);
		}

		index++;
	}

	words[index] = NULL;
	return (words);
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

	if (str == NULL || str[0] == '\0')
		return (NULL);

	count = count_words(str);
	if (count == 0)
		return (NULL);

	words = malloc(sizeof(char *) * (count + 1));
	if (words == NULL)
		return (NULL);

	return (fill_words(words, str));
}
