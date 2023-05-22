#include "main.h"

void check_bufcopy(char *bufcopy, char *buf)
{
	if (bufcopy == NULL)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}
}


void check_tokensArray(char **tokensArray, char *buf)
{
	if (tokensArray == NULL)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}
}

char *check_path_copy(char *path_copy)
{
	if (path_copy == NULL)
	{
		return (NULL);
	}
	return (path_copy);

}
