# C - Hello, World

## Description

This project is an introductionanswer this core to the C programming language. It covers the basic steps involved in creating, preprocessing, compiling, assembling, and linking C programs.

The project also introduces basic C functions such as `puts`, `printf`, and `write`, as well as the `sizeof` operator and assembly generation using Intel syntax.

## Learning Objectives

At the end of this project, I should be able to explain:

* Why C programming is useful.
* Who invented the C programming language.
* Who Dennis Ritchie, Brian Kernighan, and Linus Torvalds are.
* What happens when `gcc main.c` is executed.
* What an entry point is.
* What the `main` function is.
* How to print text using `printf`, `puts`, and `putchar`.
* How to use the `sizeof` operator.
* How to compile C programs using `gcc`.
* What the default executable name is when using `gcc`.
* How to follow the Betty coding style.
* How to find the correct header file for a standard library function.
* How the `main` function influences the return value of a program.
* The different stages involved in creating an executable from C source code.

## Requirements

### C

* Allowed editors: `vi`, `vim`, and `emacs`.
* Programs are compiled on Ubuntu using `gcc`.
* Compilation options:

```bash
-Wall -Werror -Wextra -pedantic -std=gnu89
```

* All C files must end with a new line.
* Code must follow the Betty coding style.
* Programs must compile without errors and warnings where required.
* The `system` function is not allowed.

### Shell Scripts

* Allowed editors: `vi`, `vim`, and `emacs`.
* Scripts are tested on Ubuntu.
* Every script must be exactly two lines long.
* The first line must be exactly:

```bash
#!/bin/bash
```

* All files must end with a new line.

## Tasks

### 0. Preprocessor

**File:** `0-preprocessor`

A shell script that runs a C file through the preprocessor.

The C filename is stored in the `$CFILE` environment variable, and the preprocessed output is saved in a file named `c`.

### 1. Compiler

**File:** `1-compiler`

A shell script that compiles a C source file without linking it.

The resulting object file has the same name as the source file, but with the `.o` extension.

For example:

```text
main.c → main.o
```

### 2. Assembler

**File:** `2-assembler`

A shell script that generates the assembly code of a C source file.

The output file has the same name as the C source file, but with the `.s` extension.

For example:

```text
main.c → main.s
```

### 3. Name

**File:** `3-name`

A shell script that compiles a C source file and creates an executable named:

```text
cisfun
```

### 4. Hello, puts

**File:** `4-puts.c`

A C program that prints:

```text
"Programming is like building a multilingual puzzle
```

using the `puts` function.

The program must not use `printf` and returns `0`.

### 5. Hello, printf

**File:** `5-printf.c`

A C program that prints:

```text
with proper grammar, but the outcome is a piece of art,
```

using the `printf` function.

The program must not use `puts` and returns `0`.

### 6. Size is not grandeur, and territory does not make a nation

**File:** `6-size.c`

A C program that prints the size, in bytes, of several C data types:

* `char`
* `int`
* `long int`
* `long long int`
* `float`

The program uses the `sizeof` operator.

The size of `long int` can be different on 32-bit and 64-bit systems.

### 7. Intel

**File:** `100-intel`

An advanced shell script that generates the assembly code of a C source file using **Intel syntax**.

The output uses the `.s` extension.

For example:

```text
main.c → main.s
```

The generated assembly contains:

```text
.intel_syntax noprefix
```

### 8. UNIX is basically a simple operating system, but you have to be a genius to understand the simplicity

**File:** `101-quote.c`

An advanced C program that prints:

```text
and that piece of art is useful" - Dora Korpar, 2015-10-19
```

to the standard error stream.

The program does not use `printf` or `puts`.

It uses the `write` function and returns:

```text
1
```

## Compilation Examples

Compile a standard C program with:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 file.c
```

Compile the quote program:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -o quote 101-quote.c
```

Generate assembly using Intel syntax:

```bash
gcc -S -masm=intel main.c -o main.s
```

## Compilation Process

A C program generally goes through four major stages:

```text
Preprocessing
      ↓
Compilation
      ↓
Assembly
      ↓
Linking
      ↓
Executable
```

### Preprocessing

The preprocessor handles directives such as:

```c
#include <stdio.h>
```

and produces preprocessed C code.

### Compilation

The compiler converts the preprocessed C code into assembly code.

### Assembly

The assembler converts assembly code into an object file containing machine code.

### Linking

The linker combines object files and required libraries to create the final executable.

## Betty Style

The project uses the Betty coding style.

Betty can be used to check C files:

```bash
betty filename.c
```

The project requires code to follow both Betty style and documentation rules.

## Repository

GitHub repository:

```text
alu-low_level_programming
```

Project directory:

```text
hello_world
```

## Files

```text
0-preprocessor
1-compiler
2-assembler
3-name
4-puts.c
5-printf.c
6-size.c
100-intel
101-quote.c
README.md
```

## Author

ALU Software Engineering Student




alu-low_level_programming
|   └── hello_world   
|      └── 0-preprocessor  lines it contains "#!/bin/bash
gcc -E $CFILE -o c
"
|      └── 1-compiler lines it contains "#!/bin/bash
gcc -c $CFILE
"
|      └── 2-assembler  lines it contains"#!/bin/bash
gcc -S $CFILE
"
|      └── 3-name  lines it contains"#!/bin/bash
gcc $CFILE -o cisfun
"
|      └── 4-puts.c  lines it contains"#include<stdio.h>

/**
 *  main - starting point for program execution
 * description - main will be used as function
 *  Return: 0 (success)
 */


int main(void)

{
	puts("\"Programming is like building a multilingual puzzle");

	return (0);
}"
|      └── 5-printf.c   lines it contains"#include<stdio.h>
/**
 *main - starting point for program execution
 *printf - send formatted output to the screen
 *Return: Always 0 (Success)
 */
int main(void)
{
	printf("with proper grammar, but the outcome is a piece of art,\n");
	return (0);
}"
|      └── 6-size.c  lines it contains"#include <stdio.h>
/**
 * main - Entry point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	printf("Size of a char: %d byte(s)\n", sizeof(char));
	printf("Size of an int: %d byte(s)\n", sizeof(int));
	printf("Size of a long int: %d byte(s)\n", sizeof(long int));
	printf("Size of a long long int: %d byte(s)\n", sizeof(long long int));
	printf("Size of a float: %d byte(s)\n", sizeof(float));
	return (0);
}"
|      └── 100-intel   lines it contains"#!/bin/bash
gcc -S -masm=intel "$CFILE" -o "${CFILE%.c}.s"
"
|      └── 101-quote.c   lines it contains"#include <unistd.h>

/**
 * main - Entry point
 *
 * Return: Always 1
 */
int main(void)
{
	char *str = "and that piece of art is useful\" - Dora Korpar, 2015-10-19\n";

	write(2, str, 59);
	return (1);
}"
|      └── README.md  
└── README.md  