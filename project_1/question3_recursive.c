#include <stdio.h>

/**
 * calculate_total - calculates the total distance
 * @distances: array of route distances
 * @size: number of routes
 *
 * Return: total distance
 */
int calculate_total(int distances[], int size)
{
        int i;
        int total = 0;

        for (i = 0; i < size; i++)
                total += distances[i];

        return (total);
}

/**
 * calculate_average - calculates the average distance
 * @distances: array of route distances
 * @size: number of routes
 *
 * Return: average distance
 */
double calculate_average(int distances[], int size)
{
        int total;

        total = calculate_total(distances, size);

        return ((double)total / size);
}

/**
 * find_longest - finds the longest route
 * @distances: array of route distances
 * @size: number of routes
 *
 * Return: longest distance
 */
int find_longest(int distances[], int size)
{
        int i;
        int longest = distances[0];

        for (i = 1; i < size; i++)
        {
                if (distances[i] > longest)
                        longest = distances[i];
        }

        return (longest);
}

/**
 * count_above_limit - counts routes above a specified limit
 * @distances: array of route distances
 * @size: number of routes
 * @limit: distance limit
 *
 * Return: number of routes above the limit
 */
int count_above_limit(int distances[], int size, int limit)
{
        int i;
        int count = 0;

        for (i = 0; i < size; i++)
        {
                if (distances[i] > limit)
                        count++;
        }

        return (count);
}

/**
 * recursive_sum - calculates the sum recursively
 * @distances: array of route distances
 * @size: number of routes
 *
 * Return: recursive sum of distances
 */
int recursive_sum(int distances[], int size)
{
        if (size == 0)
                return (0);

        return (distances[size - 1] + recursive_sum(distances, size - 1));
}

/**
 * main - analyzes logistics delivery route distances
 *
 * Return: 0 on success
 */
int main(void)
{
        int distances[] = {12, 25, 18, 40, 15, 30};
        int size = 6;
        int limit = 20;
        int total;
        double average;
        int longest;
        int above_limit;
        int recursive_total;

        total = calculate_total(distances, size);
        average = calculate_average(distances, size);
        longest = find_longest(distances, size);
        above_limit = count_above_limit(distances, size, limit);
        recursive_total = recursive_sum(distances, size);

        printf("===== LOGISTICS DISTANCE ANALYSIS =====\n\n");
        printf("Number of routes: %d\n", size);
        printf("Distances: ");

        {
                int i;

                for (i = 0; i < size; i++)
                        printf("%d ", distances[i]);
        }

        printf("km\n");
        printf("Distance limit: %d km\n\n", limit);

        printf("===== RESULTS =====\n");
        printf("Total distance: %d km\n", total);
        printf("Average distance: %.2f km\n", average);
        printf("Longest route: %d km\n", longest);
        printf("Routes above %d km: %d\n", limit, above_limit);
        printf("Recursive sum: %d km\n", recursive_total);

        return (0);
}