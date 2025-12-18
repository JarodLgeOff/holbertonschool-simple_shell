#include "main.h"
/**
 * find_path - Finds the full path of a command
 * @cmd: The command to find
 *
 * Return: Full path of the command, or NULL if not found
 */
char *find_path(const char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy, *dir;
	char full_path[PATH_MAX];

	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);
	dir = strtok(path_copy, ":");
	while (dir)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			char *result = strdup(full_path);

			free(path_copy);
			return (result);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}
