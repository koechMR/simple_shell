#include "main.h"

FILE *check_stream(int ac, char **av, FILE *stream)
{
	if (ac > 1)
	{
		stream = fopen(av[1], "r");
		if (stream == NULL)
		{
			perror("Failed to open stream file");
			exit(EXIT_FAILURE);
		}
		return (stream);
	}
	else
	{
		stream = stdin;
		return (stream);
	}
}

void check_EOF(ssize_t readbytes, char *buf)
{
	if (readbytes == EOF || readbytes == -1)
	{
		free(buf);
		exit(0);
	}
}

void check_exit(char *buf)
{
	if (strcmp(buf, "exit\n") == 0)
	{
		free(buf);
		exit(0);
	}
}

void check_env(char *buf)
{
	if (strcmp(buf, "env\n") == 0)
	{
		print_env();
	}
}
