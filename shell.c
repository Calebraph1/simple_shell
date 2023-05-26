#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void read_input(char *buffer, size_t size)
{
	printf("($) ");
	fgets(buffer, size, stdin);
}

void execute_command(const char *command)
{
	if (strcmp(command, "exit\n") == 0) {
	exit(0);
	}

	// Split the command into arguments
	char *args[10];
	char *token = strtok(command, " \t\n");
	int i = 0;
	while (token != NULL && i < 9) {
	args[i] = token;
	token = strtok(NULL, " \t\n");
	i++;
	}
	args[i] = NULL;

	// Fork a child process to execute the command
	pid_t pid = fork();
	if (pid == 0) {
	// Child process
	execvp(args[0], args);
	// Execvp only returns if there is an error
	perror("execvp");
	exit(1);
	} else if (pid < 0) {
	// Error forking a child process
	perror("fork");
	exit(1);
	} else {
	// Parent process
	wait(NULL);
    }
}

int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1) {
	read_input(buffer, BUFFER_SIZE);
	execute_command(buffer);
    }
    return 0;
}
