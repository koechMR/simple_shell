#include "main.h"

void process_cmd(char **tokensArray, char *program_name)
{
	char *cmd = tokensArray[0];
	char *actual_cmd = NULL;
	pid_t child_pid;
	int status, exit_status = 0;
	struct stat statbuf;

	exit_check(cmd, tokensArray, exit_status);
	check_cd(cmd, tokensArray);
	if (stat(cmd, &statbuf) == 0)
	{
		actual_cmd = strdup(cmd);
	}
	else
	{
		actual_cmd = find_cmd(cmd);
	}
	if (actual_cmd == NULL)
	{
		printf("%s: 1: %s: not found\n", program_name, cmd);
	}
	else
	{
		child_pid = fork();
		if (child_pid == 0)
		{
			execute_cmd(tokensArray, actual_cmd);
		}
		else if (child_pid < 0)
		{
			perror(cmd);
			free(actual_cmd);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}
	free(actual_cmd);
}


void exit_check(char *cmd, char **tokensArray, int exit_status)
{
	if (strcmp(cmd, "exit") == 0)
	{
		if (tokensArray[1] != NULL)
		{
			/*convert the argument to an integer*/
			exit_status = atoi(tokensArray[1]);
		}
		if (exit_status < 0)
		{
			perror("Illegal status");
			return;
		}
		else
		{
			free_tokensArray(tokensArray);
			exit(exit_status);
		}
	}
}


void check_cd(char *cmd, char **tokensArray)
{
	char *cd_buf;
	int change_dir;
	size_t size = 1024;

	if (strcmp(cmd, "cd") == 0)
	{
		cd_buf = malloc(size);
		if (tokensArray[1] == NULL)
		{
			change_dir = chdir(getenv("HOME"));
			cd_alone(change_dir, size, cd_buf);
			free(cd_buf);
			return;
		}
		else
		{
			if (strcmp(tokensArray[1], "-") == 0)
			{
				change_dir = chdir("..");

				cd_with_arguments(change_dir, size, cd_buf);
			}
			else
			{
				change_dir = chdir(tokensArray[1]);

				if (change_dir == -1)
				{
					perror("Error changing directory");
				}
				else
				{
					setenv("PWD", getcwd(cd_buf, size), 1);
				}
			}
			free(cd_buf);
			return;
		}
	}
}

char *find_cmd(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat statbuf;
	int cmd_length, directory_length;

	path = getenv("PATH");
	if (path != NULL)
	{
		path_copy = strdup(path);
		check_path_copy(path_copy);
		cmd_length = strlen(cmd);
		path_token = strtok(path_copy, ":");
		while (path_token != NULL)
		{
			directory_length = strlen(path_token);
			file_path = malloc(cmd_length + directory_length + 2);

			if (file_path == NULL)
			{
				free(path_copy);
				return (NULL);
			}
			strcpy(file_path, path_token);
			strcat(file_path, "/");
			strcat(file_path, cmd);
			if (stat(file_path, &statbuf) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}
		/* if we don't get any file_path that exists for the token*/
		free(path_copy);
		return (NULL);
	}
	return (NULL);
}

void execute_cmd(char **tokensArray, char *actual_cmd)
{
	if (actual_cmd != NULL)
	{
		if (execve(actual_cmd, tokensArray, environ) == -1)
		{
			perror(tokensArray[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		perror(tokensArray[0]);
		exit(EXIT_FAILURE);
	}
}
