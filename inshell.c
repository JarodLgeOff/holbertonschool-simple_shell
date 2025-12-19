#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0 (Success).
 */

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	int i = 0;

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
			execute_command(line);

	}
	if (line)
		free(line);

	return (0);
}
