
#include <stddef.h>
#include "3-calc.h"

/**
 * get_op_func - selects the correct operation function
 * @s: operator symbol
 *
 * Return: pointer to the matching function, or NULL
 */
int (*get_op_func(char *s))(int, int)
{
	int i;
	op_t ops[] = {
		{"+", op_add},
		{"-", op_sub},
		{"*", op_mul},
		{"/", op_div},
		{"%", op_mod},
		{NULL, NULL}
	};

	i = 0;
	while (ops[i].op != NULL)
	{
		if (s != NULL && ops[i].op[0] == s[0] && s[1] == '\0')
			return (ops[i].f);
		i++;
	}

	return (NULL);
}
