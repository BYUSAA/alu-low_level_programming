#include <stdio.h>

/**
 * print_fib - prints a Fibonacci number from three chunks
 * @a: high chunk
 * @b: middle chunk
 * @c: low chunk
 *
 * Return: Nothing.
 */
void print_fib(unsigned long a, unsigned long b, unsigned long c)
{
	if (a != 0)
		printf("%lu%09lu%09lu", a, b, c);
	else if (b != 0)
		printf("%lu%09lu", b, c);
	else
		printf("%lu", c);
}

/**
 * main - prints the first 98 Fibonacci numbers
 *
 * Return: Always 0.
 */
int main(void)
{
	unsigned long a, b, c;
	unsigned long d, e, f;
	unsigned long x, y, z, carry;
	int i;

	a = 0;
	b = 0;
	c = 1;
	d = 0;
	e = 0;
	f = 2;

	printf("1, 2");

	for (i = 3; i <= 98; i++)
	{
		x = c + f;
		carry = x / 1000000000;
		x %= 1000000000;

		y = b + e + carry;
		carry = y / 1000000000;
		y %= 1000000000;

		z = a + d + carry;

		printf(", ");
		print_fib(z, y, x);

		a = d;
		b = e;
		c = f;
		d = z;
		e = y;
		f = x;
	}

	printf("\n");

	return (0);
}
