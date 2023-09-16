#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter return info struct
 * @av: the main argument vector 
 *
 * find_cmd - finds a command in PATH
 * @info: the parameter return info struct
 *
 *
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * 
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int shell_loop(info_t *info, char **yz)
{
	size_t y = 0;
	int builtin_ret = 0;

	while (y != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		y = get_input(info);
		if (y != -1)
		{
			set_info(info, yz);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}


int find_builtin(info_t *info)
{
	int y, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (y = 0; builtintbl[y].type; y++)
		if (_strcmp(info->argv[0], builtintbl[y].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[y].func(info);
			break;
		}
	return (built_in_ret);
}


void find_cmd(info_t *info)
{
	char *path = NULL;
	int y, z;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (y = 0, z = 0; info->arg[y]; y++)
		if (!is_delim(info->arg[y], " \t\n"))
			z++;
	if (!z)
		return;

	path = find_path(info, getenvi(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || getenvi(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}


void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, setenv(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
