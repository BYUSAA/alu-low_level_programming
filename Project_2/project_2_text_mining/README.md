# Project 2 — Dynamic Text Mining and Linguistic Pattern Analyzer

## Description
This C program accepts a paragraph of any practical length, dynamically stores it, extracts words, builds a dynamically resized frequency table, and offers text-analysis operations.

## Compile and run (Ubuntu / WSL)
```bash
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o text_mining
./text_mining
```

## Input
Paste or type a paragraph. Enter a single period (`.`) on its own line to finish input. The program then builds its word statistics and displays the analysis menu.

## Features
- Dynamic text buffer and dynamic word-statistics array.
- Total word count and distinct word count.
- Longest word and most frequent word (ties are displayed).
- Word-frequency table, alphabetical/frequency sorting, and word search.
- Summary with average word length and lexical diversity.
- Function-pointer dispatch for the analysis menu.
- Pointer-based traversal of the text.
- Memory address inspection using `%p` and `(void *)`.

## Tokenization policy
Only contiguous alphabetic sequences count as words. Punctuation and whitespace separate tokens. Apostrophes and hyphens therefore split tokens. All tokens are converted to lowercase. A token longer than 39 characters is truncated to its first 39 characters before it is stored and compared; this policy can merge two long tokens sharing the same first 39 characters.

## Source
The companion `source_text.txt` contains a public-domain excerpt from Charles Dickens's *A Tale of Two Cities* (1859). The program accepts pasted text independently; enter the companion paragraph when demonstrating the supplied source.