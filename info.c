#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
int execute_command(char *cmd, char **args);

int main() {
  char *cmd = "ls -l /tmp";
  char *args[] = {"ls", "-l", "/tmp", NULL};

  /*Execute the command*/
  execute_command(cmd, args);

  return 0;
}

int execute_command(char *cmd, char **args) {
  pid_t pid = fork();
  if (pid == 0) {
    /* Child process*/
    execve(cmd, args, environ);
    exit(1);
  } else if (pid > 0) {
    /* Parent process*/
    waitpid(pid, NULL, 0);
    return 0;
  } else {
    /* Error forking*/
    return -1;
  }
}
