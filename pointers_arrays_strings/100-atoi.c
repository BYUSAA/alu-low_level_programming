#include "main.h"

/**
 * _atoi - converts a string to an integer
 * @s: string containing the number
 *
 * Return: converted integer
 */
int _atoi(char *s)
{
	int i;
	int sign;
	int result;
	int found_digit;

	i = 0;
	sign = 1;
	result = 0;
	found_digit = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '-')
		{
			sign = sign * -1;
		}
		else if (s[i] == '+')
		{
			sign = sign * 1;
		}
		else if (s[i] >= '0' && s[i] <= '9')
		{
			found_digit = 1;
			result = result * 10 + (s[i] - '0');
		}
		else if (found_digit)
		{
			break;
		}

		i++;
	}

	if (found_digit)
	{
		return (result * sign);
	}

	return (0);
}