# Custom Analysis — Lexical Diversity Score (LDS)

## Purpose

The Lexical Diversity Score describes what share of the words in the analyzed passage are distinct. It provides a simple indication of repetition in the selected text.

## Formula

`LDS = (distinct word count / total word count) × 100`

For example, 100 distinct tokens out of 200 total tokens gives an LDS of 50%.

## Calculation

The program tokenizes the input, converts each token to lowercase, and stores one entry per distinct normalized token. It sums entry frequencies to obtain the total word count, then divides the number of distinct entries by the total. Empty input is handled separately to avoid division by zero.

## Interpretation and limitations

A higher percentage means a larger share of tokens are distinct. A lower percentage means words are repeated more often. The score is affected by passage length and subject matter, so it is not a complete measure of writing quality.

The program treats alphabetic sequences as words. Punctuation, whitespace, apostrophes, and hyphens separate tokens. Words longer than 39 characters are truncated to 39 characters for storage. This keeps entries within the fixed `name[40]` field but can merge different long words that share the same first 39 characters.
