#include "main.h"

/**
 * palindrome_check - checks if characters match from both ends
 * @s: string to check
 * @left: left position
 * @right: right position
 *
 * Return: 1 if palindrome, otherwise 0
 */
int palindrome_check(char *s, int left, int right)
{
	if (left >= right)
	{
		return (1);
	}

	if (s[left] != s[right])
	{
		return (0);
	}

	return (palindrome_check(s, left + 1, right - 1));
}

/**
 * get_length - returns the length of a string recursively
 * @s: string to measure
 *
 * Return: length of the string
 */
int get_length(char *s)
{
	if (*s == '\0')
	{
		return (0);
	}

	return (1 + get_length(s + 1));
}

/**
 * is_palindrome - checks if a string is a palindrome
 * @s: string to check
 *
 * Return: 1 if palindrome, otherwise 0
 */
int is_palindrome(char *s)
{
	int length;

	length = get_length(s);

	return (palindrome_check(s, 0, length - 1));
}