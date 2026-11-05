# Project 1 — Dynamic Academic Performance and Risk Analysis Engine

## Description
A menu-driven C program that manages student records, sorts and searches them, calculates grade statistics, and identifies grade-based academic risk.

## Compile and run (Ubuntu / WSL)
```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o academic_analysis
./academic_analysis
```

## Before running
Replace `REPLACE_WITH_YOUR_STUDENT_ID` in `main.c` with your actual student ID.

## Features
- Starts with 10 fictional student records.
- Adds and removes records using dynamic allocation.
- Rejects duplicate IDs and grades outside 0–100.
- Displays records in a table.
- Sorts by grade descending, name ascending, or ID ascending.
- Calculates average and top-performing student.
- Searches by ID or exact name (`strcmp`).
- Uses pointer traversal.
- Uses an array of function pointers for menu dispatch.
- Generates a summary and custom Academic Risk Index.

## Dataset and assumptions
The initial dataset is fictional. The project uses 50 as its pass threshold. Grade below 50 is classified high risk, 50 to below 70 moderate risk, and 70–100 good standing. These are project assumptions, not official university rules.

## Memory
`malloc` allocates the initial array, `realloc` grows it when needed and attempts to shrink it after removal, and `free` releases it at exit. Allocation failures are checked.