#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * setenv_cmd - Set or modify an environ variable
 * @variable: The name of the environ variable
 * @value: The value to set for the environ variable
 *
 * Return: 0 on success, or 1 on failure
 */
int setenv_cmd(const char *variable, const char *value)
{
	if (setenv(variable, value, 1) != 0)
	{
		fprintf(stderr, "Error: Unable to set environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * unsetenv_cmd - Unset an environ variable
 * @variable: The name of the environ variable to unset
 *
 * Return: 0 on success, or 1 on failure
 */
int unsetenv_cmd(const char *variable)
{
	if (unsetenv(variable) != 0)
	{
		fprintf(stderr, "Error: Unable to unset environment variable\n");
		return (1);
	}
	return (0);
}
