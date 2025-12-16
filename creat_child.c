#include "main.h"

extern char **environ;
/**
 * create_child_process - Function that creates a child process
 *
 * Return: PID of the child process to the parent, 0 to the child, -1 on failure
 */
pid_t create_child_process(void)
{
	pid_t pid;
	int status;
	int i;

	for (i = 0; i < 5; i++)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			char *argv[] = {"ls", "-l", "/tmp", NULL};

			if (execve("/bin/ls", argv, environ) == -1)
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
	}

	return (pid);
}
