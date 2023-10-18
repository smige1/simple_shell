#include "shell.h"

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 */


/*This function checks if a file exists.
 * Returns 1 if the file exists, 0 otherwise.*/
int file_exists(char *filename)
{
      if (access(filename, F_OK) == 0)
      {
return 1;
}
else
{
return 0;
}
}

/*This function executes a command.
Returns 0 on success, -1 on failure.*/
int execute_command(char *cmd)
{
pid_t pid = fork();
if (pid == 0)
{
/* Child process*/
execve(cmd, NULL, environ);
exit(1);
}
else if (pid > 0)
{
/* Parent process*/
waitpid(pid, NULL, 0);
return 0;
}
else
{
/* Error forking*/
return -1;
}
}

int main()
{
char prompt[10] = "#cisfun$ ";
char cmd[100];

while (1)
{
printf("%s ", prompt);
fgets(cmd, sizeof(cmd), stdin);

    /* Check for end of file (Ctrl+D)*/
if (feof(stdin))
{
printf("\n");
break;
}

    /* Remove newline character from the command*/
cmd[strlen(cmd) - 1] = '\0';

    /* Check if the command is empty*/
if (strlen(cmd) == 0)
{
continue;
}

    /* Check if the command exists*/
if (!file_exists(cmd))
{
printf("Command '%s' not found\n", cmd);
continue;
}

/* Execute the command*/
if (execute_command(cmd) != 0)
{
printf("Error executing command '%s'\n", cmd);
continue;
}
}

return 0;
}
