#include "main.h"

/**
 * find_sqrt - finds the natural square root recursively
 * @n: number to find the square root of
 * @guess: current possible square root
 *
 * Return: natural square root, or -1 if none exists
 */
int find_sqrt(int n, int guess)
{
	if (guess > n / guess)
	{
		return (-1);
	}

	if (guess * guess == n)
	{
		return (guess);
	}

	return (find_sqrt(n, guess + 1));
}

/**
 * _sqrt_recursion - returns the natural square root of a number
 * @n: number to find the square root of
 *
 * Return: natural square root, or -1 if none exists
 */
int _sqrt_recursion(int n)
{
	if (n < 0)
	{
		return (-1);
	}

	if (n == 0)
	{
		return (0);
	}

	return (find_sqrt(n, 1));
}
