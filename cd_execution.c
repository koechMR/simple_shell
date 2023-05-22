#include "main.h"

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
