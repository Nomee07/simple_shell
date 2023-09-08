#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "simple_shell.h"

/**
 * execute_command - Execute a shell command in a child process.
 * @command: Command to execute.
 */

void execute_command(char *command)
{
	pid_t child_pid;
	int status;
	char *token;
	char *args[32];
	int arg_count = 0;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
		args[arg_count++] = "/bin/sh";
		args[arg_count++] = "-c";

		token = strtok(command, " ");
		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}

		args[arg_count] = NULL;
		execve("/bin/sh", args, NULL);

		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(child_pid, &status, 0);
	}
}
