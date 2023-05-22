#include "main.h"

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
