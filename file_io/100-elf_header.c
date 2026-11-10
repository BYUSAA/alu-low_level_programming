#include <elf.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * write_error_text - writes an error message to standard error
 * @text: text to write
 *
 * Return: void
 */
static void write_error_text(const char *text)
{
	size_t length;
	ssize_t written;

	length = 0;
	while (text[length] != '\0')
		length++;
	while (length > 0)
	{
		written = write(STDERR_FILENO, text, length);
		if (written <= 0)
			return;
		text += written;
		length -= (size_t)written;
	}
}

/**
 * fail - displays an ELF processing error and exits
 * @filename: file that caused the error
 * @reason: explanation of the error
 *
 * Return: this function does not return
 */
static void fail(const char *filename, const char *reason)
{
	write_error_text("Error: ");
	write_error_text(filename);
	write_error_text(": ");
	write_error_text(reason);
	write_error_text("\n");
	exit(98);
}

/**
 * decode_value - decodes an integer using the file's byte order
 * @data: bytes containing the integer
 * @length: number of bytes to decode
 * @little_endian: 1 for little endian, 0 for big endian
 *
 * Return: decoded unsigned integer
 */
static uint64_t decode_value(const unsigned char *data,
			     unsigned int length, int little_endian)
{
	uint64_t value;
	unsigned int index;
	unsigned int shift;

	value = 0;
	for (index = 0; index < length; index++)
	{
		shift = little_endian ? index * 8 : (length - index - 1) * 8;
		value |= ((uint64_t)data[index]) << shift;
	}
	return (value);
}

/**
 * elf_type - returns the display name for an ELF object type
 * @type: ELF object type value
 *
 * Return: descriptive type name
 */
static const char *elf_type(unsigned int type)
{
	switch (type)
	{
	case ET_NONE:
		return ("NONE (No file type)");
	case ET_REL:
		return ("REL (Relocatable file)");
	case ET_EXEC:
		return ("EXEC (Executable file)");
	case ET_DYN:
		return ("DYN (Shared object file)");
	case ET_CORE:
		return ("CORE (Core file)");
	default:
		return ("UNKNOWN");
	}
}

/**
 * elf_abi - returns the display name for an ELF operating-system ABI
 * @abi: ELF OS/ABI value
 *
 * Return: descriptive ABI name, or NULL when it is unknown
 */
static const char *elf_abi(unsigned int abi)
{
	if (abi == 53)
		return ("UNIX - Sortix");
	switch (abi)
	{
	case ELFOSABI_NONE:
		return ("UNIX - System V");
	case ELFOSABI_HPUX:
		return ("UNIX - HP-UX");
	case ELFOSABI_NETBSD:
		return ("UNIX - NetBSD");
	case ELFOSABI_GNU:
		return ("UNIX - GNU");
	case 4:
		return ("GNU/Hurd");
	case ELFOSABI_SOLARIS:
		return ("UNIX - Solaris");
	case ELFOSABI_AIX:
		return ("UNIX - AIX");
	case ELFOSABI_IRIX:
		return ("UNIX - IRIX");
	case ELFOSABI_FREEBSD:
		return ("UNIX - FreeBSD");
	case ELFOSABI_TRU64:
		return ("UNIX - TRU64");
	case ELFOSABI_MODESTO:
		return ("Novell - Modesto");
	case ELFOSABI_OPENBSD:
		return ("UNIX - OpenBSD");
	case 13:
		return ("VMS - OpenVMS");
	case 14:
		return ("HP - Non-Stop Kernel");
	case 15:
		return ("AROS");
	case 16:
		return ("FenixOS");
	case ELFOSABI_ARM_AEABI:
		return ("ARM");
	case ELFOSABI_ARM:
		return ("ARM");
	case ELFOSABI_STANDALONE:
		return ("Standalone App");
	default:
		return (NULL);
	}
}

/**
 * print_magic - prints the sixteen ELF identification bytes
 * @header: ELF header bytes
 *
 * Return: void
 */
static void print_magic(const unsigned char *header)
{
	unsigned int index;

	printf("  Magic:   ");
	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02x", header[index]);
		if (index + 1 < EI_NIDENT)
			printf(" ");
	}
	printf("\n");
}

