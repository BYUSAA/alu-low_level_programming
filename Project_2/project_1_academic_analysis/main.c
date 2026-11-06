/*
 * Dynamic Academic Performance and Risk Analysis Engine
 * Compile: gcc -std=c99 -Wall -Wextra -Werror -pedantic main.c -o academic_analysis
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>

#define STUDENT_ID "811201785"
#define NAME_SIZE 80
#define COURSE_SIZE 80
#define PASS_MARK 50.0
#define MODERATE_RISK_MARK 70.0

typedef struct Student
{
    int id;
    char name[NAME_SIZE];
    char course[COURSE_SIZE];
    double grade;
} Student;

typedef struct StudentList
{
    Student *items;
    size_t count;
    size_t capacity;
} StudentList;

typedef void (*MenuFunction)(StudentList *);

static int read_line(const char *prompt, char *buffer, size_t size)
{
    size_t length;
    int ch;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL)
        return 0;
    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
        return 1;
    }
    ch = getchar();
    if (ch == '\n' || ch == EOF)
        return 1;
    while (ch != '\n' && ch != EOF)
        ch = getchar();
    printf("Input too long. Please try again.\n");
    return 0;
}

static int read_int(const char *prompt, int *value)
{
    char buffer[128];
    char *end;
    long parsed;

    while (1)
    {
        if (!read_line(prompt, buffer, sizeof(buffer)))
        {
            if (feof(stdin))
                return 0;
            continue;
        }
        errno = 0;
        parsed = strtol(buffer, &end, 10);
        if (buffer[0] == '\0' || *end != '\0' || errno == ERANGE ||
            parsed < 0 || parsed > 2147483647L)
        {
            printf("Enter a valid non-negative integer.\n");
            continue;
        }
        *value = (int)parsed;
        return 1;
    }
}

static int read_grade(const char *prompt, double *value)
{
    char buffer[128];
    char *end;
    double parsed;

    while (1)
    {
        if (!read_line(prompt, buffer, sizeof(buffer)))
            continue;
        errno = 0;
        parsed = strtod(buffer, &end);
        if (buffer[0] == '\0' || *end != '\0' || errno == ERANGE || !isfinite(parsed) ||
            parsed < 0.0 || parsed > 100.0)
        {
            printf("Grade must be a number from 0 to 100.\n");
            continue;
        }
        *value = parsed;
        return 1;
    }
}

static int reserve_students(StudentList *list, size_t needed)
{
    Student *temporary;
    size_t new_capacity;

    if (needed <= list->capacity)
        return 1;
    new_capacity = (list->capacity == 0) ? 10 : list->capacity;
    while (new_capacity < needed)
        new_capacity *= 2;
    temporary = realloc(list->items, new_capacity * sizeof(Student));
    if (temporary == NULL)
        return 0;
    list->items = temporary;
    list->capacity = new_capacity;
    return 1;
}

static int id_exists(const StudentList *list, int id)
{
    const Student *ptr;

    if (list->count == 0)
        return 0;
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
        if (ptr->id == id)
            return 1;
    return 0;
}

static int initialize_students(StudentList *list)
{
    static const Student initial[] = {
        {1001, "Aline Uwase", "Programming in C", 86.5},
        {1002, "Eric Niyonzima", "Data Structures", 72.0},
        {1003, "Diane Mukamana", "Mobile Development", 91.0},
        {1004, "Patrick Habimana", "Programming in C", 48.5},
        {1005, "Grace Ingabire", "Linux Programming", 67.0},
        {1006, "Kevin Mugisha", "Data Structures", 55.5},
        {1007, "Olive Uwera", "Mobile Development", 78.0},
        {1008, "Samuel Nkurunziza", "Linux Programming", 39.0},
        {1009, "Alice Mutoni", "Programming in C", 95.0},
        {1010, "David Rukundo", "Data Structures", 62.5}
    };

    list->count = sizeof(initial) / sizeof(initial[0]);
    list->capacity = list->count;
    list->items = malloc(list->capacity * sizeof(Student));
    if (list->items == NULL)
        return 0;
    memcpy(list->items, initial, sizeof(initial));
    return 1;
}

static void display_students(StudentList *list)
{
    Student *ptr;

    if (list->count == 0)
    {
        printf("No student records are available.\n");
        return;
    }
    printf("\n%-8s %-25s %-25s %8s\n", "ID", "NAME", "COURSE", "GRADE");
    printf("-----------------------------------------------------------------------\n");
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
        printf("%-8d %-25.25s %-25.25s %7.2f\n",
               ptr->id, ptr->name, ptr->course, ptr->grade);
}

static void add_student(StudentList *list)
{
    Student student;
    char name[NAME_SIZE];
    char course[COURSE_SIZE];

    if (!read_int("Student ID: ", &student.id))
        return;
    if (id_exists(list, student.id))
    {
        printf("Duplicate ID rejected.\n");
        return;
    }
    if (!read_line("Full name: ", name, sizeof(name)) || name[0] == '\0' ||
        !read_line("Course/module: ", course, sizeof(course)) || course[0] == '\0')
    {
        printf("Name and course are required.\n");
        return;
    }
    if (!read_grade("Grade (0-100): ", &student.grade))
        return;
    strcpy(student.name, name);
    strcpy(student.course, course);
    if (!reserve_students(list, list->count + 1))
    {
        printf("Memory allocation failed; record was not added.\n");
        return;
    }
    list->items[list->count++] = student;
    printf("Student added. Records: %lu\n", (unsigned long)list->count);
}

static void sort_students(StudentList *list)
{
    int choice;
    size_t i;
    size_t j;
    int swap;
    Student temporary;

    if (list->count < 2)
    {
        printf("At least two records are needed to sort.\n");
        return;
    }
    printf("1. Grade (highest first)\n2. Name (A-Z)\n3. ID (lowest first)\n");
    if (!read_int("Sort choice: ", &choice))
        return;
    if (choice < 1 || choice > 3)
    {
        printf("Invalid sort choice.\n");
        return;
    }
    for (i = 0; i + 1 < list->count; i++)
    {
        for (j = 0; j + 1 < list->count - i; j++)
        {
            swap = 0;
            if (choice == 1 && list->items[j].grade < list->items[j + 1].grade)
                swap = 1;
            if (choice == 2 &&
                strcmp(list->items[j].name, list->items[j + 1].name) > 0)
                swap = 1;
            if (choice == 3 && list->items[j].id > list->items[j + 1].id)
                swap = 1;
            if (swap)
            {
                temporary = list->items[j];
                list->items[j] = list->items[j + 1];
                list->items[j + 1] = temporary;
            }
        }
    }
    printf("Records sorted.\n");
    display_students(list);
}

static void calculate_average(StudentList *list)
{
    Student *ptr;
    double total = 0.0;

    if (list->count == 0)
    {
        printf("No records available.\n");
        return;
    }
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
        total += ptr->grade;
    printf("Average grade: %.2f\n", total / (double)list->count);
}

static void find_top_student(StudentList *list)
{
    Student *ptr;
    Student *top;

    if (list->count == 0)
    {
        printf("No records available.\n");
        return;
    }
    top = list->items;
    for (ptr = list->items + 1; ptr < list->items + list->count; ptr++)
        if (ptr->grade > top->grade)
            top = ptr;
    printf("Top student: %s (ID %d), %s, grade %.2f\n",
           top->name, top->id, top->course, top->grade);
}

static void search_student(StudentList *list)
{
    int choice;
    int id = 0;
    char name[NAME_SIZE];
    Student *ptr;
    int found = 0;

    printf("1. Search by ID\n2. Search by exact name\n");
    if (!read_int("Search choice: ", &choice))
        return;
    if (choice == 1)
        if (!read_int("Student ID: ", &id))
            return;
    else if (choice == 2)
    {
        if (!read_line("Exact name: ", name, sizeof(name)))
            return;
    }
    else
    {
        printf("Invalid search choice.\n");
        return;
    }
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        if ((choice == 1 && ptr->id == id) ||
            (choice == 2 && strcmp(ptr->name, name) == 0))
        {
            printf("Found: %d | %s | %s | %.2f\n",
                   ptr->id, ptr->name, ptr->course, ptr->grade);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Student not found.\n");
}

static void remove_student(StudentList *list)
{
    int id;
    size_t index;
    Student *smaller;

    if (list->count == 0)
    {
        printf("No records to remove.\n");
        return;
    }
    if (!read_int("ID to remove: ", &id))
        return;
    for (index = 0; index < list->count; index++)
        if (list->items[index].id == id)
            break;
    if (index == list->count)
    {
        printf("Student not found.\n");
        return;
    }
    for (; index + 1 < list->count; index++)
        list->items[index] = list->items[index + 1];
    list->count--;
    if (list->count == 0)
    {
        free(list->items);
        list->items = NULL;
        list->capacity = 0;
    }
    else
    {
        smaller = realloc(list->items, list->count * sizeof(Student));
        if (smaller != NULL)
        {
            list->items = smaller;
            list->capacity = list->count;
        }
        /* A failed shrink is safe: the old allocation remains valid. */
    }
    printf("Student removed. Records: %lu\n", (unsigned long)list->count);
}

