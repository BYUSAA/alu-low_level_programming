
/**
 * fill_words - fills an array with words from a string
 * @words: array to fill
 * @str: string to split
 *
 * Return: 1 on success, 0 on allocation failure
 */
static int fill_words(char **words, char *str)
{
	int i;
	int length;
	int index;

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
		words[index] = copy_word(&str[i], length);
		if (words[index] == NULL)
		{
			free_words(words, index);
			return (0);
		}

		index++;
		i += length;
	}
	words[index] = NULL;
	return (1);
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

	if (fill_words(words, str) == 0)
		return (NULL);

	return (words);
}
