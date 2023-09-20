#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGS 20

/**
 * executeCommandWithArgs - Execute a command with arguments
 * @command: Command line string
 */

void executeCommandWithArgs(char *command)
{
	pid_t pid;
	char *args[MAX_ARGS];

	tokenizeCommand(command, args);
	pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		executeChildProcess(args);
	}
	else
	{
		handleParentProcess(pid);
	}
}


/**
 * tokenizeCommand - Tokenize the command line into args
 * @command: Command line string to tokenize
 * @args: An array to store the tokenized arguments
 */

void tokenizeCommand(char *command, char *args[])
{
	char *token = strtok(command, " ");
	int i = 0;
	int j = 0;

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	for (j = 0; j < MAX_ARGS; j++)
	{
		if (args[j] ==  NULL)
		break;
		args[j] = NULL;
	}
}


/**
 * executeChildProcess - Execute the command in the child process
 * @args: An array of arguments to pass to execve
 */

void executeChildProcess(char *args[])
{
	if (execve(args[0], args, NULL) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}

/**
 * handleParentProcess - Handles the parent process
 * @pid: Process ID of the child process
 */

void handleParentProcess(pid_t pid)
{
	int status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		int exit_status = WEXITSTATUS(status);
		char exit_msg[100];
		int len = snprintf(exit_msg, sizeof(exit_msg),
				"Child process exited with status %d\n", exit_status);

	if (len >= 0)
	{
		write(STDOUT_FILENO, exit_msg, len);
	}
	}
	else
	{
		char term_msg[100];
		int len = snprintf(term_msg, sizeof(term_msg),
				"Child process did not exit normally\n");

	if (len >= 0)
	{
		write(STDOUT_FILENO, term_msg, len);
	}
	}
}
