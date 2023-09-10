#include "shell.h"

/**
 * _eputs - prints input string---
 * @str: ---  string to be printed
 *
 * Return: 0 ---
 */
void _eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a = a + 1;
	}
}

/**
 * _eputchar - print de character c to stderr
 * @c: This is the  character to print
 *
 * Return: On success 1.
 * On error, -1 is returned,err. is set correctly
 */
int _eputchar(char y)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (y != BUF_FLUSH)
		buf[a = a+1] = y;
	return (1);
}


int _putfd(char y, int yz)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (y == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(yz, buf, a);
		a = 0;
	}
	if (y != BUF_FLUSH)
		buf[a=a+1] = y;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int yz)
{
	int y = 0;

	if (!str)
		return (0);
	while (*str)
	{
		y += _putfd(*str++, yz);
	}
	return (i);
}

