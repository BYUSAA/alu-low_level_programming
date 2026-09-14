# C - Functions, nested loops

This project is part of the **ALU Low-Level Programming** curriculum.

The project focuses on learning how to create and use **functions**, work with **nested loops**, understand **function prototypes**, understand **variable scope**, and use **header files** in C.

The programs in this project are written in C and compiled using GCC with strict compiler options and checked according to the **Betty coding style**.

---

## Table of Contents

1. [Project Description](#project-description)
2. [Learning Objectives](#learning-objectives)
3. [Requirements](#requirements)
4. [Compilation](#compilation)
5. [Functions](#functions)
6. [Nested Loops](#nested-loops)
7. [Function Declaration, Definition and Prototype](#function-declaration-definition-and-prototype)
8. [Variable Scope](#variable-scope)
9. [Header Files](#header-files)
10. [ASCII Characters](#ascii-characters)
11. [Modulo Operator](#modulo-operator)
12. [GCC Flags](#gcc-flags)
13. [Project Files](#project-files)
14. [Task Descriptions](#task-descriptions)
15. [Testing](#testing)
16. [Betty Style](#betty-style)
17. [Restrictions](#restrictions)
18. [Repository Structure](#repository-structure)
19. [Author](#author)

---

# Project Description

The **C - Functions, nested loops** project introduces important concepts used when writing programs in the C programming language.

A function is a reusable block of code that performs a particular task. Instead of writing the same code repeatedly, we can place the code inside a function and call that function whenever we need it.

A nested loop is a loop placed inside another loop. Nested loops are useful when a problem requires one repeated operation to happen inside another repeated operation.

For example, the following structure contains a nested loop:

```c
for (i = 0; i < 10; i++)
{
	for (j = 0; j < 10; j++)
	{
		/* code */
	}
}
```

The inner loop runs completely for every iteration of the outer loop.

This project combines functions, loops, conditions, arithmetic operations, characters, and header files to create several small C programs.

---

# Learning Objectives

At the end of this project, I should be able to explain the following concepts without using Google:

* What nested loops are
* How to use nested loops
* What a function is
* How to create and call a function
* The difference between a function declaration and a function definition
* What a function prototype is
* How function parameters work
* How a function returns a value
* The scope of variables
* The difference between local and global variables
* What the GCC flags `-Wall`, `-Werror`, `-Wextra`, `-pedantic`, and `-std=gnu89` do
* What header files are
* How to use `#include`
* How to use `_putchar`
* How ASCII character values can be used in C
* How the modulo operator `%` works
* How nested loops can solve repetitive problems

---

# Requirements

All files in this project must follow the requirements given by the assignment.

## Compiler

The programs are compiled on:

```text
Ubuntu 20.04 LTS
```

using:

```text
gcc
```

with the following compiler options:

```text
-Wall -Werror -Wextra -pedantic -std=gnu89
```

## Coding style

All C source files must follow the **Betty coding style**.

The code can be checked using:

```bash
betty-style.pl
```

and:

```bash
betty-doc.pl
```

## General requirements

* All files must end with a new line.
* A `README.md` file is mandatory.
* No global variables are allowed.
* No more than 5 functions are allowed in one file.
* The standard library is not allowed for most tasks.
* `_putchar` is allowed.
* `_putchar.c` does not have to be pushed to the repository.
* All function prototypes must be included in `main.h`.
* The prototype for `_putchar` must also be included in `main.h`.
* The `main.c` files provided in the assignment are examples for testing and do not need to be pushed.
* The repository's own test files may be different from the examples provided by the project.

---

# Compilation

The standard compilation format used throughout the project is:

```bash
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 source_file.c -o executable
```

When `_putchar.c` is needed, it can be included during compilation:

```bash
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 _putchar.c source_file.c -o executable
```

For example:

```bash
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 _putchar.c 1-main.c 1-alphabet.c -o 1-alphabet
```

The program can then be executed with:

```bash
./1-alphabet
```

---

# Functions

A function is a block of code designed to perform a specific task.

A simple function looks like:

```c
void print_message(void)
{
	_putchar('H');
}
```

The function can then be called from another function:

```c
print_message();
```

Functions help make programs:

* Easier to understand
* Easier to test
* Easier to maintain
* Easier to reuse
* Less repetitive

## Function parameters

A function can receive values called parameters.

Example:

```c
int add(int a, int b)
{
	return (a + b);
}
```

The function receives two integers and returns their sum.

It can be called using:

```c
result = add(10, 20);
```

The result is:

```text
30
```

---

# Nested Loops

A nested loop is a loop inside another loop.

Example:

```c
int i;
int j;

for (i = 0; i < 3; i++)
{
	for (j = 0; j < 3; j++)
	{
		_putchar('X');
	}
	_putchar('\n');
}
```

The outer loop controls the number of rows.

The inner loop controls how many times the operation happens inside each row.

The result is:

```text
XXX
XXX
XXX
```

Nested loops are particularly useful for:

* Tables
* Grids
* Repeated patterns
* Multiplication tables
* Time calculations
* Comparing combinations of values

This project uses nested loops in tasks such as printing the alphabet multiple times, printing every minute of the day, and generating multiplication tables.

---

# Function Declaration, Definition and Prototype

## Function declaration

A declaration tells the compiler that a function exists.

Example:

```c
int add(int, int);
```

It does not contain the function's implementation.

---

## Function definition

A definition contains the actual implementation of the function.

Example:

```c
int add(int a, int b)
{
	return (a + b);
}
```

The definition tells the compiler exactly what the function does.

---

## Function prototype

A function prototype tells the compiler:

* The function's name
* The return type
* The number of parameters
* The types of the parameters

Example:

```c
int add(int, int);
```

This means:

* Function name: `add`
* Return type: `int`
* Number of parameters: 2
* Parameter types: `int`, `int`

Function prototypes are placed in the project's header file:

```text
main.h
```

---

# Variable Scope

Variable scope determines where a variable can be accessed.

## Local variable

A variable declared inside a function is normally a local variable.

Example:

```c
void example(void)
{
	int number;

	number = 10;
}
```

The variable `number` can only be accessed within its scope.

## Global variable

A global variable is declared outside functions.

Example:

```c
int number;
```

Global variables are **not allowed in this project**.

Therefore, variables should be declared inside functions when needed.

---

# Header Files

A header file contains declarations and prototypes that can be shared between C source files.

This project uses:

```text
main.h
```

The header file contains the prototypes of the project functions.

Example:

```c
#ifndef MAIN_H
#define MAIN_H

int _putchar(char c);
void print_alphabet(void);
int _islower(int c);
int _isalpha(int c);
int print_sign(int n);
int _abs(int);
int print_last_digit(int);
void jack_bauer(void);
void times_table(void);
int add(int, int);
void print_to_98(int n);
void print_times_table(int n);

#endif
```

A source file can use these prototypes by including:

```c
#include "main.h"
```

The header guards:

```c
#ifndef MAIN_H
#define MAIN_H
```

and:

```c
#endif
```

help prevent the contents of the header from being included multiple times.

---

# ASCII Characters

C characters are represented internally using numeric values.

The project uses ASCII values when working with characters.

Some important ASCII values are:

| Character | ASCII |
| --------- | ----: |
| `A`       |    65 |
| `B`       |    66 |
| `Z`       |    90 |
| `a`       |    97 |
| `b`       |    98 |
| `z`       |   122 |
| `0`       |    48 |
| `1`       |    49 |
| `9`       |    57 |
| `-`       |    45 |

Because the lowercase alphabet is stored consecutively, we can use:

```c
if (c >= 'a' && c <= 'z')
```

to check whether a character is lowercase.

Similarly, we can check uppercase characters using:

```c
if (c >= 'A' && c <= 'Z')
```

---

# Modulo Operator

The modulo operator is:

```c
%
```

It returns the remainder after division.

For example:

```text
12 % 10 = 2
```

because:

```text
12 / 10 = 1 remainder 2
```

Another example:

```text
12 % 3 = 0
```

because 12 divides evenly by 3.

Modulo is useful for:

* Finding the last digit of a number
* Checking whether a number is even
* Checking whether a number is divisible by another number
* Separating digits
* Working with time

For example:

```c
last_digit = n % 10;
```

gets the last digit of a positive integer.

---

# GCC Flags

The project uses several GCC flags.

## `-Wall`

Enables many common compiler warnings.

```bash
-Wall
```

Warnings help identify possible problems in the program.

---

## `-Werror`

Treats warnings as errors.

```bash
-Werror
```

This means code that produces compiler warnings will not compile successfully.

---

## `-Wextra`

Enables additional warnings.

```bash
-Wextra
```

This helps catch more potential problems.

---

## `-pedantic`

Requests strict ISO C behavior and warns about non-standard language features.

```bash
-pedantic
```

---

## `-std=gnu89`

Specifies the GNU version of the C89 standard.

```bash
-std=gnu89
```

This is important because the project requires the code to be compatible with GNU89.

---

# Project Files

The project contains the following tasks:

| Task | File                     | Description                                  |
| ---: | ------------------------ | -------------------------------------------- |
|    0 | `0-putchar.c`            | Prints `_putchar`                            |
|    1 | `1-alphabet.c`           | Prints the lowercase alphabet                |
|    2 | `2-print_alphabet_x10.c` | Prints the alphabet 10 times                 |
|    3 | `3-islower.c`            | Checks for a lowercase character             |
|    4 | `4-isalpha.c`            | Checks for an alphabetic character           |
|    5 | `5-sign.c`               | Prints the sign of a number                  |
|    6 | `6-abs.c`                | Calculates the absolute value                |
|    7 | `7-print_last_digit.c`   | Prints the last digit                        |
|    8 | `8-24_hours.c`           | Prints every minute of a day                 |
|    9 | `9-times_table.c`        | Prints the 9 times table                     |
|   10 | `10-add.c`               | Adds two integers                            |
|   11 | `11-print_to_98.c`       | Prints numbers from n to 98                  |
|  100 | `100-times_table.c`      | Prints an n times table                      |
|  101 | `101-natural.c`          | Calculates multiples of 3 or 5               |
|  102 | `102-fibonacci.c`        | Prints the first 50 Fibonacci numbers        |
|  103 | `103-fibonacci.c`        | Calculates the sum of even Fibonacci numbers |
|  104 | `104-fibonacci.c`        | Prints the first 98 Fibonacci numbers        |

---

# Task Descriptions

## Task 0 - `_putchar`

File:

```text
0-putchar.c
```

The program prints:

```text
_putchar
```

followed by a new line.

The program returns `0`.

---

## Task 1 - Alphabet

File:

```text
1-alphabet.c
```

Function:

```c
void print_alphabet(void);
```

The function prints the lowercase alphabet:

```text
abcdefghijklmnopqrstuvwxyz
```

The function can only use `_putchar` twice.

---

## Task 2 - 10 x Alphabet

File:

```text
2-print_alphabet_x10.c
```

Function:

```c
void print_alphabet_x10(void);
```

The function prints the lowercase alphabet ten times.

This task introduces nested loops.

---

## Task 3 - islower

File:

```text
3-islower.c
```

Function:

```c
int _islower(int c);
```

The function checks whether a character is lowercase.

It returns:

```text
1
```

if the character is lowercase.

Otherwise it returns:

```text
0
```

---

## Task 4 - isalpha

File:

```text
4-isalpha.c
```

Function:

```c
int _isalpha(int c);
```

The function checks whether a character is alphabetic.

Both lowercase and uppercase letters are considered alphabetic.

It returns:

```text
1
```

for a letter and:

```text
0
```

for a non-letter.

---

## Task 5 - Sign

File:

```text
5-sign.c
```

Function:

```c
int print_sign(int n);
```

The function checks the sign of a number.

For a positive number:

```text
+
```

is printed and the function returns:

```text
1
```

For zero:

```text
0
```

is printed and the function returns:

```text
0
```

For a negative number:

```text
-
```

is printed and the function returns:

```text
-1
```

---

## Task 6 - Absolute Value

File:

```text
6-abs.c
```

Function:

```c
int _abs(int);
```

The function returns the absolute value of an integer.

Examples:

```text
_abs(-1)  -> 1
_abs(0)   -> 0
_abs(1)   -> 1
_abs(-98) -> 98
```

---

## Task 7 - Last Digit

File:

```text
7-print_last_digit.c
```

Function:

```c
int print_last_digit(int);
```

The function prints the last digit of an integer and returns the value of that digit.

The modulo operator is useful for this task.

---

## Task 8 - Jack Bauer

File:

```text
8-24_hours.c
```

Function:

```c
void jack_bauer(void);
```

The function prints every minute from:

```text
00:00
```

through:

```text
23:59
```

There are:

```text
24 × 60 = 1440
```

minutes in the output.

This task uses nested loops.

---

## Task 9 - Times Table

File:

```text
9-times_table.c
```

Function:

```c
void times_table(void);
```

The function prints the 9 times table starting from 0.

Example:

```text
0,  0,  0,  0,  0,  0,  0,  0,  0,  0
0,  1,  2,  3,  4,  5,  6,  7,  8,  9
0,  2,  4,  6,  8, 10, 12, 14, 16, 18
```

This task uses nested loops and multiplication.

---

## Task 10 - Add

File:

```text
10-add.c
```

Function:

```c
int add(int, int);
```

The function adds two integers and returns the result.

Example:

```text
add(89, 9)
```

returns:

```text
98
```

---

## Task 11 - Print to 98

File:

```text
11-print_to_98.c
```

Function:

```c
void print_to_98(int n);
```

The function prints all natural numbers from `n` to `98`.

If `n` is less than 98, numbers are printed in increasing order.

If `n` is greater than 98, numbers are printed in decreasing order.

Numbers are separated by:

```text
, 
```

---

# Advanced Tasks

## Task 12 - Times Table

File:

```text
100-times_table.c
```

Function:

```c
void print_times_table(int n);
```

The function prints the multiplication table for `n`.

Valid values are:

```text
0 to 15
```

If `n` is less than 0 or greater than 15, nothing should be printed.

This task requires careful formatting because numbers can contain one, two, or three digits.

---

## Task 13 - Natural Numbers

File:

```text
101-natural.c
```

The program calculates the sum of all natural numbers below `1024` that are multiples of either:

```text
3
```

or:

```text
5
```

The expected result is:

```text
233168
```

---

## Task 14 - Fibonacci

File:

```text
102-fibonacci.c
```

The program prints the first 50 Fibonacci numbers starting with:

```text
1, 2
```

Each new number is calculated by adding the previous two numbers.

The numbers are separated by:

```text
, 
```

---

## Task 15 - Even Fibonacci

File:

```text
103-fibonacci.c
```

The program considers Fibonacci numbers starting with:

```text
1, 2
```

and finds the sum of all even-valued Fibonacci numbers that do not exceed:

```text
4,000,000
```

The expected result is:

```text
4613732
```

---

## Task 16 - First 98 Fibonacci Numbers

File:

```text
104-fibonacci.c
```

The program prints the first 98 Fibonacci numbers starting with:

```text
1, 2
```

The numbers are separated by:

```text
, 
```

This task has additional restrictions.

The program must not use:

* `long long`
* `malloc`
* Pointers
* Arrays
* Tables
* Structures
* Other libraries
* Hard-coded Fibonacci numbers, except `1` and `2`

The solution therefore requires careful handling of large Fibonacci values using allowed integer types.

---

# Testing

The example `main.c` files provided by the project can be used to test individual functions.

For example, Task 10 can be tested with:

```c
#include "main.h"
#include <stdio.h>

/**
 * main - check the code
 *
 * Return: Always 0.
 */
int main(void)
{
	int n;

	n = add(89, 9);
	printf("%d\n", n);

	return (0);
}
```

Compile it with:

```bash
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 _putchar.c 10-main.c 10-add.c -o 10-add
```

Then run:

```bash
./10-add
```

Expected output:

```text
98
```

The test `main.c` files are only for local testing and are not required as project submissions.

---

# Betty Style

The project requires all code to follow Betty style.

Two important checks are:

```bash
betty-style.pl filename.c
```

and:

```bash
betty-doc.pl filename.c
```

For example:

```bash
betty-style.pl 1-alphabet.c
betty-doc.pl 1-alphabet.c
```

Betty helps check things such as:

* Indentation
* Function documentation
* Variable declarations
* Spacing
* Braces
* Naming
* Code formatting
* Documentation requirements

The goal is to make the code consistent and readable.

---

# Restrictions

The project has several restrictions.

## No global variables

Global variables are not allowed.

Avoid:

```c
int number;
```

outside a function.

Instead use local variables:

```c
void example(void)
{
	int number;

	number = 10;
}
```

---

## Maximum of five functions per file

A source file cannot contain more than five functions.

For example:

```text
function 1
function 2
function 3
function 4
function 5
```

is allowed.

Adding a sixth function to the same file is not allowed.

---

## Standard library

For most of the mandatory tasks, standard-library functions such as:

```c
printf()
puts()
scanf()
```

are not allowed.

The allowed output function is:

```c
_putchar()
```

Some advanced tasks explicitly allow the standard library.

---

# `_putchar`

`_putchar` is used to print one character at a time.

Its prototype is:

```c
int _putchar(char c);
```

For example:

```c
_putchar('A');
```

prints:

```text
A
```

A newline can be printed using:

```c
_putchar('\n');
```

The project provides `_putchar.c` for compilation, so it does not need to be submitted unless required by the repository setup.

---

# Repository Structure

The expected project directory is:

```text
alu-low_level_programming/
└── functions_nested_loops/
    ├── README.md
    ├── main.h
    ├── 0-putchar.c
    ├── 1-alphabet.c
    ├── 2-print_alphabet_x10.c
    ├── 3-islower.c
    ├── 4-isalpha.c
    ├── 5-sign.c
    ├── 6-abs.c
    ├── 7-print_last_digit.c
    ├── 8-24_hours.c
    ├── 9-times_table.c
    ├── 10-add.c
    ├── 11-print_to_98.c
    ├── 100-times_table.c
    ├── 101-natural.c
    ├── 102-fibonacci.c
    ├── 103-fibonacci.c
    └── 104-fibonacci.c
```

The test files such as:

```text
1-main.c
2-main.c
3-main.c
...
```

are used for local testing and do not need to be pushed unless specifically required.

---

# Useful Commands

Navigate to the project:

```bash
cd ~/alu-low_level_programming/functions_nested_loops
```

List project files:

```bash
ls
```

Show a file:

```bash
cat filename.c
```

Compile a program:

```bash
gcc -Wall -pedantic -Werror -Wextra -std=gnu89 ...
```

Run a program:

```bash
./program_name
```

Check Betty style:

```bash
betty-style.pl filename.c
```

Check Betty documentation:

```bash
betty-doc.pl filename.c
```

Check Git status:

```bash
git status
```

Add project files:

```bash
git add .
```

Commit changes:

```bash
git commit -m "Complete functions and nested loops tasks"
```

Push changes:

```bash
git push
```

---

# Key Concepts Learned

The main concepts covered in this project are:

```text
Functions
    |
    +-- Function declaration
    +-- Function definition
    +-- Function prototype
    +-- Parameters
    +-- Return values
    |
Nested loops
    |
    +-- Outer loop
    +-- Inner loop
    |
Characters
    |
    +-- ASCII
    +-- Character comparisons
    |
Operators
    |
    +-- Arithmetic
    +-- Modulo
    +-- Comparison
    +-- Logical operators
    |
Header files
    |
    +-- main.h
    +-- #include
    +-- Function prototypes
```

These concepts form an important foundation for writing larger C programs.

---

# Author

**Byusa M Martin De Poles**

ALU Software Engineering student

Project:

```text
C - Functions, nested loops
```

Repository:

```text
alu-low_level_programming
```

Directory:

```text
functions_nested_loops
```
