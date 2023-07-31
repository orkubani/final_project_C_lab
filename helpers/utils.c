#include "utils.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**
 * Removes all white spaces from the source_line and saves the result in dest_line.
 */
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

/**
 * Removes the prefix white spaces from the source_line and saves the result in dest_line.
 */
void remove_prefix_white_spaces(char *source_line, char *dest_line)
{
    int i = 0;
    int j = 0;
    int found_first_char = 0;

    while (source_line[i] != '\0')
    {
        if (!found_first_char && isspace(source_line[i]))
        {
            i++;
            continue;
        }

        found_first_char = 1;
        dest_line[j] = source_line[i];
        i++;
        j++;
    }

    dest_line[j - 2] = '\0';
}

/**
 * Removes the macro indentation from the sourceline and saves the result in dest_line.
 * The macro indentation is assumed to start at index 4 of sourceline.
 * I assume, macro content is written in indentation of 4 chars.
 */
void remove_macro_indentation(char *sourceline, char *dest_line)
{
    strncpy(dest_line, sourceline + FOUR_CHARS_INDENTATION, MAX_LINE_LENGTH - FOUR_CHARS_INDENTATION);
}
