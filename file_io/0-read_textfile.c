#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * write_all - writes every byte in a buffer to a file descriptor
 * @fd: file descriptor to write to
 * @buffer: bytes to write
 * @length: number of bytes to write
 *
 * Return: 1 on success, or 0 on failure
 */
static int write_all(int fd, const char *buffer, size_t length)
{
	size_t total;
	ssize_t written;

	total = 0;
	while (total < length)
	{
		written = write(fd, buffer + total, length - total);
		if (written <= 0)
			return (0);
		total += (size_t)written;
	}
	return (1);
}

/**
 * read_textfile - reads a text file and prints it to standard output
 * @filename: name of the file to read
 * @letters: maximum number of bytes to read and print
 *
 * Return: number of bytes printed, or 0 on failure
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd;
	char buffer[1024];
	ssize_t bytes_read;
	size_t total;
	size_t chunk;

	if (filename == NULL)
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	total = 0;
	while (total < letters)
	{
		chunk = letters - total;
		if (chunk > sizeof(buffer))
			chunk = sizeof(buffer);
		bytes_read = read(fd, buffer, chunk);
		if (bytes_read < 0)
		{
			close(fd);
			return (0);
		}
		if (bytes_read == 0)
			break;
		if (!write_all(STDOUT_FILENO, buffer, (size_t)bytes_read))
		{
			close(fd);
			return (0);
		}
		total += (size_t)bytes_read;
	}
	if (close(fd) == -1)
		return (0);
	return ((ssize_t)total);
}
