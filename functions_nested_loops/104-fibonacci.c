#include <stdio.h>

/**
 * main - prints the first 98 Fibonacci numbers
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned long fib1_high;
	unsigned long fib1_low;
	unsigned long fib2_high;
	unsigned long fib2_low;
	unsigned long next_high;
	unsigned long next_low;
	unsigned long carry;
	int count;

	fib1_high = 0;
	fib1_low = 1;
	fib2_high = 0;
	fib2_low = 2;

	printf("%lu, %lu", fib1_low, fib2_low);

	for (count = 3; count <= 98; count++)
	{
		next_low = fib1_low + fib2_low;
		carry = 0;

		if (next_low < fib1_low)
			carry = 1;

		next_high = fib1_high + fib2_high + carry;

		printf(", ");

		if (next_high == 0)
			printf("%lu", next_low);
		else
			printf("%lu%016lu", next_high, next_low);

		fib1_high = fib2_high;
		fib1_low = fib2_low;
		fib2_high = next_high;
		fib2_low = next_low;
	}

	printf("\n");

	return (0);
}