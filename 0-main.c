#include "simple_shell.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT_SIZE 1024

void execute_command(char *command);

/**
 * main - Entry point for the shell program.
 *
 * Return: Always 0 (success)
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
			break;

			execute_command(input);
		}
		if (!is_interactive)
		break;
	}
	free(input);
	return (0);
}
