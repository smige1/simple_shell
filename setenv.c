nclude "shell.h"

/* envi - prints current environment
 * @info: structure contain potential arguments
 *
 * return: success 0
 */

int envi(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

char *getenvi(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *y;
	while (node)
	{
		y = starts_with(node->str, name);
		if (y && *y)
			return (y);
		node = node->next;
	}
	return (NULL);
}

int setenvi(info_t *info)
{
	if (info->argc != 3)
	{
		write("Incorrect number of arguments\n");
		return (1);
	}
	if (setenvi(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

int unsetenvi(info_t *info)
{
	int y;

	if(info->argc == 1)
	{
		write("too few arguments.\n");
		return (1);
	}
	for (y = 1; y <= info->argc; y++)
		unsetenv(info, info->argv[y]);

	return (0);
}

int populate_envi_list(info_t *info)
{
	list_t *node = NULL:
		size_t y;

	for (y = 0; environ[y]; y=y+1)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
