#ifndef _SHELL_H
#define _SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <string.h>

#include <fcntl.h>
#include <errno.h>

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define USE_GETLINE 0
#define USE_STRTOK 0

#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define READ_BUF_SIZE 1024

#define CMD_OR		1
#define CMD_AND		2
#define CMD_NORM	0

#define CMD_CHAIN	3



extern char **environ;
/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 	allowing uniform prototype for function pointer struct
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @histcount: the history line number count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 *
 * @env_changed: on if environ was changed
	@status: the return status of the last exec'd command
 *
 * @readfd: the fd from which to read line input
 * @env: linked list local copy of environ
 *
 * @alias: the alias node
 * @argc: the argument count
 *
 * @linecount_flag: if on count this line of input
 * @arg: a string generated from getline containing arguements
 *
 *
 * @fname: the program filename
 *
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int find_builtin(info_t *);
void find_cmd(info_t *);
int hsh(info_t *, char **);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *find_path(info_t *, char *, char *);
char *dup_chars(char *, int, int);
int loophsh(char **);
int _eputchar(char);
int _putfd(char y, int yz);
int _putsfd(char *str, int yz);
void _eputs(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
int _myhistory(info_t *);
int _myalias(info_t *);
char *_strcat(char *, char *);
int _strlen(char *);
char *_strdup(const char *);
void _puts(char *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
int _putchar(char);
char *_strcpy(char *, char *);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
char **strtow(char *, char *);
char **strtow2(char *, char);
int is_delim(char, char *);
int _isalpha(int);
int interactive(info_t *);
int _atoi(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int bfree(void **);
void print_error(info_t *, char *);
int print_d(int, int);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _erratoi(char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
void clear_info(info_t *);
void set_info(info_t *, char **);
char *_getenv(info_t *, const char *);
void free_info(info_t *, int);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
int replace_string(char **, char *);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
char *get_history_file(info_t *info);
list_t *add_node(list_t **, const char *, int);
size_t list_len(const list_t *);

ssize_t get_node_index(list_t *, list_t *);
void free_list(list_t **);
int renumber_history(info_t *info);

#endif
