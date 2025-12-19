#include "main.h"
/**
 * main - Entry point for the simple shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @env: Environment variables.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	int i = 0;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("inshell$ ");
		i = 0;

		if (getline(&line, &len, stdin) == -1)
		{
			printf("\n");
			break;
		}

		while (line[i])
		{
			if (line[i] == '\n')
			{
				line[i] = '\0';
				break;
			}
			i++;
		}

		if (line[0] != '\0')
			execute_command(line, env);
	}
	if (line)
		free(line);

	return (0);
}
