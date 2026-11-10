# File I/O and File Descriptors

This project practices low-level file handling in C on Linux using POSIX file
descriptors and the open, read, write, and close system calls.

## Learning objectives

- Explain what a file descriptor is and how the kernel assigns one when a file
  is opened.
- Identify the standard descriptors and their POSIX names:

  | Descriptor | POSIX name | Purpose |
  | --- | --- | --- |
  | 0 | STDIN_FILENO | Standard input, usually the keyboard or an input pipe. |
  | 1 | STDOUT_FILENO | Standard output, usually the terminal or an output pipe. |
  | 2 | STDERR_FILENO | Standard error, used for diagnostics and error messages. |

- Open files with O_RDONLY, O_WRONLY, and O_RDWR, and combine flags such as
  O_CREAT, O_TRUNC, and O_APPEND.
- Set creation permissions with the mode argument to open and understand that
  the process umask can remove requested permission bits.
- Read and write bytes, handle partial writes, and close descriptors reliably.
- Distinguish a system call, which requests a kernel service, from an ordinary
  library function.

## File access flags and permissions

- O_RDONLY opens a file for reading.
- O_WRONLY opens a file for writing.
- O_RDWR opens a file for both reading and writing.
- O_CREAT creates the file when it does not exist.
- O_TRUNC reduces an existing regular file to zero length.
- O_APPEND positions each write at the end of the file.

When O_CREAT is used, the third argument to open specifies the requested
permissions. For example, 0600 requests read and write access for the owner
only, while 0664 requests read and write access for the owner and group and
read access for others. The process umask may remove permission bits.

## Project files

| File | Purpose |
| --- | --- |
| 0-read_textfile.c | Reads up to a requested number of bytes and writes them to standard output. |
| 1-create_file.c | Creates or truncates a file and writes its contents with requested mode 0600. |
| 2-append_text_to_file.c | Appends text to an existing writable file without creating it. |
| 3-cp.c | Copies a file in 1,024-byte blocks and reports the required error codes. |
| 100-elf_header.c | Displays selected fields from a 32-bit or 64-bit ELF header. |
| main.h | Shared public function prototypes and required type declarations. |

## Compilation

The mandatory tasks target Ubuntu 20.04 and GNU89:

    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 0-main.c 0-read_textfile.c -o read_textfile
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 1-main.c 1-create_file.c -o create_file
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 2-main.c 2-append_text_to_file.c -o append_text
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 3-cp.c -o cp
    gcc -Wall -Werror -Wextra -pedantic -std=gnu89 100-elf_header.c -o elf_header

The first three example main files are supplied by the tester or can be
created locally for testing; they are not part of the submitted project.
The cp and elf_header programs provide their own main functions.

## Usage

    ./read_textfile Requiescat
    ./create_file notes.txt "A short note"
    ./append_text notes.txt " appended text"
    ./cp source.txt destination.txt
    ./elf_header /bin/ls

## Implementation notes

- A successful read or write may process fewer bytes than requested. The
  implementation checks the result and completes partial writes.
- create_file requests rw------- (0600) for a newly created file. Opening an
  existing file with O_TRUNC does not change its existing permission bits.
- append_text_to_file opens with O_APPEND and does not use O_CREAT.
- cp requests rw-rw-r-- (0664) for a newly created destination. Existing
  destination permissions are preserved.
- The ELF reader reads the identification bytes first and the remainder of
  the class-specific header second. It decodes the type, version, and entry
  point according to the ELF file's byte order.

The mandatory source files follow Betty documentation and style conventions,
avoid global variables, and use no more than five functions per source file.
The advanced ELF task uses additional small helpers to keep parsing and display
logic separated.
