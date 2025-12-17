#include "main.h"

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
		
	}
	free(line);
	return (0);
	
}