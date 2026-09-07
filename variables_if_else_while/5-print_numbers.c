#include <stdio.h>

/**
 * main - prints single digit numbers
 *
 * Return: Always 0.
 */
int main(void)
{
	int n;

	for (n = 0; n <= 9; n++)
		printf("%d", n);

	printf("\n");

	return (0);
}