/**
 * load_header - reads and validates the identification and complete ELF header
 * @fd: open file descriptor
 * @filename: file name used in error messages
 * @header: buffer that receives the complete header
 * @header_size: receives the class-specific header size
 *
 * Return: 0 on success; exits with status 98 on failure
 */
static int load_header(int fd, const char *filename,
		       unsigned char *header, int *header_size)
{
	ssize_t amount;

	amount = read(fd, header, EI_NIDENT);
	if (amount != EI_NIDENT)
		fail(filename, "cannot read a complete ELF identification header");
	if (header[EI_MAG0] != ELFMAG0 || header[EI_MAG1] != ELFMAG1 ||
	    header[EI_MAG2] != ELFMAG2 || header[EI_MAG3] != ELFMAG3)
		fail(filename, "not an ELF file: invalid magic bytes");
	if (header[EI_CLASS] != ELFCLASS32 && header[EI_CLASS] != ELFCLASS64)
		fail(filename, "unsupported or invalid ELF class");
	if (header[EI_DATA] != ELFDATA2LSB && header[EI_DATA] != ELFDATA2MSB)
		fail(filename, "unsupported or invalid ELF byte order");
	*header_size = header[EI_CLASS] == ELFCLASS32 ?
		sizeof(Elf32_Ehdr) : sizeof(Elf64_Ehdr);
	amount = read(fd, header + EI_NIDENT, *header_size - EI_NIDENT);
	if (amount != *header_size - EI_NIDENT)
		fail(filename, "file contains an incomplete ELF header");
	return (0);
}

/**
 * display_header - prints the requested fields from a validated ELF header
 * @header: complete ELF header bytes
 *
 * Return: void
 */
static void display_header(const unsigned char *header)
{
	int little_endian;
	unsigned int entry_size;
	unsigned int type;
	unsigned int version;
	uint64_t entry;
	const char *abi_name;

	little_endian = header[EI_DATA] == ELFDATA2LSB;
	entry_size = header[EI_CLASS] == ELFCLASS32 ? 4 : 8;
	type = (unsigned int)decode_value(header +
		offsetof(Elf32_Ehdr, e_type), 2, little_endian);
	version = (unsigned int)decode_value(header +
		offsetof(Elf32_Ehdr, e_version), 4, little_endian);
	entry = decode_value(header + offsetof(Elf32_Ehdr, e_entry),
		entry_size, little_endian);
	printf("ELF Header:\n");
	print_magic(header);
	if (header[EI_CLASS] == ELFCLASS32)
		printf("  Class:                             ELF32\n");
	else
		printf("  Class:                             ELF64\n");
	printf("  Data:                              2's complement, ");
	if (little_endian)
		printf("little endian\n");
	else
		printf("big endian\n");
	if (version == EV_CURRENT)
		printf("  Version:                           %u (current)\n", version);
	else
		printf("  Version:                           %u\n", version);
	abi_name = elf_abi(header[EI_OSABI]);
	if (abi_name == NULL)
		printf("  OS/ABI:                            <unknown: %02x>\n",
		       header[EI_OSABI]);
	else
		printf("  OS/ABI:                            %s\n", abi_name);
	printf("  ABI Version:                       %u\n", header[EI_ABIVERSION]);
	printf("  Type:                              %s\n", elf_type(type));
	printf("  Entry point address:               0x%" PRIx64 "\n", entry);
}

/**
 * main - displays selected fields from an ELF file header
 * @argc: number of command-line arguments
 * @argv: command-line arguments
 *
 * Return: 0 on success, 98 on failure
 */
int main(int argc, char **argv)
{
	unsigned char header[sizeof(Elf64_Ehdr)];
	int fd;
	int header_size;

	if (argc != 2)
	{
		write_error_text("Usage: elf_header elf_filename\n");
		return (98);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fail(argv[1], "cannot open file");
	load_header(fd, argv[1], header, &header_size);
	if (close(fd) == -1)
		fail(argv[1], "cannot close file descriptor");
	display_header(header);
	return (0);
}
