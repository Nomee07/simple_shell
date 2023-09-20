#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * read_input - Function to read a line of input from the user.
 * @buffer: Pointer to the buffer where the input will be stored.
 * @size: Size of the buffer.
 * Return: Number of characters read.
 */

ssize_t read_input(char **buffer, size_t *size)
{
	ssize_t read_chars = getline(buffer, size, stdin);

	if (read_chars == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (read_chars);
}

/**
 * execute_command - Function to execute a command.
 * @command: The command to execute.
 * Return: Exit status of the executed command.
 */

int execute_command(const char *command)
{
	pid_t child_pid;
	int status;
	char *cmd_argv[3];
	char *cmd_envp[] = {NULL};
	
	cmd_argv[0] = (char *)command;
	cmd_argv[1] = NULL;
	cmd_argv[2] = NULL;

	child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (child_pid == 0)
	{
	if (execve(command, cmd_argv, cmd_envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	}
	else
	{
	if (waitpid(child_pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
	}
	return (status);
}
