#include <stdio.h>

/**
 * main - prints hexadecimal digits
 *
 * Return: Always 0.
 */
int main(void)
{
	int n;

	for (n = 0; n < 10; n++)
		putchar(n + '0');

	for (n = 0; n < 6; n++)
		putchar(n + 'a');

	putchar('\n');

	return (0);
}