#include "main.h"
/**
 *check_stream - function that checks and opens a stream file
 *     based on the command-line arguments
 *@ac: number of command line arguments
 *@av: command line arguments
 *@stream: pointer to a FILE structure representing the stream
 *Return: returns the opened stream file or stdin if no av is provided
 */


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
/**
*check_EOF - funuction that checks for the end-of-file
*@readbytes: number of bytes read
*@buf: pointer to a character array representing the buffer
*Return 0 on succes
*/
void check_EOF(ssize_t readbytes, char *buf)
{
	if (readbytes == EOF || readbytes == -1)
	{
		free(buf);
		exit(0);
	}
}
/**
 *check_exit - fuunction to check exit
 *@buf: char buf to be passed
 *Return 0 on success
 */

void check_exit(char *buf)
{
	if (strcmp(buf, "exit\n") == 0)
	{
		free(buf);
		exit(0);
	}
}
/**
 *check_env - function to check the env
 *@buf: char buf parameter to be checked
 */

void check_env(char *buf)
{
	if (strcmp(buf, "env\n") == 0)
	{
		/*print_env();*/
	}
}
