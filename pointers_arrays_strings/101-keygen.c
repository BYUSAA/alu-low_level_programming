#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * main - generates a random password
 *
 * Return: Always 0
 */
int main(void)
{
	int i;
	int length;
	char characters[] =
		"abcdefghijklmnopqrstuvwxyz"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"0123456789";
	int size;

	srand(time(NULL));

	length = 10;
	size = sizeof(characters) - 1;

	for (i = 0; i < length; i++)
	{
		putchar(characters[rand() % size]);
	}

	putchar('\n');

	return (0);
}