#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * executeCommandWithPath - Execute command with a given path
 * @command: Command to execute
 * @args: Array of argumentsfor the command
 * @environ: The environment variables to use
 */

void executeCommandWithPath(char *command,
		char *const args[], char *const environ[])
{
	char *path = getenv("PATH");
	char *path_cpy = strdup(path);
	char *dir = strtok(path_cpy, ":");

	if (path == NULL)
	{
		perror("getenv");
		return;
	}

	if (path_cpy == NULL)
	{
		perror("strdup");
		return;
	}

	while (dir != NULL)
	{
		char full_path[1024];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);

		if (access(full_path, X_OK) == 0)
		{
			execve(full_path, args, environ);
			perror("execve");
		}
		dir = strtok(NULL, ":");
	}
	free(path_cpy);
}
