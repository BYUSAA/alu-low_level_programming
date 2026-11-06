# Project 1 — Dynamic Academic Performance and Risk Analysis Engine

**Student:** Byusa Mukarage Martin De Poles  
**Student ID:** 811201785

## Purpose

This menu-driven C program manages a small academic dataset. It supports record creation and removal, sorting, searching, performance summaries, and a grade-based risk indicator.

## Build and run

Run these commands from this directory:

```sh
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o academic_analysis
./academic_analysis
```

## Features

- Starts with 10 fictional student records.
- Uses a dynamically allocated array and grows it with `realloc`.
- Adds and removes records; duplicate IDs are rejected.
- Validates grades to the inclusive range 0–100.
- Sorts by grade, name, or ID; searches by ID or exact name.
- Calculates average, highest and lowest grades, pass count, and below-pass count.
- Uses pointer traversal and a function-pointer table for menu dispatch.
- Releases allocated memory before exit.

## Academic Risk Index

The program calculates `ARI = 100 - grade`. The categories are coursework assumptions: high risk for grades below 50, moderate risk from 50 to below 70, and good standing from 70 to 100. These are not official ALU academic-risk rules. See [analysis_explanation.md](analysis_explanation.md).

## Test evidence

Run `bash Project_2/tests/run_smoke_tests.sh` from the repository root. It compiles all three programs and checks scripted operations, including a Project 1 add/remove/summary sequence. The automated checks do not replace manual testing of every menu option and invalid-input path.
