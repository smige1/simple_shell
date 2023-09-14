#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 * set_info - initializes info_t struct
 * @info: struct address
 * free_info - frees info_t struct fields
 * @av: argument vector
 * 
 * @info: struct address
 * @all: true if freeing all fields
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}


void set_info(info_t *info, char **av)
{
	int y = 0;

	info->yname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (y = 0; info->argv && info->argv[y]; y++)
			;
		info->argc = y;

		replace_alias(info);
		replace_vars(info);
	}
}


void free_info(info_t *info, int all)
{
	yfree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		yfree(info->environ);
			info->environ = NULL;
		zfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

