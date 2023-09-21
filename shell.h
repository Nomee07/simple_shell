#ifndef SHELL_H
#define SHELL_H

extern char **environ;

void tokenize_command(char *command, char *args[]);
void execute_child(char *args[]);
void execute_single_command(char *command);
void executeCommand(char *command);
void executeCommandWithArgs(char *command);
void executeChildProcess(char *args[]);
void handleParentProcess(pid_t pid);
void tokenizeCommand(char *command, char *args[]);
void executeCommandWithPath(char *command,
		char *const args[], char *const environ[]);
int is_builtin_command(const char *command);
void executeCommandWithExit(char *command);
int setenv_cmd(const char *variable, const char *value);
int unsetenv_cmd(const char *variable);


#endif
