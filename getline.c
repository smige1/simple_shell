#include "shell.h"

/**
 * input_buf - buffers chained commands
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * @ptr: address of pointer to buffer, preallocated or NULL
 * 
 * 
 * @info: parameter struct
 * 
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 * 
 * @info: parameter struct
 *
 * Return: bytes read
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @iv: size
 *
 * Return: ry
 */


size_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t ry = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		ry = getline(buf, &len_p, stdin);
#else
		ry = _getline(info, buf, &len_p);
#endif
		if (ry > 0)
		{
			if ((*buf)[ry - 1] == '\n')
			{
				(*buf)[ry - 1] = '\0'; 
				ry--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*len = ry;
				info->cmd_buf = buf;
			}
		}
	}
	return (ry);
}


size_t get_input(info_t *info)
{
	static char *buf; 
	static size_t iv, jv, len;
	size_t ry = 0;
	char **buf_pf = &(info->arg), *pf;

	_putchar(BUF_FLUSH);
	ry = input_buf(info, &buf, &len);
	if (ry == -1) 
		return (-1);
	if (len) 
	{
		jv = iv;
		pf = buf + iv;

		check_chain(info, buf, &jv, iv, len);
		while (jv < len) 
		{
			if (is_chain(info, buf, &jv))
				break;
			jv++;
		}

		iv = jv + 1; 
		if (iv >= len) 
		{
			iv = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_pf = pf; 
		return (_strlen(pf));
	}

	*buf_pf = buf; 
	return (ry); 
}


size_t read_buf(info_t *info, char *buf, size_t *p)
{
	size_t r = 0;

	if (*p)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*p = r;
	return (r);
}


int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t y;
	size_t x = 0, z = 0;
	char *pf = NULL, *new_pf = NULL, *c;

	p = *ptr;
	if (pf && length)
		z = *length;
	if (v == len)
		v = len = 0;

	x = read_buf(info, buf, &len);
	if (x == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + v, '\n');
	y = c ? 1 + (unsigned int)(c - buf) : len;
	new_pf = _realloc(p, z, z ? z + y : y + 1);
	if (!new_pf)
		return (pf ? free(p), -1 : -1);

	if (z)
		_strncat(new_pf, buf + v, y - v);
	else
		_strncpy(new_pf, buf + v, y -  + 1);

	z += y - i;
	v = y;
	pf = new_pf;

	if (length)
		*length = z;
	*ptr = p;
	return (z);
}


void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
