#include "main.h"

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
