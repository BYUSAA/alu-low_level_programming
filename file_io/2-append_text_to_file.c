#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * string_length - returns the length of a string
 * @text: string to measure
 *
 * Return: number of characters in the string
 */
static size_t string_length(const char *text)
{
	size_t length;

	length = 0;
	while (text[length] != '\0')
		length++;
	return (length);
}

/**
 * write_all - writes every byte in a buffer to a file descriptor
 * @fd: file descriptor to write to
 * @text: bytes to write
 * @length: number of bytes to write
 *
 * Return: 1 on success, or 0 on failure
 */
static int write_all(int fd, const char *text, size_t length)
{
	size_t total;
	ssize_t written;

	total = 0;
	while (total < length)
	{
		written = write(fd, text + total, length - total);
		if (written <= 0)
			return (0);
		total += (size_t)written;
	}
	return (1);
}

/**
 * append_text_to_file - appends text to an existing file
 * @filename: name of the file to append to
 * @text_content: NULL-terminated text to append
 *
 * Return: 1 on success, or -1 on failure
 */
int append_text_to_file(const char *filename, char *text_content)
{
	int fd;
	size_t length;

	if (filename == NULL)
		return (-1);
	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (-1);
	length = 0;
	if (text_content != NULL)
		length = string_length(text_content);
	if (!write_all(fd, text_content, length))
	{
		close(fd);
		return (-1);
	}
	if (close(fd) == -1)
		return (-1);
	return (1);
}
