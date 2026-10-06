#include <stdio.h>

/**
 * factorial - calculates the factorial of a number recursively
 * @n: number whose factorial is calculated
 *
 * Return: factorial of n
 */
unsigned long factorial(int n)
{
	if (n == 0 || n == 1)
		return (1);

	return (n * factorial(n - 1));
}

/**
 * main - entry point of the program
 *
 * Return: 0 on success
 */
int main(void)
{
	int number;
	unsigned long result;

	printf("===== RECURSIVE FACTORIAL CALCULATOR =====\n\n");

	printf("Enter a non-negative integer: ");

	if (scanf("%d", &number) != 1)
	{
		printf("Invalid input. Please enter an integer.\n");
		return (1);
	}

	if (number < 0)
	{
		printf("Invalid input. Factorial is not defined for negative numbers.\n");
		return (1);
	}

	result = factorial(number);

	printf("\n===== RESULT =====\n");
	printf("%d! = %lu\n", number, result);

	return (0);
}
