#include "main.h"
/**
* main - entry point of the program
*@ac: argurment count
*@av: pointer argurment vector
*Return: 0 on success
*/

int main(int ac, char **av)
{
	char *buf, *bufcopy, *writebuf = "($) ",  *program_name = av[0];
	char **tokensArray = NULL;
	const char *delimeter = " \t\n";
	size_t n = 0, tokenQuantity = 0;
	ssize_t readbytes;
	FILE *stream = NULL;

	stream = check_stream(ac, av, stream);
	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
		{
			write(STDERR_FILENO, writebuf, 4);
		}
		/* allocate memory for buf*/
		buf = NULL;
		readbytes = getline(&buf, &n, stream);
		if (strcmp(buf, " \n") == 0)
		{
			free(buf);
			continue;
		}
		check_EOF(readbytes, buf);
		check_exit(buf);
		/*check_env(buf);*/
		bufcopy = malloc(readbytes + 1);
		check_bufcopy(bufcopy, buf);
		strcpy(bufcopy, buf);
		tokenQuantity = no_of_tokens(bufcopy, delimeter);
		tokensArray = malloc((tokenQuantity + 1) * sizeof(char *));
		check_tokensArray(tokensArray, buf);
		tokensArray = tokenization(buf, tokensArray, delimeter);
		process_cmd(tokensArray, program_name);
		free_tokensArray(tokensArray);
	}
	close_stream(ac, stream);
	return (0);
}
