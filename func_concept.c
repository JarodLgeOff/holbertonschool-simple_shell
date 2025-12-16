#include "main.h"
/**
 * _getppid - Function that prints the parent process ID
 *
 * Return: Always 0 (Success)
 */
int _getppid(void)
{
	printf("Parent Process ID: %d\n", getppid());
	return (0);
}
/**
 * _pid_max - Function that prints the maximum process ID
 *
 * Return: Always 0 (Success)
 */
int _pid_max(void)
{
	long pid_max;

	pid_max = sysconf(_SC_PID_MAX);
	if (pid_max == -1)
	{
		perror("sysconf");
		return (-1);
	}
	printf("Maximum Process ID: %ld\n", pid_max);
	return (0);
}
/**
 * function_av - Function that prints all command-line arguments
 * @av: Array of command-line arguments
 *
 * Return: void
 */
void function_av(char **av)
{
	int i;

	for (i = 0; av[i] != NULL; i++)
	{
		printf("argv[%d]: %s\n", i, av[i]);
	}
}
/**
 * _getline - Function that reads a line of input from stdin
 * @line: Pointer to store the input line
 *
 * Return: void
 */
void _getline(char *line)
{
	size_t len = 0;
	ssize_t read;

	printf("Enter a line of input: ");
	read = getline(&line, &len, stdin);
	if (read == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	printf("You entered: %s", line);
}
/**
 * _strtok - Function that tokenizes a string based on given delimiters
 * @str: The string to be tokenized
 * @delim: The delimiters
 *
 * Return: Pointer to the next token or NULL if no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *token;
	char *end;

	if (str != NULL)
	{
		token = str;
	}

	if (token == NULL)
	{
		return (NULL);
	}

	while (*token != '\0' && strchr(delim, *token) != NULL)
	{
		token++;
	}

	if (*token == '\0')
	{
		return (NULL);
	}

	end = token;
	while (*end != '\0' && strchr(delim, *end) == NULL)
	{
		end++;
	}

	if (*end != '\0')
	{
		*end = '\0';
		end++;
	}
	else
	{
		end = NULL;
	}

	return (token);
}
