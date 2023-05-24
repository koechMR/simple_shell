#include "main.h"

void trim_spaces(char *str) {
	size_t len, start = 0, i;
	ssize_t end;

	len = strlen(str);
	end = len - 1;
	
	/*find index ot the first non-space character from the start*/
	while ((start < len) && (str[start] == ' '))
	{
		start++;
	}

	/*Find the index of the first non-space character from the end*/
	while ((end >= 0) && (str[end] == ' '))
	{
		end--;
	}

	for (i = 0; i <= end - start; i++)
	{
		str[i] = str[start + i];
	}
	/* Null_terminating the trimmed string*/
	str[i] = '\0';
}
