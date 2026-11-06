/*
 * Dynamic Text Mining and Linguistic Pattern Analyzer
 * Compile: gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o text_mining
 *
 * Input rule: alphabetic runs are words; punctuation, whitespace, apostrophes
 * and hyphens separate words. Words are converted to lowercase. Tokens longer
 * than 39 characters are safely truncated to 39 characters for this dataset.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define STUDENT_ID "811201785"
#define WORD_SIZE 40

typedef struct wordStat
{
    char name[WORD_SIZE];
    size_t count;
} WordStat;

typedef struct TextData
{
    char *text;
    size_t text_length;
    size_t total_words;
    WordStat *stats;
    size_t distinct_words;
    size_t stats_capacity;
} TextData;

typedef void (*AnalysisFunction)(TextData *);

static int append_text(char **text, size_t *length, size_t *capacity,
                       const char *line)
{
    size_t line_length = strlen(line);
    size_t needed = *length + line_length + 2;
    char *temporary;
    size_t new_capacity;

    if (needed > *capacity)
    {
        new_capacity = (*capacity == 0) ? 256 : *capacity;
        while (new_capacity < needed)
            new_capacity *= 2;
        temporary = realloc(*text, new_capacity);
        if (temporary == NULL)
            return 0;
        *text = temporary;
        *capacity = new_capacity;
    }
    memcpy(*text + *length, line, line_length);
    *length += line_length;
    (*text)[(*length)++] = '\n';
    (*text)[*length] = '\0';
    return 1;
}

static int read_text(TextData *data)
{
    char *line = NULL;
    size_t line_length = 0;
    size_t line_capacity = 0;
    size_t text_capacity = 0;
    size_t new_capacity;
    char *temporary;
    int character;

    printf("Paste/type your paragraph. Enter a single period (.) on its own line to finish.\n");
    data->text = NULL;
    data->text_length = 0;

    /* Read complete lines dynamically so very long lines are not split. */
    while ((character = getchar()) != EOF)
    {
        if (character == '\r')
            continue;
        if (character == '\n')
        {
            if (line_length == 1 && line[0] == '.')
                break;
            if (line_capacity == 0)
            {
                line = malloc(1);
                if (line == NULL)
                    goto allocation_error;
                line_capacity = 1;
            }
            line[line_length] = '\0';
            if (!append_text(&data->text, &data->text_length,
                             &text_capacity, line))
                goto allocation_error;
            line_length = 0;
            continue;
        }

        if (line_length + 1 >= line_capacity)
        {
            new_capacity = (line_capacity == 0) ? 128 : line_capacity * 2;
            temporary = realloc(line, new_capacity);
            if (temporary == NULL)
                goto allocation_error;
            line = temporary;
            line_capacity = new_capacity;
        }
        line[line_length++] = (char)character;
    }

    if (line_length > 0 && !(line_length == 1 && line[0] == '.'))
    {
        if (line_capacity == 0)
        {
            line = malloc(1);
            if (line == NULL)
                goto allocation_error;
            line_capacity = 1;
        }
        line[line_length] = '\0';
        if (!append_text(&data->text, &data->text_length,
                         &text_capacity, line))
            goto allocation_error;
    }
    free(line);

    if (data->text == NULL)
    {
        data->text = malloc(1);
        if (data->text == NULL)
            return 0;
        data->text[0] = '\0';
    }
    return 1;

allocation_error:
    fprintf(stderr, "Unable to grow the input or text buffer.\n");
    free(line);
    free(data->text);
    data->text = NULL;
    data->text_length = 0;
    return 0;
}

static int reserve_stats(TextData *data, size_t needed)
{
    WordStat *temporary;
    size_t new_capacity;

    if (needed <= data->stats_capacity)
        return 1;
    new_capacity = (data->stats_capacity == 0) ? 16 : data->stats_capacity * 2;
    while (new_capacity < needed)
        new_capacity *= 2;
    temporary = realloc(data->stats, new_capacity * sizeof(WordStat));
    if (temporary == NULL)
        return 0;
    data->stats = temporary;
    data->stats_capacity = new_capacity;
    return 1;
}

static int normalize_and_store(TextData *data, const char *start,
                                size_t length)
{
    char word[WORD_SIZE];
    size_t i;
    size_t stored_length = length;
    size_t index;

    if (length == 0)
        return 1;
    if (stored_length >= WORD_SIZE)
        stored_length = WORD_SIZE - 1;
    for (i = 0; i < stored_length; i++)
        word[i] = (char)tolower((unsigned char)start[i]);
    word[stored_length] = '\0';

    for (index = 0; index < data->distinct_words; index++)
    {
        if (strcmp(data->stats[index].name, word) == 0)
        {
            data->stats[index].count++;
            data->total_words++;
            return 1;
        }
    }
    if (!reserve_stats(data, data->distinct_words + 1))
    {
        fprintf(stderr, "Unable to grow word statistics array.\n");
        return 0;
    }
    strcpy(data->stats[data->distinct_words].name, word);
    data->stats[data->distinct_words].count = 1;
    data->distinct_words++;
    data->total_words++;
    return 1;
}

