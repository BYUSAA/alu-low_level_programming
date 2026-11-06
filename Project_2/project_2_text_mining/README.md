# Project 2 — Dynamic Text Mining and Linguistic Pattern Analyzer

**Student:** Byusa Mukarage Martin De Poles  
**Student ID:** 811201785

## Purpose

This program accepts a paragraph, stores it in a dynamically growing text buffer, extracts normalized words, and builds a dynamically resized frequency table.

## Build and run

Run these commands from this directory:

\`\`\`sh
gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o text_mining
./text_mining
\`\`\`

Paste the prose from \`source_text.txt\`; do not paste the bibliographic heading lines. Enter a single period (\`.\`) on a line by itself to finish. The input-line buffer grows dynamically, so a long line is not split at a fixed 511-character boundary.

## Analysis features

The menu provides total word count, longest word, most frequent word (including ties), word-frequency display, alphabetical and frequency sorting, word search, a text summary with average word length and Lexical Diversity Score, and memory-address inspection. Menu dispatch uses function pointers, text traversal uses pointers, and memory is released before normal exit.

If growing the word-statistics array fails, analysis stops with an error rather than silently omitting a word.

## Tokenization policy

A word is a contiguous run of alphabetic characters. Punctuation and whitespace are separators, so apostrophes and hyphens split tokens. Tokens are converted to lowercase. Tokens longer than 39 characters are truncated to 39 characters before storage and comparison; different long words sharing the first 39 characters can therefore be treated as one entry.

## Custom analysis

\`LDS = (distinct word count / total word count) × 100\`

The score is the percentage of analyzed tokens that are distinct. It is not a complete measure of writing quality. See [analysis_explanation.md](analysis_explanation.md).

## Source

The prose in \`source_text.txt\` is an excerpt from Charles Dickens's *A Tale of Two Cities* (1859), Book the First, Chapter I, “The Period”. It is public-domain text. The program accepts pasted text; it does not open the source file automatically.

## Test evidence

Run \`bash Project_2/tests/run_smoke_tests.sh\` from the repository root. It checks the supplied text, summary generation, and memory-address display.
