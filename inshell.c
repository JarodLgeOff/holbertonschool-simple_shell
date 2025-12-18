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

	while (1)
	{
		write(STDOUT_FILENO, "inshell$ ", 9);

		if (getline(&line, &len, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		int i = 0;

		while (line[i])
		{
			if (line[i] == '\n')
			{
				line[i] = '\0';
				break;
			}
			i++;
		}
	}
	free(line);
	return (0);
}
