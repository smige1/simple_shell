
#include "shell.h"

/**
 * _strlen - returns the length of a string__
 * @s: the string whose length to check
 *
 * Return: integer length of string___
 */
int _strlen(char *s)
{
	int z = 0;

	if (!s)
		return (0);

	while (*s++)
		z++;
	return (z);
}
