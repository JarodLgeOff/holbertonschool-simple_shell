#include "main.h"
/**
 * get_path_env - Retrieves the value of the PATH environment variable
 * @env: The environment variables
 * Return: Pointer to the PATH value, or NULL if not found
 */
char *get_path_env(char **env)
{
	int i;

	for (i = 0; env[i]; i++)
	{
		if (strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}
	return (NULL);
}
/**
 * find_path - Finds the full path of a command
 * @cmd: The command to find
 * @env: The environment variables
 * Return: Full path of the command, or NULL if not found
 */
char *find_path(const char *cmd, char **env)
{
	char *path, *path_copy, *dir, *full_path;

	if (strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (strdup(cmd));
		return (NULL);
	}

	path = get_path_env(env);
	if (!path || *path == '\0')
		return (NULL);

	path_copy = strdup(path);

	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");

	while (dir)
	{
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);
		if (full_path)
		{
			sprintf(full_path, "%s: %d: %s not found\n", dir, cmd);
			if (access(full_path, X_OK) == 0)
			{
				free(path_copy);
				return (full_path);
			}
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
