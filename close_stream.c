#include "main.h"
/**
* close_stream - function to close the stream
*@ac: argument count
*@stream: pointer to FILE
*Return: none
*/

void close_stream(int ac, FILE *stream)
{
	if (ac > 1)
	{
		fclose(stream);
	}
}
