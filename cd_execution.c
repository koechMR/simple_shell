#include "main.h"
/**
*cd_alone - function that change directory
*@change_dir: parameter to check
*@size: size of the cd_buf
*@cd_buf: pointer to char array
*Return: none
*/

void cd_alone(int change_dir, size_t size, char *cd_buf)
{
	/*change_dir = chdir(getenv("HOME"));*/
	if (change_dir == -1)
	{
		perror("Error changing directory");
	}
	else
	{
		setenv("PWD", getcwd(cd_buf, size), 1);
	}
}
/**
*cd_with_arguments - function that changes the current working dir to parent
*@change_dir: int value to check
*@size: size of the cd_buf buffer
*@cd_buf: pointer to char array
*Return: none
*/

void cd_with_arguments(int change_dir, size_t size, char *cd_buf)
{
	/*change_dir = chdir("..");*/
	if (change_dir == -1)
	{
		perror("Error changing directory");
	}
	else
	{
		setenv("PWD", getcwd(cd_buf, size), 1);
	}
}
