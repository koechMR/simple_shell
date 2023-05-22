#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
extern char **environ;
void execute_cmd(char **tokensArray, char *actual_cmd);
char *find_cmd(char *cmd);
void print_env(void);
size_t no_of_tokens(char *bufcopy, const char *delimeter);
char **tokenization(char *buf, char **tokensArray, const char *delimeter);
void process_cmd(char **tokensArray, char *program_name);
/*int _putchar(char c);*/
void free_tokensArray(char **tokensArray);

/**
 * main - Entry point
 *
 * Return: Always 0.
 */

int main(int ac, char **av)
{
	char *buf, *bufcopy, *writebuf = "($) ",  *program_name = av[0];
	char **tokensArray = NULL;
	const char * delimeter = " \t\n";
	size_t n = 0, tokenQuantity = 0;
	ssize_t readbytes;
	FILE *stream;

	if(ac > 1)
	{
		stream = fopen(av[1], "r");
		if (stream == NULL)
		{
			perror("Failed to open stream file");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		stream = stdin;
	}

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDERR_FILENO, writebuf, 4);
		}
		/*printf("($) ");*/
		/* allocate memory for buf*/
		buf = NULL;
		readbytes = getline(&buf, &n, stdin);
		if (readbytes == EOF || readbytes == -1)
		{
			free(buf);
			exit(0);
		}

		if (strcmp(buf, "exit\n") == 0)
		{
			free(buf);
			exit(0);
		}
		if (strcmp(buf, "env\n") == 0)
		{
			print_env();
			continue;
		}
		if (strcmp(buf, "clear\n") == 0)
			printf("\033[2J\033[H");
		bufcopy = malloc(readbytes + 1);
		if (bufcopy == NULL)
		{
			perror("Memory allocation failed");
			free(buf);
			exit(1);
		}
		strcpy(bufcopy, buf);
		tokenQuantity = no_of_tokens(bufcopy, delimeter);

		tokensArray = malloc((tokenQuantity + 1) * sizeof(char *));
		if (tokensArray == NULL)
		{
			perror("Memory allocation failed");
			free(buf);
			return (-1);
		}
		tokensArray = tokenization(buf, tokensArray, delimeter);
		process_cmd(tokensArray, program_name);

		/* free memory*/
		free_tokensArray(tokensArray);
	}
	/*if (ac > 1)
	{
		close(stream);
	}*/
	return (0);
}

size_t no_of_tokens(char *bufcopy, const char *delimeter)
{
	char *token;
	int tokenQuantity = 0;

	token = strtok(bufcopy, delimeter);
	while (token != NULL)
	{
		tokenQuantity++;
		token = strtok(NULL, delimeter);
	}
	free(bufcopy);
	return (tokenQuantity);


}

char **tokenization(char *buf, char **tokensArray, const char *delimeter)
{
	int i;
	char *token;

	token = strtok(buf, delimeter);
	for (i = 0; token != NULL; i++)
	{
		tokensArray[i] = malloc(sizeof(char) * (strlen(token) + 1));
		if (tokensArray[i] == NULL)
		{
			perror("Memory allocation failed");
			free(buf);
			return (NULL);
		}
		strcpy(tokensArray[i], token);
		token = strtok(NULL, delimeter);
	}
	tokensArray[i] = NULL;
	free(buf);
	return (tokensArray);
}

void process_cmd(char **tokensArray, char *program_name)
{
	char *cmd = tokensArray[0];
	char *actual_cmd = NULL, *cd_buf;
	pid_t child_pid;
	int status, exit_status = 0, change_dir;
	struct stat statbuf;
	size_t size = 1024;

	/*check if the command is an exit*/
	if (strcmp(cmd, "exit") == 0)
	{
		if (tokensArray[1] != NULL)
		{
			/*convert the argument to an integer*/
			exit_status = atoi(tokensArray[1]);
		}
		if (exit_status < 0)
		{
			fprintf(stderr, "%s: 1: exit: Illegal number: %d\n", program_name, exit_status);
			return;
		}
		else
		{
			free_tokensArray(tokensArray);
			exit(exit_status);
		}
	}

	/*check if the command is a cd*/
	if (strcmp(cmd, "cd") == 0)
	{
		cd_buf = malloc(size);
		if (tokensArray[1] == NULL)
		{
			change_dir = chdir(getenv("HOME"));
			if (change_dir == -1)
			{
				perror("Error changing directory");
			}
			else
			{
				setenv("PWD", getcwd(cd_buf, size), 1);
			}
			free(cd_buf);
			return;
		}
		else
		{
			if (strcmp(tokensArray[1], "-") == 0)
			{
				change_dir = chdir("..");
				if (change_dir == -1)
				{
					perror("Error changing directory");
				}
				else
				{
					setenv("PWD", getcwd(cd_buf, size), 1);
				}
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

	/* check if cmd is an existing file path */
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
		/* create a child process */
		child_pid = fork();
		if (child_pid == 0)
		{
			/* Execute the command */
			execute_cmd(tokensArray, actual_cmd);
		}
		else if (child_pid < 0)
		{
			/* error forking*/
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

char *find_cmd(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat statbuf;
	int cmd_length, directory_length;

	path = getenv("PATH");

	if (path != NULL)
	{
		path_copy = strdup(path);

		if (path_copy == NULL)
		{
			return (NULL);
		}
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
			/*strcat(file_path, "\0");*/
			if (stat(file_path, &statbuf) == 0)
			{
				free(path_copy);
				return (file_path);
			}
			/* move on to the next path_token */
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

void free_tokensArray(char **tokensArray)
{
	int i = 0;

	while (tokensArray[i])
	{
		free(tokensArray[i]);
		i++;
	}
	free(tokensArray);
}

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
