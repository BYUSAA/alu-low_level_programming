#include "main.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * copy_data - copies bytes from one descriptor to another
 * @source: descriptor to read from
 * @destination: descriptor to write to
 *
 * Return: 0 on success, -1 on read failure, or -2 on write failure
 */
static int copy_data(int source, int destination)
{
	char buffer[1024];
	ssize_t bytes_read;
	ssize_t bytes_written;
	size_t offset;

	while (1)
	{
		bytes_read = read(source, buffer, sizeof(buffer));
		if (bytes_read == -1)
			return (-1);
		if (bytes_read == 0)
			return (0);
		offset = 0;
		while (offset < (size_t)bytes_read)
		{
			bytes_written = write(destination, buffer + offset,
				(size_t)bytes_read - offset);
			if (bytes_written <= 0)
				return (-2);
			offset += (size_t)bytes_written;
		}
	}
}

/**
 * close_checked - closes a descriptor or exits with the required error
 * @fd: descriptor to close
 *
 * Return: void
 */
static void close_checked(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * main - copies the contents of one file to another
 * @argc: number of command-line arguments
 * @argv: command-line arguments
 *
 * Return: 0 on success; exits with the required error code on failure
 */
int main(int argc, char **argv)
{
	int source;
	int destination;
	int status;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
	source = open(argv[1], O_RDONLY);
	if (source == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
	destination = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (destination == -1)
	{
		close_checked(source);
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit(99);
	}
	status = copy_data(source, destination);
	close_checked(destination);
	close_checked(source);
	if (status == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
	if (status == -2)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		exit(99);
	}
	return (0);
}
