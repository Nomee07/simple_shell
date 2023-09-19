#ifndef SHELL_H
#define SHELL_H

extern char **environ;

void tokenize_command(char *command, char *args[]);
void execute_child(char *args[]);
void executeCommand(char *command);
void executeCommandWithArgs(char *command);
void executeChildProcess(char *args[]);
void handleParentProcess(pid_t pid);
void tokenizeCommand(char *command, char *args[]);
void executeCommandWithPath(char *command,
		char *const args[], char *const environ[]);

#endif
