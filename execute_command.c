#include "main.h"
/**
* execute_command - Executes a command by forking a child process
* @argv: Array of arguments (argv[0] is the command)
* @env: Environment variables array
* Return: 0 on success, -1 on failure
*/

int execute_command(char **argv, char **env)
{
	pid_t pid;
	char *path_cmd;

	int status;

	if (!argv || !argv[0])
		return (0);

	path_cmd = find_path(argv[0], env);
	if (!path_cmd)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", "./hsh", 1, argv[0]);
		return (127);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path_cmd);
		return (1);
	}

	if (pid == 0)
	{
		execve(path_cmd, argv, env);
		perror("execve");
		exit(126);
	} else
	{
		waitpid(pid, &status, 0);
	}

	free(path_cmd);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
