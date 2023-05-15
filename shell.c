#include "main.h"

/**
 * main - Entry point
 *
 * Return: Always 0.
 */

int main(void)
{
	char *buf, *bufcopy, *writebuf = "($) ";
	char **tokensArray = NULL;
	const char * delimeter = " \n";
	size_t n = 0;
	ssize_t readbytes;
	int tokenQuantity = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDERR_FILENO, writebuf, 4);
		}
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
			print_env();
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
		process_cmd(tokensArray);

		/* free memory*/
		free_tokensArray(tokensArray);
	}
	return (0);
}


void execute_cmd(char **tokensArray, char *actual_cmd)
{
	if (actual_cmd != NULL)
	{
		if (execve(actual_cmd, tokensArray, environ) == -1)
		{
			perror(tokensArray[0]);
			/*exit(1);*/
		}
		}
		else
		{
			perror(tokensArray[0]);
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
		/** Check if the token is a file and return its duplicate
		  * for execution
		  */
		/*if (stat(cmd, &statbuf) == 0)
		{
			return (strdup(cmd));
		}*/
		if (access(cmd, X_OK) == 0)
		{
			return (strdup(cmd));
		}
		return (NULL);
	}
	return (NULL);
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


int no_of_tokens(char *bufcopy, const char *delimeter)
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

void process_cmd(char **tokensArray)
{
	char *cmd = tokensArray[0];
	char *actual_cmd;
	pid_t child_pid;
	int status;

	actual_cmd = find_cmd(cmd);

	if (actual_cmd == NULL)
	{
		perror(cmd);
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
		}
		else
		{
			wait(&status);
			free(actual_cmd);
		}
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
