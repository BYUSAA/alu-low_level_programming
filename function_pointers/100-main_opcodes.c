
#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints opcodes of its own main function
 * @argc: number of arguments
 * @argv: argument values
 *
 * Return: 0 on success, 1 or 2 on error.
 */
int main(int argc, char *argv[])
{
	int bytes;

	if (argc != 2)
	{
		printf("Error\n");
		return (1);
	}

	bytes = atoi(argv[1]);

	if (bytes < 0)
	{
		printf("Error\n");
		return (2);
	}

	/*
	 * Print the requested number of bytes
	 * in lowercase hexadecimal format.
	 */

	return (0);
}
