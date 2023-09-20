#include "shell.h"

/**
 * starts_with - checks for needle if it starts with haystack
 * @notworking: string to search
 * @working: substring to find
 *
 * Return: success 1
 */
char *starts_with(const char *notworking, const char *working)
{
	while (*working)
		if (*working++ != *notworking++)
			return (NULL);
	return ((char *)notworking);
}