static void custom_analysis(StudentList *list)
{
    Student *ptr;
    size_t high = 0;
    size_t moderate = 0;
    size_t good = 0;
    double total_risk = 0.0;

    if (list->count == 0)
    {
        printf("No records available for analysis.\n");
        return;
    }
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        total_risk += 100.0 - ptr->grade;
        if (ptr->grade < PASS_MARK)
            high++;
        else if (ptr->grade < MODERATE_RISK_MARK)
            moderate++;
        else
            good++;
    }
    printf("\nACADEMIC RISK INDEX\n");
    printf("Individual formula: ARI = 100 - grade\n");
    printf("High risk (grade < 50): %lu\n", (unsigned long)high);
    printf("Moderate risk (50 <= grade < 70): %lu\n", (unsigned long)moderate);
    printf("Good standing (70-100): %lu\n", (unsigned long)good);
    printf("Average class ARI: %.2f/100\n", total_risk / (double)list->count);
    printf("Higher ARI means greater grade-based academic risk.\n");
}

static void summary_report(StudentList *list)
{
    Student *ptr;
    double total = 0.0;
    double highest;
    double lowest;
    size_t passed = 0;
    size_t failed = 0;

    if (list->count == 0)
    {
        printf("No records: summary report unavailable.\n");
        return;
    }
    highest = list->items[0].grade;
    lowest = list->items[0].grade;
    for (ptr = list->items; ptr < list->items + list->count; ptr++)
    {
        total += ptr->grade;
        if (ptr->grade > highest)
            highest = ptr->grade;
        if (ptr->grade < lowest)
            lowest = ptr->grade;
        if (ptr->grade >= PASS_MARK)
            passed++;
        else
            failed++;
    }
    printf("\n========== ACADEMIC SUMMARY ==========\n");
    printf("Total records: %lu\n", (unsigned long)list->count);
    printf("Average: %.2f\nHighest: %.2f\nLowest: %.2f\n",
           total / (double)list->count, highest, lowest);
    printf("Passed (>=50): %lu\nBelow pass mark: %lu\n",
           (unsigned long)passed, (unsigned long)failed);
    custom_analysis(list);
}

