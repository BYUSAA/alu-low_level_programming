
#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints the opcodes of its own main function
 * @argc: number of arguments
 * @argv: argument values
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int bytes;
	int i;
	unsigned char *address;

	if (argc != 2)
	{
		printf("Error\n");
		exit(1);
	}

	bytes = atoi(argv[1]);
	if (bytes < 0)
	{
		printf("Error\n");
		exit(2);
	}

	address = (unsigned char *)main;

	for (i = 0; i < bytes; i++)
		printf("%02x%s", address[i], i == bytes - 1 ? "\n" : " ");

	if (bytes == 0)
		printf("\n");

	return (0);
}
