#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * interactive_mode - Run the shell in interactive mode
 */

void interactive_mode(void)
{
	char *input = NULL;
	size_t input_size = BUFFER_SIZE;
	ssize_t read_chars;
	int status;
	char exit_status_str[8];
	int len = snprintf(exit_status_str,
			sizeof(exit_status_str), "%d\n", WEXITSTATUS(status));

	while (1)
	{
		input = (char *)malloc(input_size);
	if (!input)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, "$ ", 2);
	read_chars = read_input(&input, &input_size);

	if (input[read_chars - 1] == '\n')
	input[read_chars - 1] = '\0';

	if (strcmp(input, "exit") == 0)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}

	status = execute_command(input);
	write(STDOUT_FILENO, exit_status_str, len);

	free(input);
	}

}

/**
 * non_interactive_mode - Run the shell in non-interactive mode
 * @argc: The number of command line args
 * @argv: An array of strings
 */

void non_interactive_mode(int argc, char *argv[])
{
	int status;
	int i;
	char exit_status_str[8];
	int len = snprintf(exit_status_str,
			sizeof(exit_status_str), "%d\n", WEXITSTATUS(status));

	for (i = 1; i < argc; i++)
	{
		status = execute_command(argv[i]);
		write(STDOUT_FILENO, exit_status_str, len);
	}
}

/**
 * main - Entry point of the shell
 * @argc: The number of command line args
 * @argv: An array of strings
 *
 * Return: Exit status
 */

int main(int argc, char *argv[])
{
	int i;

	if (argc > 1)
	{
	for (i = 1; i < argc; i++)
	{
		FILE *file = fopen(argv[i], "r");

		if (file == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		non_interactive_mode(argc, argv);
		fclose(file);
	}
	}
	else
	{
		interactive_mode();
	}
	return(0);
}
