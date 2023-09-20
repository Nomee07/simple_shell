#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024


/**
 * main - Entry point of the program
 * Return: 0 on success, or an error code on failure.
 */

int main(void)
{
	char *input = NULL;
	size_t input_size = MAX_INPUT_SIZE;
	ssize_t read_bytes;
	int is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (is_interactive)
			printf("($) ");

	read_bytes = getline(&input, &input_size, stdin);
	if (read_bytes == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}

	if (read_bytes > 1)
	{
		input[read_bytes - 1] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			int exit_status = 0;
			char* exit_arg = strtok(NULL, " \t\n");

			if (exit_arg != NULL)
			{
				exit_status = atoi(exit_arg);
			}
			free(input);
			exit(exit_status);
		}

		executeCommand(input);
	}
	if (!is_interactive)
	break;
	}
	free(input);
	return (0);
}
