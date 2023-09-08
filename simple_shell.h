#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAX_INPUT_SIZE 1024


void execute_command(char *command);

#endif
