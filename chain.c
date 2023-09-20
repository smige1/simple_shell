#include "shell.h"

/**
 * chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 *
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * 
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * 
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * 
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int chain(info_t *info, char *buf, size_t *p)
{
	size_t y = *z;

	if (buf[y] == '|' && buf[y + 1] == '|')
	{
		buf[] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*z = y;
	return (1);
}


void check_chain(info_t *info, char *buf, size_t *z, size_t x, size_t len)
{
	size_t y = *z;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[x] = 0;
			y = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[x] = 0;
			y = len;
		}
	}

	*z = y;
}


int replace_alias(info_t *info)
{
	int y;
	list_t *node;
	char *z;

	for (y = 0; y < 10; y++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!z)
			return (0);
		z = _strdup(z + 1);
		if (!z)
			return (0);
		info->argv[0] = z;
	}
	return (1);
}


int replace_vars(info_t *info)
{
	int y = 0;
	list_t *node;

	for (y = 0; info->argv[y]; y++)
	{
		if (info->argv[y][0] != '$' || !info->argv[y][1])
			continue;

		if (!_strcmp(info->argv[y], "$?"))
		{
			replace_string(&(info->argv[y]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[y], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[y][1], '=');
		if (node)
		{
			replace_string(&(info->argv[y]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[y], _strdup(""));

	}
	return (0);
}


int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
