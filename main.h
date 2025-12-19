#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <string.h>

int execute_command(char *cmd, char **env);
char *find_path(const char *cmd, char **env);

#endif