static int build_statistics(TextData *data)
{
    const char *ptr;
    const char *start;
    size_t length;

    data->stats = NULL;
    data->stats_capacity = 0;
    data->distinct_words = 0;
    data->total_words = 0;
    ptr = data->text;
    while (*ptr != '\0')
    {
        while (*ptr != '\0' && !isalpha((unsigned char)*ptr))
            ptr++;
        if (*ptr == '\0')
            break;
        start = ptr;
        while (*ptr != '\0' && isalpha((unsigned char)*ptr))
            ptr++;
        length = (size_t)(ptr - start);
        if (!normalize_and_store(data, start, length))
            return 0;
    }
    return 1;
}

static void count_words(TextData *data)
{
    printf("Total words: %lu\n", (unsigned long)data->total_words);
}

static void longest_word(TextData *data)
{
    size_t i;
    size_t longest = 0;
    size_t length;

    if (data->distinct_words == 0)
    {
        printf("No words found.\n");
        return;
    }
    for (i = 0; i < data->distinct_words; i++)
    {
        length = strlen(data->stats[i].name);
        if (length > longest)
            longest = length;
    }
    printf("Longest word(s), length %lu:\n", (unsigned long)longest);
    for (i = 0; i < data->distinct_words; i++)
        if (strlen(data->stats[i].name) == longest)
            printf("  %s\n", data->stats[i].name);
}

static void most_frequent(TextData *data)
{
    size_t i;
    size_t highest = 0;

    if (data->distinct_words == 0)
    {
        printf("No words found.\n");
        return;
    }
    for (i = 0; i < data->distinct_words; i++)
        if (data->stats[i].count > highest)
            highest = data->stats[i].count;
    printf("Most frequent word(s), frequency %lu:\n", (unsigned long)highest);
    for (i = 0; i < data->distinct_words; i++)
        if (data->stats[i].count == highest)
            printf("  %s\n", data->stats[i].name);
}

static void display_word_statistics(TextData *data)
{
    size_t i;

    if (data->distinct_words == 0)
    {
        printf("No word statistics available.\n");
        return;
    }
    printf("\n%-25s %s\n", "WORD", "FREQUENCY");
    printf("------------------------------------\n");
    for (i = 0; i < data->distinct_words; i++)
        printf("%-25s %lu\n", data->stats[i].name,
               (unsigned long)data->stats[i].count);
}

static void sort_word_statistics(TextData *data)
{
    int choice;
    size_t i;
    size_t j;
    int swap;
    WordStat temporary;
    char line[64];
    char *end;
    long parsed;

    printf("1. Alphabetical (A-Z)\n2. Frequency (highest first)\n");
    printf("Sort choice: ");
    if (fgets(line, sizeof(line), stdin) == NULL)
        return;
    parsed = strtol(line, &end, 10);
    if (end == line || (*end != '\n' && *end != '\0'))
    {
        printf("Invalid choice.\n");
        return;
    }
    choice = (int)parsed;
    if (choice != 1 && choice != 2)
    {
        printf("Invalid choice.\n");
        return;
    }
    for (i = 0; i + 1 < data->distinct_words; i++)
    {
        for (j = 0; j + 1 < data->distinct_words - i; j++)
        {
            swap = 0;
            if (choice == 1 &&
                strcmp(data->stats[j].name, data->stats[j + 1].name) > 0)
                swap = 1;
            if (choice == 2 &&
                data->stats[j].count < data->stats[j + 1].count)
                swap = 1;
            if (swap)
            {
                temporary = data->stats[j];
                data->stats[j] = data->stats[j + 1];
                data->stats[j + 1] = temporary;
            }
        }
    }
    printf("Word statistics sorted.\n");
    display_word_statistics(data);
}

static void search_word(TextData *data)
{
    char query[WORD_SIZE];
    size_t i;
    size_t j;

    printf("Enter word to search: ");
    if (fgets(query, sizeof(query), stdin) == NULL)
        return;
    query[strcspn(query, "\n")] = '\0';
    for (j = 0; query[j] != '\0'; j++)
        query[j] = (char)tolower((unsigned char)query[j]);
    for (i = 0; i < data->distinct_words; i++)
    {
        if (strcmp(query, data->stats[i].name) == 0)
        {
            printf("'%s' appears %lu time(s).\n", query,
                   (unsigned long)data->stats[i].count);
            return;
        }
    }
    printf("Word not found.\n");
}

