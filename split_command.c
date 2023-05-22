#include "main.h"

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
