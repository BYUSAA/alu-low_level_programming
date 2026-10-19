
# C - Structures, typedef

This project introduces structures and typedef in the C programming language.

## Learning Objectives

- Understand what structures are and how to use them.
- Understand how to access structure members.
- Learn how to initialize and print a structure.
- Understand how typedef creates an alias for a data type.
- Learn dynamic memory allocation using malloc.
- Learn how to free dynamically allocated memory.

## Requirements

- Ubuntu 20.04 LTS
- GCC compiler
- Compilation flags: -Wall -Werror -Wextra -pedantic -std=gnu89
- Betty coding style
- No global variables
- All header files must have include guards.

## Files

| File | Description |
|---|---|
| dog.h | Defines struct dog, dog_t, and function prototypes |
| 1-init_dog.c | Initializes a dog structure |
| 2-print_dog.c | Prints information about a dog |
| 4-new_dog.c | Creates a dog and copies its strings |
| 5-free_dog.c | Frees the allocated memory for a dog |

## Tasks

### Task 0: Poppy
Defines a structure with the dog's name, age, and owner.

### Task 1: Initialize a dog
Assigns values to the members of a dog structure.

### Task 2: Print a dog
Prints the dog's name, age, and owner, handling NULL pointers.

### Task 3: dog_t
Creates dog_t as an alias for struct dog.

### Task 4: Create a new dog
Allocates memory for a dog and stores copies of its name and owner.

### Task 5: Free a dog
Releases the memory allocated for the dog and its strings.

## Compilation

Compile the source files with the required compiler flags and the appropriate test main file.

Example:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
main.c 1-init_dog.c -o test

## Author

Byusa Martin
