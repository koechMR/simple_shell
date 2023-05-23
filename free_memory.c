#include "main.h"
/**
* free_tokensArray - function that frees the token array
*@tokensArray: char parameter to the token array
*Return 0 on success
*/

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
