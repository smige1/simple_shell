#include "shell.h"

/**
 **_strchr - locates a character in a string___
 *@s: the string to be parsed____
 *@c: the character to look for____
 *Return: (s) a pointer to the memory area s____
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
