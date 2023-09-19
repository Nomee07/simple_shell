#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include "shell.h"

#define MAX_ARGS 64
#define MAX_INPUT_SIZE 1024

/**
 * tokenize_command - Tokenize a command string into args
 * @command: The command string to be tokenized
 * @args: Array to store
 */

void tokenize_command(char *command, char *args[])
{
	char *token;
	int i = 0;

	token = strtok(command, " ");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
}

/**
 * execute_child - Execute the child process
 * @args: Array of arguments for the command
 */

void execute_child(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}


/**
 * executeCommand - Execute a command
 * @command: Command to be executed
 */

void executeCommand(char *command)
{
	pid_t pid;
	char *args[MAX_ARGS];

	tokenize_command(command, args);

	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execute_child(args);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			int exit_status = WEXITSTATUS(status);

			if (exit_status != 0)
			{
				fprintf(stderr, "hsh: %s: Exit status %d\n", args[0], exit_status);
			}
			else if (WIFSIGNALED(status))
			{
				int term_signal = WTERMSIG(status);

				fprintf(stderr, "Child process terminated by signal %d\n", term_signal);
			}
		}
	}
}
