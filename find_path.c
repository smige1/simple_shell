/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
int is_cmd(info_t *info, char *path)
{
	struct stat yz;

	(void)info;
	if (!path || stat(path, &yz))
		return (0);

	if (yz.yz_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int y = 0, z = 0;

	for (z = 0, y = start; y < stop; y++)
		if (pathstr[y] != ':')
			buf[z++] = pathstr[y];
	buf[z] = 0;
	return (buf);
}


char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int y = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[y] || pathstr[y] == ':')
		{
			path = dup_chars(pathstr, curr_pos, y);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[y])
				break;
			curr_pos = y;
		}
		y++;
	}
	return (NULL);
}
