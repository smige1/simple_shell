#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * is_delim - checks if character is a delimeter
 * @delim: the delimeter string
 * _isalpha - checks for alphabetic character
 * @v: The character to input
 * _atoi - converts a string to an integer
 * @x: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}


int is_del(char v, char *del)
{
	while (*del)
		if (*del++ == v)
			return (1);
	return (0);
}



int alpha(int v)
{
	if ((v >= 'a' && v <= 'z') || (v >= 'A' && v <= 'Z'))
		return (1);
	else
		return (0);
}



int atoi(char *x)
{
	int y, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (y = 0; x[y] != '\0' && flag != 2; y++)
	{
		if (x[y] == '-')
			sign *= -1;

		if (x[y] >= '0' && x[y] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (x[y] - '0');
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
