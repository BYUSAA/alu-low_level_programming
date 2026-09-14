#include "main.h"

/**
 * print_number - prints an integer
 * @n: number to print
 *
 * Return: Nothing.
 */
void print_number(int n)
{
	if (n >= 100)
		_putchar((n / 100) + '0');

	if (n >= 10)
		_putchar(((n / 10) % 10) + '0');

	_putchar((n % 10) + '0');
}

/**
 * print_times_table - prints the n times table
 * @n: size of the multiplication table
 *
 * Return: Nothing.
 */
void print_times_table(int n)
{
	int row;
	int column;
	int result;
	int spaces;

	if (n < 0 || n > 15)
		return;

	for (row = 0; row <= n; row++)
	{
		for (column = 0; column <= n; column++)
		{
			result = row * column;

			if (column == 0)
			{
				print_number(result);
			}
			else
			{
				_putchar(',');
				spaces = 3;

				if (result >= 10)
					spaces--;

				if (result >= 100)
					spaces--;

				while (spaces > 0)
				{
					_putchar(' ');
					spaces--;
				}

				print_number(result);
			}
		}

		_putchar('\n');
	}
}