static void generate_text_summary(TextData *data)
{
    size_t i;
    size_t total_characters = 0;
    size_t longest = 0;
    double average_length = 0.0;
    size_t longest_index = 0;
    size_t most_index = 0;

    if (data->total_words == 0)
    {
        printf("The text contains no words.\n");
        return;
    }
    for (i = 0; i < data->distinct_words; i++)
    {
        size_t word_length = strlen(data->stats[i].name);
        total_characters += word_length * data->stats[i].count;
        if (word_length > longest)
        {
            longest = word_length;
            longest_index = i;
        }
        if (data->stats[i].count > data->stats[most_index].count)
            most_index = i;
    }
    average_length = (double)total_characters / (double)data->total_words;
    printf("\n========== TEXT SUMMARY ==========\n");
    printf("Total words: %lu\n", (unsigned long)data->total_words);
    printf("Distinct words: %lu\n", (unsigned long)data->distinct_words);
    printf("Average word length: %.2f characters\n", average_length);
    printf("Longest word: %s (%lu characters)\n",
           data->stats[longest_index].name, (unsigned long)longest);
    printf("Most frequent word: %s (%lu occurrence(s))\n",
           data->stats[most_index].name,
           (unsigned long)data->stats[most_index].count);
    printf("Lexical Diversity Score: %.2f%%\n",
           100.0 * (double)data->distinct_words / (double)data->total_words);
    printf("==================================\n");
}

static void memory_inspection(TextData *data)
{
    printf("\nMEMORY INSPECTION\n");
    printf("Text buffer address: %p\n", (void *)data->text);
    printf("Word statistics array: %p\n", (void *)data->stats);
    if (data->distinct_words > 0)
        printf("Selected word-stat entry: %p\n", (void *)&data->stats[0]);
    else
        printf("Selected word-stat entry: unavailable (no words)\n");
    printf("The addresses identify the allocated text buffer, the first\n");
    printf("word-statistics element, and a selected entry in that array.\n");
}

int main(void)
{
    TextData data;
    int choice;
    AnalysisFunction operations[7] = {
        count_words, longest_word, most_frequent,
        display_word_statistics, sort_word_statistics,
        search_word, generate_text_summary
    };
    const char *labels[7] = {
        "Count words", "Find longest word", "Find most frequent word",
        "Display word statistics", "Sort word statistics",
        "Search for a word", "Generate text summary"
    };
    char menu_line[64];
    char *end;
    long selected;
    size_t i;

    data.text = NULL;
    data.stats = NULL;
    data.text_length = 0;
    data.total_words = 0;
    data.distinct_words = 0;
    data.stats_capacity = 0;

    printf("============================================================\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic Text Mining and Linguistic Pattern Analyzer\n");
    printf("Source: A Tale of Two Cities, Charles Dickens (1859, public domain)\n");
    printf("Custom Analysis: Lexical Diversity Score\n");
    printf("============================================================\n");

    if (!read_text(&data))
        return EXIT_FAILURE;
    if (!build_statistics(&data))
    {
        fprintf(stderr, "Could not build word statistics.\n");
        free(data.text);
        free(data.stats);
        return EXIT_FAILURE;
    }

    printf("\nInput contains %lu words and %lu distinct words.\n",
           (unsigned long)data.total_words,
           (unsigned long)data.distinct_words);

    while (1)
    {
        printf("\nANALYSIS MENU\n");
        for (i = 0; i < 7; i++)
            printf("%lu. %s\n", (unsigned long)(i + 1), labels[i]);
        printf("8. Inspect memory addresses\n9. Exit\n");
        printf("Choose an option: ");
        if (fgets(menu_line, sizeof(menu_line), stdin) == NULL)
            break;
        selected = strtol(menu_line, &end, 10);
        if (end == menu_line || (*end != '\n' && *end != '\0'))
        {
            printf("Enter a valid menu number.\n");
            continue;
        }
        choice = (int)selected;
        if (choice >= 1 && choice <= 7)
            operations[choice - 1](&data);
        else if (choice == 8)
            memory_inspection(&data);
        else if (choice == 9)
            break;
        else
            printf("Choose a number from 1 to 9.\n");
    }

    free(data.text);
    free(data.stats);
    data.text = NULL;
    data.stats = NULL;
    printf("Allocated text and statistics memory released. Goodbye.\n");
    return EXIT_SUCCESS;
}