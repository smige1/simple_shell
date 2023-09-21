#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */


int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}


int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}


int _atoi(char *s)
{
	int z, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (z = 0; s[z] != '\0' && flag != 2; z++)
	{
		if (s[z] == '-')
			sign *= -1;

		if (s[z] >= '0' && s[z] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[z] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
