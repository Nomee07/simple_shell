#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

/**
 * executeCommandWithExit - Execute command for exit status
 * @command: Command to be executed
 */

void executeCommandWithExit(char *command)
{
	int status;
	char *args[MAX_INPUT_SIZE];
	char *token = strtok(command, " \t\n");
	int i = 1;

	pid_t child_pid = fork();

	if (token == NULL)
	{
		return;
	}
	strcpy(args[0], token);

	while ((token = strtok(NULL, " \t\n")) != NULL)
	{
		args[i++] = token;
	}
	args[i] = NULL;

	if (child_pid == 0)
	{	execvp(args[0], args);
		perror("Command execution failed");
		exit(EXIT_FAILURE);
	}
	else if (child_pid > 0)
	{
		waitpid(child_pid, &status, 0);
	}
	else
	{
		perror("Fork failed");
	}
}
