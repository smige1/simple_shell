#include "shell.h"

/**
 * free - free up  pointer and address
 * @ptr: addr pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
