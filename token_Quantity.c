#include "main.h"
/**
*no_of_tokens - function that checks the number of tokens
*@bufcopy: pointer to char array
*@delimeter: pointer to a char constant used for tokenization
*Return: number of tokens found in the string
*/

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
