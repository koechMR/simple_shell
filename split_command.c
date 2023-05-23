#include "main.h"
/**
* tokenization - This function performs tokenization of a string using
*  a specified delimiter.
* @buf: Pointer to a character array representing the input
* string to be tokenized.
* @tokensArray: Double pointer to a char array representing the
*  array to store the tokens.
* @delimeter: Pointer to a constant char array representing the
* delimiter used for tokenization.
* Return: Returns the tokensArray after tokenization or
*        NULL if memory allocation fails.
*/


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
