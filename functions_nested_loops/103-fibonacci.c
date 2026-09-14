#include <stdio.h>

/**
 * main - prints the sum of even Fibonacci numbers
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned long fib1;
	unsigned long fib2;
	unsigned long next;
	unsigned long sum;

	fib1 = 1;
	fib2 = 2;
	sum = 0;

	while (fib1 <= 4000000)
	{
		if (fib1 % 2 == 0)
			sum += fib1;

		next = fib1 + fib2;
		fib1 = fib2;
		fib2 = next;
	}

	printf("%lu\n", sum);

	return (0);
}