# 0x0E. C - Function Pointers

## Description

This project introduces function pointers in the C programming language. It explores how to declare, use, and pass functions as arguments to other functions.

## Learning Objectives

- Understand what function pointers are.
- Learn how to declare and use function pointers.
- Understand what a function pointer holds.
- Understand where function pointers point in virtual memory.
- Use function pointers to execute different operations dynamically.

## Requirements

- Ubuntu 20.04 LTS
- GCC
- Compiler flags: `-Wall -Werror -Wextra -pedantic -std=gnu89`
- Betty coding style
- No global variables
- Maximum five functions per file
- No more than the permitted C standard library functions for each task

## Files

| File | Description |
|---|---|
| `function_pointers.h` | Function prototypes for tasks 0–2 |
| `0-print_name.c` | Prints a name using a function pointer |
| `1-array_iterator.c` | Executes a function on every array element |
| `2-int_index.c` | Searches an array using a comparison function |
| `3-calc.h` | Calculator structures and prototypes |
| `3-op_functions.c` | Arithmetic operation functions |
| `3-get_op_func.c` | Selects an operation using a function pointer |
| `3-main.c` | Calculator program |
| `100-main_opcodes.c` | Prints the opcodes of its own main function |

## Compilation

Tasks 0–2 are compiled with their corresponding test files.

Calculator:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
3-main.c 3-op_functions.c 3-get_op_func.c -o calc
```

Advanced task:

```bash
gcc -std=gnu89 100-main_opcodes.c -o main
```

## Author

Byusa Martin
