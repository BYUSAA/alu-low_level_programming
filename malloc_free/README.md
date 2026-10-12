
# 0x0A. malloc, free

This project introduces dynamic memory allocation in C using
malloc and free.

## Learning Objectives

- Understand automatic and dynamic memory allocation.
- Learn how to use malloc and free.
- Understand when and why dynamic memory allocation is needed.
- Learn how to handle allocation failures.
- Understand how to check for memory leaks using Valgrind.

## Requirements

- Compiled on Ubuntu 20.04 LTS using gcc.
- Compiler flags: -Wall -Werror -Wextra -pedantic -std=gnu89.
- Code follows the Betty coding style.
- No global variables.
- No more than five functions per file.
- Only malloc and free are allowed from the C standard library.
- All function prototypes are declared in main.h.

## Files

| File | Description |
|---|---|
| 0-create_array.c | Creates and initializes an array of characters. |
| 1-strdup.c | Duplicates a string using dynamic memory allocation. |
| 2-str_concat.c | Concatenates two strings. |
| 3-alloc_grid.c | Allocates and initializes a two-dimensional integer grid. |
| 4-free_grid.c | Frees a two-dimensional integer grid. |
| 100-argstostr.c | Concatenates command-line arguments. |
| 101-strtow.c | Splits a string into words. |
| main.h | Contains function prototypes. |

## Compilation

Example:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
0-main.c 0-create_array.c -o test

## Memory Management

Memory allocated with malloc should be released with free
when it is no longer needed.

Valgrind can help identify memory leaks and invalid memory access.
