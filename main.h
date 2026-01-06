#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <linux/limits.h>
#include <string.h>

int execute_command(char **argv, char **env);

char *get_path_env(char **env);

char *find_path(const char *cmd, char **env);

char **split_line(char *line);

#endif
