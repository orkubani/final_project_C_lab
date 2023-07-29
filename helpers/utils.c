#include "utils.h"
#include <stdio.h>
#include <ctype.h>

void remove_white_spaces(char *source_line, char *dest_line)
{
	int i = 0;
	int j = 0;

	while (source_line[i] != '\0')
	{
		if (isspace(source_line[i]) == 0)
		{
			dest_line[j] = source_line[i];
			j++;
		}
		i++;
	}

	dest_line[j] = '\0';
}

void remove_prefix_white_spaces(char *source_line, char *dest_line)
{
    int i = 0;
    int j = 0;

    while (source_line[i] != '\0')
    {
        if (isspace(source_line[i]) == 0)
        {
            for (;source_line[i] != '\0'; i++) 
            {
                dest_line[j] = source_line[i];
                j++;
            }
        }

        i++;
    }

    dest_line[j] = '\0';
}
