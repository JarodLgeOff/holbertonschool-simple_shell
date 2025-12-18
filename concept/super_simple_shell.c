#include "main.h"

extern char **environ;

pid_t simple_shell(void)
{
	pid_t pid;
	char *argv[] = {"/bin/sh", NULL};
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve("/bin/sh", argv, environ) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}

	return (pid);
}
