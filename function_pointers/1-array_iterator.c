
#include "function_pointers.h"

/**
 * array_iterator - executes a function on each array element
 * @array: array to iterate over
 * @size: number of elements in the array
 * @action: function to execute on each element
 *
 * Return: Nothing.
 */
void array_iterator(int *array, size_t size, void (*action)(int))
{
	size_t i;

	if (array == NULL || action == NULL || size == 0)
		return;

	for (i = 0; i < size; i++)
	{
		action(array[i]);
	}
}
