#include "shell.h"

int main()
{
  char *command;
  char **args;
  int status;

  /* Display the prompt */
  write(STDOUT_FILENO, "#cisfun$ ", 8);

  /* Read the command line */
  read(STDIN_FILENO, command, 1024);

  /* Tokenize the command line into arguments */
  args = strtok(command, " ");

  /* Check if the command is built-in */
  if (strcmp(args[0], "exit") == 0)
  {
    exit(0);
  }

  /* Check if the command exists */
  if (access(args[0], X_OK) == -1)
  {
    write(STDOUT_FILENO, ".\/shell: No such file or directory\n", 32);
    goto prompt;
  }

  /* Execute the command */
  status = execve(args[0], args, environ);

  /* Handle errors*/
  if (status == -1)
  {
    perror("execve");
  }

prompt:
  /*Display the prompt again*/
  write(STDOUT_FILENO, "#cisfun$ ", 8);

  return (0);
}

