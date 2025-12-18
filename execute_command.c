#include "main.h"
/**
 * execute_command - Executes a command by forking a child process
 * @cmd: The command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char *cmd)
{
	pid_t pid;
	char *path_cmd = find_path(cmd);
	char *argv[] = {NULL, NULL};
	int status;

	if (!path_cmd)
	{
		fprintf(stderr, "%s: command not found\n", cmd);
		return (-1);
	}

	argv[0] = path_cmd;
	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		free(path_cmd);
		return (-1);
	}
	else if (pid == 0)
	{
		execve(path_cmd, argv, environ);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	free(path_cmd);
	return (0);
}
