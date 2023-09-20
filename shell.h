#ifndef SHELL_H
#define SHELL_H

#define BUFFER_SIZE 1024

extern char **environ;

ssize_t read_input(char **buffer, size_t *size);
int execute_command(const char *command);
void interactive_mode(void);
void non_interactive_mode(int argc, char *argv[]);
void executeCommand(char *command);
void executeCommandWithArgs(char *command);
void executeChildProcess(char *args[]);
void handleParentProcess(pid_t pid);
void tokenizeCommand(char *command, char *args[]);
void executeCommandWithPath(char *command,
		char *const args[], char *const environ[]);
int is_builtin_command(const char *command);

#endif
