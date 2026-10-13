
#include <stdlib.h>
#include "main.h"

/**
 * alloc_grid - allocates a two-dimensional integer grid
 * @width: number of columns
 * @height: number of rows
 *
 * Return: pointer to the grid, or NULL on failure
 */
int **alloc_grid(int width, int height)
{
	int **grid;
	int row;
	int col;

	if (width <= 0 || height <= 0)
		return (NULL);

	grid = malloc(sizeof(int *) * height);
	if (grid == NULL)
		return (NULL);

	for (row = 0; row < height; row++)
	{
		grid[row] = malloc(sizeof(int) * width);
		if (grid[row] == NULL)
		{
			while (row > 0)
			{
				row--;
				free(grid[row]);
			}
			free(grid);
			return (NULL);
		}

		for (col = 0; col < width; col++)
			grid[row][col] = 0;
	}

	return (grid);
}
