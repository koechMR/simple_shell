#include "main.h"
/**
*print_env - function that print the env and take no argument
*Return 0 on success
*/

void print_env(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		printf("%s\n", environ[i]);
		i++;
	}
}
