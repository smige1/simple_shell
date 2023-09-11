#include "shell.h"

/* get_env - return the string array
 * @info: structure containing potential arguments
 * unsetenv - remove an environment variable
 * @var: the string env var property
 * setenv - initialize a new environment vaiable
 * @values: the string env var value
 *
 * return: success 0
 */

int setenv(info_t *info, char *var, char *values)
{
	char *buf = NULL;
	list_t *node;
	char *r

		if (!var || !values)
			return (0);

	buf = malloc(strlen(var) + strlen(value) + 2);
	if (!buf)
		return (1);
	strcpy(buf, var);
	strcat(buf, "=");
	strcat(buf, values);
	node = info->env;
	while (node)
	{
		r = starts_with(node->str, var);
		if (r && *r == "=")
		{
			free(node->str);
			node->str = buf;
			info->env_change = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_change = 1;
	return (0);
}