static void exit_program(StudentList *list)
{
    (void)list;
    printf("Exiting program.\n");
}

int main(void)
{
    StudentList list;
    int choice;
    int running = 1;
    MenuFunction menu[] = {
        add_student, display_students, sort_students, calculate_average,
        find_top_student, search_student, remove_student, custom_analysis,
        summary_report, exit_program
    };
    const char *labels[] = {
        "Add student", "Display students", "Sort students",
        "Calculate average", "Find top student", "Search student",
        "Remove student", "Custom academic analysis", "Summary report", "Exit"
    };

    list.items = NULL;
    list.count = 0;
    list.capacity = 0;

    printf("============================================================\n");
    printf("Student ID: %s\n", STUDENT_ID);
    printf("Project: Dynamic Academic Performance and Risk Analysis Engine\n");
    printf("Custom Analysis: Academic Risk Index (ARI)\n");
    printf("============================================================\n");

    if (!initialize_students(&list))
    {
        fprintf(stderr, "Could not allocate initial student dataset.\n");
        return EXIT_FAILURE;
    }

    while (running)
    {
        size_t i;
        printf("\nMAIN MENU\n");
        for (i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
            printf("%lu. %s\n", (unsigned long)(i + 1), labels[i]);
        if (!read_int("Choose an option: ", &choice))
            break;
        if (choice < 1 || choice > 10)
        {
            printf("Choose a number from 1 to 10.\n");
            continue;
        }
        menu[choice - 1](&list);
        if (choice == 10)
            running = 0;
    }

    free(list.items);
    list.items = NULL;
    list.count = 0;
    list.capacity = 0;
    printf("Dynamic memory released. Goodbye.\n");
    return EXIT_SUCCESS;
}