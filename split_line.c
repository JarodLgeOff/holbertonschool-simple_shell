#include "main.h"
/**
 * split_line - Splits a string into an array of arguments (tokens)
 * @line: The string to split
 *
 * Return: A pointer to the array of strings, or NULL on failure
 */
char **split_line(char *line)
{
	int bufsize = 64, i = 0, k;
	char **tokens = malloc(bufsize * sizeof(char *));
	char **new_tokens;
	char *token;
	char *delim = " \t\n";

	if (!tokens)
	{
		fprintf(stderr, "hsh: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, delim);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			new_tokens = malloc(bufsize * sizeof(char *));
			if (!new_tokens)
			{
				free(tokens);
				fprintf(stderr, "hsh: allocation error\n");
				exit(EXIT_FAILURE);
			}
			for (k = 0; k < i; k++)
				new_tokens[k] = tokens[k];

			free(tokens);
			tokens = new_tokens;
		}

		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	return (tokens);
}
