#include "main.h"
/**
* check_bufcopy - function that checks for buffer copy
*@bufcopy: first parameter to be checked
*@buf: this is the pointer to buf
*Return 0 on success
*/

void check_bufcopy(char *bufcopy, char *buf)
{
	if (bufcopy == NULL)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}
}
/**
* check_tokensArray - this function checks memory allocation for the tokenarray
* was successful
*@tokensArray: first parameter of double pointer to tokenarray
*@buf:  pointer to a character array buf
*Return 0 on success
*/


void check_tokensArray(char **tokensArray, char *buf)
{
	if (tokensArray == NULL)
	{
		perror("Memory allocation failed");
		free(buf);
		exit(1);
	}
}
/**
*check_path_copy - this function checks the path to copy
*@path_copy: pointer to a character array path copy
*Return: return NULL if the path_copy is NULL,
* otherwise return the path_copy pointer
*/

char *check_path_copy(char *path_copy)
{
	if (path_copy == NULL)
	{
		return (NULL);
	}
	return (path_copy);

}
