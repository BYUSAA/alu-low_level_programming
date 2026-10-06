# C Programming and Arduino Smart Parking System

## Project Overview

This project is a formative assessment to demonstrate an understanding of the basics of C programming and embedded systems. It provides 4 tasks which illustrate the concepts of C programming.

### Tasks

1. **Water Quality Monitoring System**
Mobile Money Transaction Processing System refers to the system that processes the transaction for mobile money.
3. **Recursive Factorial Calculator**
4. **Smart Parking System**

The core principles of programming (variables, data types, input and output handling, conditional statements, loops, functions, recursion, arrays, and input validation) and basic concepts of embedded systems are used in each task.


## Compilation Standard

GCC (GNU Compiler Collection) is the compiler used for all the C programs in this project with strict flags to achieve high quality and error detection of the code:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89
```

These flags can be used to detect errors, warnings and code quality issues in the compilation process, thereby minimizing runtime issues.

To connect the math library for the calculations to `fabs()` for the Water Quality Monitoring System:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 question1_water_quality.c -o question1_water_quality -lm
```


What is the definition of a water quality monitoring system?Question: What is the definition of water quality monitoring system?

## Objective

This program determines a water quality index, based on turbidity and temperature. It determines the water quality as one of three types:

* **Good**
* **Warning**
* **Critical**

These classifications are significant to track water safety.

## Calculation

The following formulas are used for the calculation:

```text
Temperature deviation = |temperature - 25|
Turbidity penalty = turbidity / 2
Water Quality Index = 100 - (temperature deviation + turbidity penalty)
```

The classification is done based on Water Quality Index:

| Index          | Status   |
| -------------- | -------- |
| 80 or above    | Good     |
| 60 to below 80 | Warning  |
| Below 60       | Critical |

## Concepts Used

The program includes the following concepts of C programming:

- Data types and variable declaration, especially `double`
The syntax and how to use functions.How to define and use functions.
Conditional logic using if, else if and else.
Using `scanf` functions to input from the user
- Basic math operations
Using `printf` for output - 1

## File Name

The program is stored in:

```text
question1_water_quality.c
```

## Compilation Command

To create the Water Quality Monitoring System, click on:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 question1_water_quality.c -o question1_water_quality -lm
```

## Testing Results

The program was tested with different temperature and turbidity values to check its accuracy:

| Temperature | Turbidity | Index | Status   |
| ----------: | --------: | ----: | -------- |
|          28 |        10 |    92 | Good     |
|          25 |        50 |    75 | Warning  |
|          25 |       100 |    50 | Critical |
|          25 |        40 |    80 | Good     |
|          25 |        80 |    60 | Warning  |

The program was found to be correct for given inputs in these tests.

## Use of C in Real Life

The reason for the widespread use of C in embedded systems is that it is efficient and can directly control the hardware. Real-life applications include:

- Microcontrollers
- Sensor data processing
- Automotive systems
- Industrial monitoring systems
- Internet of Things (IoT) devices

### Error Examples

#### Syntax Error Example

The most often problem that occurs is the omission of a semicolon, this results in a syntax error:

```c
printf("Hello")
```

The above should be corrected to read:

```c
printf("Hello");
```

#### Logical Error Example

Logical errors can cause a program to compile, but give a wrong answer. For example, the turbidity calculation could be wrong:

```c
turbidity_penalty = turbidity * 2.0;
```

The correct calculation should be:

```c
turbidity_penalty = turbidity / 2.0;
```

The first line is syntactically correct, but not logically.

### Compilation Process Overview

In a typical C program, the process of making it executable goes through a number of steps:

```text
C Source Code
     |
     v
Preprocessing
     |
     v
Compilation
     |
     v
Assembly
     |
     v
Object Code
     |
     v
Linking
     |
     v
Executable Program
```

This process converts the source code into a code that can be understood and executed by the computer.


What is the name of the Mobile money transaction processing system?

## Objective

This programme mimics a simple mobile money system, through which users can:

1. Deposit money
2. Withdraw money
3. Check their balance
4. View transaction summaries
5. Exit the program

## Key Features

The program incorporates a number of concepts in programming, including:

Writing loops with the while statement.Using the while statement to write loops.
Use `switch` statements to handle user options.
- Ensure that withdrawals cannot go over the available balance
- Arithmetic to deal with balances and transactions.

It does not let users withdraw more money than available and it will not permit any negative or zero amount of transactions.

## File Name

The program code is in:

```text
question2_mobile_money.c
```

## Compilation Command

To run this program, compile using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 question2_mobile_money.c -o question2_mobile_money
```

## Testing Results

The Mobile Money Transaction Processing System was found to be working as expected with real life scenarios of successful transactions:

- **Deposit**: 50,000 RWF
- **Withdrawal**: 20,000 RWF
- **Remaining balance**: 30,000 RWF

The summary properly recorded transactions:

```text
Successful deposits: 1
Successful withdrawals: 1
Current balance: 30000 RWF
```

---

# Question 3: Recursive Factorial Calculator

## Objective

Recursive program to compute factorial for non-negative integer. Factorials have applications in math, particularly in permutations and combinations.

For example:

```text
5! = 5 × 4 × 3 × 2 × 1
5! = 120
```

## Recursive Logic

The program specifies the following simple recursive function:

```c
unsigned long factorial(int n)
```

The base case is:

```c
if (n == 0 || n == 1)
    return (1);
```

If this value is not equal to 1, then call itself again:

```c
return (n * factorial(n - 1));
```

This recursive method is decomposing the problem.

## Core Concepts Used

The Recursive Factorial Calculator illustrates some of the concepts of C programing:

Use of functions and recursion.Recursion and function definitions.
- Control structures

The program demonstrates breaking a problem into smaller tasks to solve a complex problem.



To sum up, these projects will strengthen the C programming skills and embedded systems, providing a solid foundation for the more complex ideas and applications in programming. This learning will give you practical experience with key programming concepts and how they're applied in the world.
