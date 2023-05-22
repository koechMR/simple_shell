#include "main.h"

void close_stream(int ac, FILE *stream)
{
	if (ac > 1)
	{
		fclose(stream);
	}
}
