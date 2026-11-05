# Custom Analysis — Lexical Diversity Score (LDS)

## Purpose
LDS describes the proportion of distinct words relative to all words in the analyzed text.

## Formula
`LDS = (distinct word count / total word count) × 100`

If there are 100 distinct words among 200 total words:

`LDS = (100 / 200) × 100 = 50%`

## Interpretation
A larger percentage means a larger share of the tokens are distinct. A smaller percentage indicates more repetition. LDS is affected by text length and topic; it is not, by itself, a complete measure of writing quality.

## Implementation
The program counts each normalized token in the word-statistics array, then divides the number of distinct entries by the total token count. Empty text is handled separately to avoid division by zero.
