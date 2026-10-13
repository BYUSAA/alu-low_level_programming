
#include <stdlib.h>
#include "main.h"

/**
 * free_grid - frees a two-dimensional grid
 * @grid: grid to free
 * @height: number of rows in the grid
 *
 * Return: nothing
 */
void free_grid(int **grid, int height)
{
	int row;

	if (grid == NULL)
		return;

	for (row = 0; row < height; row++)
		free(grid[row]);

	free(grid);
}
