#include <stdio.h>

/**
 * main - prints the first 50 Fibonacci numbers
 *
 * Return: Always 0.
 */
int main(void)
{
	int count;
	unsigned long fib1;
	unsigned long fib2;
	unsigned long next;

	fib1 = 1;
	fib2 = 2;

	for (count = 1; count <= 50; count++)
	{
		if (count == 1)
			printf("%lu", fib1);
		else if (count == 2)
			printf(", %lu", fib2);
		else
		{
			next = fib1 + fib2;
			printf(", %lu", next);
			fib1 = fib2;
			fib2 = next;
		}
	}

	printf("\n");

	return (0);
}
