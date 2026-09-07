# C - Variables, if, else, while

This project contains C programs that demonstrate the use of variables, conditional statements, loops, arithmetic operators, relational operators, logical operators, and the ASCII character set.

## Requirements

* Ubuntu 20.04
* GCC
* C programming language
* Betty coding style
* Compilation flags:

  * `-Wall`
  * `-Werror`
  * `-Wextra`
  * `-pedantic`
  * `-std=gnu89`

## Files

| File                       | Description                                                            |
| -------------------------- | ---------------------------------------------------------------------- |
| `0-positive_or_negative.c` | Prints whether a random number is positive, zero, or negative          |
| `1-last_digit.c`           | Prints the last digit of a random number                               |
| `2-print_alphabet.c`       | Prints the lowercase alphabet                                          |
| `3-print_alphabets.c`      | Prints the lowercase and uppercase alphabet                            |
| `4-print_alphabt.c`        | Prints the lowercase alphabet except `q` and `e`                       |
| `5-print_numbers.c`        | Prints single-digit numbers from `0` to `9`                            |
| `6-print_numberz.c`        | Prints single-digit numbers using `putchar`                            |
| `7-print_tebahpla.c`       | Prints the lowercase alphabet in reverse                               |
| `8-print_base16.c`         | Prints hexadecimal digits from `0` to `f`                              |
| `9-print_comb.c`           | Prints all possible combinations of two different single-digit numbers |

## Compilation

Programs are compiled using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 filename.c -o filename
```

Example:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 7-print_tebahpla.c -o 7-print_tebahpla
```

## Testing

Run a compiled program using:

```bash
./filename
```

Example:

```bash
./7-print_tebahpla
```

Betty style can be checked with:

```bash
betty filename.c
```

## Learning Objectives

This project practices:

* Declaring and assigning variables
* Using `int`, `char`, and `unsigned int`
* Arithmetic operators
* Relational operators
* Logical operators
* `if` and `if...else` statements
* `while` and `for` loops
* Printing characters and numbers
* ASCII values
* Random number generation
* Using `putchar`
* Understanding hexadecimal numbers
* Writing code that follows Betty style

## Author

Byusa M Martin De Poles
